#include "walksat_factory.hpp"


namespace sls { namespace frontend {


namespace {

typedef sls::sat::standard::sat sat;

struct variable : 
            public sls::properties::truth, 
            public sls::properties::score {};
struct literal {};
struct clause : 
            public sls::properties::watcher2<typename sat::variable_type>, 
            public sls::properties::num_true_literals {};
struct properties
{
    typedef variable variable_properties_type;
    typedef literal literal_properties_type;
    typedef clause clause_properties_type;
};

}

template<typename State>
using walksat_facets = sls::facets::facet_compositor<
    State,
    sls::facets::truth_facet<State>,
    sls::facets::breakcount_facet<State>,
    sls::facets::watcher_facet<State>,
    sls::facets::unsat_facet<State>,
    sls::facets::null_weight_facet<State>
>;

DECL_STATE(walksat, sat, properties, sls::frontend::walksat_facets)

//} /* unnamed */


sls::solvers::solver_base* const create_walksat_sat_solver(
                                            problem const& problem,
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