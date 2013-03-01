#ifndef __SSA_TRANSITIONS_WATCH1_SCORE_BROKEN_HANDLER_HPP__
#define __SSA_TRANSITIONS_WATCH1_SCORE_BROKEN_HANDLER_HPP__


namespace ssa { namespace transitions {


template<typename StateType>
class watch1_score_broken_minus_handler
{
public:
    typedef StateType                           state_type;
    typedef typename state_type::clause_type    clause_type;
    typedef typename state_type::variable_type  variable_type;

public:
    static void handle_minus(StateType& state, typename StateType::clause_type clause, typename StateType::variable_type flip)
    {
        if(state.num_true_literals(clause) == 1)
        {       
            for(auto literal : clause)
                state.inc_makecount(literal.variable(), state.weight(clause));

            state.dec_breakcount(flip, state.weight(clause));
        }
        else if(state.num_true_literals(clause) == 2)
        {
            for(auto literal : clause)
                if(state.is_sat(literal) &&
                   literal.variable() != flip)
                {
                    state.watcher1(clause, literal.variable());
                    break;
                }

            state.inc_breakcount(state.watcher1(clause), state.weight(clause));
        }

        state.dec_num_true_literals(clause);
    }
};


template<typename StateType>
class watch1_score_broken_plus_handler
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
            for(auto literal : clause)
                state.dec_makecount(literal.variable(), state.weight(clause));

            state.inc_breakcount(flip, state.weight(clause));
            state.watcher1(clause, flip);
        }
        else if(state.num_true_literals(clause) == 1)
            state.dec_breakcount(state.watcher1(clause), state.weight(clause));

        state.inc_num_true_literals(clause);
    }
};


} /* transitions */ } /* ssa */


#endif
