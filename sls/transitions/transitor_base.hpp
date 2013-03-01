#ifndef __SSA_TRANSITIONS_TRANSITOR_BASE_HPP__
#define __SSA_TRANSITIONS_TRANSITOR_BASE_HPP__


namespace ssa { namespace transitions {


template<typename StateType>
class transitor_base
{
	typedef StateType 							state_type;
	typedef typename state_type::variable_type 	variable_type;

public:
	virtual void operator()(state_type& state, variable_type flip) = 0;
};


} /* transitions */ } /* ssa */


#endif