#include "kmerDecoder.hpp"
#include <iostream>

using std::endl;
using std::cout;

void dump(kmerDecoder * KD);

int main(int argc, char **argv) {

    if(argc < 2){
        std::cerr << "Please pass TSV file path" << std::endl;
        exit(1);
    }

    int chunk_size = 1;

    kmerDecoder *KD = new Items(argv[1], chunk_size);

    dump(KD);

    return 0;
}

void dump(kmerDecoder * KD){
    while (!KD->end()) {
        KD->next_chunk();

        for (const auto &seq : *KD->getKmers()) {
            // std::cout << "Read ID: " << seq.first << std::endl;
            for (const auto &kmer : seq.second) {
                std::cout << seq.first << '\t' << kmer.str << '\t' << kmer.hash << std::endl;
            }
        }
    }
}