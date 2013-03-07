#ifndef _SLS_FACETS_FACET_COMPOSITOR_HPP_
#define _SLS_FACETS_FACET_COMPOSITOR_HPP_


#include <vector>
#include "facet_base.hpp"
#include "../state/state_lang.hpp"


namespace sls { namespace facets {


template
<
    typename State,
    typename InnerState,
    typename ...Facets
>
struct facet_compositor : public Facets...
{
    INNER_STATE_TYPEDEFS(InnerState)

    // call the reset-method of each facet in a well-defined manner
    template<typename Facet>
    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        Facet::reset(clauses, variable_count);
    }

    template<typename Facet1, typename Facet2, typename ...RestFacets>
    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        Facet1::reset(clauses, variable_count);
        reset<Facet2, RestFacets...>(clauses, variable_count);
    }

    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        reset<Facets...>(clauses, variable_count);
    }

    // call the before_pick-method of each facet in a well-defined manner
    template<typename Facet>
    void before_pick(size_t flip)
    {
        Facet::before_pick(flip);
    }

    template<typename StateFacet1, typename StateFacet2, typename ...RestFacets>
    void before_pick(size_t flip)
    {
        StateFacet1::before_pick(flip);
        before_pick<StateFacet2, RestFacets...>(flip);
    }

    void before_pick(size_t flip)
    {
        before_pick<Facets...>(flip);
    }

    // call the after_pick-method of each facet in a well-defined manner
    template<typename Facet>
    void after_pick(size_t flip, variable_type variable)
    {
        Facet::after_pick(flip, variable);
    }

    template<typename Facet1, typename Facet2, typename ...RestFacets>
    void after_pick(size_t flip, variable_type variable)
    {
        Facet1::after_pick(flip, variable);
        after_pick<Facet2, RestFacets...>(flip, variable);
    }

    void after_pick(size_t flip, variable_type variable)
    {
        after_pick<Facets...>(flip, variable);
    }

    // call the flush-method of each facet in a well-defined manner
    template<typename Facet>
    void flush()
    {
        Facet::flush();
    }

    template<typename Facet1, typename Facet2, typename ...RestFacets>
    void flush()
    {
        Facet1::flush();
        flush<Facet2, RestFacets...>();
    }

    void flush()
    {
        flush<Facets...>();
    }
};


} /* facets */ } /* sls */


#endif
