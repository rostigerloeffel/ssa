#ifndef __SLS_SAT_KSAT_SAT_HPP__
#define __SLS_SAT_KSAT_SAT_HPP__


#include "variable_literal.hpp"
#include "clause.hpp"


namespace sls
{


namespace sat
{


namespace ksat
{


template<unsigned int K>
struct sat
{
    typedef sls::sat::ksat::variable_type 	variable_type;
    typedef sls::sat::ksat::literal_type	literal_type;
    typedef sls::sat::ksat::clause_type<K>	clause_type;

    static inline variable_type make_variable(std::uint32_t cnf_variable)
    {
        return variable_type { cnf_variable - 1 };
    }

    static inline literal_type make_literal(variable_type variable, bool polarity)
    {
        return literal_type { (variable.value << 1) + static_cast<std::uint_fast32_t>(polarity) };
    }

    template<typename Iterator>
    static inline clause_type make_clause(Iterator begin, Iterator end)
    {
        return clause_type { internal::push_clause_to_stack(begin, end) };
    }

    static inline clause_type make_clause(std::initializer_list<literal_type> literals)
    {
        return clause_type { internal::push_clause_to_stack(literals.begin(), literals.end()) };
    }

    template<typename Iterator>
    static inline clause_type replace_clause(clause_type clause, Iterator begin, Iterator end)
    {
        internal::replace_clause_on_stack(clause.value, begin, end);

        return clause;
    }

    static inline clause_type replace_clause(clause_type clause, std::initializer_list<literal_type> literals)
    {
        internal::replace_clause_on_stack(clause.value, literals.begin(), literals.end());
        
        return clause;
    }

    static inline void remove_clause(clause_type clause)
    {
        return;
    }    

    template<typename SATPrimitive>
    static inline size_t index(SATPrimitive primitive)
    {
        return primitive.value;
    }
};


} /* ksat */


} /* sat */


} /* sls */


#endif
