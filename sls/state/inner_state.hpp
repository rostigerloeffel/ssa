#ifndef _SLS_STATE_INNER_STATE_HPP_
#define _SLS_STATE_INNER_STATE_HPP_


#include "state_lang.hpp"


namespace sls { namespace state {


template
<
  	typename SAT,
  	typename Properties,
    typename ClauseStore = std::vector<typename SAT::clause_type>,
    typename LiteralStore = std::vector<typename SAT::literal_type>,
    typename VariableStore = std::vector<typename SAT::variable_type>
>
class inner_state
{
public:
    SAT_TYPEDEFS(SAT)
    PROP_TYPEDEFS(Properties)

    typedef typename std::vector<variable_properties_type>::iterator 		variable_properties_iterator;
    typedef typename std::vector<variable_properties_type>::const_iterator	const_variable_properties_iterator;
    typedef typename std::vector<literal_properties_type>::iterator 		literal_properties_iterator;
    typedef typename std::vector<literal_properties_type>::const_iterator	const_literal_properties_iterator;
    typedef typename std::vector<clause_properties_type>::iterator 			clause_properties_iterator;
    typedef typename std::vector<clause_properties_type>::const_iterator	const_clause_properties_iterator;

    typedef ClauseStore                                         			clause_store_type;
    typedef LiteralStore                                        			literal_store_type;
    typedef VariableStore                                       			variable_store_type;

    typedef typename clause_store_type::iterator 							clause_iterator;
    typedef typename clause_store_type::const_iterator 						const_clause_iterator;
    typedef typename literal_store_type::iterator 							literal_iterator;
    typedef typename literal_store_type::const_iterator 					const_literal_iterator;
    typedef typename variable_store_type::iterator 							variable_iterator;
    typedef typename variable_store_type::const_iterator 					const_variable_iterator;

private:
    std::vector<variable_properties_type>   variable_properties_;
    std::vector<literal_properties_type>    literal_properties_;
    std::vector<clause_properties_type>     clause_properties_;

    variable_store_type                 	variables_;
    literal_store_type                  	literals_;
    clause_store_type                   	clauses_;

public:
	inner_state(std::vector<clause_type> const& clauses, size_t variable_count)
		:	variable_properties_(variable_count), 
            literal_properties_(variable_count * 2), 
            clause_properties_(clauses.size())
    {
    	prepare(clauses, variable_count);
    }

    inline void prepare(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        std::copy(clauses.begin(), clauses.end(), std::back_inserter(clauses_));

        for(auto cnf_variable = 1u; cnf_variable <= variable_count; ++cnf_variable)
        {
            auto variable = sat_type::make_variable(cnf_variable);

            variables_.push_back(variable);
            literals_.push_back(sat_type::make_literal(variable, true));
            literals_.push_back(sat_type::make_literal(variable, false));
        }
    }

	inline variable_properties_type const& variable_properties(variable_type variable) const
	{
		return variable_properties_[sat_type::index(variable)];
	}

	inline variable_properties_type& variable_properties(variable_type variable)
	{
		return variable_properties_[sat_type::index(variable)];
	}

	inline variable_properties_type const& operator[](variable_type variable) const
	{
		return variable_properties_[sat_type::index(variable)];
	}

	inline variable_properties_type& operator[](variable_type variable)
	{
		return variable_properties_[sat_type::index(variable)];
	}	

	inline literal_properties_type const& literal_properties(literal_type literal) const
	{
		return literal_properties_[sat_type::index(literal)];
	}

	inline literal_properties_type& literal_properties(literal_type literal)
	{
		return literal_properties_[sat_type::index(literal)];
	}

	inline literal_properties_type const& operator[](literal_type literal) const
	{
		return literal_properties_[sat_type::index(literal)];
	}

	inline literal_properties_type& operator[](literal_type literal)
	{
		return literal_properties_[sat_type::index(literal)];
	}

	inline clause_properties_type const& clause_properties(clause_type clause) const
	{
		return clause_properties_[sat_type::index(clause)];
	}

	inline clause_properties_type& clause_properties(clause_type clause)
	{
		return clause_properties_[sat_type::index(clause)];
	}

	inline clause_properties_type const& operator[](clause_type clause) const
	{
		return clause_properties_[sat_type::index(clause)];
	}

	inline clause_properties_type& operator[](clause_type clause)
	{
		return clause_properties_[sat_type::index(clause)];
	}

	inline const_variable_properties_iterator variable_properties_begin() const
	{
		return variable_properties_.begin();
	}

	inline variable_properties_iterator variable_properties_begin()
	{
		return variable_properties_.begin();
	}

	inline const_variable_properties_iterator variable_properties_end() const
	{
		return variable_properties_.end();
	}

	inline variable_properties_iterator variable_properties_end()
	{
		return variable_properties_.end();
	}

		inline const_literal_properties_iterator literal_properties_begin() const
	{
		return literal_properties_.begin();
	}

	inline literal_properties_iterator literal_properties_begin()
	{
		return literal_properties_.begin();
	}

	inline const_literal_properties_iterator literal_properties_end() const
	{
		return literal_properties_.end();
	}

	inline literal_properties_iterator literal_properties_end()
	{
		return literal_properties_.end();
	}

	inline const_clause_properties_iterator clause_properties_begin() const
	{
		return clause_properties_.begin();
	}

	inline clause_properties_iterator clause_properties_begin()
	{
		return clause_properties_.begin();
	}

	inline const_clause_properties_iterator clause_properties_end() const
	{
		return clause_properties_.end();
	}

	inline clause_properties_iterator clause_properties_end()
	{
		return clause_properties_.end();
	}

	inline const_variable_iterator variables_begin() const
	{
		return variables_.begin();
	}

	inline variable_iterator variables_begin()
	{
		return variables_.begin();
	}

	inline const_variable_iterator variables_end() const
	{
		return variables_.end();
	}

	inline variable_iterator variables_end()
	{
		return variables_.end();
	}

	inline variable_store_type const& variables() const
	{
		return variables_;
	}

	inline variable_store_type& variables()
	{
		return variables_;
	}

	inline const_literal_iterator literals_begin() const
	{
		return literals_.begin();
	}

	inline literal_iterator literals_begin()
	{
		return literals_.begin();
	}

	inline const_literal_iterator literals_end() const
	{
		return literals_.end();
	}

	inline literal_iterator literals_end()
	{
		return literals_.end();
	}

	inline literal_store_type const& literals() const
	{
		return literals_;
	}

	inline literal_store_type& literals()
	{
		return literals_;
	}

	inline const_clause_iterator clauses_begin() const
	{
		return clauses_.begin();
	}

	inline clause_iterator clauses_begin()
	{
		return clauses_.begin();
	}

	inline const_clause_iterator clauses_end() const
	{
		return clauses_.end();
	}

	inline clause_iterator clauses_end()
	{
		return clauses_.end();
	}

	inline clause_store_type const& clauses() const
	{
		return clauses_;
	}

	inline clause_store_type& clauses()
	{
		return clauses_;
	}
};


} /* state */ } /* sls */


#endif