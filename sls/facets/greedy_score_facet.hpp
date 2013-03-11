#ifndef _SLS_FACETS_GREEDY_SCORE_FACET_HPP_
#define _SLS_FACETS_GREEDY_SCORE_FACET_HPP_


#include "facet_base.hpp"
#include "signals.hpp"
#include "facet.hpp"
#include "../storage/mutable_priority_queue.hpp"
#include "comparators.hpp"


namespace sls { namespace facets {


begin_facet(greedy_score, 
    typename Comparator)

    typedef Comparator                                  comparator_type;
    typedef decltype(variable_properties_type::score)   score_type;

    typedef sls::storage::mutable_priority_queue<
                variable_type, 
                comparator_type>                        greedy_store_type;

private:
    greedy_store_type   greedy_;
    variable_type       walk_;

public:
    facet_constr(greedy_score, greedy_(0, {get_inner_state}), walk_(variable_type::null()))

    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        greedy_.resize(variable_count);
        walk_ = sat_type::variable_type::null();
    }

    void after_pick(size_t flip, variable_type variable)
    {
        walk_ = variable;
    }

    void flush()
    {
        walk_ = sat_type::variable_type::null();
    }

    inline bool has_greedy() const
    {
        return !greedy_.empty();
    }

    inline variable_type most_greedy() const
    {
    	return greedy_.top();
    }

    facet_slot(score_inc, variable, diff)
    {
        if(get_inner_state[variable].score > score_type(0) && 
           get_inner_state[variable].score <= diff)   
        {
            if(walk_ != variable)
                greedy_.push(variable);
        }
        else if(greedy_.contains(variable))
            greedy_.update_after_inc(variable);
    }

    facet_slot(score_dec, variable, diff)
    {
        if(greedy_.contains(variable))
        {
            if(get_inner_state[variable].score <= score_type(0))
                greedy_.remove(variable);
            else
                greedy_.update_after_dec(variable);
        }
    }
end_facet


template<typename State, typename InnerState>
using greedy_score_age_facet = greedy_score_facet<State, InnerState, sls::comparators::score_age<InnerState>>;

template<typename State, typename InnerState>
using greedy_score_rand_facet = greedy_score_facet<State, InnerState, sls::comparators::score_rand<InnerState>>;


} /* facets */ } /* sls */


#endif