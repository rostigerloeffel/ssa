#ifndef __SLS_STORAGE_QUANTITY_WRAPPER_HPP__
#define __SLS_STORAGE_QUANTITY_WRAPPER_HPP__


#include "random_access_list.hpp"

#include "index.hpp"


namespace sls
{


namespace storage
{


template
<
    typename ValueType,
    typename ContainerType = random_access_list<ValueType>,
    typename Indexer = indexer<ValueType>,
    typename QuantityStoreType = std::vector<size_t>
>
class quantity_wrapper
{
public:
    typedef ContainerType                               container_type;
    typedef typename container_type::value_type         value_type;
    typedef typename container_type::iterator           iterator;
    typedef typename container_type::const_iterator     const_iterator;
    typedef Indexer                                     indexer_type;
    typedef QuantityStoreType                           quantity_store_type;
    typedef typename quantity_store_type::value_type    quantity_type;

private:
    container_type      container_;
    quantity_store_type quantities_;
    indexer_type        indexer_;

public:
    inline void resize(size_t size)
    {
        container_.resize(size);
        quantities_.resize(size);
        std::fill(std::begin(quantities_), std::end(quantities_), quantity_type(0));
    }

    inline size_t size() const
    {
        return container_.size();
    }

    inline void push_back(value_type const& item)
    {
        if(++quantities_[indexer_(item)] == 1)
            container_.push_back(item);
    }

    inline void remove(value_type const& item)
    {
        if(--quantities_[indexer_(item)] == 0)
            container_.remove(item);
    }

    inline quantity_type quantity(value_type const& item)
    {
        return quantities_[indexer_(item)];
    }

    inline void clear()
    {
        container_.clear();
        std::fill(std::begin(quantities_), std::end(quantities_), quantity_type(0));
    }

    inline value_type& operator[](size_t index)
    {
        return container_[index];
    }

    inline value_type const& operator[](size_t index) const
    {
        return container_[index];
    }

    inline iterator begin()
    {
        return container_.begin();
    }

    inline iterator end()
    {
        return container_.end();
    }

    inline const_iterator begin() const
    {
        return container_.begin();
    }

    inline const_iterator end() const
    {
        return container_.end();
    }
};



} /* storage */


} /* sls */


#endif
