#ifndef _SLS_FACETS_GREEDY_SCORE_TCC_FACET_HPP_
#define _SLS_FACETS_GREEDY_SCORE_TCC_FACET_HPP_


#include <vector>
#include <algorithm>
#include "facet.hpp"
#include "signals.hpp"
#include "facet_base.hpp"
#include "comparators.hpp"
#include "../storage/mutable_priority_queue.hpp"
#include "../storage/random_access_list.hpp"


namespace sls { namespace facets {


begin_facet(greedy_score_tcc,
    typename Comparator,
    typename TccStoreType = sls::storage::random_access_list<typename InnerState::variable_type>)

    typedef decltype(variable_properties_type::score)   score_type;
    typedef decltype(variable_properties_type::tcc)     tcc_type;

    typedef Comparator                                  comparator_type;

    typedef sls::storage::mutable_priority_queue<
                variable_type, 
                comparator_type>                        greedy_store_type;

private:
    greedy_store_type   greedy_; 

public:
    facet_constr(greedy_score_tcc, greedy_(0, {get_inner_state}))

    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
	    greedy_.resize(variable_count);
    }

    inline bool has_greedy() const
    {
        return !greedy_.empty();
    }

    inline variable_type most_greedy() const
    {
        return greedy_.top();
    }

    facet_slot(tcc_inc, variable, diff)
    {
        if(tcc(variable) == tcc_type(1) && 
           score(variable) > score_type(0))
            greedy_.push(variable);

        if(greedy_.contains(variable))
            greedy_.update_after_inc(variable);
    }

    facet_slot(tcc_dec, variable, diff)
    {
        std::cerr << "not implemented yet!" << std::endl;
    }

    facet_slot(tcc_reset, variable)
    {
        if(greedy_.contains(variable))
            greedy_.update_after_dec(variable);
    }

    facet_slot(score_inc, variable, diff)
    {
        if(this_state.score(variable) > score_type(0) && 
           this_state.score(variable) <= diff)   
        {
            if(this_state.tcc(variable) > tcc_type(0))
                greedy_.push(variable);
        }
        else if(greedy_.contains(variable))
            greedy_.update_after_inc(variable);
    }

    facet_slot(score_dec, variable, diff)
    {
        if(greedy_.contains(variable))
        {
            if(this_state.score(variable) <= score_type(0))
                greedy_.remove(variable);
            else
                greedy_.update_after_dec(variable);
        }
    }
};


template<typename State, typename InnerState>
using greedy_score_tcc_age_facet = greedy_score_tcc_facet<State, InnerState, sls::comparators::score_tcc_age<InnerState>>;

template<typename State, typename InnerState>
using greedy_score_tcc_rand_facet = greedy_score_tcc_facet<State, InnerState, sls::comparators::score_tcc_rand<InnerState>>;


} /* facets */ } /* sls */


#endif