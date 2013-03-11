#ifndef __SSA_REWEIGHT_REWEIGHT_UTIL_HPP__
#define __SSA_REWEIGHT_REWEIGHT_UTIL_HPP__


namespace ssa { namespace reweight {


template<typename StateType>
void inc_clause_weight(StateType& state, typename StateType::clause_type clause, int inc)
{
    if(state.num_true_literals(clause) == 0)
        for(auto literal : clause)
            state.inc_makecount(literal.variable(), inc);
    else if(state.num_true_literals(clause) == 1)
        state.inc_breakcount(state.watcher1(clause), inc);

    state.inc_weight(clause, inc);
}

template<typename StateType>
void dec_clause_weight(StateType& state, typename StateType::clause_type clause, int dec)
{
    // If the clause is broken we have to decrease the score of all contained variables
    if(state.num_true_literals(clause) == 0)
    //if(state.watcher1(clause) == sat_type::variable_type::null())
        for(auto literal : clause)
            state.dec_makecount(literal.variable(), dec);
    // Else if the clause was unit before we have to increase the score of watcher1
    else if(state.num_true_literals(clause) == 1)
    //else if(state.watcher2(clause) == sat_type::variable_type::null())
        state.dec_breakcount(state.watcher1(clause), dec);

    state.dec_weight(clause, dec);
}


} /* reweight */ } /* ssa */


#endif