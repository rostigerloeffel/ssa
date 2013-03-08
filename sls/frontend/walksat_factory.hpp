#ifndef _SLS_UTIL_SPARROW_FACTORY_HPP_
#define _SLS_UTIL_SPARROW_FACTORY_HPP_


#include <iostream>

#include "../util/commandline.hpp"

#include "problem_types.hpp"
#include "frontend_lang.hpp"
#include "usability.hpp"

#include "../state/state.hpp"
#include "../state/inner_state.hpp"

#include "../facets/facet_compositor.hpp"
#include "../facets/truth_facet.hpp"
#include "../facets/unsat_facet.hpp"
#include "../facets/watcher_facet.hpp"
#include "../facets/breakcount_facet.hpp"
#include "../facets/null_weight_facet.hpp"

#include "../sat/standard/sat.hpp"
#include "../sat/ksat/sat.hpp"

#include "../properties/common_variable_properties.hpp"
#include "../properties/common_clause_properties.hpp"

#include "../selectors/wsat.hpp"

#include "../solvers/gensat.hpp"

#include "../transitions/transition_typedefs.hpp"


namespace sls { namespace frontend {


sls::solvers::solver_base* const create_walksat_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd);


} /* frontend */ } /* sls */


#endif