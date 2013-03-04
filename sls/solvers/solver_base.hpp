#ifndef _SLS_SOLVERS_SOLVER_BASE_HPP_
#define _SLS_SOLVERS_SOLVER_BASE_HPP_


namespace sls { namespace solvers {


class solver_base
{
public:
	virtual std::vector<int> solve() = 0;
};


} /* solvers */ } /* sls */


#endif