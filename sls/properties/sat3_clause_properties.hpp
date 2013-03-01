#ifndef _SLS_PROPERTIES_SAT3_CLAUSE_PROPERTIES_HPP__
#define _SLS_PROPERTIES_SAT3_CLAUSE_PROPERTIES_HPP__


namespace sls
{


namespace properties
{


template<typename VariableType>
struct sat3_clause_properties
{
	VariableType watcher1;
	VariableType watcher2;
	uint8_t num_true_literals : 2;
	uint8_t weight : 6;
};


} /* properties */


} /* sls */


#endif