#include "listDecoder.hpp"



flat_hash_map<std::string,std::vector<item_row>>* listDecoder::getKmers(){
    return &this->kmers;
}

void listDecoder::initialize_seqan(){

    if (!seqan::open(this->seqFileIn, seqan::toCString(this->fileName)))
    {
        std::cerr << "ERROR: Could not open the file.\n";
        exit(1);
    }

}

bool listDecoder::end(){
    return this->seqan_end;
}

std::string listDecoder::get_filename(){
    return this->fileName;
}


listDecoder * listDecoder::initialize_hasher(int kmer_size, int hash_mode){
    return new Items(kmer_size, hash_mode);
}