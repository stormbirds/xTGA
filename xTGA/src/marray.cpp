//============ Copyright � 2019 Brett Anthony. All rights reserved. ============
///
/// This work is licensed under the terms of the MIT license.
/// For a copy, see <https://opensource.org/licenses/MIT>.
//==============================================================================
/// file 	: marray.cpp
/// purpose : Provides the definition of a ManagedArray.
//==============================================================================

#include "xTGA/marray.h"

template <class T>
class xtga::ManagedArray<T>::__ManagedArrayImpl
{
public:
	__ManagedArrayImpl(UInt64 size);
	__ManagedArrayImpl(T* data, UInt64 size);
	virtual ~__ManagedArrayImpl();

	T* _rawData;
	UInt64 _size;
	UInt32 _eSize;
};

template <class T>
xtga::ManagedArray<T>::__ManagedArrayImpl::__ManagedArrayImpl(UInt64 size)
{
	this->_rawData = new T[size];
	this->_size = size;
	this->_eSize = sizeof(T);
}

template <class T>
xtga::ManagedArray<T>::__ManagedArrayImpl::__ManagedArrayImpl(T* data, UInt64 size)
{
	this->_rawData = data;
	this->_size = size;
	this->_eSize = sizeof(T);
}

template <class T>
xtga::ManagedArray<T>::__ManagedArrayImpl::~__ManagedArrayImpl()
{
	delete[] this->_rawData;
}

template <class T>
xtga::ManagedArray<T>* xtga::ManagedArray<T>::Alloc(UInt64 size)
{
	auto rval = new xtga::ManagedArray<T>();
	rval->_impl = new __ManagedArrayImpl(size);
	return rval;
}

template <class T>
xtga::ManagedArray<T>* xtga::ManagedArray<T>::Alloc(T* data, UInt64 size)
{
	auto rval = new xtga::ManagedArray<T>();
	rval->_impl = new __ManagedArrayImpl(data, size);
	return rval;
}

template <class T>
void xtga::ManagedArray<T>::Free(ManagedArray<T>*& obj)
{
	delete obj->_impl;
	obj->_impl = nullptr;
	delete obj;
	obj = nullptr;
}

template <typename T>
T& xtga::ManagedArray<T>::at(UInt64 index, ERRORCODE* error)
{
	if (index >= this->_impl->_size)
	{
		XTGA_SETERROR(error, ERRORCODE::INDEX_OUT_OF_RANGE);
		return *this->_impl->_rawData;
	}

	return *(T*)((UChar*)this->_impl->_rawData + (index * this->_impl->_eSize));
}

template <typename T>
T& xtga::ManagedArray<T>::operator[](UInt64 index)
{
	return this->at(index);
}

template <typename T>
UInt64 xtga::ManagedArray<T>::size() const
{
	return this->_impl->_size;
}

template <class T>
xtga::ManagedArray<T>::ManagedArray() : _impl(nullptr) { }

/* Template Instantiation */

#include "xTGA/pixelformats.h"
template class xtga::ManagedArray<xtga::pixelformats::RGBA8888>;
template class xtga::ManagedArray<xtga::pixelformats::BGRA8888>;
template class xtga::ManagedArray<xtga::pixelformats::BGRA5551>;
template class xtga::ManagedArray<xtga::pixelformats::BGR888>;
template class xtga::ManagedArray<xtga::pixelformats::BGR565>;
template class xtga::ManagedArray<xtga::pixelformats::I8>;
template class xtga::ManagedArray<xtga::pixelformats::IA88>;
template class xtga::ManagedArray<xtga::pixelformats::IPixel>;