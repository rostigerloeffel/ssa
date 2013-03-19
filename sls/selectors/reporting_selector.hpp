#ifndef _SLS_SELECTORS_REPORTING_SELECTOR_HPP_
#define _SLS_SELECTORS_REPORTING_SELECTOR_HPP_


#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include "selector_base.hpp"


namespace sls { namespace selectors {


template<typename StateType>
class reporting_selector : public selector_base<StateType>
{
    typedef StateType                                       state_type;
    typedef typename state_type::sat_type                   sat_type;
    typedef typename state_type::variable_properties_type   variable_properties_type;
    typedef typename state_type::variable_type              variable_type;

    selector_base<state_type>*  selector_;

    double avg_score_;
    double avg_age_;
    double avg_tcc_;

public:
    reporting_selector(selector_base<state_type>* const selector)
        :   selector_(selector),
            avg_score_(0.0),
            avg_age_(0.0),
            avg_tcc_(0.0)
    {
    }

    bool is_applicable(state_type const& state)
    {
        return selector_->is_applicable(state);
    }

    variable_type select(state_type& state)
    {
        auto pick = selector_->select(state);

        // std::cout << "--- pick stats --------------------------\n";
        // std::cout << "selector: " << selector_->name() << "\n";
        // std::cout << "pick = " << pick << '\n';
        // std::cout << "score = " << state.score(pick) << '\n';
        // std::cout << "age = " << state.age(pick) << '\n';
        // std::cout << "tcc = " << state.tcc(pick) << '\n';

        avg_score_  = (avg_score_   * 0.9999)   + (static_cast<double>(state.score(pick))   * 0.0001); 
        avg_age_    = (avg_age_     * 0.9999)   + (static_cast<double>(state.age(pick))     * 0.0001); 
        avg_tcc_    = (avg_tcc_     * 0.9999)   + (static_cast<double>(state.tcc(pick))     * 0.0001); 

        std::cout << "--- pick stats --------------------------\n";
        std::cout << "selector: " << selector_->name() << "\n";
        std::cout << "pick = " << pick << '\n';
        std::cout << "score = " << avg_score_ << '\n';
        std::cout << "age = " << avg_age_ << '\n';
        std::cout << "tcc = " << avg_tcc_ << '\n';

        return pick;
    }
};


} /* selectors */ } /* sls */


#endif
