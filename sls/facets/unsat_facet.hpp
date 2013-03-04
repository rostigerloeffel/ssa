#ifndef _SLS_FACETS_UNSAT_FACET_HPP_
#define _SLS_FACETS_UNSAT_FACET_HPP_


#include <vector>
#include <algorithm>
#include "facet.hpp"
#include "facet_base.hpp"
#include "../storage/random_access_list.hpp"


namespace sls { namespace facets {


begin_facet(unsat, typename UnsatStore = 
                        sls::storage::random_access_list<typename State::clause_type>)
    typedef UnsatStore unsat_store_type;
    unsat_store_type unsats_;

public:
	facet_constr(unsat, unsats_())

    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        std::for_each(get_inner_state.clause_properties_begin(), get_inner_state.clause_properties_end(), 
        	[](clause_properties_type& prop){ prop.num_true_literals = 0ul; });

        unsats_.resize(clauses.size());
        unsats_.clear();

        std::copy(clauses.begin(), clauses.end(), std::back_inserter(unsats_));
    }

    inline size_t num_true_literals(clause_type clause) const
    {
        return get_inner_state[clause].num_true_literals;
    }

    inline void inc_num_true_literals(clause_type clause)
    {
        if(++get_inner_state[clause].num_true_literals == 1ul)
            unsats_.remove(clause);
    }

    inline void dec_num_true_literals(clause_type clause)
    {
        if(--get_inner_state[clause].num_true_literals == 0ul)
            unsats_.push_back(clause);
    }

    inline unsat_store_type const& unsats() const
    {
        return unsats_;
    }

    inline unsat_store_type& unsats()
    {
        return unsats_;
    }
};


} /* facets */ } /* sls */


#endif