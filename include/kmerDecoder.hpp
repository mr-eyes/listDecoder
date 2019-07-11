#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <seqan/seq_io.h>
#include <parallel_hashmap/phmap.h>

using phmap::flat_hash_map;

/* 
--------------------------------------------------------
                        InputModule:Parent
--------------------------------------------------------
*/

class kmerDecoder {

protected:
    unsigned int chunk_size;
    seqan::StringSet<seqan::CharString> ids;
    seqan::StringSet<seqan::CharString> seqs;
    flat_hash_map<std::string, std::vector<std::string>> kmers;
    seqan::SeqFileIn *seqFileIn;
    bool seqan_end = false;

public:

    flat_hash_map<std::string, std::vector<std::string>> *getKmers();

    virtual void extractKmers() = 0;

    bool end();

    void next_chunk();

};


/* 
--------------------------------------------------------
                        Default Kmers
--------------------------------------------------------
*/


class Kmers : public kmerDecoder {

private:
    unsigned kSize;

public:

    Kmers(seqan::SeqFileIn &SeqIn, unsigned int chunk_size, int kSize) {
        this->kSize = kSize;
        this->seqFileIn = &SeqIn;
        this->chunk_size = chunk_size;
    }

    void extractKmers();
};


/* 
--------------------------------------------------------
                        Skipmers
--------------------------------------------------------
*/

class Skipmers : public kmerDecoder {
private:
    int m, n, k;
    int S;

public:
    Skipmers(seqan::SeqFileIn &SeqIn, unsigned int chunk_size, uint8_t m, uint8_t n, uint8_t k) {
        if (n < 1 or n < m or k < m or k % m != 0) {
            std::cerr << "Error: invalid skip-mer shape! m= " << m << " n=" << n << " k= " << k << std::endl
                      << "Conditions: 0 < m <= n, k must multiple of m." << std::endl;
            exit(1);
        }

        this->m = m;
        this->n = n;
        this->k = k;
        this->seqFileIn = &SeqIn;
        this->chunk_size = chunk_size;
    }

    void extractKmers();

    virtual ~Skipmers() {}
};


/* 
--------------------------------------------------------
                        Minimizers
--------------------------------------------------------
*/

typedef struct mkmh_minimizer {
    uint64_t pos;
    uint32_t length;
    std::string seq;

    bool operator<(const mkmh_minimizer &rhs) const { return seq < rhs.seq; };
} mkmh_minimizer;


class Minimizers : public kmerDecoder {
private:
    int k, w;

    struct mkmh_kmer_list_t {
        char **kmers;
        int length;
        int k;

        mkmh_kmer_list_t() {

        };

        mkmh_kmer_list_t(int length, int k) {
            this->length = length;
            this->k = k;
            this->kmers = new char *[length];
        };

        ~mkmh_kmer_list_t() {
            for (int i = 0; i < this->length; ++i) {
                delete[] this->kmers[i];
            }
            delete[] this->kmers;
        };
    };

protected:
    std::vector<mkmh_minimizer> kmer_tuples(std::string seq, int k);

    mkmh_kmer_list_t kmerize(char *seq, int seq_len, int k);

    std::vector<std::string> kmerize(std::string seq, int k);

    void kmerize(char *seq, const int &seq_len, const int &k, char **kmers, int &kmer_num);

    template<typename T>
    std::vector<T> v_set(std::vector<T> kmers);

public:
    Minimizers() {}

    Minimizers(seqan::SeqFileIn &SeqIn, unsigned int chunk_size, int k, int w) {
        this->k = k;
        this->w = w;
        this->seqFileIn = &SeqIn;
        this->chunk_size = chunk_size;
    }

    std::vector<mkmh_minimizer> getMinimizers(std::string &seq);

    void extractKmers();

    virtual ~Minimizers() {};
};