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
    flat_hash_map<std::string, std::vector<item_row>> kmers; //use
    std::string fileName;
    seqan::SeqFileIn seqFileIn;

    void initialize_seqan();

    bool seqan_end = true;

    virtual void extractItems() = 0;

    

    


    // Mode 0: Murmar Hashing | Irreversible
    // Mode 1: Integer Hashing | Reversible | Full Hashing
    // Mode 2: TwoBitsHashing | Not considered hashing, just store the two bits representation


public:

    flat_hash_map<std::string, std::vector<item_row>> *getKmers();

    Hasher * hasher;

    int hash_mode = 0;
    bool canonical = true;
    std::string slicing_mode = "";

    virtual int get_kSize() = 0;

    bool end();

    

    std::string get_filename();

    virtual void setHashingMode(int hash_mode, bool canonical = true) = 0;

    // hash single kmer
    uint64_t hash_kmer(std::string kmer_str) {
        return this->hasher->hash(kmer_str);
    }


    // Inverse hash single kmer
    std::string ihash_kmer(uint64_t kmer_hash) {
        return this->hasher->Ihash(kmer_hash);
    }

    static listDecoder *initialize_hasher(int kmer_size, int hash_mode = 1);


    static Hasher *create_hasher(int kmer_size, int hash_mode = 1) {

        switch (hash_mode) {
            case 0:
                return (new MumurHasher(2038074761));
            case 1:
                return (new IntegerHasher(kmer_size));
            case 2:
                return (new TwoBitsHasher(kmer_size));
            default:
                std::cerr << "Hashing mode : " << hash_mode << ", is not supported \n";
                std::cerr << "Mode 0: Murmar Hashing | Irreversible\n"
                             "Mode 1: Integer Hashing | Reversible\n"
                             "Mode 2: TwoBitsHashing | Not considered hashing, just store the two bits representation\n"
                          <<
                          "Default: Integer Hashing" << std::endl;
                exit(1);
        }

    }

};


/* 
--------------------------------------------------------
                        Default Kmers
--------------------------------------------------------
*/


class Items : public listDecoder {

private:
    
    void extractItems();
        // New

    std::hash<std::string> child_hasher;
    flat_hash_map<uint64_t, std::string> hash_to_str;
    flat_hash_map<std::string, std::vector<std::string>> parent_to_children;
//    std::string filename = "/home/mabuelanin/Desktop/dev-plan/decoder_casting/listDecoder/bin/sample.tsv";
    std::string filename;
    bool END = true;

public:
    int kSize{};

    void next_chunk();

    Items(const std::string &filename) {
        this->filename = filename;
        this->extractItems();
    }

    explicit Items(int k_size, int hash_mode = 1) : kSize(k_size) {
        this->hasher = new IntegerHasher(kSize);
        this->slicing_mode = "kmers";
        this->hash_mode = 1;
        this->canonical = true;
        if (hash_mode != 1) {
            this->setHashingMode(hash_mode);
        }
    };

    Items(const std::string &filename, unsigned int chunk_size, int kSize) {
        this->kSize = kSize;
        this->fileName = filename;
        this->chunk_size = chunk_size;
        this->initialize_seqan();
        this->hasher = new IntegerHasher(kSize);
        this->hash_mode = 1;
        this->canonical = true;
        this->slicing_mode = "kmers";
    }

    void setHashingMode(int hash_mode, bool canonical = true) {

        this->hash_mode = hash_mode;
        this->canonical = canonical;

        if (hash_mode == 0) hasher = (new MumurHasher(2038074761));
        else if (hash_mode == 1) {
            if (canonical) hasher = (new IntegerHasher(kSize));
            else hasher = (new noncanonical_IntegerHasher(kSize));
        } else if (hash_mode == 2) {
            if (canonical) {
                hasher = (new TwoBitsHasher(kSize));
            } else {
                hasher = (new noncanonical_TwoBitsHasher(kSize));
            }
        } else {
            hasher = (new IntegerHasher(kSize));
        }

    }


    int get_kSize() {
        return this->kSize;
    }
};