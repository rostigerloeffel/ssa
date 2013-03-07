#ifndef _SLS_FACETS_BREAKCOUNT_FACET_HPP_
#define _SLS_FACETS_BREAKCOUNT_FACET_HPP_


#include <vector>
#include <algorithm>
#include "facet.hpp"
#include "facet_base.hpp"


namespace sls { namespace facets {


begin_facet(breakcount)
    typedef decltype(variable_properties_type::score) score_type;

    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        std::for_each(get_inner_state.variable_properties_begin(), get_inner_state.variable_properties_end(), 
        	[](variable_properties_type& prop){ 
                prop.score = score_type(0); 
            });
    }

    inline score_type breakcount(variable_type variable) const
    {
        return -get_inner_state[variable].score;
    }

    inline void inc_makecount(variable_type variable, score_type diff) {}
    inline void dec_makecount(variable_type variable, score_type diff) {}

    inline void inc_breakcount(variable_type variable, score_type diff)
    {
        get_inner_state[variable].score -= diff;
    }

    inline void dec_breakcount(variable_type variable, score_type diff)
    {
        get_inner_state[variable].score += diff;
    }
end_facet


} /* facets */ } /* sls */


#endif