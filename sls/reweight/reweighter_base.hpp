#ifndef _SLS_REWEIGHT_REWEIGHTER_BASE_HPP_
#define _SLS_REWEIGHT_REWEIGHTER_BASE_HPP_


namespace sls { namespace reweight {


template<typename State>
class reweighter_base
{
    typedef State state_type;

public:
    virtual void operator()(state_type& state) = 0;
};


} /* reweight */ } /* sls */


#endif
