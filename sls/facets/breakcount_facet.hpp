#ifndef _SLS_FACETS_BREAKCOUNT_FACET_HPP_
#define _SLS_FACETS_BREAKCOUNT_FACET_HPP_


#include <vector>
#include <algorithm>
#include "facet.hpp"
#include "facet_base.hpp"


namespace sls { namespace facets {


begin_facet(breakcount)
public:
    typedef decltype(variable_properties_type::score) score_type;

    facet_constr(breakcount)

    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        std::for_each(inner_state_.variable_properties_begin(), inner_state_.variable_properties_end(), 
        	[](variable_properties_type& prop){ prop.score = score_type(0); });
    }

    inline score_type breakcount(variable_type variable) const
    {
        return -inner_state_[variable].score;
    }

    inline void inc_makecount(variable_type variable, score_type diff) {}
    inline void dec_makecount(variable_type variable, score_type diff) {}

    inline void inc_breakcount(variable_type variable, score_type diff)
    {
        inner_state_[variable].score -= diff;
    }

    inline void dec_breakcount(variable_type variable, score_type diff)
    {
        inner_state_[variable].score += diff;
    }
};


} /* facets */ } /* sls */


#endif