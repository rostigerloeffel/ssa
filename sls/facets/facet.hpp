#ifndef _SLS_FACETS_FACET_HPP_
#define _SLS_FACETS_FACET_HPP_


#define begin_facet(name, ...) \
	#define facet_name name \
	template \
	< \
		typename State, \
	    typename InnerState, \
	    ##__VA_ARGS__ \
	> \
	class name##_facet : public facet_base<State, InnerState> \
	{ \
	public: \
		typedef State 												state_type; \
\
	    typedef InnerState                                          inner_state_type; \
	    typedef typename inner_state_type::sat_type                 sat_type; \
	    typedef typename inner_state_type::properties_type          properties_type; \
\
	    typedef typename sat_type::clause_type                      clause_type; \
	    typedef typename sat_type::literal_type                     literal_type; \
	    typedef typename sat_type::variable_type                    variable_type; \
\
	    typedef typename properties_type::variable_properties_type  variable_properties_type; \
	    typedef typename properties_type::literal_properties_type   literal_properties_type; \
	    typedef typename properties_type::clause_properties_type    clause_properties_type; \
\
	private: \
	    inner_state_type& inner_state_;
	    
#define facet_constr(name, ...) \
	public: \
		name##_facet(inner_state_type& inner_state) \
			:	inner_state_(inner_state), ##__VA_ARGS__ \
	    { \
	    }

#define end_facet \
	#undef facet_name \ 
	};

#define state (*static_cast<State*>(this))


#endif