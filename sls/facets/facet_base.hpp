#ifndef _SLS_FACETS_FACET_BASE_HPP_
#define _SLS_FACETS_FACET_BASE_HPP_


#include <vector>


namespace sls { namespace facets {


template<typename State, typename InnerState>
struct facet_base
{
    INNER_STATE_TYPEDEFS(InnerState)

    virtual void reset(std::vector<clause_type> const& clauses, size_t variable_count)  {}
    virtual void before_pick(size_t flip)                                               {}
    virtual void after_pick(size_t flip, variable_type variable)                        {}
    virtual void flush()                                                                {}
};


} /* facets */ } /* sls */


#endif
