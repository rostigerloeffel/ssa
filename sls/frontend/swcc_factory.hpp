#ifndef _SLS_FRONTEND_SWCC_FACTORY_HPP_
#define _SLS_FRONTEND_SWCC_FACTORY_HPP_


#include "../util/commandline.hpp"

#include "problem_types.hpp"
#include "usability.hpp"

#include "../state/state.hpp"
#include "../state/inner_state.hpp"

#include "../facets/facet_compositor.hpp"
#include "../facets/truth_facet.hpp"
#include "../facets/unsat_facet.hpp"
#include "../facets/watcher_facet.hpp"
#include "../facets/age_facet.hpp"
#include "../facets/neighbour_facet.hpp"
#include "../facets/greedy_score_tcc_facet.hpp"
#include "../facets/greedy_sd_score_facet.hpp"
#include "../facets/greedy_accessor_facet.hpp"
#include "../facets/tcc_sender_facet.hpp"
#include "../facets/score_sender_facet.hpp"
#include "../facets/weight_facet.hpp"
#include "../facets/avg_weight_facet.hpp"

#include "../selectors/compositor.hpp"
#include "../selectors/greedy.hpp"
#include "../selectors/reweighting_selector.hpp"
#include "../selectors/oldest.hpp"
#include "../selectors/reporting_selector.hpp"

#include "../reweight/swcc.hpp"

#include "../sat/standard/sat.hpp"

#include "../properties/common_variable_properties.hpp"
#include "../properties/common_clause_properties.hpp"

#include "../solvers/gensat.hpp"

#include "../transitions/transition_typedefs.hpp"


namespace sls { namespace frontend {


sls::solvers::solver_base* const create_swcc_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd);

sls::solvers::solver_base* const create_swcca_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd);

sls::solvers::solver_base* const create_swqcc_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd);

sls::solvers::solver_base* const create_swqcca_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd);


} /* frontend */ } /* sls */


#endif