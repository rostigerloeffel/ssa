#ifndef _SLS_SELECTORS_REWEIGHTING_SELECTOR_HPP_
#define _SLS_SELECTORS_REWEIGHTING_SELECTOR_HPP_


#include "selector_base.hpp"
#include "../reweight/reweighter_base.hpp"


namespace sls { namespace selectors {


template<typename State>
class reweighting_selector : public selector_base<State>
{
    typedef State state_type;
    typedef typename state_type::variable_type variable_type;

    selector_base<state_type>* const selector_;
    sls::reweight::reweighter_base<state_type>* const reweighter_;

public:
	reweighting_selector(
					selector_base<state_type>* const selector, 
					sls::reweight::reweighter_base<state_type>* const reweighter)
		:	selector_(selector),
			reweighter_(reweighter)
	{}

    bool is_applicable(state_type const& state)
    {
    	return selector_->is_applicable(state);
    }

    variable_type select(state_type& state)
    {
        (*reweighter_)(state);

        return selector_->select(state);
    }

    std::string const name() const 
    {
    	return "reweighting selector";
    }
};


} /* selectors */ } /* sls */


#endif