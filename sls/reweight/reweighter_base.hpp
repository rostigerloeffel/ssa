#ifndef __SSA_REWEIGHT_REWEIGHTER_BASE_HPP__
#define __SSA_REWEIGHT_REWEIGHTER_BASE_HPP__


namespace ssa { namespace reweight {


template<typename StateType>
class reweighter_base
{
    typedef StateType state_type;

public:
    virtual void operator()(state_type& state) = 0;
};


} /* reweight */ } /* ssa */


#endif
