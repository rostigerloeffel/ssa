#ifndef __SSA_TRANSITIONS_WEIGHTED_INITIALIZER_BASE_HPP__
#define __SSA_TRANSITIONS_WEIGHTED_INITIALIZER_BASE_HPP__


#include "../frontend/problem_types.hpp"


namespace ssa { namespace transitions {


template<typename StateType>
class weighted_initializer_base
{
	typedef StateType 							state_type;
	typedef typename state_type::clause_type 	clause_type;

public:
	virtual state_type operator()(ssa::frontend::problem const& problem) const = 0;
};


} /* transitions */ } /* ssa */


#endif