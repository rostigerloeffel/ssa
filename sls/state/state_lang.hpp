#ifndef _SLS_STATE_STATE_LANG_HPP_
#define _SLS_STATE_STATE_LANG_HPP_


#include <type_traits>


namespace {

template<class T> struct is_base_type_const                 : std::false_type {};
template<class T> struct is_base_type_const<T const>        : std::true_type {};
template<class T> struct is_base_type_const<T const*>       : std::true_type {};
template<class T> struct is_base_type_const<T const* const> : std::true_type {};
template<class T> struct is_base_type_const<T const&>       : std::true_type {};
template<class T> struct is_base_type_const<T* const>       : std::false_type {};

} /* unnamed */

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

#define INNER_STATE_TYPEDEFS(innerstate) \
	typedef innerstate                                  	inner_state_type; \
    typedef typename inner_state_type::variable_store_type 	variable_store_type; \
    typedef typename inner_state_type::literal_store_type  	literal_store_type; \
	typedef typename inner_state_type::clause_store_type   	clause_store_type; \
	SAT_TYPEDEFS(typename inner_state_type::sat_type) \
	PROP_TYPEDEFS(typename inner_state_type::properties_type)

#define STATE_TYPEDEFS(state) \
	typedef state state_type; \
	INNER_STATE_TYPEDEFS(typename state_type::inner_state_type)

#define get_inner_state \
	(static_cast< \
		typename std::conditional< \
        	is_base_type_const<decltype(*this)>::value, \
		State const* const, \
		State* const>::type>(this)->inner_state())

#endif
