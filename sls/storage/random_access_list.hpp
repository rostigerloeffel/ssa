#ifndef __SLS_STORAGE_CONST_ACCESS_LIST_HPP__
#define __SLS_STORAGE_CONST_ACCESS_LIST_HPP__


#include <cassert>
#include <vector>
#include <limits>
#include "index.hpp"


namespace sls
{


namespace storage
{


template
<
    typename Item,
    typename Indexer = indexer<Item>,
    typename List = std::vector<Item>,
    typename IndexContainer = std::vector<size_t>
>
class random_access_list
{
public:
    typedef Item                                value_type;
    typedef Indexer                             indexer_type;
    typedef List                                list_type;
    typedef IndexContainer                      index_container_type;
    typedef typename list_type::iterator        iterator;
    typedef typename list_type::const_iterator  const_iterator;

private:
    indexer_type            indexer_;
    list_type               items_;
    index_container_type    indices_;

public:
    inline void resize(size_t size)
    {
        items_.reserve(size);
        indices_.resize(size);
    }

    inline size_t size() const
    {
        return items_.size();
    }

    inline void push_back(value_type const& item)
    {
        //assert(indexer_(item) >= 0);
        //assert(indexer_(item) < indices_.size());

        indices_[indexer_(item)] = items_.size();
        items_.push_back(item);
    }

    inline void remove(value_type const& item)
    {
        //assert(indices_[indexer_(item)] < items_.size());
        //assert(items_.size() > 0);

        indices_[indexer_(items_.back())] = indices_[indexer_(item)];
        items_[indices_[indexer_(item)]] = std::move(items_.back());

        // Needed by "contains"
        //indices_[indexer_(item)] = std::numeric_limits<size_t>::max();

        items_.pop_back();
    }
/*
    inline bool contains(value_type const& item) const
    {
        return indices_[indexer_(item)] < items_.size();
    }
*/
    inline bool empty() const
    {
        return size() == 0u;
    }

    inline void clear()
    {
        items_.clear();
    }

    inline value_type& operator[](size_t index)
    {
        assert(index >= 0);
        assert(index < items_.size());

        return items_[index];
    }

    inline value_type const& operator[](size_t index) const
    {
        assert(index >= 0);
        assert(index < items_.size());

        return items_[index];
    }

    inline iterator begin()
    {
        return items_.begin();
    }

    inline iterator end()
    {
        return items_.end();
    }

    inline const_iterator begin() const
    {
        return items_.begin();
    }

    inline const_iterator end() const
    {
        return items_.end();
    }
};


} /* storage */


} /* sls */


#endif
