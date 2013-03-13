#ifndef _SLS_SELECTORS_OLDEST_HPP_
#define _SLS_SELECTORS_OLDEST_HPP_


#include "selector_base.hpp"


namespace sls { namespace selectors {


template<typename StateType>
class oldest : public selector_base<StateType>
{
    typedef StateType state_type;
    typedef typename state_type::sat_type sat_type;
    typedef typename state_type::variable_type variable_type;

public:
    bool is_applicable(state_type const& state)
    {
        return true;
    }

    variable_type select(state_type& state)
    {
        auto unsat = state.unsats()[std::rand() % state.unsats().size()];

        auto pick = variable_type::null();
        for(auto literal : unsat)
            if(pick == variable_type::null() ||
               state.last_flip(literal.variable()) < state.last_flip(pick))
                pick = literal.variable();

        return pick;
    }

    std::string const name() const 
    {
        return "oldest selector";
    }

};


} /* selectors */ } /* sls */


#endif
