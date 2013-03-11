#ifndef _SLS_FACETS_AGE_FACET_HPP_
#define _SLS_FACETS_AGE_FACET_HPP_


#include <vector>
#include <algorithm>
#include "facet.hpp"
#include "facet_base.hpp"


namespace sls { namespace facets {


begin_facet(age)
private:
    size_t flips_;

public:
    facet_constr(age, flips_(0ul))

    inline void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        std::for_each(inner_state_.variable_properties_begin(), inner_state_.variable_properties_end(), 
            [](variable_properties_type& prop){ 
                prop.last_flip = 0; 
        });

        flips_ = 0ul;
    }

    inline void after_pick(size_t flip, variable_type variable)
    {
        flips_ = flip;
        get_inner_state[variable].last_flip = flip;
    }

    inline size_t flips() const
    {
        return flips_;
    }

    inline void last_flip(variable_type variable, size_t flip)
    {
        get_inner_state[variable].last_flip = flip;
    }

    inline size_t last_flip(variable_type variable) const
    {
        return get_inner_state[variable].last_flip;
    }

    inline size_t age(variable_type variable) const
    {
        return flips_ - last_flip(variable);
    }
end_facet


} /* facets */ } /* sls */


#endif