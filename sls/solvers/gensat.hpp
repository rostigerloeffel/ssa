#ifndef _SLS_SOLVERS_GENSAT_HPP_
#define _SLS_SOLVERS_GENSAT_HPP_


#include <unistd.h>
#include <cassert>
#include <ctime>
#include "solver_base.hpp"
#include "../util/signal.hpp"
#include "../selectors/selector_base.hpp"
#include "../transitions/initializer_base.hpp"
#include "../transitions/transitor_base.hpp"
#include "../frontend/problem_types.hpp"


namespace sls { namespace solvers {


template<typename StateType>
class gensat : public solver_base
{
public:
	typedef StateType 							state_type;
	typedef typename state_type::sat_type 		sat_type;
	typedef typename sat_type::variable_type	variable_type;
	typedef typename sat_type::literal_type		literal_type;
	typedef typename sat_type::clause_type		clause_type;

private:
	sls::frontend::problem		 						problem_;
	sls::transitions::initializer_base<state_type>&		initializer_;
	sls::transitions::transitor_base<state_type>&		transitor_;
	sls::selectors::selector_base<state_type>* const	selector_;

public:
	gensat(
		sls::frontend::problem const& problem,	
		sls::transitions::initializer_base<state_type>& initializer,
		sls::transitions::transitor_base<state_type>& transitor,
		sls::selectors::selector_base<state_type>* const selector)
		: 	problem_(problem),
			initializer_(initializer),
			transitor_(transitor),
			selector_(selector)
	{
	}

	std::vector<int> solve()
	{
	    auto start = std::clock();

	    auto state = initializer_(problem_);
		auto flips = 0;

	    auto end = std::clock();
	    auto time = static_cast<double>(end - start) / static_cast<double>(CLOCKS_PER_SEC);

	    std::cerr << "c initialization time : " << time << std::endl;

	    start = std::clock();

	    while(!sls::util::is_interrupted() && state.unsats().size() > 0 && flips < 2000000000)
	    {
	        state.before_pick(flips);
	        selector_->before_pick(state);

	        selector_->is_applicable(state);
	        auto pick = selector_->select(state);

	        ++flips;
	        state.after_pick(flips, pick);

			transitor_(state, pick);

	        state.flush();
	    }


	    end = std::clock();
	    time = static_cast<double>(end - start) / static_cast<double>(CLOCKS_PER_SEC);

	    std::cout 
            << "c "
            << state.variables().size() << ","
            << state.clauses().size() << ","
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


} /* solvers */ } /* sls */


#endif