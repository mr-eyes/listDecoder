#include "listDecoder.hpp"



flat_hash_map<std::string,std::vector<item_row>>* listDecoder::getKmers(){
    return &this->kmers;
}

void listDecoder::initialize_seqan(){}

std::string listDecoder::get_filename(){
    return this->fileName;
}