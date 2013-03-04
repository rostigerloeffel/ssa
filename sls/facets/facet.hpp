#ifndef _SLS_FACETS_FACET_HPP_
#define _SLS_FACETS_FACET_HPP_


#include "../state/state_lang.hpp"


#define begin_facet(name, ...) \
	template \
	< \
		typename State, \
	    ##__VA_ARGS__ \
	> \
	struct name##_facet : public facet_base<State> \
	{ \
		STATE_TYPEDEFS(State)


#define facet_constr(name, ...) \
	public: \
		name##_facet() \
			:	__VA_ARGS__ \
	    { \
	    }

#define end_facet \
	};

#define this_state (*static_cast<State*>(this))


#endif