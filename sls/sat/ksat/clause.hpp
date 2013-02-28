#ifndef __SLS_SAT_KSAT_CLAUSE_HPP__
#define __SLS_SAT_KSAT_CLAUSE_HPP__


#include <iostream>
#include <limits>
#include <vector>
#include <cstdint>
#include "variable_literal.hpp"


namespace sls
{


namespace sat
{


namespace ksat
{


namespace internal
{


static std::uint_fast32_t           next_index_ = 0;
static std::vector<literal_type>    clauses_;


template<typename Iterator>
static std::uint_fast32_t push_clause_to_stack(Iterator begin, Iterator end)
{
    std::copy(begin, end, std::back_inserter(clauses_));

    return next_index_++;
}

template<typename Iterator>
static void replace_clause_on_stack(std::uint_fast32_t clause_value, Iterator begin, Iterator end)
{
    auto k = std::distance(begin, end);

    for(auto literal_index = 0; begin != end; ++end, ++literal_index)
        clauses_[(clause_value * k) + literal_index] = *begin;
}


} /* internal */


template<unsigned int K>
class clause_type
{
public:
	typedef std::vector<literal_type>::iterator 		iterator;
	typedef std::vector<literal_type>::const_iterator	const_iterator;

    std::uint_fast32_t value;

    static inline clause_type null()
    {
    	return clause_type { std::numeric_limits<std::uint_fast32_t>::max() };
    }

    inline std::uint_fast32_t size() const
    {
        return K;
    }

    inline literal_type operator[](std::uint_fast32_t index) const
    {
        return *(internal::clauses_.begin() + (value * K) + index);
    }

    inline iterator begin()
	{   
        return internal::clauses_.begin() + (value * K); 
	}

	inline iterator end()
	{   
        return internal::clauses_.begin() + (value * K) + K; 
	}

    inline const_iterator cbegin()
	{   
        return internal::clauses_.begin() + (value * K); 
	}

    inline const_iterator cend()
	{   
        return internal::clauses_.begin() + (value * K) + K; 
	}
};

template<unsigned int K>
inline bool operator==(clause_type<K> lhs, clause_type<K> rhs)
{
    return lhs.value == rhs.value;
}

template<unsigned int K>
inline bool operator!=(clause_type<K> lhs, clause_type<K> rhs)
{
	return lhs.value != rhs.value;
}

template<unsigned int K>
inline bool operator<(clause_type<K> lhs, clause_type<K> rhs)
{
	return lhs.value < rhs.value;
}

template<unsigned int K>
inline size_t index(clause_type<K> clause)
{
    return clause.value;
}

template<unsigned int K>
inline std::ostream& operator<<(std::ostream& stream, clause_type<K> clause)
{
	stream << "[";

	for(auto literal : clause)
		stream << literal << ", ";

	return stream << "]";
}


} /* ksat */


} /* sat */


} /* sls */


#endif
