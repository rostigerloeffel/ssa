#ifndef _SLS_FACETS_FACET_HPP_
#define _SLS_FACETS_FACET_HPP_


#include "../state/state_lang.hpp"


#define begin_facet(name, ...) \
	template \
	< \
		typename State, \
		typename InnerState, \
	    ##__VA_ARGS__ \
	> \
	struct name##_facet : public facet_base<State, InnerState> \
	{ \
		INNER_STATE_TYPEDEFS(InnerState)

#define facet_constr(name, ...) \
	public: \
		name##_facet() \
			:	__VA_ARGS__ \
	    {}

#define end_facet \
	};


#endif