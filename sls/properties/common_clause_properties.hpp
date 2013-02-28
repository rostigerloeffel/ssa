#ifndef _SLS_PROPERTIES_COMMON_CLAUSE_PROPERTIES_HPP_
#define _SLS_PROPERTIES_COMMON_CLAUSE_PROPERTIES_HPP_


#include "../util/int_typedefs.hpp"


namespace sls { namespace properties {


template<typename VariableType>
struct watcher2
{
	VariableType watcher1;
	VariableType watcher2;
};

struct num_true_literals
{
	std::uint_fast8_t num_true_literals;
};

struct weight
{
	std::uint_fast32_t weight;
};

struct weight_increments
{
	std::uint_fast8_t weight_increments;
};

template<typename VariableType>
struct satisfying_literal
{
	VariableType satisfying;
};


} /* properties */ } /* sls */


#endif