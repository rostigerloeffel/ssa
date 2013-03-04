#ifndef _SLS_TRANSITIONS_INITIALIZER_BASE_HPP_
#define _SLS_TRANSITIONS_INITIALIZER_BASE_HPP_


#include "../frontend/problem_types.hpp"


namespace sls { namespace transitions {


template<typename StateType>
class initializer_base
{
	STATE_TYPEDEFS(StateType)

public:
	virtual state_type operator()(sls::frontend::problem const& problem) const = 0;
};


} /* transitions */ } /* sls */


#endif