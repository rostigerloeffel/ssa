#include "sattime_factory.hpp"


namespace ssa { namespace frontend {


namespace {

typedef sls::sat::standard::sat sat;

struct variable : 
            public sls::properties::truth, 
            public sls::properties::age, 
            public sls::properties::score {};
struct literal {};
struct clause : 
            public sls::properties::watcher2<typename sat::variable_type>, 
            public sls::properties::num_true_literals,
            public sls::properties::satisfying_literal<typename sat::variable_type>, 
            public sls::properties::weight {};

struct properties
{
    typedef variable variable_properties_type;
    typedef literal literal_properties_type;
    typedef clause clause_properties_type;
};

typedef sls::state::inner_state<sat, properties> inner_state;

typedef sls::state::state<
    sat,
    properties,
    sls::facets::facet_compositor<
        inner_state,
        sls::facets::age_facet<inner_state>,
        sls::facets::truth_facet<inner_state>,
        sls::facets::promising_age_facet<inner_state>,
        sls::facets::watcher_facet<inner_state>,
        sls::facets::weight_facet<inner_state>,
        sls::facets::broken_facet<inner_state>,
        sls::facets::satisfying_facet<inner_state>
    >
> state_type;

} /* unnamed */


ssa::solvers::solver_base* const create_sattime_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd)
{
    return new ssa::solvers::gensat<state_type>(
                    problem,
                    *(new ssa::transitions::default_initializer<state_type>()),
                    *(new ssa::transitions::watch2_sat_transitor<state_type>()),
                    new sls::selectors::compositor<state_type>
                    {
                            new sls::selectors::greedy<state_type>(),
                            new sls::selectors::plus<state_type>(
                                new sls::selectors::sattime<state_type>())
                    });
}


} /* frontend */ } /* ssa */