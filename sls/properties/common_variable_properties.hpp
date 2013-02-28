#ifndef _SLS_PROPERTIES_COMMON_VARIABLE_PROPERTIES_HPP_
#define _SLS_PROPERTIES_COMMON_VARIABLE_PROPERTIES_HPP_


#include <vector>


namespace sls { namespace properties {


struct truth
{
	bool truth;
};

struct score
{
	std::int_fast32_t score;
};

struct age
{
	std::uint_fast32_t last_flip;
};

struct blocked
{
	bool blocked;
};

struct polarity_count
{
	std::uint_fast32_t positive;
	std::uint_fast32_t negative;
};

struct flops
{
	std::uint_fast32_t flops;
};

struct tcc
{
	std::uint_fast32_t tcc;
};

template<typename VariableType>
struct neighbours
{
	std::vector<VariableType> neighbours;
};


} /* properties */ } /* sls */


#endif