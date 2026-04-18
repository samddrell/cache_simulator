#include<iostream>
#include<cstdlib>   // for atoi
#include<fstream>  // need this for file I/O
#include<vector>

using namespace std;

const int MAX_SIZE = 1000;

vector<unsigned long> fileio(string filename) {
    /* create input and output filenames */
    //   string input_filename = filename + "_input";
    string input_filename = filename;
    string output_filename = "cache_sim_outpu";

    /* create input and output files streams */
    ofstream output;
    ifstream input;


    /* open input stream for reading */
    input.open(input_filename);

    /* check if input stream has been succesfully opened; bail otherwise */
    if (!input.is_open()) {
        cerr << "Could not open input file " << input_filename << ". Exiting ..." << endl;
        exit(0);
    }
        
    vector<unsigned long> nums;
    unsigned long val;
    int count = 0;
    while (input >> val && count < MAX_SIZE) {
        nums.push_back(val);
        count++;
    }

    /* done reading from input file; close the stream */
    input.close();
    
    /* open output file stream for writing */
    output.open(output_filename);

    /* no need to check if output file is open; we will create new file if it doesn't exist; 
        overwrite otherwise */
    for (int i = 0; i < count; i++)
        output << "ADDR : " << nums[i] << endl; 

    /* close output stream */
    output.close();
    return nums;
}

int main(int argc, char*argv[]) {

    /* check if the correct number of arguments have been passed; bail otherwise */
    if (argc < 4) {
        cout << "Usage: " << endl;
        cout << "   ./cache num_entries associativity filename" << endl;
        return 0;
    }

    /* get args; all args come in as strings; need to convert to int with atoi() */
    unsigned entries = atoi(argv[1]);
    unsigned assoc = atoi(argv[2]);

    string input_filename = argv[3];

    /* print the args */
    cout << "Number of entries: " << entries << endl;
    cout << "Associativity: " << assoc << endl;
    cout << "Input File Name: " << input_filename << endl;

    vector<unsigned long> nums = fileio(input_filename);

    Cache cache(assoc, entries);

    for (unsigned long addr : nums) {
        if (cache.check_address(addr)) {
            cout << "Cache hit for address: " << addr << endl;
        } else {
            cout << "Cache miss for address: " << addr << endl;
        }
    }
    
    return 0;
}


