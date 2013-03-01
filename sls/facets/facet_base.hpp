#ifndef _SLS_FACETS_FACET_BASE_HPP_
#define _SLS_FACETS_FACET_BASE_HPP_


#include <vector>


namespace sls { namespace facets {


template
<
    typename State,
	typename InnerState
>
class facet_base
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
    virtual void reset(std::vector<clause_type> const& clauses, size_t variable_count)  {}
    virtual void before_pick(size_t flip)                                               {}
    virtual void after_pick(size_t flip, variable_type variable)                        {}
    virtual void flush()                                                                {}
};


} /* facets */ } /* sls */


#endif
