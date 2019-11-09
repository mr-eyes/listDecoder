#include "kmerDecoder.hpp"
#include "listDecoder.hpp"
#include <iostream>

void dump(kmerDecoder * LD);

int main(int argc, char **argv) {

    if(argc < 2){
        std::cerr << "Please pass TSV file path" << std::endl;
        exit(1);
    }

    listDecoder::kmerDecoder *LD = new listDecoder::Items(argv[1]);
    kmerDecoder * KD = (kmerDecoder *) LD;

    dump(LD);

    return 0;
}

void dump(kmerDecoder * LD){
    while (!LD->end()) {
        LD->next_chunk();

        for (const auto &seq : *LD->getKmers()) {
            std::cout << "Read ID: " << seq.first << std::endl;
            for (const auto &kmer : seq.second) {
                std::cout << kmer.str << ": " << kmer.hash << std::endl;
            }
        }
    }
}