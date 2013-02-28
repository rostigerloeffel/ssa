#ifndef __SSA_PRIORITY_VECTOR_HPP__
#define __SSA_PRIORITY_VECTOR_HPP__


#include <vector>


namespace sls { namespace storage {


template
<
    typename ItemType,
    typename ComparatorType = std::less<ItemType>
>
class priority_vector
{
public:
    typedef ComparatorType                              comparator_type;
    typedef std::vector<ItemType>                       container_type;

    typedef typename container_type::value_type         value_type;
    typedef typename container_type::reference          reference;
    typedef typename container_type::const_reference    const_reference;
    typedef typename container_type::size_type          size_type;

    typedef typename container_type::iterator           iterator;
    typedef typename container_type::const_iterator     const_iterator;
    typedef typename container_type::difference_type    difference_type;

private:
    container_type  container_;
    comparator_type comparator_;

public:
    explicit priority_vector(
            size_type max_size,
            comparator_type const& comparator   = comparator_type(),
            container_type const& container     = container_type())
        :   container_(container),
            comparator_(comparator)
    {
    }

    explicit priority_vector(
            comparator_type const& comparator   = comparator_type(),
            container_type const& container     = container_type())
        :   container_(container),
            comparator_(comparator)
    {
    }

    template<typename InputIterator>
    explicit priority_vector(
            InputIterator begin,
            InputIterator end,
            comparator_type const& comparator   = comparator_type(),
            container_type const& container     = container_type())
        :   container_(container),
            comparator_(comparator)
    {
        container_.insert(container_.end(), begin, end);
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
    }

    const_reference top() const
    {
        const_iterator top = container_.begin();
        for(const_iterator it = container_.begin(); it != container_.end(); ++it)
            if(comparator_(*top, *it))
                top = it;

        return *top;
    }

    void push(value_type const& item)
    {
        container_.push_back(item);
    }

    void pop()
    {
        const_iterator top = container_.begin();
        for(const_iterator it = container_.begin(); it != container_.end(); ++it)
            if(comparator_(*top, *it))
                top = it;

        container_.erase(top);
    }

    void remove(value_type const& item)
    {
        container_.erase(std::find(container_.begin(), container_.end(), item));
    }

    void update(value_type const& item)
    {
    }

    void update_after_inc(value_type const& item)
    {
    }

    void update_after_dec(value_type const& item)
    {
    }

    inline bool contains(value_type const& item) const
    {
        for(auto item2 : container_)
            if(item2 == item)
                return true;

        return false;
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
        return container_.cbegin();
    }

    const_iterator end() const
    {
        return container_.cend();
    }
};


template
<
    typename ItemType,
    typename ComparatorType
>
std::ostream& operator<<(std::ostream& stream, priority_vector<ItemType, ComparatorType> vector)
{
    stream << '[';
    for(auto item : vector)
        stream << item << ", ";
    stream << ']' << std::endl;

    return stream;
}


} /* storage */ } /* ssa */


#endif
