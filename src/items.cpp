#include "kmerDecoder.hpp"
#include "gzstream.h"
#include <sstream>


std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

Items::Items(const std::string &filename, int chunk_size) {
        this->chunk_size = chunk_size; // To allow duplicate parents
        cerr << "chunkSize = " << this->chunk_size << endl;
        this->filename = filename;
        file = ifstream(this->filename);
        // Skip header
        file >> row;
        this->seqan_end = false;
}

void Items::extractKmers(){
    this->kmers.clear();

    std::string parent, child, metadata;
    int i = 0;
    for(; i < this->chunk_size && this->file.peek() != EOF; i++)
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

    if(i < this->chunk_size){
        this->END = true;
        this->seqan_end = true;
        this->file.close();
    }else{
        this->seqan_end = false;
    }
}

void Items::next_chunk(){
        this->extractKmers();
}

bool Items::end(){
    return this->seqan_end;
}

void Items::setHashingMode(int hash_mode, bool canonical){

}

void Items::seq_to_kmers(std::string &seq, std::vector<kmer_row> &kmers){

}