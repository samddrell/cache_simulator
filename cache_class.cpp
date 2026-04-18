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

    void set_tag(int _tag) { tag = _tag; }
    void set_valid(bool _valid) { valid = _valid; }

    void set_ref(int _ref) { ref = _ref; }
    int get_ref() { return ref; }

  private:  
    bool valid;

    // Do we need this for this assignment?
    unsigned tag;

    int ref;

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

        clock = 0;
    }

    ~Cache(){}

    bool check_address(unsigned long addr) {
      // Calculate index based on the address and number of sets
      int index = addr % num_sets;

      // Calculate tag based on the address and number of sets
      int tag = addr / num_sets;

      // Check for hit in the cache
      for (int way = 0; way < assoc; ++way) {
        if (entries[index][way].get_valid() && entries[index][way].get_tag() == tag) {
          entries[index][way].set_ref(clock++);
          return true;  // Hit
        }
      }
      
      // If miss, find an empty slot
      for (int way = 0; way < assoc; ++way) {
        if (!entries[index][way].get_valid()) {
          entries[index][way].set_valid(true);
          entries[index][way].set_tag(tag);
          entries[index][way].set_ref(clock++);
          
          return false; // Miss
        }
      }

      // LRU replacement: find the way with the smallest reference time

      int lru_way = 0;
      int min_ref = entries[index][0].get_ref();

      for (int way = 1; way < assoc; ++way) {
        if (entries[index][way].get_ref() < min_ref) {
          min_ref = entries[index][way].get_ref();
          lru_way = way;
        }
      }

      entries[index][lru_way].set_valid(true);
      entries[index][lru_way].set_tag(tag);
      entries[index][lru_way].set_ref(clock++);

      return false; // Cache miss
    }
    
  private:
    int assoc;
    unsigned num_entries;
    int num_sets;
    vector<vector<Entry>> entries;
    int clock; // for LRU replacement policy

    // // Do we need this?
    // void display(ofstream& outfile);

    // // Do we need this?
    // int get_index(unsigned long addr);

    // int get_tag(unsigned long addr);

    // unsigned long retrieve_addr(int way, int index);
    
    // bool hit(ofstream& outfile, unsigned long addr);

    // void update(ofstream& outfile, unsigned long addt);

};


