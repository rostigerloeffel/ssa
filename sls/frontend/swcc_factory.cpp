#include "swcc_factory.hpp"


namespace sls { namespace frontend {


template<typename State, typename InnerState>
using swqcca_facets = sls::facets::facet_compositor<
    State, InnerState,
    sls::facets::neighbour_facet<State, InnerState>,
    sls::facets::greedy_score_tcc_age_facet<State, InnerState>,
    sls::facets::greedy_sd_score_age_facet<State, InnerState>,
    sls::facets::score_sender_facet<State, InnerState,
    	sls::facets::greedy_score_tcc_age_facet<State, InnerState>,
    	sls::facets::greedy_sd_score_age_facet<State, InnerState>>,
    sls::facets::tcc_sender_facet<State, InnerState,
    	sls::facets::greedy_score_tcc_age_facet<State, InnerState>>,
   	sls::facets::greedy_accessor_facet<State, InnerState,
   		sls::facets::greedy_score_tcc_age_facet<State, InnerState>,
   	    sls::facets::greedy_sd_score_age_facet<State, InnerState>>,
    sls::facets::age_facet<State, InnerState>,
    sls::facets::truth_facet<State, InnerState>,
    sls::facets::watcher_facet<State, InnerState>,
    sls::facets::avg_weight_facet<State, InnerState>,
    sls::facets::unsat_facet<State, InnerState>
>;

declare_state(swqcca,
    declare_sat_backend(standard::sat),

    declare_properties(
            variable_props(truth, age, score, tcc, blocked, neighbours<typename sat_type::variable_type>),
            literal_props(empty),
            clause_props(watcher2<typename sat_type::variable_type>, num_true_literals, weight)),

    use_facets(swqcca_facets))




// typedef sls::state::state<
//     sat,
//     properties,
//     sls::facets::facet_compositor<
//         inner_state,
//         sls::facets::neighbour_facet<inner_state>,
//         sls::facets::cc_greedy_facet<inner_state>,
//         sls::facets::age_facet<inner_state>,
//         sls::facets::truth_facet<inner_state>,
//         sls::facets::watcher_facet<inner_state>,
//         sls::facets::avg_weight_facet<inner_state>,
//         sls::facets::unsat_facet<inner_state>
//     >
// > swcc_state_type;

// typedef sls::state::state<
//     sat,
//     properties,
//     sls::facets::facet_compositor<
//         inner_state,
//         sls::facets::neighbour_facet<inner_state>,
//         sls::facets::cca_greedy_facet<inner_state>,
//         sls::facets::age_facet<inner_state>,
//         sls::facets::truth_facet<inner_state>,
//         sls::facets::watcher_facet<inner_state>,
//         sls::facets::avg_weight_facet<inner_state>,
//         sls::facets::unsat_facet<inner_state>
//     >
// > swcca_state_type;

// typedef sls::state::state<
//     sat,
//     properties,
//     sls::facets::facet_compositor<
//         inner_state,
//         sls::facets::neighbour_facet<inner_state>,
//         sls::facets::tcc_greedy_facet<inner_state>,
//         sls::facets::age_facet<inner_state>,
//         sls::facets::truth_facet<inner_state>,
//         sls::facets::watcher_facet<inner_state>,
//         sls::facets::avg_weight_facet<inner_state>,
//         sls::facets::unsat_facet<inner_state>
//     >
// > swqcc_state_type;

// typedef sls::state::state<
//     sat,
//     properties,
//     sls::facets::facet_compositor<
//         inner_state,
//         sls::facets::neighbour_facet<inner_state>,
//         sls::facets::tcca_greedy_facet<inner_state>,
//         sls::facets::age_facet<inner_state>,
//         sls::facets::truth_facet<inner_state>,
//         sls::facets::watcher_facet<inner_state>,
//         sls::facets::avg_weight_facet<inner_state>,
//         sls::facets::unsat_facet<inner_state>
//     >
// > swqcca_state_type;

// } /* unnamed */


// sls::solvers::solver_base* const create_swcc_sat_solver(
//                                             problem const& problem, 
//                                             sls::util::commandline const& cmd)
// {
//     std::cerr << "c create swcc sat solver" << std::endl;
//     typedef swcc_state_type state_type;

//     return new sls::solvers::gensat<state_type>(
//                     problem,
//                     *(new sls::transitions::default_initializer<state_type>()),
//                     *(new sls::transitions::default_transitor<state_type>()),
//                     new sls::selectors::compositor<state_type>
//                     {
//                         new sls::selectors::greedy<state_type>(),
//                         new sls::selectors::reweighting_selector<state_type>(
//                             new sls::selectors::oldest<state_type>(),
//                             new sls::reweight::swcc<state_type>())
//                     });
// }

// sls::solvers::solver_base* const create_swcca_sat_solver(
//                                             problem const& problem, 
//                                             sls::util::commandline const& cmd)
// {
//     std::cerr << "c create swcca sat solver" << std::endl;
//     typedef swcca_state_type state_type;

//     return new sls::solvers::gensat<state_type>(
//                     problem,
//                     *(new sls::transitions::default_initializer<state_type>()),
//                     *(new sls::transitions::default_transitor<state_type>()),
//                     new sls::selectors::compositor<state_type>
//                     {
//                         new sls::selectors::ccd<state_type>(),
//                         new sls::selectors::sd<state_type>(),
//                         new sls::selectors::reweighting_selector<state_type>(
//                             new sls::selectors::oldest<state_type>(),
//                             new sls::reweight::swcc<state_type>())
//                     });
// }

// sls::solvers::solver_base* const create_swqcc_sat_solver(
//                                             problem const& problem, 
//                                             sls::util::commandline const& cmd)
// {
//     std::cerr << "c create swqcc sat solver" << std::endl;
//     typedef swqcc_state_type state_type;

//     return new sls::solvers::gensat<state_type>(
//                     problem,
//                     *(new sls::transitions::default_initializer<state_type>()),
//                     *(new sls::transitions::default_transitor<state_type>()),
//                     new sls::selectors::compositor<state_type>
//                     {
//                         new sls::selectors::ccd<state_type>(),
//                         new sls::selectors::reweighting_selector<state_type>(
//                             new sls::selectors::oldest<state_type>(),
//                             new sls::reweight::swqcc<state_type>())
//                     });
// }

sls::solvers::solver_base* const create_swqcca_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd)
{
    std::cerr << "c create swqcca sat solver" << std::endl;

    return new sls::solvers::gensat<swqcca::state>(
                    problem,
                    *(new sls::transitions::default_initializer<swqcca::state>()),
                    *(new sls::transitions::default_transitor<swqcca::state>()),

                    new sls::selectors::compositor<swqcca::state>
                    {
                        new sls::selectors::greedy_nth<swqcca::state, 1u>(),
                        new sls::selectors::greedy_nth<swqcca::state, 2u>(),
                        new sls::selectors::reweighting_selector<swqcca::state>(
                            new sls::selectors::oldest<swqcca::state>(),
                        	new sls::reweight::swqcca<swqcca::state>())
                    });
}


} /* frontend */ } /* sls */