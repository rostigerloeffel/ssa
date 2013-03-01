#ifndef __SSA_SOLVERS_SOLVER_BASE_HPP__
#define __SSA_SOLVERS_SOLVER_BASE_HPP__


namespace ssa { namespace solvers {


class solver_base
{
public:
	virtual std::vector<int> solve() = 0;
};


} /* solvers */ } /* ssa */


#endif