#include "kmerDecoder.hpp"
#include "gzstream.h"
#include <sstream>


std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

Items::Items(const std::string &filename) {
        this->chunk_size = 1; // To allow duplicate parents
        this->filename = filename;
        file = ifstream(this->filename);
        // Skip header
        file >> row;
}

void Items::extractKmers(){
    this->next_chunk();
}

void Items::next_chunk(){
    
    std::string parent, child, metadata;

    for(int i = 0; i < this->chunk_size && this->file.peek() != EOF; i++)
    {
        this->file >> row;
        parent = row[0];
        child = row[1];

        uint64_t childHash = this->child_hasher(child);
        kmer_row itemRow;
        itemRow.str = child;
        itemRow.hash = childHash;
        this->kmers[parent].emplace_back(itemRow);
        this->hash_to_str[childHash] = child;

    }

    if(this->kmers.size() < this->chunk_size){
        this->END = true;
        this->seqan_end = true;
        this->file.close();
    }else{
        this->END = false;
        this->seqan_end = false;
    }

}

bool Items::end(){
    return this->seqan_end;
}

void Items::setHashingMode(int hash_mode, bool canonical){

}

void Items::seq_to_kmers(std::string &seq, std::vector<kmer_row> &kmers){

}