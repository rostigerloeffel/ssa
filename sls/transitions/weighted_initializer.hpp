#ifndef _SLS_TRANSITIONS_WEIGHT_INITIALIZER_BASE_HPP_
#define _SLS_TRANSITIONS_WEIGHT_INITIALIZER_BASE_HPP_


#include <vector>
#include <map>
#include "weighted_initializer_base.hpp"
#include "../frontend/problem_types.hpp"


namespace sls { namespace transitions {


template<typename StateType>
class weighted_initializer : public weighted_initializer_base<StateType>
{
	typedef StateType 							state_type;
    typedef typename state_type::sat_type       sat_type;
	typedef typename state_type::clause_type 	clause_type;
	typedef typename state_type::literal_type	literal_type;
	typedef typename state_type::variable_type	variable_type;

public:
	state_type operator()(sls::frontend::problem const& problem) const
	{
		std::vector<clause_type> clauses;
		clauses.reserve(problem.clauses.size());
		std::map<size_t, size_t> clause_to_weight;

		for(auto prob_clause : problem.clauses)
		{
			std::vector<literal_type> literals;
			literals.reserve(prob_clause.literals.size());

			for(auto literal : prob_clause.literals)
				literals.push_back(
					sat_type::make_literal(
						sat_type::make_variable(std::abs(literal)), 
						(literal > 0 ? true : false)));

			auto clause = sat_type::make_clause(literals.begin(), literals.end());

			clause_to_weight[sat_type::index(clause)] = prob_clause.weight;
			clauses.push_back(clause);
		}

		state_type state(clauses, problem.variable_count);

		for(auto clause : state.clauses())
		{
			state.weight(clause) = clause_to_weight[sat_type::index(clause)];
			state.unsat_sum() += state.weight(clause);
		}

	    // setup unsat-facet (depends on truth-facet)
	    for(auto clause : state.clauses())
	        for(auto literal : clause)
	            if(state.is_sat(literal))
	            {
	                state.inc_num_true_literals(clause);

	                if(state.num_true_literals(clause) == 1)
	                    state.watcher1(clause, literal.variable());
	                else if(state.num_true_literals(clause) == 2)
	                    state.watcher2(clause, literal.variable());
	            }

	    // setup score-facet (depends on truth-facet)
	    for(auto variable : state.variables())
	    {
	        auto positive_literal = sat_type::make_literal(variable, state.truth(variable));
	        auto negative_literal = sat_type::make_literal(variable, !state.truth(variable));

	        for(auto clause : state.clauses_by_literal(positive_literal))
	            if(state.num_true_literals(clause) == 1)
	                state.inc_breakcount(variable, state.weight(clause));

	        for(auto clause : state.clauses_by_literal(negative_literal))
	            if(state.num_true_literals(clause) == 0)
	                state.inc_makecount(variable, state.weight(clause));
	    }

    	return state;
	}
};


} /* transitions */ } /* sls */


#endif