#include "ssa2013_factory.hpp"


namespace ssa { namespace frontend {


// namespace {

// typedef sls::sat::standard::sat sat;

// struct variable : 
//             public sls::properties::neighbours<typename sat::variable_type>,
//             public sls::properties::tcc,
//             public sls::properties::truth, 
//             public sls::properties::age, 
//             public sls::properties::score {};
// struct literal {};
// struct clause : 
//             public sls::properties::watcher2<typename sat::variable_type>, 
//             public sls::properties::num_true_literals, 
//             public sls::properties::weight {};

// struct properties
// {
//     typedef variable variable_properties_type;
//     typedef literal literal_properties_type;
//     typedef clause clause_properties_type;
// };

// typedef sls::state::inner_state<sat, properties> inner_state;

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
//         sls::facets::broken_facet<inner_state>
//     >
// > ssa2013_state_type;

// } /* unnamed */


// ssa::solvers::solver_base* const create_ssa2013_sat_solver(
//                                             problem const& problem, 
//                                             sls::util::commandline const& cmd)
// {
//     std::cerr << "c create ssa2013 sat solver" << std::endl;
//     typedef ssa2013_state_type state_type;

//     return new ssa::solvers::gensat<state_type>(
//                     problem,
//                     *(new ssa::transitions::default_initializer<state_type>()),
//                     *(new ssa::transitions::default_transitor<state_type>()),
                    
//                     //new sls::selectors::reporting_selector<state_type>(
//                         new sls::selectors::compositor<state_type>
//                         {
//                             new sls::selectors::ccd<state_type>(),
//                             new sls::selectors::sd<state_type>(),
//                             new sls::selectors::reweighting_selector<state_type>(
//                                 //new sls::selectors::reporting_selector<state_type>(
//                                     new sls::selectors::sparrow_cca<state_type>()
//                                 //)
//                                 ,
//                                 //new sls::selectors::oldest<state_type>(),
//                                 new ssa::reweight::swqcca<state_type>())
//                         }
//                     //)
//                     );
// }


} /* frontend */ } /* ssa */