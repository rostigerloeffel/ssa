#ifndef __SSA_REWEIGHT_TCC_SMOOTHER_HPP__
#define __SSA_REWEIGHT_TCC_SMOOTHER_HPP__


#include "reweighter_base.hpp"


namespace ssa { namespace reweight {


template<typename StateType>
class tcc_smoother : public reweighter_base<StateType>
{
    typedef StateType state_type;

public:
    void operator()(state_type& state)
    {
        state.smooth_tcc();
    }
};


} /* reweight */ } /* ssa */


#endif