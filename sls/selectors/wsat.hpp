#ifndef _SLS_SELECTORS_WSAT_HPP_
#define _SLS_SELECTORS_WSAT_HPP_


namespace sls { namespace selectors {

static constexpr auto prob = 0.5;

template<typename StateType>
class wsat : public selector_base<StateType>
{
    typedef StateType                           state_type;
    typedef typename state_type::variable_type  variable_type;

    std::vector<variable_type> zerobreaks_;
    std::vector<variable_type> minbreaks_;

public:
    wsat()
        :   zerobreaks_(),
            minbreaks_()
    {
    }

    bool is_applicable(state_type const& state)
    {
        return true;
    }

    variable_type select(state_type& state)
    {
        auto broken_clause = state.broken()[std::rand() % state.broken().size()];

        zerobreaks_.clear();
        minbreaks_.clear();

        zerobreaks_.reserve(broken_clause.size());
        minbreaks_.reserve(broken_clause.size());

        size_t minbreakcount = 99999ul;

        for(auto literal : broken_clause)
        {
            if(state.breakcount(literal.variable()) == 0ul)
                zerobreaks_.push_back(literal.variable());
            else if(state.breakcount(literal.variable()) == minbreakcount && zerobreaks_.empty())
                minbreaks_.push_back(literal.variable());
            else if(state.breakcount(literal.variable()) < minbreakcount && zerobreaks_.empty())
            {
                minbreakcount = state.breakcount(literal.variable());
                minbreaks_.clear();
                minbreaks_.push_back(literal.variable());
            }
        }

        if(!zerobreaks_.empty())
            return zerobreaks_[std::rand() % zerobreaks_.size()];
        else if(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX) < prob)
            return broken_clause[std::rand() % broken_clause.size()].variable();
        else
            return minbreaks_[std::rand() % minbreaks_.size()];
    }

    std::string const name() const 
    {
        return "wsat selector";
    }

};


} /* selectors */ } /* sls */


#endif
