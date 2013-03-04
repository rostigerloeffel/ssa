#ifndef __SSA_SCORE_SENDER_FACET_HPP__
#define __SSA_SCORE_SENDER_FACET_HPP__


#include "facet_base.hpp"
#include "signals.hpp"
#include "facet.hpp"


namespace sls { namespace facets {


begin_facet(score_sender, typename ...ScoreListener)
    typedef decltype(variable_properties_type::score) score_type;

    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        std::for_each(get_inner_state.variable_properties_begin(), get_inner_state.variable_properties_end(), 
        	[](variable_properties_type& prop){ 
                prop.score = score_type(0); 
            });
    }

    inline score_type score(variable_type variable) const
    {
        return get_inner_state[variable].score;
    }

    inline void inc_makecount(variable_type variable, score_type diff)
    {
        get_inner_state[variable].score += diff;
        send_signal(score_inc, variable, diff);
    }

    inline void dec_makecount(variable_type variable, score_type diff)
    {
        get_inner_state[variable].score -= diff;
        send_signal(score_dec, variable, diff);
    }

    inline void inc_breakcount(variable_type variable, score_type diff)
    {
        get_inner_state[variable].score -= diff;
        send_signal(score_dec, variable, diff);
    }

    inline void dec_breakcount(variable_type variable, score_type diff)
    {
        get_inner_state[variable].score += diff;
        send_signal(score_inc, variable, diff);
    }

private:
    facet_signal(score_inc, ScoreListener, variable_type, score_type)
    facet_signal(score_dec, ScoreListener, variable_type, score_type)
end_facet


} /* facets */ } /* sls */


#endif