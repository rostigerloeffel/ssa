#ifndef _SLS_REWEIGHT_TCC_SMOOTHER_HPP_
#define _SLS_REWEIGHT_TCC_SMOOTHER_HPP_


#include "reweighter_base.hpp"


namespace sls { namespace reweight {


template<typename State>
class tcc_smoother : public reweighter_base<State>
{
    typedef State state_type;

public:
    void operator()(state_type& state)
    {
        state.smooth_tcc();
    }
};


} /* reweight */ } /* sls */


#endif