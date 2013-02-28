#ifndef __SLS_SAT_STANDARD_CLAUSE_HPP__
#define __SLS_SAT_STANDARD_CLAUSE_HPP__


#include <iostream>
#include <limits>
#include <vector>
#include <cstdint>
#include "variable_literal.hpp"


namespace sls
{


namespace sat
{


namespace standard
{


namespace internal
{


struct clause_info_t
{
    std::uint_fast32_t offset;
    std::uint_fast32_t size;
};


static std::uint_fast32_t           next_index_ = 0;
static std::vector<literal_type>    clauses_;
static std::vector<clause_info_t>   clause_info_;


template<typename Iterator>
static std::uint_fast32_t push_clause_to_stack(Iterator begin, Iterator end)
{
    clause_info_.push_back(
    { 
        static_cast<std::uint_fast32_t>(clauses_.size()), 
        static_cast<std::uint_fast32_t>(std::distance(begin, end)) 
    });

    std::copy(begin, end, std::back_inserter(clauses_)); 

    return next_index_++;
}


} /* internal */


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
        return internal::clause_info_[value].size;
    }

    inline literal_type operator[](std::uint_fast32_t index) const
    {
        return *(internal::clauses_.begin() + internal::clause_info_[value].offset + index);
    }

    inline iterator begin()
	{   
        return internal::clauses_.begin() + internal::clause_info_[value].offset; 
	}

	inline iterator end()
	{   
        return internal::clauses_.begin() + internal::clause_info_[value].offset + internal::clause_info_[value].size; 
	}

    inline const_iterator cbegin()
	{   
        return internal::clauses_.begin() + internal::clause_info_[value].offset; 
	}

    inline const_iterator cend()
	{   
        return internal::clauses_.begin() + internal::clause_info_[value].offset + internal::clause_info_[value].size; 
	}
};

inline bool operator==(clause_type lhs, clause_type rhs)
{
    return lhs.value == rhs.value;
}

inline bool operator!=(clause_type lhs, clause_type rhs)
{
	return lhs.value != rhs.value;
}

inline bool operator<(clause_type lhs, clause_type rhs)
{
	return lhs.value < rhs.value;
}

inline size_t index(clause_type clause)
{
    return clause.value;
}

inline std::ostream& operator<<(std::ostream& stream, clause_type clause)
{
	stream << "[";

	for(auto literal : clause) 
		stream << literal << ", ";

	return stream << "]";
}


} /* standard */


} /* sat */


} /* sls */


#endif
