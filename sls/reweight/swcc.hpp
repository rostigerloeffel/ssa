#ifndef _SLS_REWEIGHT_SWCC_HPP_
#define _SLS_REWEIGHT_SWCC_HPP_


#include "reweighter_base.hpp"
#include "reweight_util.hpp"


namespace sls { namespace reweight {


template<typename StateType>
class swcc : public reweighter_base<StateType>
{
    typedef StateType state_type;
    typedef typename state_type::properties_type properties_type;
    typedef typename properties_type::clause_properties_type clause_properties_type;

    typedef decltype(clause_properties_type::weight) weight_type;

    double rho_;
    weight_type gamma_;

public:
    swcc(double rho = 0.3, weight_type gamma = weight_type(300))
        :   rho_(rho),
            gamma_(gamma)
    {}

    void operator()(state_type& state)
    {
        if(state.avg_weight() > gamma_)
            smooth_clause_weights(state);
        else
            increase_clause_weights(state);

        //state.sd_bound(298); //std::floor(state.avg_weight()));
    }

private:
    inline void increase_clause_weights(state_type& state)
    {
        for(auto clause : state.broken())
            inc_clause_weight(state, clause, weight_type(1));
    }

    inline void smooth_clause_weights(state_type& state)
    {
        for(auto clause : state.clauses())
        {
            auto old_weight = state.weight(clause);
            auto new_weight = std::floor(rho_ * old_weight) + std::floor((1.0 - rho_) * state.avg_weight());

            auto diff = old_weight - new_weight;

            if(old_weight > new_weight)
                dec_clause_weight(state, clause, old_weight - new_weight);
            else if(old_weight < new_weight)
                inc_clause_weight(state, clause, new_weight - old_weight);
        }
    }
};


template<typename StateType>
class swqcc : public reweighter_base<StateType>
{
    typedef StateType state_type;
    typedef typename state_type::properties_type properties_type;
    typedef typename properties_type::clause_properties_type clause_properties_type;

    typedef decltype(clause_properties_type::weight) weight_type;

    double rho_;
    weight_type gamma_;

public:
    swqcc(double rho = 0.3, weight_type gamma = weight_type(300))
        :   rho_(rho),
            gamma_(gamma)
    {}

    void operator()(state_type& state)
    {
        if(state.avg_weight() > gamma_)
        {
            smooth_clause_weights(state);
            state.smooth_tcc();
        }
        else
            increase_clause_weights(state);

        //state.sd_bound(298); //std::floor(state.avg_weight()));
    }

private:
    inline void increase_clause_weights(state_type& state)
    {
        for(auto clause : state.broken())
            inc_clause_weight(state, clause, weight_type(1));
    }

    inline void smooth_clause_weights(state_type& state)
    {
        for(auto clause : state.clauses())
        {
            auto old_weight = state.weight(clause);
            auto new_weight = std::floor(rho_ * old_weight) + std::floor((1.0 - rho_) * state.avg_weight());

            auto diff = old_weight - new_weight;

            if(old_weight > new_weight)
                dec_clause_weight(state, clause, old_weight - new_weight);
            else if(old_weight < new_weight)
                inc_clause_weight(state, clause, new_weight - old_weight);
        }
    }
};


template<typename StateType>
class swqcca : public reweighter_base<StateType>
{
    typedef StateType state_type;
    typedef typename state_type::properties_type properties_type;
    typedef typename properties_type::clause_properties_type clause_properties_type;

    typedef decltype(clause_properties_type::weight) weight_type;

    double rho_;
    weight_type gamma_;

public:
    swqcca(double rho = 0.3, weight_type gamma = weight_type(300))
        :   rho_(rho),
            gamma_(gamma)
    {}

    void operator()(state_type& state)
    {
        if(state.avg_weight() > gamma_)
        {
            smooth_clause_weights(state);
            state.smooth_tcc();
        }
        else
            increase_clause_weights(state);

        state.sd_bound(state.avg_weight());
        //state.sd_bound(298); //std::floor(state.avg_weight()));
    }

private:
    inline void increase_clause_weights(state_type& state)
    {
        for(auto clause : state.broken())
            inc_clause_weight(state, clause, weight_type(1));
    }

    inline void smooth_clause_weights(state_type& state)
    {
        for(auto clause : state.clauses())
        {
            auto old_weight = state.weight(clause);
            auto new_weight = std::floor(rho_ * old_weight) + std::floor((1.0 - rho_) * (gamma_ + 1));//state.avg_weight());

            auto diff = old_weight - new_weight;

            if(old_weight > new_weight)
                dec_clause_weight(state, clause, old_weight - new_weight);
            else if(old_weight < new_weight)
                inc_clause_weight(state, clause, new_weight - old_weight);
        }
    }
};


} /* reweight */ } /* sls */


#endif