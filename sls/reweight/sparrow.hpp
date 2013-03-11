#ifndef _SLS_REWEIGHT_SPARROW_HPP_
#define _SLS_REWEIGHT_SPARROW_HPP_


#include "reweighter_base.hpp"
#include "reweight_util.hpp"


namespace sls { namespace reweight {


template<typename State>
class sparrow : public reweighter_base<State>
{
    typedef State state_type;

    double smooth_probability_;

public:
	sparrow(double smooth_probability = 0.347)
		: smooth_probability_(smooth_probability)
	{}

    void operator()(state_type& state)
    {
        if(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX) < smooth_probability_)
            smooth_clause_weights(state);
        else
            increase_clause_weights(state);
    }

private:
    inline void increase_clause_weights(state_type& state)
    {
        for(auto clause : state.unsats())
        	inc_clause_weight(state, clause, 1);
    }

    inline void smooth_clause_weights(state_type& state)
    {
        for(auto clause : state.weighted())
        	dec_clause_weight(state, clause, 1);
    }
};


} /* reweight */ } /* sls */


#endif