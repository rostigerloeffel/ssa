#include "swcc_factory.hpp"


namespace ssa { namespace frontend {


template<typename State, typename InnerState>
using swqcca_facets = sls::facets::facet_compositor<
    State, InnerState,
    sls::facets::neighbour_facet<State, InnerState>,
    sls::facets::greedy_score_tcc_age_facet<State, InnerState>,
    sls::facets::score_sender_facet<State, InnerState,
    	sls::facets::greedy_score_tcc_age_facet<State, InnerState>>,
    sls::facets::tcc_sender_facet<State, InnerState,
    	sls::facets::greedy_score_tcc_age_facet<State, InnerState>>,
    sls::facets::age_facet<State, InnerState>,
    sls::facets::truth_facet<State, InnerState>,
    sls::facets::watcher_facet<State, InnerState>,
    sls::facets::weight_facet<State, InnerState>,
    sls::facets::unsat_facet<State, InnerState>
>;

declare_state(swqcca,
    declare_sat_backend(standard::sat),

    declare_properties(
            variable_props(truth, age, score, tcc, blocked, neighbours<typename sat::variable_type>),
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


// ssa::solvers::solver_base* const create_swcc_sat_solver(
//                                             problem const& problem, 
//                                             sls::util::commandline const& cmd)
// {
//     std::cerr << "c create swcc sat solver" << std::endl;
//     typedef swcc_state_type state_type;

//     return new ssa::solvers::gensat<state_type>(
//                     problem,
//                     *(new ssa::transitions::default_initializer<state_type>()),
//                     *(new ssa::transitions::default_transitor<state_type>()),
//                     new sls::selectors::compositor<state_type>
//                     {
//                         new sls::selectors::greedy<state_type>(),
//                         new sls::selectors::reweighting_selector<state_type>(
//                             new sls::selectors::oldest<state_type>(),
//                             new ssa::reweight::swcc<state_type>())
//                     });
// }

// ssa::solvers::solver_base* const create_swcca_sat_solver(
//                                             problem const& problem, 
//                                             sls::util::commandline const& cmd)
// {
//     std::cerr << "c create swcca sat solver" << std::endl;
//     typedef swcca_state_type state_type;

//     return new ssa::solvers::gensat<state_type>(
//                     problem,
//                     *(new ssa::transitions::default_initializer<state_type>()),
//                     *(new ssa::transitions::default_transitor<state_type>()),
//                     new sls::selectors::compositor<state_type>
//                     {
//                         new sls::selectors::ccd<state_type>(),
//                         new sls::selectors::sd<state_type>(),
//                         new sls::selectors::reweighting_selector<state_type>(
//                             new sls::selectors::oldest<state_type>(),
//                             new ssa::reweight::swcc<state_type>())
//                     });
// }

// ssa::solvers::solver_base* const create_swqcc_sat_solver(
//                                             problem const& problem, 
//                                             sls::util::commandline const& cmd)
// {
//     std::cerr << "c create swqcc sat solver" << std::endl;
//     typedef swqcc_state_type state_type;

//     return new ssa::solvers::gensat<state_type>(
//                     problem,
//                     *(new ssa::transitions::default_initializer<state_type>()),
//                     *(new ssa::transitions::default_transitor<state_type>()),
//                     new sls::selectors::compositor<state_type>
//                     {
//                         new sls::selectors::ccd<state_type>(),
//                         new sls::selectors::reweighting_selector<state_type>(
//                             new sls::selectors::oldest<state_type>(),
//                             new ssa::reweight::swqcc<state_type>())
//                     });
// }

ssa::solvers::solver_base* const create_swqcca_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd)
{
    std::cerr << "c create swqcca sat solver" << std::endl;

    return new ssa::solvers::gensat<swqcca::state>(
                    problem,
                    *(new ssa::transitions::default_initializer<swqcca::state>()),
                    *(new ssa::transitions::default_transitor<swqcca::state>()),

                    new sls::selectors::compositor<swqcca::state>
                    {
                        new sls::selectors::greedy<swqcca::state>(),
                        new sls::selectors::reweighting_selector<swqcca::state>(
                            new sls::selectors::oldest<swqcca::state>(),
                            new ssa::reweight::swqcca<swqcca::state>())
                    });
}


} /* frontend */ } /* ssa */