#ifndef _SLS_FACETS_SIGNALS_HPP_
#define _SLS_FACETS_SIGNALS_HPP_


#define nargs_impl(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, N, ...) N
#define nargs(...) nargs_impl(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define tv1(t1) t1 var1
#define tv2(t1, t2) tv1(t1), t2 var2
#define tv3(t1, t2, t3) tv2(t1, t2), t3 var3
#define tv4(t1, t2, t3, t4) tv3(t1, t2, t3), t4 var4
#define tv5(t1, t2, t3, t4, t5) tv3(t1, t2, t3, t4), t5 var5
#define type_var_decl_n_2(count, ...) tv##count(__VA_ARGS__)
#define type_var_decl_n(count, ...) type_var_decl_n_2(count, __VA_ARGS__)
#define type_var_decl(...) type_var_decl_n(nargs(__VA_ARGS__), __VA_ARGS__)

#define v1(t1) var1
#define v2(t1, t2) v1(t1), var2
#define v3(t1, t2, t3) v2(t1, t2), var3
#define v4(t1, t2, t3, t4) v3(t1, t2, t3), var4
#define v5(t1, t2, t3, t4, t5) v4(t1, t2, t3, t4), var5
#define var_decl_n_2(count, ...) v##count(__VA_ARGS__)
#define var_decl_n(count, ...) var_decl_n_2(count, __VA_ARGS__)
#define var_decl(...) var_decl_n(nargs(__VA_ARGS__), __VA_ARGS__)

#define facet_signal(message, listener, ...) \
    inline void send_##message(type_var_decl(__VA_ARGS__)) \
    { \
        send_##message<listener...>(var_decl(__VA_ARGS__)); \
    } \
    template<typename listener##1> \
    inline void send_##message(type_var_decl(__VA_ARGS__)) \
    { \
       static_cast<listener##1*>(static_cast<State*>(this))->on_##message(var_decl(__VA_ARGS__)); \
    } \
    template<typename listener##1, typename listener##2, typename ...listener##Others> \
    inline void send_##message(type_var_decl(__VA_ARGS__)) \
    { \
       static_cast<listener##1*>(static_cast<State*>(this))->on_##message(var_decl(__VA_ARGS__)); \
       send_##message<listener##2, listener##Others...>(var_decl(__VA_ARGS__)); \
    }

#define send_signal(message, ...) send_##message(__VA_ARGS__)

#define gt1(t1) typename Type1
#define gt2(t1, t2) gt1(t1), typename Type2
#define gt3(t1, t2, t3) gt2(t1, t2), typename Type3
#define gt4(t1, t2, t3, t4) gt3(t1, t2, t3), typename Type4
#define gt5(t1, t2, t3, t4, t5) gt4(t1, t2, t3, t4), typename Type5
#define gen_type_decl_n_2(count, ...) gt##count(__VA_ARGS__)
#define gen_type_decl_n(count, ...) gen_type_decl_n_2(count, __VA_ARGS__)
#define gen_type_decl(...) gen_type_decl_n(nargs(__VA_ARGS__), __VA_ARGS__)

#define gtv1(v1) Type1 v1
#define gtv2(v1, v2) gtv1(v1), Type2 v2
#define gtv3(v1, v2, v3) gtv2(v1, v2), Type3 v3
#define gtv4(v1, v2, v3, v4) gtv3(v1, v2, v3), Type4 v4
#define gtv5(v1, v2, v3, v4, v5) gtv4(v1, v2, v3, v4), Type5 v5
#define gen_type_var_decl_n_2(count, ...) gtv##count(__VA_ARGS__)
#define gen_type_var_decl_n(count, ...) gen_type_var_decl_n_2(count, __VA_ARGS__)
#define gen_type_var_decl(...) gen_type_var_decl_n(nargs(__VA_ARGS__), __VA_ARGS__)

#define facet_slot(message, ...) \
    template<gen_type_decl(__VA_ARGS__)> \
    inline void on_##message(gen_type_var_decl(__VA_ARGS__))        


#endif
