#include "listDecoder.hpp"
#include "gzstream.h"

void Items::extractItems(){

    std::string parent, child, metadata;
    igzstream in(this->filename.c_str());

    // skip first line
    in >> parent >> child >> metadata;

    while (in) {
        in >> parent >> child >> metadata;
        uint64_t childHash = this->child_hasher(child);

        item_row itemRow;
        itemRow.str = child;
        itemRow.hash = childHash;

        this->kmers[parent].emplace_back(itemRow);
        this->hash_to_str[childHash] = child;

        std::cout << "[!] " << parent << ":" << child << std::endl;

    }

}

void Items::next_chunk(){
   this->END = true;
}