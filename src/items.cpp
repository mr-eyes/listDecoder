#include "kmerDecoder.hpp"
#include "gzstream.h"
#include <sstream>

void Items::extractKmers(){

    std::string parent, child, metadata;
    igzstream in(this->filename.c_str());

    std::string line;

    // skip first line
    std::getline(in, line);

    while(std::getline(in, line)){
        std::stringstream   linestream(line);
        std::getline(linestream, parent, '\t');
        linestream >> child >> metadata;

        uint64_t childHash = this->child_hasher(child);
        kmer_row itemRow;
        itemRow.str = child;
        itemRow.hash = childHash;
        this->kmers[parent].emplace_back(itemRow);
        this->hash_to_str[childHash] = child;
    }

}

void Items::next_chunk(){
    this->seqan_end = true;
}

bool Items::end(){
    return this->seqan_end;
}

void Items::setHashingMode(int hash_mode, bool canonical){

}

void Items::seq_to_kmers(std::string &seq, std::vector<kmer_row> &kmers){

}