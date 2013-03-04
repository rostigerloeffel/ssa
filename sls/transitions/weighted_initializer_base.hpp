#ifndef _SLS_TRANSITIONS_WEIGHTED_INITIALIZER_BASE_HPP_
#define _SLS_TRANSITIONS_WEIGHTED_INITIALIZER_BASE_HPP_


#include "../frontend/problem_types.hpp"


namespace sls { namespace transitions {


template<typename StateType>
class weighted_initializer_base
{
	typedef StateType 							state_type;
	typedef typename state_type::clause_type 	clause_type;

public:
	virtual state_type operator()(sls::frontend::problem const& problem) const = 0;
};


} /* transitions */ } /* sls */


#endif