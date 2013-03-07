#ifndef _SLS_PROPERTIES_PROPERTIES_LANG_
#define _SLS_PROPERTIES_PROPERTIES_LANG_

#define DECL_PROPERTIES(name, variables, literals, clauses) \
	namespace name { \
	struct properties \
	{ \
    	variables literals clauses \
	}; \
	}

#define NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, N, ...) N
#define NARGS(...) NARGS_IMPL(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define UNROLL1(p1) public sls::properties::p1
#define UNROLL2(p1, p2) UNROLL1(p1), UNROLL1(p2)
#define UNROLL3(p1, p2, p3) UNROLL1(p1), UNROLL2(p2, p3)
#define UNROLL4(p1, p2, p3, p4) UNROLL1(p1), UNROLL3(p2, p3, p4)
#define UNROLL5(p1, p2, p3, p4, p5) UNROLL1(p1), UNROLL4(p2, p3, p4, p5)
#define UNROLL6(p1, p2, p3, p4, p5, p6) UNROLL1(p1), UNROLL5(p2, p3, p4, p5, p6)
#define UNROLL7(p1, p2, p3, p4, p5, p6, p7) UNROLL1(p1), UNROLL6(p2, p3, p4, p5, p6, p7)
#define UNROLL8(p1, p2, p3, p4, p5, p6, p7, p8) UNROLL1(p1), UNROLL7(p2, p3, p4, p5, p6, p7, p8)
#define UNROLL9(p1, p2, p3, p4, p5, p6, p7, p8, p9) UNROLL1(p1), UNROLL8(p2, p3, p4, p5, p6, p7, p8, p9)
#define UNROLL10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) UNROLL1(p1), UNROLL9(p2, p3, p4, p5, p6, p7, p8, p9, p10)

#define UNROLL_PROP_N_2(n, ...) UNROLL##n(__VA_ARGS__)
#define UNROLL_PROP_N(n, ...) UNROLL_PROP_N_2(n, __VA_ARGS__)
#define UNROLL_PROP(...) UNROLL_PROP_N(NARGS(__VA_ARGS__), __VA_ARGS__)

#define VAR(...) \
    struct variable_properties_type : UNROLL_PROP(__VA_ARGS__) {};
#define LIT(...) \
    struct literal_properties_type : UNROLL_PROP(__VA_ARGS__) {};
#define CLAUSE(...) \
    struct clause_properties_type : UNROLL_PROP(__VA_ARGS__) {};

#endif