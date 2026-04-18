#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
class Entry {
  public:
    Entry() {
      valid = false;
    }

    Entry(int in_ref) {
      set_ref(in_ref);
      valid = true;
    }

    ~Entry(){}
    void display(ofstream& outfile);
    bool get_valid() { return valid; }
    int get_tag() { return tag; }

  private:  
    bool valid;

    // Do we need this for this assignment?
    unsigned tag;

    int ref;

    void set_tag(int _tag) { tag = _tag; }
    

    void set_valid(bool _valid) { valid = _valid; }

    void set_ref(int _ref) { ref = _ref; }
    int get_ref() { return ref; }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Cache {
  public:
    Cache(int assoc_in, int num_entries_in) {
        assoc = assoc_in;
        num_entries = num_entries_in;
        num_sets = num_entries / assoc;

        entries.resize(num_sets);
        for (int i = 0; i < num_sets; i++) {
            entries[i].resize(assoc);
        }
    }

    ~Cache(){}

    bool check_address(unsigned long addr) {
      // Calculate index based on the address and number of sets
      int index = addr % num_sets;

      // Calculate tag based on the address and number of sets
      int tag = addr / num_sets;

      for (int way = 0; way < assoc; ++way) {
        if (entries[index][way].get_valid() && entries[index][way].get_tag() == tag) {
            return true;  // Hit
        }
        else {
          // Add entry

          // Find Empty way
          
          // Else overwrite 
        }
      }
      return false; // Cache miss
    }
    
  private:
    int assoc;
    unsigned num_entries;
    int num_sets;
    vector<vector<Entry>> entries;

    // // Do we need this?
    // void display(ofstream& outfile);

    // // Do we need this?
    // int get_index(unsigned long addr);

    // int get_tag(unsigned long addr);

    // unsigned long retrieve_addr(int way, int index);
    
    // bool hit(ofstream& outfile, unsigned long addr);

    // void update(ofstream& outfile, unsigned long addt);

};


