#ifndef __SSA_SOLVERS_WEIGHTED_MAXSAT_HPP__
#define __SSA_SOLVERS_WEIGHTED_MAXSAT_HPP__


#include "solver_base.hpp"
#include "../selectors/selector_base.hpp"
#include "../transitions/weighted_initializer_base.hpp"
#include "../transitions/transitor_base.hpp"
#include "../frontend/problem_types.hpp"


namespace ssa { namespace solvers {


template<typename StateType>
class weighted_maxsat : public solver_base
{
public:
	typedef StateType 							state_type;
	typedef typename state_type::sat_type 		sat_type;
	typedef typename sat_type::variable_type	variable_type;
	typedef typename sat_type::literal_type		literal_type;
	typedef typename sat_type::clause_type		clause_type;

private:
	ssa::frontend::problem		 								problem_;
	double														maxtime_;
	ssa::transitions::weighted_initializer_base<state_type>&	initializer_;
	ssa::transitions::transitor_base<state_type>&				transitor_;
	sls::selectors::selector_base<state_type>* const			selector_;

public:
	weighted_maxsat(
		ssa::frontend::problem const& problem,
		double maxtime,
		ssa::transitions::weighted_initializer_base<state_type>& initializer,
		ssa::transitions::transitor_base<state_type>& transitor,
		sls::selectors::selector_base<state_type>* const selector)
		: 	
			problem_(problem),
			maxtime_(maxtime),
			initializer_(initializer),
			transitor_(transitor),
			selector_(selector)
	{}

	std::vector<int> solve()
	{
		auto start = std::clock();
		auto end = std::clock();
	    auto time = static_cast<double>(end - start) / static_cast<double>(CLOCKS_PER_SEC);
	    
	    auto flips = 0;
	    auto state = initializer_(problem_);

	    auto current_optimum_sum = problem_.top_weight;

	    std::cout << "c top-weight = " << problem_.top_weight << std::endl;

	    while(!sls::util::is_interrupted() && state.unsat().size() > 0 && time < maxtime_)
	    {
	        state.before_pick(flips);
	        selector_->before_pick(state);

	        selector_->is_applicable(state);
	        auto pick = selector_->select(state);

	        ++flips;
	        state.after_pick(flips, pick);

			transitor_(state, pick);

	        state.flush();

	        time = static_cast<double>(end - start) / static_cast<double>(CLOCKS_PER_SEC);

	        if(state.unsat_sum() < current_optimum_sum)
	        {
	        	current_optimum_sum = state.unsat_sum();
	        	std::cout << "o " << current_optimum_sum << std::endl;
	        	// do some fancy stuff to keep current assignment
	        }
	    }

	    std::cout 
            << "c " 
            << flips << "," 
            << (!sls::util::is_interrupted() ? time : -time) << "," 
            << static_cast<int>(static_cast<double>(flips)/time) << std::endl;

        if(sls::util::is_interrupted())
        	exit(0);

	    std::vector<int> model(state.variables().size());
	    for(auto i = 0; i < state.variables().size(); ++i)
	    	model[i] = (i + 1) * (static_cast<int>(state.truth(sat_type::make_variable(i + 1))) * 2 - 1);

	    return model;
	}
};


} /* solvers */ } /* ssa */


#endif