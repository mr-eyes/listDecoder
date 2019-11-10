#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <seqan/seq_io.h>
#include <parallel_hashmap/phmap.h>
#include <stdint.h>
#include "HashUtils/hashutil.hpp"

using phmap::flat_hash_map;

struct item_row {
        std::string str;
        uint64_t hash;
    };

/* 
--------------------------------------------------------
                        InputModule:Parent
--------------------------------------------------------
*/

class listDecoder {


protected:

    unsigned int chunk_size;
    seqan::StringSet<seqan::CharString> ids;
    seqan::StringSet<seqan::CharString> seqs;
    flat_hash_map<std::string, std::vector<item_row>> kmers;
    std::string fileName;
    seqan::SeqFileIn seqFileIn;

    void initialize_seqan();

    bool seqan_end = true;


public:

    flat_hash_map<std::string, std::vector<item_row>> *getKmers();

    Hasher * hasher;

    int hash_mode = 0;
    bool canonical = true;
    std::string slicing_mode = "";

    virtual int get_kSize() = 0;

    bool end();

    

    std::string get_filename();

};


/* 
--------------------------------------------------------
                        Items
--------------------------------------------------------
*/


class Items : public listDecoder {

private:
    
    void extractItems();

    std::hash<std::string> child_hasher;
    flat_hash_map<uint64_t, std::string> hash_to_str;
    flat_hash_map<std::string, std::vector<std::string>> parent_to_children;

    std::string filename;
    bool END = true;

public:
    int kSize = 32;

    void next_chunk();

    Items(const std::string &filename) {
        this->filename = filename;
        this->extractItems();
    }


    int get_kSize() {
        return this->kSize;
    }


    // hash single item
    uint64_t hash_kmer(const std::string &item_str) {
        return this->child_hasher(item_str);
    }

    // Inverse hash single item
    std::string ihash_kmer(const uint64_t &item_hash) {
        return this->hash_to_str[item_hash];
    }

};