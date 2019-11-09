#include "listDecoder.hpp"
#include "gzstream.h"

namespace listDecoder {

    Items::Items(const std::string &filename) {
        this->filename = filename;
        this->extractItems();
    }


    void Items::extractItems() {

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

            this->items[parent].emplace_back(itemRow);
            this->hash_to_str[childHash] = child;

        }


    }

    flat_hash_map<std::string, std::vector<item_row>> *kmerDecoder::getKmers() {
        return &this->items;
    }

    void kmerDecoder::next_chunk() {
        this->END = true;
    }

    bool kmerDecoder::end() {
        return this->END;
    }

}