#ifndef _SLS_SELECTORS_GREEDY_HPP_
#define _SLS_SELECTORS_GREEDY_HPP_


#include "selector_base.hpp"


namespace sls { namespace selectors {


template<typename State>
class greedy : public selector_base<State>
{
    typedef State                               state_type;
    typedef typename state_type::variable_type  variable_type;

public:
    bool is_applicable(state_type const& state)
    {
        return state.has_greedy();
    }

    variable_type select(state_type& state)
    {
        return state.most_greedy();
    }

    std::string const name() const 
    {
        return "greedy selector";
    }

};


} /* selectors */ } /* sls */


#endif
