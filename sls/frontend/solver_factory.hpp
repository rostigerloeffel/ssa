#ifndef _SLS_FRONTEND_SOLVER_FACTORY_HPP_
#define _SLS_FRONTEND_SOLVER_FACTORY_HPP_


#include <iostream>
#include <string>
#include "../util/commandline.hpp"
#include "dimacs_parser.hpp"
#include "problem_types.hpp"
#include "walksat_factory.hpp"
/*#include "sparrow_factory.hpp"
#include "swcc_factory.hpp"
#include "sattime_factory.hpp"
#include "ssa2013_factory.hpp"*/


namespace sls { namespace frontend {


inline sls::solvers::solver_base* const create_sat_solver(
                                                problem const& problem, 
                                                sls::util::commandline const& cmd)
{
    return create_walksat_sat_solver(problem, cmd);
}

inline sls::solvers::solver_base* const create_maxsat_solver(
                                                problem const& problem, 
                                                sls::util::commandline const& cmd)
{
    return create_walksat_sat_solver(problem, cmd);
}

inline sls::solvers::solver_base* const create_weighted_maxsat_solver(
                                                problem const& problem, 
                                                sls::util::commandline const& cmd)
{
    return create_walksat_sat_solver(problem, cmd);
}

inline sls::solvers::solver_base* const create_solver(
                                                sls::util::commandline const& cmd)
{
    auto file   = cmd.get("-file", std::string("test.cnf"));
    auto dimacs = parse_dimacs_from_file(file);

    if(cmd.get("-type", std::string("auto")) == "weighted-maxsat")
    {
        std::cerr << "c initialize weighted-maxsat solver" << std::endl;
        return create_weighted_maxsat_solver(dimacs, cmd);
    }
    else if(cmd.get("-type", std::string("auto")) == "maxsat")
    {
        std::cerr << "c initialize (unweighted-)maxsat solver" << std::endl;
        return create_maxsat_solver(dimacs, cmd);
    }
    else if(cmd.get("-type", std::string("auto")) == "sat")
    {
        std::cerr << "c initialize sat solver" << std::endl;
        return create_sat_solver(dimacs, cmd);
    }
    else // if(cmd.get("-type"), std::string("auto") == "auto")
    {
        std::cerr << "c recognize type from file : ";
        if(dimacs.is_weighted || dimacs.is_partial)
        {
            std::cerr << "weighted maxsat" << std::endl;
            return create_weighted_maxsat_solver(dimacs, cmd);
        }
        else // !dimacs.is_weighted && !dimacs.is_partial
        {
            std::cerr << "sat" << std::endl;
            return create_sat_solver(dimacs, cmd);
        }
    }
}


} /* frontend */ } /* sls */


#endif