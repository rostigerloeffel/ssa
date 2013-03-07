#ifndef _SLS_FACETS_WATCHER_FACET_HPP_
#define _SLS_FACETS_WATCHER_FACET_HPP_


#include <vector>
#include <algorithm>
#include "facet.hpp"
#include "facet_base.hpp"


namespace sls { namespace facets {


begin_facet(watcher)
    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        std::for_each(get_inner_state.clause_properties_begin(), get_inner_state.clause_properties_end(), 
        	[](clause_properties_type& prop){ 
        		prop.watcher1 = sat_type::variable_type::null();
        		prop.watcher2 = sat_type::variable_type::null(); 
            });
    }

    inline variable_type watcher1(clause_type clause) const
    {
        return get_inner_state[clause].watcher1;
    }

    inline void watcher1(clause_type clause, variable_type variable)
    {
        get_inner_state[clause].watcher1 = variable;
    }

    inline variable_type watcher2(clause_type clause) const
    {
        return static_cast<
                    typename std::conditional<
                        std::is_const<typename std::remove_pointer<decltype(this)>::type>::value,
                        State const* const,
                        State* const>::type>(this)->inner_state()[clause].watcher2;
    }

    inline void watcher2(clause_type clause, variable_type variable)
    {
        get_inner_state[clause].watcher2 = variable;
    }
end_facet


} /* facets */ } /* sls */


#endif