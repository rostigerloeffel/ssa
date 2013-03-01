#ifndef _SLS_SELECTORS_SELECTOR_BASE_HPP_
#define _SLS_SELECTORS_SELECTOR_BASE_HPP_


#include <string>


namespace sls { namespace selectors {


template<typename StateType>
class selector_base
{
    typedef StateType state_type;
    typedef typename state_type::variable_type variable_type;

public:
    virtual bool is_applicable(state_type const& state) = 0;
    virtual variable_type select(state_type& state) = 0;

    virtual void before_pick(state_type& state) 
    {
    }

    virtual std::string const name() const 
    {
    	return "unnamed selector";
    }
};


} /* selectors */ } /* sls */


#endif
