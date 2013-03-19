#ifndef _SLS_UTIL_SPARROW_FACTORY_HPP_
#define _SLS_UTIL_SPARROW_FACTORY_HPP_


#include "../util/commandline.hpp"

#include "problem_types.hpp"
#include "usability.hpp"

#include "../state/state.hpp"
#include "../state/inner_state.hpp"

#include "../facets/facet_compositor.hpp"
#include "../facets/truth_facet.hpp"
#include "../facets/age_facet.hpp"
#include "../facets/unsat_facet.hpp"
#include "../facets/watcher_facet.hpp"
#include "../facets/weight_facet.hpp"
//#include "../facets/static_weight_facet.hpp"
//#include "../facets/unsat_weightsum_facet.hpp"
#include "../facets/score_sender_facet.hpp"
#include "../facets/greedy_score_facet.hpp"

#include "../selectors/compositor.hpp"
#include "../selectors/greedy.hpp"
#include "../selectors/reweighting_selector.hpp"
#include "../selectors/sparrow.hpp"

#include "../reweight/sparrow.hpp"

#include "../sat/standard/sat.hpp"
#include "../sat/ksat/sat.hpp"

#include "../properties/common_variable_properties.hpp"
#include "../properties/common_clause_properties.hpp"

#include "../solvers/gensat.hpp"
// #include "../solvers/maxsat.hpp"
// #include "../solvers/weighted_maxsat.hpp"

#include "../transitions/transition_typedefs.hpp"


namespace sls { namespace frontend {


sls::solvers::solver_base* const create_sparrow_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd);

sls::solvers::solver_base* const create_sparrow_maxsat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd);

sls::solvers::solver_base* const create_sparrow_weighted_maxsat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd);


} /* frontend */ } /* sls */


#endif