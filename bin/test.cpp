#include "listDecoder.hpp"
#include <iostream>
//#include "kmerDecoder.hpp"


using std::endl;
using std::cout;

void dump(listDecoder * LD);

int main(int argc, char **argv) {

    if(argc < 2){
        std::cerr << "Please pass TSV file path" << std::endl;
        exit(1);
    }

    listDecoder *LD = new Items(argv[1]);

    dump(LD);

    return 0;
}

void dump(listDecoder * LD){
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