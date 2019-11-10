#include "listDecoder.hpp"

void Items::seq_to_kmers(std::string & seq, std::vector <item_row> & kmers){

    kmers.clear();

    kmers.reserve(seq.size());

    for (unsigned long i = 0; i < seq.size() - get_kSize() + 1; i++)
        {
            item_row kmer;
            kmer.str = seq.substr(i, get_kSize());
            kmer.hash = this->hasher->hash(kmer.str);
            kmers.push_back(kmer);
        }

}

void Items::extractKmers(){

    std::string id;
    std::string seq;

    for(unsigned seq_num = 0; seq_num < seqan::length(this->ids); seq_num++){

        if(seqan::length(this->seqs[seq_num]) < this->get_kSize()) continue; 

        seq = std::string((char*)seqan::toCString(this->seqs[seq_num]));
        id =  std::string((char*)seqan::toCString(this->ids[seq_num]));

        this->kmers[id].reserve(seq.size());

        for (unsigned long i = 0; i < seq.size() - get_kSize() + 1; i++)
        {
            item_row kmer;
            kmer.str = seq.substr(i, get_kSize());
            kmer.hash = this->hasher->hash(kmer.str);
            this->kmers[id].push_back(kmer);
        }

    }


}