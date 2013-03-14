#ifndef _SLS_FACETS_NEIGHBOUR_FACET_HPP_
#define _SLS_FACETS_NEIGHBOUR_FACET_HPP_


#include "facet.hpp"
#include "facet_base.hpp"


namespace sls { namespace facets {


begin_facet(neighbour)

    typedef decltype(variable_properties_type::neighbours) neighbour_store_type;

    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        std::vector<std::vector<variable_type>> tmp;

        tmp.resize(variable_count);
        for(auto clause : get_inner_state.clauses())
            for(auto literal1 : clause)
                for(auto literal2 : clause)
                    if(literal1 != literal2)
                        tmp[sat_type::index(literal1.variable())].push_back(literal2.variable());

        for(auto variable : get_inner_state.variables())
            get_inner_state[variable].neighbours =
                neighbour_store_type(
                    tmp[sat_type::index(variable)].begin(), 
                        std::unique(
                            tmp[sat_type::index(variable)].begin(), 
                            tmp[sat_type::index(variable)].end()));
    }

    inline neighbour_store_type const& neighbours(variable_type variable) const
    {
        return get_inner_state[variable].neighbours;
    }
}; 


} /* facets */ } /* sls */


#endif