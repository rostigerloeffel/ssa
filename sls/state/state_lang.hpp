#ifndef _SLS_STATE_STATE_LANG_HPP_
#define _SLS_STATE_STATE_LANG_HPP_


#define SAT_TYPEDEFS(sat) \
    typedef sat 	                         sat_type; \
    typedef typename sat_type::variable_type variable_type; \
    typedef typename sat_type::literal_type  literal_type; \
    typedef typename sat_type::clause_type   clause_type;

#define PROP_TYPEDEFS(props) \
    typedef props                                          		properties_type; \
    typedef typename properties_type::variable_properties_type  variable_properties_type; \
    typedef typename properties_type::literal_properties_type   literal_properties_type; \
    typedef typename properties_type::clause_properties_type    clause_properties_type;

#define STATE_TYPEDEFS(state) \
	typedef state state_type; \
    SAT_TYPEDEFS(typename state_type::sat_type) \
    PROP_TYPEDEFS(typename state_type::properties_type)

#define INNER_STATE_TYPEDEFS(innerstate) \
	typedef InnerState                                  	inner_state_type; \
    typedef typename inner_state_type::variable_store_type 	variable_store_type; \
    typedef typename inner_state_type::literal_store_type  	literal_store_type; \
	typedef typename inner_state_type::clause_store_type   	clause_store_type; \
	SAT_TYPEDEFS(typename inner_state_type::sat_type) \
	PROP_TYPEDEFS(typename inner_state_type::properties_type)

#define DECL_STATE(name, sat, props, facets) \
	typedef sls::state::inner_state<sat, props> name##_inner_state; \
	class name##_state : public sls::state::state_interface<name##_inner_state>, \
						 public facets<name##_state, name##_inner_state> \
	{ \
	public: \
		SAT_TYPEDEFS(sat) \
		PROP_TYPEDEFS(props) \
\
	private: \
		name##_inner_state inner_state_; \
\
	public: \
		name##_state(std::vector<clause_type> const& clauses, size_t variable_count) \
			:	inner_state_(clauses, variable_count), \
				state_interface(inner_state_), \
				facets(inner_state_) \
		{ \
			reset(clauses, variable_count); \
		} \
	};


#endif
