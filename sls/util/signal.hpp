#ifndef __SLS_UTIL_SIGNAL_HPP__
#define __SLS_UTIL_SIGNAL_HPP__


#include <iostream>
#include <csignal>


namespace sls
{


namespace util
{


namespace internal
{


static bool interrupted = false;


} /* internal */


inline bool is_interrupted()
{
	return internal::interrupted;
}


inline bool unset_interrupt()
{
	internal::interrupted = false;
}


inline void termination_handler(int signal)
{
	if(!is_interrupted())
	{
		std::cerr << "c caught signal " << signal << ", abort computation!" << std::endl;
		internal::interrupted = true;
	}
	else
	{
		std::cerr << "c caught signal " << signal << " another time, abort immediately!" << std::endl;
		exit(0);
	}
}


} /* util */


} /* sls */


#endif