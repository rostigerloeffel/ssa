#include "walksat_factory.hpp"


namespace sls { namespace frontend {



typedef sls::sat::standard::sat sat;

DECL_PROPERTIES(walksat, 
    VAR(truth, score),
    LIT(empty),
    CLAUSE(watcher2<typename sat::variable_type>, num_true_literals))
DECL_FACETS(facets, truth_facet, breakcount_facet, watcher_facet, unsat_facet, null_weight_facet)
DECL_STATE(walksat, sat, walksat::properties, facets)


//} /* unnamed */


::sls::solvers::solver_base* const create_walksat_sat_solver(
                                            sls::frontend::problem const& problem,
                                            sls::util::commandline const& cmd)
{
    std::cerr << "c create walksat sat solver" << std::endl;

    return new sls::solvers::gensat<walksat_state>(
                    problem,
                    *(new sls::transitions::default_initializer<walksat_state>()),
                    *(new sls::transitions::default_transitor<walksat_state>()),
                    new sls::selectors::wsat<walksat_state>());
}


} /* frontend */ } /* sls */