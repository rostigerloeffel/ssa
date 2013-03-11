#ifndef _SLS_FACETS_COMPARATORS_HPP_
#define _SLS_FACETS_COMPARATORS_HPP_


namespace sls { namespace comparators {


template<typename InnerState>
struct score_age
{
    InnerState& inner_state;

    inline bool operator()(typename InnerState::variable_type lhs, 
    					   typename InnerState::variable_type rhs) const
    {
        return
            inner_state[lhs].score < inner_state[rhs].score ||
        	
        	(inner_state[lhs].score == inner_state[rhs].score &&
        	inner_state[lhs].last_flip > inner_state[rhs].last_flip);
    }
};

template<typename InnerState>
struct score_rand
{
    InnerState& inner_state;

    inline bool operator()(typename InnerState::variable_type lhs, 
    					   typename InnerState::variable_type rhs) const
    {
        return
            inner_state[lhs].score < inner_state[rhs].score ||
        	
            (rand() % 2 == 0);
    }
};

template<typename InnerState>
struct score_tcc_age
{
    InnerState& inner_state;

    inline bool operator()(typename InnerState::variable_type lhs, 
    					   typename InnerState::variable_type rhs) const
    {
        return
            inner_state[lhs].score < inner_state[rhs].score ||

            (inner_state[lhs].score == inner_state[rhs].score &&
             inner_state[lhs].tcc < inner_state[rhs].tcc) ||

            (inner_state[lhs].score == inner_state[rhs].score &&
             inner_state[lhs].tcc == inner_state[rhs].tcc &&
             inner_state[lhs].last_flip > inner_state[rhs].last_flip);
    }
};

template<typename InnerState>
struct score_tcc_rand
{
    InnerState& inner_state;

    inline bool operator()(typename InnerState::variable_type lhs, 
    					   typename InnerState::variable_type rhs) const
    {
        return
            inner_state[lhs].score < inner_state[rhs].score ||

            (inner_state[lhs].score == inner_state[rhs].score &&
             inner_state[lhs].tcc < inner_state[rhs].tcc) ||

            (rand() % 2 == 0);
    }
};


} /* comparators */ } /* sls */


#endif