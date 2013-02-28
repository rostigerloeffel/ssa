#ifndef __SLS_STORAGE_INDEX_HPP__
#define __SLS_STORAGE_INDEX_HPP__


namespace sls
{


namespace storage
{


template<typename ValueType>
struct indexer
{
    inline size_t operator()(ValueType value) const
    {
        return index(value);
    }
};


}


}


#endif
