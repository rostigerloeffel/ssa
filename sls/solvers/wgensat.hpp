#ifndef __SLS_SOLVERS_WGENSAT_HPP__
#define __SLS_SOLVERS_WGENSAT_HPP__


#include "solver_base.hpp"
#include "../selectors/selector_base.hpp"
#include "../transitions/initializer_base.hpp"
#include "../transitions/transitor_base.hpp"

#include <unistd.h>
#include <cassert>


namespace sls
{


namespace solvers
{


template
<
	typename StateType
>
class wgensat : public solver_base
{
public:
	typedef StateType 							state_type;
	typedef typename state_type::sat_type 		sat_type;
	typedef typename sat_type::variable_type	variable_type;
	typedef typename sat_type::literal_type		literal_type;
	typedef typename sat_type::clause_type		clause_type;

private:
	std::vector<clause_type> 							clauses_;
	size_t												variable_count_;
	sls::transitions::initializer_base<state_type>&		initializer_;
	sls::transitions::transitor_base<state_type>&		transitor_;
	sls::selectors::selector_base<state_type>* const	selector_;

public:
	wgensat(
		std::vector<clause_type> const& clauses, 
		size_t variable_count,
		sls::transitions::initializer_base<state_type>& initializer,
		sls::transitions::transitor_base<state_type>& transitor,
		sls::selectors::selector_base<state_type>* const selector)
		: 	clauses_(clauses),
			variable_count_(variable_count),
			initializer_(initializer),
			transitor_(transitor),
			selector_(selector)
	{
	}

	std::vector<int> solve()
	{
		auto flips = 0;
	    auto start = std::clock();

	    auto state = initializer_(clauses_, variable_count_);

	    while(!sls::util::is_interrupted() && state.unsat().size() > 0)
	    {
	    	
	    	
	        state.before_pick(flips);

	        selector_->is_applicable(state);
	        auto pick = selector_->select(state);

	        ++flips;
	        state.after_pick(flips, pick);

			transitor_(state, pick);

	        state.flush();
	    }


	    auto end = std::clock();
	    auto time = static_cast<double>(end - start) / static_cast<double>(CLOCKS_PER_SEC);

	    std::cout 
            << "c " 
            << variable_count_ << "," 
            << clauses_.size() << "," 
            << flips << "," 
            << (!sls::util::is_interrupted() ? time : -1.0) << "," 
            << static_cast<int>(static_cast<double>(flips)/time) << std::endl;

	    std::vector<int> model(variable_count_);
	    for(auto i = 0; i < variable_count_; ++i)
	    	model[i] = (i + 1) * (static_cast<int>(state.truth(sat_type::make_variable(i + 1))) * 2 - 1);

	    return model;
	}
};


} /* solvers */


} /* sls */


#endif