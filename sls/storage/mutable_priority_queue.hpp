#ifndef __SLS_STORAGE_MUTABLE_PRIORITY_QUEUE_HPP__
#define __SLS_STORAGE_MUTABLE_PRIORITY_QUEUE_HPP__


#include <cassert>
#include <vector>
#include <functional>
#include <algorithm>
#include "index.hpp"


namespace sls
{


namespace storage
{


template
<
    typename ItemType,
    typename ComparatorType = std::less<ItemType>,
    typename IndexerType = indexer<ItemType>,
    typename ContainerType = std::vector<ItemType>,
    typename IndexContainer = std::vector<typename ContainerType::difference_type>
>
class mutable_priority_queue
{
public:
    typedef ContainerType   container_type;
    typedef ComparatorType  comparator_type;
    typedef IndexerType     indexer_type;
    typedef IndexContainer  index_container_type;

    typedef typename container_type::value_type         value_type;
    typedef typename container_type::reference          reference;
    typedef typename container_type::const_reference    const_reference;
    typedef typename container_type::size_type          size_type;

    typedef typename container_type::iterator           iterator;
    typedef typename container_type::const_iterator     const_iterator;
    typedef typename container_type::difference_type    difference_type;

//private:
    container_type          container_;
    comparator_type         comparator_;
    indexer_type            indexer_;
    index_container_type    indices_;

public:
    explicit mutable_priority_queue(
            size_type max_size                  = 0ul,
            comparator_type const& comparator   = comparator_type(),
            indexer_type const& indexer         = indexer_type(),
            container_type const& container     = container_type())
        : container_(container),
          comparator_(comparator),
          indexer_(indexer),
          indices_(container.size())
    {
        resize(max_size);
        build_indices();
    }

    template<typename InputIterator>
    explicit mutable_priority_queue(
            InputIterator const& begin,
            InputIterator const& end,
            size_type max_size,
            comparator_type const& comparator   = comparator_type(),
            indexer_type const& indexer         = indexer_type(),
            container_type const& container     = container_type())
        : container_(container),
          comparator_(comparator),
          indexer_(indexer),
          indices_(container.size())
    {
        resize(max_size);

        container_.insert(container_.end(), begin, end);
        std::make_heap(container_.begin(), container_.end(), comparator_);

        build_indices();
    }

    bool empty() const
    {
        return container_.empty();
    }

    size_type size() const
    {
        return container_.size();
    }

    void resize(size_type size)
    {
        container_.reserve(size);
        indices_.resize(size);

        std::fill(indices_.begin(), indices_.end(), -1);
    }

    const_reference top() const
    {
        return container_.front();
    }

    void push(value_type const& item)
    {
        //assert(is_heap(0));

        container_.push_back(item);
        indices_[indexer_(item)] = difference_type((container_.end() - container_.begin()) - 1);

        sift_up(difference_type((container_.end() - container_.begin()) - 1));

        //assert(is_heap(0));
    }

    void pop()
    {
        remove(container_.front());
    }

    void remove(value_type const& item)
    {
        difference_type const index = indices_[indexer_(item)];
        indices_[indexer_(item)] = -1;

        if(index == size() - 1)
        {
            container_.pop_back();
            return;
        }
        else
        {
            move_value(index, std::move(container_.back()));

            container_.pop_back();

            sift_down(sift_up(index));
            //assert(0);
            //assert(is_heap(0));

            return;
        }
    }

    void update(value_type const& item)
    {
        sift_down(sift_up(indices_[indexer_(item)]));

        //assert(is_heap(0));
    }

    void update_after_inc(value_type const& item)
    {
        sift_up(indices_[indexer_(item)]);
    }

    void update_after_dec(value_type const& item)
    {
        sift_down(indices_[indexer_(item)]);
    }

    inline bool contains(value_type const& item) const
    {
        return indices_[indexer_(item)] != -1;
    }

    container_type& container()
    {
        return container_;
    }

    iterator begin()
    {
        return container_.begin();
    }

    iterator end()
    {
        return container_.end();
    }

    const_iterator begin() const
    {
        return container_.begin();
    }

    const_iterator end() const
    {
        return container_.end();
    }

private:/*
    inline difference_type right(difference_type index) 
    {
        return (index + 1) * 2;
    }
    inline difference_type left(difference_type index)
    {
        return right(index) - 1;
    }

    inline bool is_heap(difference_type index)
    {
        // index has no children
        if(left(index) >= container_.size())
            return true;

        // index has only one child
        if(right(index) >= container_.size())
            return (comparator_(*(container_.begin() + left(index)), *(container_.begin() + index)) || equal_(*(container_.begin() + left(index)), *(container_.begin() + index)))
                    && is_heap(left(index));

        // index has both children
        return
            (comparator_(*(container_.begin() + left(index)), *(container_.begin() + index)) || equal_(*(container_.begin() + left(index)), *(container_.begin() + index))) &&
            (comparator_(*(container_.begin() + right(index)), *(container_.begin() + index)) || equal_(*(container_.begin() + right(index)), *(container_.begin() + index))) &&
            is_heap(left(index)) && is_heap(right(index));
    }*/


    inline void move_value(difference_type hole_index, value_type value)
    {
        assert(hole_index >= 0);
        assert(hole_index < container_.size());

        indices_[indexer_(value)] = hole_index;
        *(container_.begin() + hole_index) = std::move(value);
    }

    inline void build_indices()
    {
        std::fill(indices_.begin(), indices_.end(), -1);

        for(auto it = container_.begin(); it != container_.end(); ++it)
            indices_[indexer_(*it)] = it - container_.begin();
    }

    difference_type sift_up(difference_type hole_index)
    {
        value_type      value   = std::move(*(container_.begin() + hole_index));
        difference_type parent  = (hole_index - 1) / 2;

        while(hole_index > 0 && comparator_(*(container_.begin() + parent), value))
        {
            move_value(hole_index, std::move(*(container_.begin() + parent)));

            hole_index = parent;
            parent = (hole_index - 1) / 2;
        }

        move_value(hole_index, std::move(value));

        return hole_index;
    }

    difference_type sift_down(difference_type hole_index)
    {
        value_type      value           = std::move(*(container_.begin() + hole_index));
        difference_type second_child    = hole_index;

        while(second_child < (container_.size() - 1) / 2)
        {
            second_child = 2 * (second_child + 1);

            if(comparator_(*(container_.begin() + second_child), *(container_.begin() + (second_child - 1))))
                second_child--;

            if(comparator_(value, *(container_.begin() + second_child)))
                move_value(hole_index, std::move(*(container_.begin() + second_child)));
            else
            {
                move_value(hole_index, std::move(value));
                return hole_index;
            }

            hole_index = second_child;
        }

        if((container_.size() & 1) == 0 &&
           second_child == (container_.size() - 1) / 2 &&
           comparator_(value, *(container_.begin() + ((second_child + 1) * 2) - 1)))
        {
            move_value(hole_index, std::move(*(container_.begin() + ((second_child + 1) * 2) - 1)));
            hole_index = ((second_child + 1) * 2) - 1;
        }

        move_value(hole_index, std::move(value));
        return hole_index;
    }
};


template
<
    typename ItemType,
    typename ComparatorType,
    typename IndexerType,
    typename ContainerType,
    typename IndexContainer
>
std::ostream& operator<<(std::ostream& stream, mutable_priority_queue<ItemType, ComparatorType, IndexerType, ContainerType, IndexContainer> queue)
{
    stream << '[';
    for(auto item : queue)
        stream << item << ", ";
    stream << ']' << std::endl;

    stream << '[';
    for(auto index : queue.indices_)
        stream << index << ", ";
    stream << ']' << std::endl;

    return stream;
}


} /* storage */


} /* sls */


#endif
