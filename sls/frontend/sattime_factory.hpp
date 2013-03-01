#ifndef __SSA_FRONTEND_SATTIME_FACTORY_HPP__
#define __SSA_FRONTEND_SATTIME_FACTORY_HPP__


#include "../util/commandline.hpp"

#include "problem_types.hpp"

#include "../state/state.hpp"
#include "../state/inner_state.hpp"

#include "../facets/facet_compositor.hpp"
#include "../facets/truth_facet.hpp"
#include "../facets/age_facet.hpp"
#include "../facets/promising_greedy_facet.hpp"
#include "../facets/broken_facet.hpp"
#include "../facets/watcher_facet.hpp"
#include "../facets/weight_facet.hpp"
#include "../facets/static_weight_facet.hpp"
#include "../facets/unsat_weightsum_facet.hpp"
#include "../facets/satisfying_facet.hpp"

#include "../selectors/compositor.hpp"
#include "../selectors/greedy.hpp"
#include "../selectors/sattime.hpp"
#include "../selectors/plus.hpp"

#include "../sat/standard/sat.hpp"

#include "../properties/common_variable_properties.hpp"
#include "../properties/common_clause_properties.hpp"

#include "../solvers/gensat.hpp"

#include "../transitions/transition_typedefs.hpp"


namespace ssa { namespace frontend {


ssa::solvers::solver_base* const create_sattime_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd);


} /* frontend */ } /* ssa */


#endif