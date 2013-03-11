#ifndef __SSA_REWEIGHT_COMPOSITOR_HPP__
#define __SSA_REWEIGHT_COMPOSITOR_HPP__


#include <vector>
#include "reweighter_base.hpp"


namespace ssa { namespace selectors {


template<typename StateType>
class compositor : public reweighter_base<StateType>
{
    typedef StateType state_type;
    typedef typename state_type::variable_type variable_type;

    std::vector<reweighter_base<state_type>*> reweighters_;
 
public:
    compositor()
        :   reweighters_() 
    {}

    compositor(std::initializer_list<reweighter_base<state_type>*> reweighters)
        :   reweighters_(reweighters.begin(), reweighters.end()) 
    {}

    void operator()(state_type& state)
    {
        for(auto reweighter : reweighters_)
            (*reweighter)(state);
    }
};


} /* reweighters */ } /* ssa */


#endif
