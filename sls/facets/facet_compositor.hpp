#ifndef _SLS_FACETS_FACET_COMPOSITOR_HPP_
#define _SLS_FACETS_FACET_COMPOSITOR_HPP_


#include <vector>
#include "facet_base.hpp"


namespace sls { namespace facets {


template
<
    typename State,
    typename InnerState,
    typename ...Facets
>
class facet_compositor : public Facets...
{
public:
    typedef InnerState                                          inner_state_type;
    typedef typename inner_state_type::sat_type                 sat_type;
    typedef typename inner_state_type::properties_type          properties_type;

    typedef typename sat_type::clause_type                      clause_type;
    typedef typename sat_type::literal_type                     literal_type;
    typedef typename sat_type::variable_type                    variable_type;

    typedef typename properties_type::variable_properties_type  variable_properties_type;
    typedef typename properties_type::literal_properties_type   literal_properties_type;
    typedef typename properties_type::clause_properties_type    clause_properties_type;

public:
    facet_compositor(inner_state_type& inner_state)
        :   Facets(inner_state)...
    {
    }

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
