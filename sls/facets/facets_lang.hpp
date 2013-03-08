#ifndef _SLS_FACETS_FACET_LANG_HPP_
#define _SLS_FACETS_FACET_LANG_HPP_

/*
#define NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, N, ...) N
#define NARGS(...) NARGS_IMPL(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define UNROLL_FACETS_1(f1) sls::facets::f1<State, InnerState>
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

#define DECL_FACETS(name, ...) \
	template<typename State, typename InnerState> \
	using facets = sls::facets::facet_compositor< \
	    State, InnerState, \
	    UNROLL_FACETS(__VA_ARGS__) \
	>;*/


#endif