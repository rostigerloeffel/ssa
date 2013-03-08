#include "walksat_factory.hpp"


namespace sls { namespace frontend {


declare_state(walksat,
    declare_sat_backend(standard::sat),

    declare_properties(
            variable_props(truth, score),
            literal_props(empty),
            clause_props(watcher2<typename sat_type::variable_type>, num_true_literals)),

    declare_facets(truth, breakcount, watcher, unsat, null_weight))



::sls::solvers::solver_base* const create_walksat_sat_solver(
                                            sls::frontend::problem const& problem,
                                            sls::util::commandline const& cmd)
{
    std::cerr << "c create walksat sat solver" << std::endl;

    return new sls::solvers::gensat<walksat::state>(
                    problem,
                    *(new sls::transitions::default_initializer<walksat::state>()),
                    *(new sls::transitions::default_transitor<walksat::state>()),
                    new sls::selectors::wsat<walksat::state>());
}


} /* frontend */ } /* sls */