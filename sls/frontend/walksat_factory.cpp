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

template<typename State, typename InnerState>
using facets = sls::facets::facet_compositor<
    State, InnerState,
    sls::facets::neighbour_facet<State, InnerState>,
    sls::facets::cc_greedy_facet<State, InnerState>,
    sls::facets::age_facet<State, InnerState>,
    sls::facets::truth_facet<State, InnerState>,
    sls::facets::watcher_facet<State, InnerState>,
    sls::facets::avg_weight_facet<State, InnerState>,
    sls::facets::broken_facet<State, InnerState>
>;

DECL_STATE(walksat, sat, properties, facets)

} /* unnamed */


ssa::solvers::solver_base* const create_walksat_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd)
{
    std::cerr << "c create walksat sat solver" << std::endl;

    return new ssa::solvers::gensat<walksat_state>(
                    problem,
                    *(new ssa::transitions::default_initializer<walksat_state>()),
                    *(new ssa::transitions::default_transitor<walksat_state>()),
                    new sls::selectors::wsat<walksat_state>());
}


} /* frontend */ } /* sls */