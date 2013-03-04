#ifndef _SLS_OCC_TRANSITOR_HPP_
#define _SLS_OCC_TRANSITOR_HPP_


#include "transitor_base.hpp"


namespace sls { namespace transitions {


template
<
	typename StateType,
	typename HandlePlus,
	typename HandleMinus
>
class occ_transitor : public transitor_base<StateType>
{
public:
	STATE_TYPEDEFS(StateType)

	typedef HandlePlus 							handle_plus_policy;
	typedef HandleMinus 						handle_minus_policy;

public:
	void operator()(state_type& state, variable_type flip)
	{
		auto const& pos_clauses = state.clauses_by_literal(sat_type::make_literal(flip, state.truth(flip)));

    	for(auto clause : pos_clauses)
        	handle_minus_policy::handle_minus(state, clause, flip);

    	auto const& neg_clauses = state.clauses_by_literal(sat_type::make_literal(flip, !state.truth(flip)));

    	for(auto clause : neg_clauses)
        	handle_plus_policy::handle_plus(state, clause, flip);

    	state.flip(flip);
	}
};


} /* transitions */ } /* sls */


#endif