#ifndef _SLS_REWEIGHT_COMPOSITOR_HPP_
#define _SLS_REWEIGHT_COMPOSITOR_HPP_


#include <vector>
#include "reweighter_base.hpp"


namespace sls { namespace selectors {


template<typename State>
class compositor : public reweighter_base<State>
{
    typedef State state_type;
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


} /* reweighters */ } /* sls */


#endif
