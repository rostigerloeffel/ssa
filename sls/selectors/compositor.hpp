#ifndef _SLS_SELECTORS_COMPOSITOR_HPP_
#define _SLS_SELECTORS_COMPOSITOR_HPP_


#include <vector>
#include "selector_base.hpp"


namespace sls { namespace selectors {


template<typename State>
class compositor : public selector_base<State>
{
    typedef State state_type;
    typedef typename state_type::variable_type variable_type;

    std::vector<selector_base<state_type>*> selectors_;
    selector_base<state_type>*              applicable_;

public:
    compositor()
        :   selectors_(), 
            applicable_(nullptr)
    {
    }

    compositor(std::initializer_list<selector_base<state_type>*> selectors)
        :   selectors_(selectors.begin(), selectors.end()), 
            applicable_(nullptr)
    {
    }

    bool is_applicable(state_type const& state)
    {
        for(auto selector : selectors_)
            if(selector->is_applicable(state))
            {
                applicable_ = selector;
                return true;
            }

        return false;
    }

    variable_type select(state_type& state)
    {
        return applicable_->select(state);
    }

    std::vector<selector_base<state_type>*>& selectors()
    {
        return selectors_;
    }
};


} /* selectors */ } /* sls */


#endif
