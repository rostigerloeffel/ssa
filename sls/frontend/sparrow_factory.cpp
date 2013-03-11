#include "sparrow_factory.hpp"


namespace sls { namespace frontend {


// declare_state(walksat,
//     declare_sat_backend(standard::sat),

//     declare_properties(
//             variable_props(truth, age, score),
//             literal_props(empty),
//             clause_props(watcher2<typename sat_type::variable_type>, num_true_literals, weight)),

//     declare_facets(truth, breakcount, watcher, unsat, null_weight))


typedef sls::sat::standard::sat sat;

struct variable : 
            public sls::properties::truth, 
            public sls::properties::age, 
            public sls::properties::score {};
struct literal {};
struct clause : 
            public sls::properties::watcher2<typename sat::variable_type>, 
            public sls::properties::num_true_literals, 
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
        sls::facets::greedy_score_age_facet<inner_state>,
        sls::facets::score_sender_facet<inner_state, 
            sls::facets::greedy_score_age_facet<inner_state>
        >,
        sls::facets::watcher_facet<inner_state>,
        sls::facets::weight_facet<inner_state>,
        sls::facets::unsat_facet<inner_state>
    >
> sat_state_type;


// typedef sat_state_type maxsat_state_type;

// typedef sls::state::state<
//     sat,
//     properties,
//     sls::facets::facet_compositor<
//         inner_state,
//         sls::facets::age_facet<inner_state>,
//         sls::facets::truth_facet<inner_state>,
//         sls::facets::promising_greedy_facet<inner_state>,
//         sls::facets::watcher_facet<inner_state>,
//         sls::facets::static_weight_facet<inner_state>,
//         sls::facets::unsat_weightsum_facet<inner_state>
//     >
// > weighted_maxsat_state_type;



template<typename State>
struct sparrow_conf
{
    double sp;
    double c1;
    double c2;
    double c3;
    sls::transitions::transitor_base<State>* transitor;
};

size_t is_ksat(problem const& problem)
{
    auto k = 0ul;
    for(auto clause : problem.clauses)
        if(k > 0ul && k != clause.literals.size())
            return 0ul;
        else
            k = clause.literals.size();

    return k;
}

template<typename State>
sparrow_conf<State> get_conf(
                            problem const& problem, 
                            sls::util::commandline const& cmd)
{
    sparrow_conf<State> conf;

    switch(is_ksat(problem))
    {
        case 7ul:
            conf.sp = cmd.get("-sparrow-sp", 0.83);
            conf.c1 = cmd.get("-sparrow-c1", 6.5);
            conf.c2 = cmd.get("-sparrow-c2", 4.0);
            conf.c3 = cmd.get("-sparrow-c3", 100000.0);
            conf.transitor = new sls::transitions::watch1_transitor<State>();
        break;

        case 5ul:
            conf.sp = cmd.get("-sparrow-sp", 1.0);
            conf.c1 = cmd.get("-sparrow-c1", 2.85);
            conf.c2 = cmd.get("-sparrow-c2", 4.0);
            conf.c3 = cmd.get("-sparrow-c3", 75000.0);
            conf.transitor = new sls::transitions::watch1_transitor<State>();
        break;

        case 3ul:
            conf.sp = cmd.get("-sparrow-sp", 0.347);
            conf.c1 = cmd.get("-sparrow-c1", 2.15);
            conf.c2 = cmd.get("-sparrow-c2", 4.0);
            conf.c3 = cmd.get("-sparrow-c3", 200000.0);
            conf.transitor = new sls::transitions::watch2_transitor<State>();
        break;

        default:
            conf.sp = cmd.get("-sparrow-sp", 0.83);
            conf.c1 = cmd.get("-sparrow-c1", 6.5);
            conf.c2 = cmd.get("-sparrow-c2", 4.0);
            conf.c3 = cmd.get("-sparrow-c3", 100000.0);
            conf.transitor = new sls::transitions::watch2_transitor<State>();
    }

    if(cmd.get("-transitor", std::string("auto")) == "watch2")
        conf.transitor = new sls::transitions::watch2_transitor<State>();
    else if(cmd.get("-transitor", std::string("auto")) == "watch1")
        conf.transitor = new sls::transitions::watch1_transitor<State>();

    std::cout << "c sparrow configuration:" 
              << " c1 = " << conf.c1 
              << " c2 = " << conf.c2 
              << " c3 = " << conf.c3 
              << " sp = " << conf.sp << std::endl;

    return conf;
}

template<typename State>
sls::selectors::selector_base<State>* get_selector(
                                            sls::util::commandline const& cmd,
                                            sparrow_conf<State> const& conf)
{
    return new sls::selectors::compositor<State>{
                    new sls::selectors::greedy<State>(),
                    new sls::selectors::reweighting_selector<State>(
                        new sls::selectors::sparrow<State>(conf.c1, conf.c2, conf.c3),
                        new sls::reweight::sparrow<State>(conf.sp))};
}


sls::solvers::solver_base* const create_sparrow_sat_solver(
                                            problem const& problem, 
                                            sls::util::commandline const& cmd)
{
    std::cerr << "c create sparrow sat solver" << std::endl;

    typedef sat_state_type state_type;

    auto conf = get_conf<state_type>(problem, cmd);

    return new sls::solvers::gensat<state_type>(
                    problem,
                    *(new sls::transitions::default_initializer<state_type>()),
                    *(conf.transitor),
                    get_selector(cmd, conf));
}

// sls::solvers::solver_base* const create_sparrow_maxsat_solver(
//                                             problem const& problem, 
//                                             sls::util::commandline const& cmd)
// {
//     std::cerr << "c create sparrow maxsat solver" << std::endl;

//     typedef maxsat_state_type state_type;

//     auto conf = get_conf<state_type>(problem, cmd);

//     return new sls::solvers::maxsat<state_type>(
//                     problem,
//                     cmd.get("-maxtime", 300.0),
//                     *(new sls::transitions::default_initializer<state_type>()),
//                     *(conf.transitor),
//                     get_selector(cmd, conf));
// }

// sls::solvers::solver_base* const create_sparrow_weighted_maxsat_solver(
//                                             problem const& problem, 
//                                             sls::util::commandline const& cmd)
// {
//     std::cerr << "c create sparrow weighted maxsat solver" << std::endl;

//     typedef weighted_maxsat_state_type state_type;

//     auto conf = get_conf<state_type>(problem, cmd);

//     return new sls::solvers::weighted_maxsat<state_type>(
//                     problem,
//                     cmd.get("-maxtime", 300.0),
//                     *(new sls::transitions::weighted_initializer<state_type>()),
//                     *(conf.transitor),
//                     get_selector(cmd, conf));
// }


} /* frontend */ } /* sls */