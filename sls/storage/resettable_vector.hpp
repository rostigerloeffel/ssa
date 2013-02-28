#ifndef __SLS_STORAGE_RESETTABLE_VECTOR_HPP__
#define __SLS_STORAGE_RESETTABLE_VECTOR_HPP__


#include <vector>


namespace sls
{


namespace storage
{


template
<
	typename ValueType,
	typename AllocType = std::allocator<ValueType>
>
class resettable_vector : public std::vector<ValueType, AllocType>
{
public:
	typedef std::vector<ValueType, AllocType>					vector_type;
	typedef ValueType                    						value_type;
   	typedef typename vector_type::pointer               		pointer;
   	//typedef typename _Alloc_traits::const_pointer      			const_pointer;
   	//typedef typename _Alloc_traits::reference          			reference;
   	//typedef typename _Alloc_traits::const_reference    			const_reference;
   	//typedef __gnu_cxx::__normal_iterator<pointer, vector> 		iterator;
   	//typedef __gnu_cxx::__normal_iterator<const_pointer, vector>	const_iterator;
   	//typedef std::reverse_iterator<const_iterator>  				const_reverse_iterator;
   	//typedef std::reverse_iterator<iterator>        				reverse_iterator;
   	typedef size_t                     							size_type;
   	//typedef ptrdiff_t                  							difference_type;
   	typedef AllocType                                 			allocator_type;

protected:
   	using vector_type::_M_allocate;
   	using vector_type::_M_deallocate;
   	using vector_type::_M_impl;
   	using vector_type::_M_get_Tp_allocator;

public:
	inline void reset()
	{
		this->_M_impl._M_finish = this->_M_impl._M_start;
	}
};


} /* storage */


} /* sls */


#endif