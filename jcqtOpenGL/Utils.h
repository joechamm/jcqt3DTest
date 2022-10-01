/*****************************************************************//**
 * \file   Utils.h
 * \licence MIT License

Copyright (c) 2022 Joseph Cunningham

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 * \brief  
 * 
 * \author joechamm
 * \date   September 2022
 *********************************************************************/
#ifndef __UTILS_H__
#define __UTILS_H__

#include "jcqtopengl_global.h"

#include <QList>
#include <QByteArrayList>

namespace jcqt
{
	template <typename T>
	inline void mergeLists ( QList<T>& l1, const QList<T>& l2 )
	{
		l1.append ( l2 );
	}

	inline qint32 addUnique ( QByteArrayList& files, const QByteArray& file )
	{
		if ( file.isEmpty () )
			return -1;

		if ( !files.contains ( file ) )
		{
			files.push_back ( file );
			return ( qint32 ) files.size () - 1;
		}

		return ( qint32 ) files.indexOf ( file, 0 );
	}

	// From https://stackoverflow.com/a/64152990/1182653
	// Delete a list of items from std::vector with indices in 'selection'
	template <class T, class Index = qint32> inline void eraseSelected ( QList<T>& v, const QList<Index>& selection )
		// e.g., eraseSelected({1, 2, 3, 4, 5}, {1, 3})  ->   {1, 3, 5}
		//                         ^     ^    2 and 4 get deleted
	{
		// cut off the elements moved to the end of the vector by std::stable_partition
		v.resize ( std::distance (
			v.begin (),
			// the stable_partition moves any element whose index is in 'selection' to the end
			std::stable_partition ( v.begin (), v.end (),
				[&selection, &v] ( const T& item ) {
					return !std::binary_search (
						selection.begin (), selection.end (),
						/* std::distance(std::find(v.begin(), v.end(), item), v.begin()) - if you don't like the pointer arithmetic below */
						static_cast< Index >( static_cast< const T* >( &item ) - &v [ 0 ] ) );
				} ) ) );
	}
}


#endif // !__UTILS_H__
