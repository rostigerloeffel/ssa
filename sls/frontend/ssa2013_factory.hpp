#ifndef __SSA_FRONTEND_SSA2013_FACTORY_HPP__
#define __SSA_FRONTEND_SSA2013_FACTORY_HPP__


#include "../util/commandline.hpp"

#include "problem_types.hpp"

#include "../state/state.hpp"
#include "../state/inner_state.hpp"

#include "../facets/facet_compositor.hpp"
#include "../facets/truth_facet.hpp"
#include "../facets/promising_greedy_facet.hpp"
#include "../facets/unsat_facet.hpp"
#include "../facets/watcher_facet.hpp"
#include "../facets/avg_weight_facet.hpp"
#include "../facets/age_facet.hpp"
#include "../facets/neighbour_facet.hpp"
#include "../facets/tcca_greedy_facet.hpp"
#include "../facets/score_sender_facet.hpp"
#include "../facets/greedy_score_facet.hpp"

#include "../selectors/compositor.hpp"
#include "../selectors/ccd.hpp"
#include "../selectors/sd.hpp"
#include "../selectors/reweighting_selector.hpp"
#include "../selectors/oldest.hpp"
#include "../selectors/sparrow_cca.hpp"
#include "../selectors/reporting_selector.hpp"

#include "../reweight/swcc.hpp"

#include "../sat/standard/sat.hpp"

#include "../properties/common_variable_properties.hpp"
#include "../properties/common_clause_properties.hpp"

#include "../solvers/gensat.hpp"

#include "../transitions/transition_typedefs.hpp"


namespace ssa { namespace frontend {


ssa::solvers::solver_base* const create_ssa2013_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd);


} /* frontend */ } /* ssa */


#endif