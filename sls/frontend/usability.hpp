#ifndef _SLS_FRONTEND_USABILITY_HPP_
#define _SLS_FRONTEND_USABILITY_HPP_


#include "../state/state_lang.hpp"


#define NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, N, ...) N
#define NARGS(...) NARGS_IMPL(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)


#define UNROLL_PROP_1(p1) public sls::properties::p1
#define UNROLL_PROP_2(p1, p2) UNROLL_PROP_1(p1), UNROLL_PROP_1(p2)
#define UNROLL_PROP_3(p1, p2, p3) UNROLL_PROP_1(p1), UNROLL_PROP_2(p2, p3)
#define UNROLL_PROP_4(p1, p2, p3, p4) UNROLL_PROP_1(p1), UNROLL_PROP_3(p2, p3, p4)
#define UNROLL_PROP_5(p1, p2, p3, p4, p5) UNROLL_PROP_1(p1), UNROLL_PROP_4(p2, p3, p4, p5)
#define UNROLL_PROP_6(p1, p2, p3, p4, p5, p6) UNROLL_PROP_1(p1), UNROLL_PROP_5(p2, p3, p4, p5, p6)
#define UNROLL_PROP_7(p1, p2, p3, p4, p5, p6, p7) UNROLL_PROP_1(p1), UNROLL_PROP_6(p2, p3, p4, p5, p6, p7)
#define UNROLL_PROP_8(p1, p2, p3, p4, p5, p6, p7, p8) UNROLL_PROP_1(p1), UNROLL_PROP_7(p2, p3, p4, p5, p6, p7, p8)
#define UNROLL_PROP_9(p1, p2, p3, p4, p5, p6, p7, p8, p9) UNROLL_PROP_1(p1), UNROLL_PROP_8(p2, p3, p4, p5, p6, p7, p8, p9)
#define UNROLL_PROP_10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) UNROLL_PROP_1(p1), UNROLL_PROP_9(p2, p3, p4, p5, p6, p7, p8, p9, p10)

#define UNROLL_PROP_N_2(n, ...) UNROLL_PROP_##n(__VA_ARGS__)
#define UNROLL_PROP_N(n, ...) UNROLL_PROP_N_2(n, __VA_ARGS__)
#define UNROLL_PROP(...) UNROLL_PROP_N(NARGS(__VA_ARGS__), __VA_ARGS__)


#define UNROLL_FACETS_1(f1) sls::facets::f1##_facet<State, InnerState>
#define UNROLL_FACETS_2(f1, f2) UNROLL_FACETS_1(f1), UNROLL_FACETS_1(f2)
#define UNROLL_FACETS_3(f1, f2, f3) UNROLL_FACETS_1(f1), UNROLL_FACETS_2(f2, f3)
#define UNROLL_FACETS_4(f1, f2, f3, f4) UNROLL_FACETS_1(f1), UNROLL_FACETS_3(f2, f3, f4)
#define UNROLL_FACETS_5(f1, f2, f3, f4, f5) UNROLL_FACETS_1(f1), UNROLL_FACETS_4(f2, f3, f4, f5)
#define UNROLL_FACETS_6(f1, f2, f3, f4, f5, f6) UNROLL_FACETS_1(f1), UNROLL_FACETS_5(f2, f3, f4, f5, f6)
#define UNROLL_FACETS_7(f1, f2, f3, f4, f5, f6, f7) UNROLL_FACETS_1(f1), UNROLL_FACETS_6(f2, f3, f4, f5, f6, f7)
#define UNROLL_FACETS_8(f1, f2, f3, f4, f5, f6, f7, f8) UNROLL_FACETS_1(f1), UNROLL_FACETS_7(f2, f3, f4, f5, f6, f7, f8)
#define UNROLL_FACETS_9(f1, f2, f3, f4, f5, f6, f7, f8, f9) UNROLL_FACETS_1(f1), UNROLL_FACETS_8(f2, f3, f4, f5, f6, f7, f8, f9)
#define UNROLL_FACETS_10(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10) UNROLL_FACETS_1(f1), UNROLL_FACETS_9(f2, f3, f4, f5, f6, f7, f8, f9, f10)

#define UNROLL_FACETS_N_2(n, ...) UNROLL_FACETS_##n(__VA_ARGS__)
#define UNROLL_FACETS_N(n, ...) UNROLL_FACETS_N_2(n, __VA_ARGS__)
#define UNROLL_FACETS(...) UNROLL_FACETS_N(NARGS(__VA_ARGS__), __VA_ARGS__)

#define declare_sat_backend(sat_decl) \
	typedef ::sls::sat::sat_decl sat_type;

#define declare_properties(variables, literals, clauses) \
	struct properties \
	{ \
    	variables literals clauses \
	};

#define variable_props(...) \
    struct variable_properties_type : UNROLL_PROP(__VA_ARGS__) {};
#define literal_props(...) \
    struct literal_properties_type : UNROLL_PROP(__VA_ARGS__) {};
#define clause_props(...) \
    struct clause_properties_type : UNROLL_PROP(__VA_ARGS__) {};

#define declare_facets(...) \
	template<typename State, typename InnerState> \
	using facets = sls::facets::facet_compositor< \
	    State, InnerState, \
	    UNROLL_FACETS(__VA_ARGS__) \
	>;

#define declare_state(name, sat_decl, prop_decl, facets_decl) \
	namespace name { \
	sat_decl prop_decl facets_decl \
	typedef ::sls::state::inner_state<sat_type, properties> inner_state_t; \
	struct state : public ::sls::state::state_interface<state, inner_state_t>, \
				   public facets<state, inner_state_t> \
	{ \
		INNER_STATE_TYPEDEFS(inner_state_t) \
\
		inner_state_type inner_state_; \
\
		state(std::vector<clause_type> const& clauses, size_t variable_count) \
			:	inner_state_(clauses, variable_count) \
		{ \
			::sls::state::state_interface<state, inner_state_t>::prepare(); \
			facets<state, inner_state_t>::reset(clauses, variable_count); \
		} \
		inline inner_state_type& inner_state() \
		{ \
			return inner_state_; \
		} \
		inline inner_state_type const& inner_state() const \
		{ \
			return inner_state_; \
		} \
	}; \
	}


#endif