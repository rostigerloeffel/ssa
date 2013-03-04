#ifndef _SLS_STATE_STATE_INTERFACE_HPP_
#define _SLS_STATE_STATE_INTERFACE_HPP_


#include <vector>
#include "state_lang.hpp"


namespace sls { namespace state {


template<typename InnerState>
class state_interface
{
public:
	INNER_STATE_TYPEDEFS(InnerState)

private:
    inner_state_type&                   inner_state_;

    std::vector<clause_store_type>      literal_index_to_clauses_;
    std::vector<clause_store_type>      variable_index_to_clauses_;
    std::vector<variable_store_type>    variable_index_to_variables_;

public:
    state_interface(inner_state_type& inner_state)
        :   inner_state_(inner_state),
            literal_index_to_clauses_(), 
            variable_index_to_clauses_(), 
            variable_index_to_variables_()
    {
        prepare(clauses, variable_count);
    }

    void prepare(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        inner_state_.prepare(clauses, variable_count);

        literal_index_to_clauses_.resize(inner_state_.literals().size());
        for(auto clause : inner_state_.clauses())
            for(auto literal : clause)
                literal_index_to_clauses_[sat_type::index(literal)].push_back(clause);

        variable_index_to_clauses_.resize(variables().size());
        for(auto clause : inner_state_.clauses())
            for(auto literal : clause)
                variable_index_to_clauses_[sat_type::index(literal.variable())].push_back(clause);

        variable_index_to_variables_.resize(variables().size());
        for(auto clause : inner_state_.clauses())
            for(auto literal1 : clause)
                for(auto literal2 : clause)
                    if(literal1 != literal2)
                        variable_index_to_variables_[sat_type::index(literal1.variable())].push_back(literal2.variable());
    }

    inline clause_store_type const& clauses() const
    {
        return inner_state_.clauses();
    }

    inline literal_store_type const& literals() const
    {
        return inner_state_.literals();
    }

    inline variable_store_type const& variables() const
    {
        return inner_state_.variables();
    }

    inline clause_store_type const& clauses_by_literal(literal_type literal) const
    {
        return literal_index_to_clauses_[sat_type::index(literal)];
    }

    inline clause_store_type const& clauses_by_variable(variable_type variable) const
    {
        return variable_index_to_clauses_[sat_type::index(variable)];
    }

    inline variable_store_type const& variables_by_variable(variable_type variable) const
    {
        return variable_index_to_variables_[sat_type::index(variable)];
    }
};


} /* state */ } /* sls */


#endif