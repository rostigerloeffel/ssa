#ifndef _SLS_FACETS_WEIGHT_FACET_HPP_
#define _SLS_FACETS_WEIGHT_FACET_HPP_


#include <vector>
#include <algorithm>
#include "facet_base.hpp"
#include "../storage/random_access_list.hpp"
#include "../storage/resettable_vector.hpp"


namespace sls { namespace facets {


begin_facet(weight,
    typename WeightedStoreType = sls::storage::random_access_list<typename InnerState::clause_type)

    typedef decltype(clause_properties_type::weight)    weight_type;
    typedef WeightedStoreType                           weighted_store_type;

private:
    weighted_store_type                             weighted_;
    sls::storage::resettable_vector<clause_type>    temp_;

public:
    facet_constr(weight, weighted_(), temp_())

    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        std::for_each(inner_state_.clause_properties_begin(), inner_state_.clause_properties_end(), 
        	[](clause_properties_type& prop){ 
                prop.weight = weight_type(1); 
            });

        weighted_.resize(clauses.size());
        weighted_.clear();

        temp_.reserve(clauses.size());
        temp_.clear();
    }

    void flush()
    {
        for(auto clause : temp_)
            weighted_.remove(clause);

        // TODO: Fix this!!!
        temp_.reset();
    }

    inline weight_type weight(clause_type clause) const
    {
        return get_inner_state[clause].weight;
    }

    inline void inc_weight(clause_type clause)
    {
        if((get_inner_state[clause].weight += weight_type(1)) == weight_type(2))
            weighted_.push_back(clause);
    }

    inline void dec_weight(clause_type clause)
    {
        if((get_inner_state[clause].weight -= weight_type(1)) == weight_type(1))
            temp_.push_back(clause);
    }

    inline void inc_weight(clause_type clause, weight_type increment)
    {
        if((get_inner_state[clause].weight += increment) >= weight_type(2) && 
            weight(clause) - increment < weight_type(2))
            weighted_.push_back(clause);
    }

    inline void dec_weight(clause_type clause, weight_type decrement)
    {
        if((get_inner_state[clause].weight -= decrement) <= weight_type(1) &&
            weight(clause) + decrement > 1)
            temp_.push_back(clause);
    }

    inline weighted_store_type const& weighted() const
    {
        return weighted_;
    }
};


} /* facets */


} /* sls */


#endif