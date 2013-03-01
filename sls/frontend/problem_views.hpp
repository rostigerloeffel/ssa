#ifndef __SSA_FRONTEND_PROBLEM_VIEWS_HPP__
#define __SSA_FRONTEND_PROBLEM_VIEWS_HPP__


#include <vector>
#include <iostream>


namespace ssa { namespace frontend {


struct clause
{
	std::vector<int> literals;
};

struct weighted_clause : public clause
{
	weighted_clause(std::vector<int> const& l, size_t w)
		: clause { l }, weight { w }
	{}

	size_t weight;
};

struct sat_problem
{
	std::vector<clause> clauses;

	size_t variable_count;
};

struct maxsat_problem
{
	std::vector<clause> soft_clauses;

	size_t variable_count;
};

struct partial_maxsat_problem
{
	std::vector<weighted_clause> clauses;
	std::vector<weighted_clause> soft_clauses;

	size_t variable_count;
	size_t top_weight;
};

struct weighted_maxsat_problem
{
	std::vector<weighted_clause> soft_clauses;

	size_t variable_count;
};

struct partial_weighted_maxsat_problem
{
	partial_weighted_maxsat_problem(std::vector<weighted_clause> const& c, std::vector<weighted_clause> const& sc, size_t vc, size_t tw)
		: clauses(c), soft_clauses(sc), variable_count(vc), top_weight(tw)
	{
		std::cout << "init" << std::endl;
	}

	partial_weighted_maxsat_problem(partial_weighted_maxsat_problem const& other)
		: clauses(other.clauses), soft_clauses(other.soft_clauses), variable_count(other.variable_count), top_weight(other.top_weight)
	{
		std::cout << "copy" << std::endl;
	}

	partial_weighted_maxsat_problem(partial_weighted_maxsat_problem&& other)
		: clauses(std::move(other.clauses)), soft_clauses(std::move(other.soft_clauses)), variable_count(std::move(other.variable_count)), top_weight(std::move(other.top_weight))
	{
		std::cout << "move" << std::endl;
	}

	std::vector<weighted_clause> clauses;
	std::vector<weighted_clause> soft_clauses;

	size_t variable_count;
	size_t top_weight;
};

/*
struct problem
{
	problem()
		: 
		is_weighted(false), 
		is_partial(false), 
		clauses(), 
		clause_count(0ul), 
		variable_count(0ul), 
		hard_clause_count(0ul), 
		top_weight(std::numeric_limits<size_t>::max())
	{}

	bool is_weighted;
	bool is_partial;
	std::vector<weighted_clause> clauses;
	size_t clause_count;
	size_t variable_count;
	size_t hard_clause_count;
    size_t top_weight;
};
*/


} /* frontend */ } /* ssa */


#endif