#ifndef __SSA_TRANSITIONS_SIMPLE_INITIALIZER_BASE_HPP__
#define __SSA_TRANSITIONS_SIMPLE_INITIALIZER_BASE_HPP__


#include "initializer_base.hpp"
#include "../frontend/problem_types.hpp"


namespace ssa { namespace transitions {


template<typename StateType>
class simple_initializer : public initializer_base<StateType>
{
	typedef StateType 							state_type;
    typedef typename state_type::sat_type       sat_type;
	typedef typename state_type::clause_type 	clause_type;
	typedef typename state_type::literal_type	literal_type;

public:
	state_type operator()(ssa::frontend::problem const& problem) const
	{
		std::vector<clause_type> clauses;
		clauses.reserve(problem.clauses.size());

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

			clauses.push_back(clause);
		}


		state_type state(clauses, problem.variable_count);


    	typedef decltype(state_type::variable_properties_type::score) score_type;


	    // setup broken-facet (depends on truth-facet)
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
	                state.inc_breakcount(variable, score_type(1));

	        for(auto clause : state.clauses_by_literal(negative_literal))
	            if(state.num_true_literals(clause) == 0)
	                state.inc_makecount(variable, score_type(1));
	    }

    	return state;
	}
};


} /* transitions */ } /* ssa */


#endif