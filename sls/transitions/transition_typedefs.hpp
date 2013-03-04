#ifndef _SLS_TRANSITIONS_TRANSITION_TYPEDEFS_HPP_
#define _SLS_TRANSITIONS_TRANSITION_TYPEDEFS_HPP_


#include "occ_transitor.hpp"
#include "counting_occ_transitor.hpp"
#include "watch1_score_unsat_handler.hpp"
#include "watch2_score_unsat_handler.hpp"
#include "watch2_breakcount_unsat_handler.hpp"
#include "watch2_sat_score_unsat_handler.hpp"
#include "simple_initializer.hpp"
#include "weighted_initializer.hpp"


namespace sls { namespace transitions {


template<typename StateType>
using default_initializer = simple_initializer<StateType>;

template<typename StateType>
using watch2_transitor = occ_transitor<StateType, watch2_score_unsat_plus_handler<StateType>, watch2_score_unsat_minus_handler<StateType>>;

template<typename StateType>
using watch2_sat_transitor = occ_transitor<StateType, watch2_sat_score_unsat_plus_handler<StateType>, watch2_score_unsat_minus_handler<StateType>>;

template<typename StateType>
using watch2_breakcount_transitor = occ_transitor<StateType, watch2_breakcount_unsat_plus_handler<StateType>, watch2_breakcount_unsat_minus_handler<StateType>>;

template<typename StateType>
using default_transitor = watch2_transitor<StateType>;

template<typename StateType>
using watch1_transitor = occ_transitor<StateType, watch1_score_unsat_plus_handler<StateType>, watch1_score_unsat_minus_handler<StateType>>;

template<typename StateType>
using counting_transitor = counting_occ_transitor<StateType, watch2_score_unsat_plus_handler<StateType>, watch2_score_unsat_minus_handler<StateType>>;


} /* transitions */ } /* sls */


#endif