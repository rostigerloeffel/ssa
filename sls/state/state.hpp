#ifndef _SLS_STATE_STATE_HPP_
#define _SLS_STATE_STATE_HPP_


#include "inner_state.hpp"


namespace sls { namespace state {


#define DECL_STATE(name, sat, props, facets) \
	typedef inner_state<sat, props> name##_inner_state; \ 
	struct name##_state : public facets<name##_state, name##_inner_state> {};


} /* state */ } /* sls */


#endif