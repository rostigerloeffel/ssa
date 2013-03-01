#ifndef _SLS_FACETS_TRUTH_FACET_HPP_
#define _SLS_FACETS_TRUTH_FACET_HPP_


#include <vector>
#include <algorithm>
#include "facet.hpp"
#include "facet_base.hpp"


namespace sls { namespace facets {


begin_facet(truth)
    facet_constr(truth)

    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        randomize();
    }

    inline void randomize()
    {
        std::for_each(inner_state_.variable_properties_begin(), inner_state_.variable_properties_end(), 
        	[](variable_properties_type& prop){ prop.truth = static_cast<bool>(std::rand() % 2); });
    }

    inline void flip(variable_type variable)
    {
        inner_state_[variable].truth = !inner_state_[variable].truth;
    }

    inline bool truth(variable_type variable) const
    {
        return inner_state_[variable].truth;
    }

    inline bool is_sat(literal_type literal) const
    {
        return (literal.polarity() ? truth(literal.variable()) : !truth(literal.variable()));
    }
end_facet 


} /* facets */ } /* sls */


#endif