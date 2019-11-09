#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <parallel_hashmap/phmap.h>
#include <cstdint>

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

namespace listDecoder {


    class kmerDecoder {

    protected:
        flat_hash_map<uint64_t, std::string> hash_to_str;
        flat_hash_map<std::string, std::vector<std::string>> parent_to_children;
        std::hash<std::string> child_hasher;
        flat_hash_map<std::string, std::vector<item_row>> items;
        bool END = false;

    public:
        flat_hash_map<std::string, std::vector<item_row>> *getKmers();

        bool end();

        void next_chunk();


        // hash single kmer
        uint64_t hash_kmer(const std::string &item_str) {
            return this->child_hasher(item_str);
        }

        // Inverse hash single kmer
        std::string ihash_kmer(const uint64_t &item_hash) {
            return this->hash_to_str[item_hash];
        }

    };


/* 
--------------------------------------------------------
                        Default Kmers
--------------------------------------------------------
*/

    class Items : public kmerDecoder {

    private:
        std::string filename;

        void extractItems();

    public:
        explicit Items(const std::string &filename);

    };


}