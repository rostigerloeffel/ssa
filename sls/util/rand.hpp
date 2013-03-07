#ifndef __SLS_UTIL_RAND_HPP__
#define __SLS_UTIL_RAND_HPP__


#include <fstream>


namespace sls
{


namespace util
{


inline unsigned int read_seed()
{
    std::ifstream noise("/dev/urandom", std::istream::binary);

    unsigned int seed;
    noise.read(reinterpret_cast<char*>(&seed), sizeof(seed));

    return seed;
}


} /* util */


} /* sls */


#endif