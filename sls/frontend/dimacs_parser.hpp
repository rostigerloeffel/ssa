#ifndef _SLS_FRONTEND_DIMACS_PARSER_HPP_
#define _SLS_FRONTEND_DIMACS_PARSER_HPP_


#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <unordered_set>
#include "problem_types.hpp"


namespace sls { namespace frontend {

namespace {

inline std::vector<std::string> tokenize(std::string const& line)
{
    std::vector<std::string> tokens;

    auto pos = line.find_first_not_of(" ");
    auto pos2 = std::string::npos;
    while(pos != std::string::npos)
    {
        pos2 = line.find_first_of(" ", pos);

        tokens.push_back(line.substr(pos, pos2 - pos));

        pos = line.find_first_not_of(" ", (pos2 == std::string::npos) ? pos2 : pos2 + 1);
    }

    return tokens;
}

} /* unnamed */

struct dimacs_clause : public weighted_clause
{
	dimacs_clause()
		: weighted_clause { std::vector<int>(), 0ul }
	{}
/*
	std::vector<int> literals;
	size_t weight;
	bool is_hard;*/
};

struct dimacs_problem : public problem
{
/*	dimacs_problem()
		: is_weighted(false), is_partial(false), clauses(), clause_count(0ul), variable_count(0ul), hard_clause_count(0ul), top_weight(std::numeric_limits<size_t>::max())
	{}

	bool is_weighted;
	bool is_partial;
	std::vector<dimacs_clause> clauses;
	size_t clause_count;
	size_t variable_count;
	size_t hard_clause_count;
    size_t top_weight;*/
};

inline dimacs_problem parse_dimacs(std::istream& cnf)
{
	dimacs_problem problem;
	bool wcnf = false;
	size_t soft_clause_count = 0ul;

    while(!cnf.eof())
    {
        std::string line;
        std::getline(cnf, line);
        auto tokens = tokenize(line);

        if(tokens.empty())
        	continue;

        if(tokens[0] == "p")
        {
        	if(tokens[1] == "cnf")
        		wcnf = false;
        	else if(tokens[1] == "wcnf")
        		wcnf = true;
        	else
        	{
        		std::cerr << "c warning: invalid dimacs header (" << line << "), abort parsing!" << std::endl;
        		return problem;
        	}

            problem.variable_count 	= std::stoi(tokens[2]);
            problem.clause_count    = std::stoi(tokens[3]);
            problem.clauses.resize(problem.clause_count);

            if(tokens.size() > 4)
            {
            	problem.top_weight = static_cast<size_t>(std::stoi(tokens[4]));
            	problem.is_partial = true;
            }
        }
        else if(tokens[0] != "c")
        {
            std::unordered_set<int>             clause_literals;
            std::unordered_set<unsigned int>    clause_variables;
            dimacs_clause						clause;

            if(wcnf)
            	clause.weight = static_cast<size_t>(std::stoi(tokens[0]));

            for(size_t i = (wcnf ? 1 : 0); i < tokens.size() - 1; ++i)
            {
                clause_literals.insert(std::stoi(tokens[i]));
                clause_variables.insert(std::abs(std::stoi(tokens[i])));
            }

            if(clause_literals.size() == clause_variables.size() && clause_literals.size() > 0)
            {
            	clause.literals.resize(clause_literals.size());
            	std::copy(clause_literals.begin(), clause_literals.end(), clause.literals.begin());

            	if(clause.weight >= problem.top_weight)
            	{	
            		//clause.is_hard = true;
            		problem.clauses[problem.hard_clause_count] = clause; 
            		++problem.hard_clause_count;
            	}
            	else
            	{
            		//clause.is_hard = false;
            		problem.clauses[problem.clause_count - soft_clause_count - 1] = clause;
            		++soft_clause_count;
            	}

            	if(clause.weight > 1 && clause.weight < problem.top_weight)
            		problem.is_weighted = true;
            }
            else
            {
                std::cout << "c warning: drop tautology (" << line << ")" << std::endl;
                problem.clauses[problem.clause_count - soft_clause_count - 1] = problem.clauses[problem.clause_count - 1];
                --problem.clause_count;
            }
        }
    }

    problem.clauses.resize(problem.clause_count);

    return problem;
}

inline dimacs_problem parse_dimacs_from_file(std::string const& path)
{
    std::fstream in(path.c_str());
    std::istream stream(in.rdbuf());

    return parse_dimacs(stream);
}

/*
namespace {

std::vector<clause> copy_dimacs_clauses(std::vector<dimacs_clause> const& dimacs, size_t start = 0ul, size_t end = 0ul)
{
    end = (end > 0ul ? end : dimacs.size());

    std::vector<clause> clauses;
    clauses.reserve(end - start);

    for(auto i = start; i < end; ++i)
        clauses.push_back(clause { dimacs[i].literals });

    return clauses;
}

std::vector<weighted_clause> copy_weighted_dimacs_clauses(std::vector<dimacs_clause> const& dimacs, size_t start = 0ul, size_t end = 0ul)
{
    end = (end > 0ul ? end : dimacs.size());

    std::vector<weighted_clause> clauses;
    clauses.reserve(end - start);

    for(auto i = start; i < end; ++i)
        clauses.push_back(weighted_clause { dimacs[i].literals, dimacs[i].weight });

    return clauses;
}


template<typename ProblemType>
struct dimacs_converter;

template<>
struct dimacs_converter<sat_problem>
{
    static sat_problem convert(dimacs_problem const& dimacs)
    {
        return sat_problem { 
            copy_dimacs_clauses(dimacs.clauses), dimacs.variable_count };
    }
};

template<>
struct dimacs_converter<maxsat_problem>
{
    static maxsat_problem convert(dimacs_problem const& dimacs)
    {
        return maxsat_problem { 
            copy_dimacs_clauses(dimacs.clauses), dimacs.variable_count };
    }
};

template<>
struct dimacs_converter<partial_maxsat_problem>
{
    static partial_maxsat_problem convert(dimacs_problem const& dimacs)
    {
        return partial_maxsat_problem { 
            copy_weighted_dimacs_clauses(dimacs.clauses, 0, dimacs.hard_clause_count), 
            copy_weighted_dimacs_clauses(dimacs.clauses, dimacs.hard_clause_count),
            dimacs.variable_count,
            dimacs.top_weight };
    }
};

template<>
struct dimacs_converter<weighted_maxsat_problem>
{
    static weighted_maxsat_problem convert(dimacs_problem const& dimacs)
    {
        return weighted_maxsat_problem { 
            copy_weighted_dimacs_clauses(dimacs.clauses), dimacs.variable_count };
    }
};

template<>
struct dimacs_converter<partial_weighted_maxsat_problem>
{
    static partial_weighted_maxsat_problem convert(dimacs_problem const& dimacs)
    {
        return partial_weighted_maxsat_problem { 
            copy_weighted_dimacs_clauses(dimacs.clauses, 0, dimacs.hard_clause_count), 
            copy_weighted_dimacs_clauses(dimacs.clauses, dimacs.hard_clause_count),
            dimacs.variable_count,
            dimacs.top_weight };
    }
};

}


template<typename ProblemType>
ProblemType dimacs_to(dimacs_problem const& dimacs)
{
    return dimacs_converter<ProblemType>::convert(dimacs);
}
*/

} /* frontend */ } /* sls */


#endif