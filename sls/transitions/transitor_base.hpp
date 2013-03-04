#ifndef _SLS_TRANSITIONS_TRANSITOR_BASE_HPP_
#define _SLS_TRANSITIONS_TRANSITOR_BASE_HPP_


namespace sls { namespace transitions {


template<typename StateType>
class transitor_base
{
	STATE_TYPEDEFS(StateType)

public:
	virtual void operator()(state_type& state, variable_type flip) = 0;
};


} /* transitions */ } /* sls */


#endif