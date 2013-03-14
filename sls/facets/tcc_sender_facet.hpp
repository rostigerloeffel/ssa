#ifndef _SLS_FACETS_TCC_SENDER_FACET_HPP_
#define _SLS_FACETS_TCC_SENDER_FACET_HPP_


#include "facet_base.hpp"
#include "signals.hpp"
#include "facet.hpp"
#include "../storage/random_access_list.hpp"
#include "../storage/resettable_vector.hpp"


namespace sls { namespace facets {


begin_facet(tcc_sender, 
    typename ...TccListener)
    
    typedef sls::storage::random_access_list<
                variable_type>                      tcc_store_type;

private:
    tcc_store_type                                  tcc_lookup_;
    sls::storage::resettable_vector<variable_type>  temp_;

public: 
    typedef decltype(variable_properties_type::tcc) tcc_type;

    facet_constr(tcc_sender, tcc_lookup_(), temp_())

    void after_pick(size_t flip, variable_type variable)
    {
        reset_tcc(variable);

        for(auto neighbour : this_state.neighbours(variable))
            inc_tcc(neighbour, tcc_type(1));
    }

    void reset(std::vector<clause_type> const& clauses, size_t variable_count)
    {
        std::for_each(get_inner_state.variable_properties_begin(), get_inner_state.variable_properties_end(), 
        	[](variable_properties_type& prop){ 
                prop.tcc = tcc_type(0); 
            });
    }

    inline tcc_type tcc(variable_type variable) const
    {
        return get_inner_state[variable].tcc;
    }

    inline tcc_type& tcc(variable_type variable)
    {
        return get_inner_state[variable].tcc;
    }

    inline void inc_tcc(variable_type variable, tcc_type diff)
    {
        tcc(variable) += diff;
        send_signal(tcc_inc, variable, diff);
    }

    inline void dec_tcc(variable_type variable, tcc_type diff)
    {
        tcc(variable) -= diff;
        send_signal(tcc_dec, variable, diff);
    }

    inline void reset_tcc(variable_type variable)
    {
        tcc(variable) = tcc_type(0);
        send_signal(tcc_reset, variable);
    }

    inline void smooth_tcc()
    {
        for(auto variable : tcc_lookup_)
        {
            tcc(variable) = 
                tcc_type((static_cast<double>(tcc(variable)) * 0.3) + 1.0);

            if(tcc(variable) <= tcc_type(2))
                temp_.push_back(variable);
        }

        for(auto variable : temp_)
            tcc_lookup_.remove(variable);

        // TODO: Fix this!!!
        temp_.reset();
    }    

private:
    facet_signal(tcc_inc, TccListener, variable_type, tcc_type)
    facet_signal(tcc_dec, TccListener, variable_type, tcc_type)
    facet_signal(tcc_reset, TccListener, variable_type)
end_facet


} /* facets */ } /* ssa */


#endif