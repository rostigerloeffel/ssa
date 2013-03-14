#ifndef _SLS_FACETS_GREEDY_ACCESSOR_FACET_HPP_
#define _SLS_FACETS_GREEDY_ACCESSOR_FACET_HPP_


#include "facet_base.hpp"


namespace sls { namespace facets {


namespace {

struct null_type {};

template<unsigned int N, typename ...Args>
struct get_nth;
 
template<typename Arg, typename ...Args>
struct get_nth<1, Arg, Args...>
{ 
	typedef Arg type; 
};
 
template<unsigned int N>
struct get_nth<N>
{ 
	typedef null_type type; 
};
 
template<unsigned int N, typename Arg, typename ...Args>
struct get_nth<N, Arg, Args...>
{ 
	typedef typename get_nth<N - 1, Args...>::type type; 
};

} /* unnamed */


template<
	typename State,
    typename InnerState,
    typename ...GreedyFacets
>
class greedy_accessor_facet : public facet_base<State, InnerState> //: public GreedyFacets...
{
public: 
	INNER_STATE_TYPEDEFS(InnerState)

    typedef decltype(variable_properties_type::score) score_type;

    template<unsigned int N>
    inline bool has_greedy_nth() const
    {
    	return static_cast<
    		typename get_nth<N, GreedyFacets...>::type const* const>(
    			static_cast<State const* const>(this))->has_greedy();      
	}

    template<unsigned int N>
    inline variable_type most_greedy_nth() const
    {
    	return static_cast<
    		typename get_nth<N, GreedyFacets...>::type const* const>(
    			static_cast<State const* const>(this))->most_greedy();      
    }
};


} /* facets */ } /* sls */


#endif