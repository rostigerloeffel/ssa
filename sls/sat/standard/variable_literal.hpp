#ifndef __SLS_SAT_STANDARD_VARIABLE_LITERAL_HPP__
#define __SLS_SAT_STANDARD_VARIABLE_LITERAL_HPP__


#include <iostream>
#include <cstdint>


namespace sls
{


namespace sat
{


namespace standard
{


class variable_type
{
public:
    static inline variable_type null()
    {
        return variable_type { std::numeric_limits<std::uint_fast32_t>::max() };
    }

    inline std::uint_fast32_t cnf_variable() const
    {
        return value + 1;
    }

    std::uint_fast32_t value;
};

class literal_type
{
public:
    std::uint_fast32_t value;

    static inline literal_type null()
    {
        return literal_type { std::numeric_limits<std::uint_fast32_t>::max() };
    }

    inline variable_type variable() const
    {
        return variable_type { value >> 1 };
    }

    inline bool polarity() const
    {
        return value & 1;
    }

    inline literal_type negate() const
    {
        return literal_type { value ^ 1 };
    }
};

inline bool operator==(variable_type lhs, variable_type rhs)
{
    return lhs.value == rhs.value;
}

inline bool operator!=(variable_type lhs, variable_type rhs)
{
    return lhs.value != rhs.value;
}

inline bool operator<(variable_type lhs, variable_type rhs)
{
    return lhs.value < rhs.value;
}

inline bool operator==(literal_type lhs, literal_type rhs)
{
    return lhs.value == rhs.value;
}

inline bool operator!=(literal_type lhs, literal_type rhs)
{
    return lhs.value != rhs.value;
}

inline bool operator<(literal_type lhs, literal_type rhs)
{
    return lhs.value < rhs.value;
}

inline size_t index(variable_type variable)
{
    return variable.value;
}

inline size_t index(literal_type literal)
{
    return literal.value;
}

inline std::ostream& operator<<(std::ostream& stream, variable_type variable)
{
    return stream << variable.cnf_variable();
}

inline std::ostream& operator<<(std::ostream& stream, literal_type literal)
{
    return stream << (literal.polarity() ? "" : "-") << literal.variable();
}


} /* standard */


} /* sat */


} /* sls */


#endif
