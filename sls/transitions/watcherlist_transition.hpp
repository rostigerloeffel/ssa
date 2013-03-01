#ifndef __SSA_TRANSITIONS_WATCHERLIST_TRANSITION_HPP__
#define __SSA_TRANSITIONS_WATCHERLIST_TRANSITION_HPP__


namespace ssa { namespace transitions { 

namespace internal {

/*
template<typename StateType>
void _becomes_sat_wl(StateType& state, typename StateType::clause_type clause, typename StateType::variable_type flip) __attribute__((noinline));
template<typename StateType>
void _becomes_unsat_wl(StateType& state, typename StateType::clause_type clause, typename StateType::variable_type flip) __attribute__((noinline));
*/

template<typename StateType>
void _becomes_unsat_wl(StateType& state, typename StateType::clause_type clause, typename StateType::variable_type flip)
{
    typedef typename StateType::sat_type sat_type;
/*
    std::cout << "u " << clause 
        << " " << (state.watcher2(clause) != sat_type::variable_type::null() ? 2 : 1) << std::endl;
*/
    if(state.watcher1(clause) == flip)
        state.watcher1(clause, state.watcher2(clause));


    // We have at least two satisfied literals
    if(state.watcher2(clause) != sat_type::variable_type::null())
    {
        state.watcher2(clause, sat_type::variable_type::null());

        for(auto literal : clause)
            if(state.is_sat(literal) &&
                literal.variable() != flip &&
                literal.variable() != state.watcher1(clause))
            {
                state.watcher2(clause, literal.variable());
                state.watcherlist(literal.variable()).push_back(clause);
                break;
            }
    }


    if(state.watcher1(clause) == sat_type::variable_type::null())
    {       
        for(auto literal : clause)
            state.inc_score(literal.variable(), state.weight(clause));

        state.inc_score(flip, state.weight(clause));

        state.broken().push_back(clause);
    }
    else if(state.watcher2(clause) == sat_type::variable_type::null())
        state.dec_score(state.watcher1(clause), state.weight(clause));
}


template<typename StateType>
void _becomes_sat_wl(StateType& state, typename StateType::clause_type clause, typename StateType::variable_type flip)
{
    typedef typename StateType::sat_type sat_type;

 /*   
    std::cout << "s " << clause << " " 
        << (int(state.watcher1(clause) != sat_type::variable_type::null()) +
            int(state.watcher2(clause) != sat_type::variable_type::null()))

    << std::endl;
*/


    if(state.watcher1(clause) == sat_type::variable_type::null())
    {
        for(auto literal : clause)
            state.dec_score(literal.variable(), state.weight(clause));
        state.dec_score(flip, state.weight(clause));

        state.watcher1(clause, flip);
        state.watcherlist(flip).push_back(clause);

        state.broken().remove(clause);
    }
    else if(state.watcher2(clause) == sat_type::variable_type::null())
    {
        state.inc_score(state.watcher1(clause), state.weight(clause));

        state.watcher2(clause, flip);
        state.watcherlist(flip).push_back(clause);
    }
}


} /* internal */


template<typename StateType>
void transit_wl(StateType& state, typename StateType::variable_type flip)
{
    typedef StateType state_type;
    typedef typename state_type::sat_type sat_type;

    auto const& watched_clauses = state.watcherlist(flip);
/*
std::cout 
    << "old=" 
    << state.watcherlist(flip).size() << std::endl;

std::cout << "current " << (state.truth(flip) ? "" : "-") << flip << " score=" << state.score(flip) << std::endl;
*/
/*
static size_t flips = 0;
static size_t watched_size = 0;
static size_t all_size = 0;

    watched_size += watched_clauses.size();
    all_size += state.clauses_by_literal(sat_type::make_literal(flip, state.truth(flip))).size();
    ++flips;

    if(flips % 100000 == 0)
        std::cout << watched_size / double(all_size) << std::endl;
*/

    for(auto clause : watched_clauses)
        internal::_becomes_unsat_wl(state, clause, flip);

    state.erase_watcherlist(flip);
/*
std::cout << "new=" << state.watcherlist(flip).size() << std::endl;
std::cout << "now " << (state.truth(flip) ? "" : "-") << flip << " score=" << state.score(flip) << std::endl;
*/
    auto const& neg_clauses = state.clauses_by_literal(sat_type::make_literal(flip, !state.truth(flip)));

    for(auto clause : neg_clauses)
        internal::_becomes_sat_wl(state, clause, flip);
/*
std::cout << "new=" << state.watcherlist(flip).size() << std::endl;
std::cout << "now 2 " << (state.truth(flip) ? "" : "-") << flip << " score=" << state.score(flip) << std::endl;
*/
    state.flip(flip);
}


} /* transitions */ } /* ssa */


#endif
