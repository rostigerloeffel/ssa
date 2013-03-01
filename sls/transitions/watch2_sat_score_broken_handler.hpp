#ifndef __SSA_TRANSITIONS_WATCH2_SAT_SCORE_BROKEN_HANDLER_HPP__
#define __SSA_TRANSITIONS_WATCH2_SAT_SCORE_BROKEN_HANDLER_HPP__


namespace ssa { namespace transitions {


template<typename StateType>
class watch2_sat_score_broken_plus_handler
{
public:
    typedef StateType                           state_type;
    typedef typename state_type::clause_type    clause_type;
    typedef typename state_type::variable_type  variable_type;

public:
    static void handle_plus(StateType& state, typename StateType::clause_type clause, typename StateType::variable_type flip)
    {
        if(state.num_true_literals(clause) == 0)
        {
            state.satisfying(clause) = flip;

            for(auto literal : clause)
                state.dec_makecount(literal.variable(), state.weight(clause));

            state.inc_breakcount(flip, state.weight(clause));
            state.watcher1(clause, flip);
        }
        else if(state.num_true_literals(clause) == 1)
        {
            state.dec_breakcount(state.watcher1(clause), state.weight(clause));
            state.watcher2(clause, flip);
        }

        state.inc_num_true_literals(clause);
    }
};


} /* transitions */ } /* ssa */


#endif
