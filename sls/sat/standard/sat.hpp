#ifndef __SLS_SAT_STANDARD_SAT_HPP__
#define __SLS_SAT_STANDARD_SAT_HPP__


#include "variable_literal.hpp"
#include "clause.hpp"


namespace sls
{


namespace sat
{


namespace standard
{


struct sat
{
    typedef sls::sat::standard::variable_type 	variable_type;
    typedef sls::sat::standard::literal_type	literal_type;
    typedef sls::sat::standard::clause_type		clause_type;

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

    template<typename SATPrimitive>
    static inline size_t index(SATPrimitive primitive)
    {
        return primitive.value;
    }
};


} /* standard */


} /* sat */


} /* sls */


#endif
