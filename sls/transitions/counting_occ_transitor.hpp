#ifndef __SSA_COUNTING_OCC_TRANSITOR_HPP__
#define __SSA_COUNTING_OCC_TRANSITOR_HPP__


#include <iostream>
#include <iomanip>
#include <vector>
#include "transitor_base.hpp"


namespace ssa { namespace transitions {


template
<
	typename StateType,
	typename HandlePlus,
	typename HandleMinus
>
class counting_occ_transitor : public transitor_base<StateType>
{
public:
	typedef StateType 							state_type;
	typedef typename state_type::sat_type 		sat_type;
	typedef typename state_type::variable_type	variable_type;
	typedef HandlePlus 							handle_plus_policy;
	typedef HandleMinus 						handle_minus_policy;

private:
	size_t flips_;
	size_t pos_clauses_;
	size_t neg_clauses_;
	std::vector<size_t> pos_trans_;
	std::vector<size_t> neg_trans_;

public:
	counting_occ_transitor()
		:	flips_(0ul),
			pos_clauses_(0ul),
			neg_clauses_(0ul),
			pos_trans_(),
			neg_trans_()
	{
		pos_trans_.resize(1000);
		neg_trans_.resize(1000);
	}

	void operator()(state_type& state, variable_type flip)
	{
		auto const& pos_clauses = state.clauses_by_literal(sat_type::make_literal(flip, state.truth(flip)));

    	for(auto clause : pos_clauses)
    	{
    		++neg_clauses_;
        	++neg_trans_[state.num_true_literals(clause)]; 
        	handle_minus_policy::handle_minus(state, clause, flip);
        }

    	auto const& neg_clauses = state.clauses_by_literal(sat_type::make_literal(flip, !state.truth(flip)));

    	for(auto clause : neg_clauses)
    	{
    		++pos_clauses_;
    		++pos_trans_[state.num_true_literals(clause)];
        	handle_plus_policy::handle_plus(state, clause, flip);
        }

    	state.flip(flip);

    	if(++flips_ % 100000 == 0)
    		print_stats();
	}

	void print_stats()
	{
		std::cout << "-------------------------------------------------------" << std::endl;
		std::cout << "flips : " << flips_ << std::endl;
		std::cout << "avg clauses / flip : " << std::setprecision(4) << static_cast<double>(pos_clauses_ + neg_clauses_) / static_cast<double>(flips_) << std::endl;
		std::cout << "+ : " << static_cast<double>(pos_clauses_) / static_cast<double>(flips_) << std::endl;
		for(auto i = 0ul; i < 1000; ++i)
			if(pos_trans_[i] > 0)
				std::cout << i << "+ : " << static_cast<double>(pos_trans_[i]) / static_cast<double>(pos_clauses_) << std::endl;

		std::cout << "- : " << static_cast<double>(neg_clauses_) / static_cast<double>(flips_) << std::endl;
		for(auto i = 0ul; i < 1000; ++i)
			if(neg_trans_[i] > 0)
				std::cout << i << "- : " << static_cast<double>(neg_trans_[i]) / static_cast<double>(neg_clauses_) << std::endl;
	}
};


} /* transitions */ } /* sls */


#endif