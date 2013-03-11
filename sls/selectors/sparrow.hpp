#ifndef __SLS_SELECTORS_SPARROW_HPP__
#define __SLS_SELECTORS_SPARROW_HPP__


#include <cmath>
#include <limits>
#include <list>
#include "selector_base.hpp"


namespace sls { namespace selectors {


template<typename StateType>
class sparrow : public selector_base<StateType>
{
    typedef StateType state_type;
    typedef typename state_type::sat_type sat_type;
    typedef typename state_type::variable_type variable_type;

    double              c1_;
    double              c2_;
    double              c3_;

    std::vector<double> p_s;
    std::vector<double> p_a;

public:
    explicit sparrow(double c1 = 2.15, double c2 = 4.0, double c3 = 100000.0)
        :   c1_(c1), 
            c2_(c2), 
            c3_(c3), 
            p_s(), 
            p_a()
    {
        p_s.reserve(7);
        p_a.reserve(7);
    }

    bool is_applicable(state_type const& state)
    {
        return true;
    }

    variable_type select(state_type& state)
    {
        // pick clause
        auto broken_clause = state.broken()[std::rand() % state.broken().size()];

        p_s.resize(broken_clause.size());
        p_a.resize(broken_clause.size());

        auto sparrow_sum = 0.0;
        auto i = 0;
        for(auto literal : broken_clause)
        {
            if(state.score(literal.variable()) <= 0)
                p_s[i] = std::pow(c1_, static_cast<double>(state.score(literal.variable())));
            else
                p_s[i] = 1.0f;
            p_a[i] = std::pow((static_cast<double>(state.age(literal.variable())) / c3_), c2_) + 1.0;

            sparrow_sum += (p_s[i] * p_a[i]);

            ++i;
        }

        auto score_pos = ((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * sparrow_sum);
        auto score_sum = 0.0;

        i = 0;
        for(auto literal : broken_clause)
        {
            score_sum += p_s[i] * p_a[i];

            if(score_pos <= score_sum)
                return literal.variable();

            ++i;
        }

        auto v = state.clauses()[std::rand() % state.clauses().size()][std::rand() % broken_clause.size()].variable();
        return v;
    }

    std::string const name() const 
    {
        return "sparrow selector";
    }
};


} /* selectors */ } /* sls */


#endif
