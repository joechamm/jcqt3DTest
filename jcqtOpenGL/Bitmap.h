/*****************************************************************//**
 * \file   Bitmap.h
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
 * \date   October 2022
 *********************************************************************/
#ifndef __BITMAP_H__
#define __BITMAP_H__

#include "jcqtopengl_global.h"

#include <QList>
#include <glm/glm.hpp>

namespace jcqt
{
	using glm::vec4;

	enum class eBitmapType : quint8
	{
		eBitmapType_2D = 1,
		eBitmapType_CUBE = 2
	};

	enum class eBitmapFormat : quint8
	{
		eBitmapFormat_UNSIGNED_BYTE = 1,
		eBitmapFormat_FLOAT = 2
	};

	/// R/RG/RGB/RGBA bitmaps
	class JCQTOPENGL_EXPORT Bitmap
	{
	public:
		qint32 w_ = 0;
		qint32 h_ = 0;
		qint32 d_ = 1;
		qint32 comp_ = 3;
		eBitmapFormat fmt_ = eBitmapFormat::eBitmapFormat_UNSIGNED_BYTE;
		eBitmapType type_ = eBitmapType::eBitmapType_2D;
		QList<quint8> data_;

	public:
		Bitmap () = default;
		Bitmap ( qint32 w, qint32 h, qint32 comp, eBitmapFormat fmt );		
		Bitmap ( qint32 w, qint32 h, qint32 d, qint32 comp, eBitmapFormat fmt );		
		Bitmap ( qint32 w, qint32 h, qint32 comp, eBitmapFormat fmt, const void* ptr );		

		static qint32 getBytesPerComponent ( eBitmapFormat fmt )
		{
			if ( fmt == eBitmapFormat::eBitmapFormat_UNSIGNED_BYTE ) return 1;
			if ( fmt == eBitmapFormat::eBitmapFormat_FLOAT ) return 4;
			return 0;
		}

		void setPixel ( qint32 x, qint32 y, const vec4& c );
		vec4 getPixel ( qint32 x, qint32 y ) const;

	private:
		// function pointer aliases
		using setPixel_t = void( Bitmap::* )( qint32, qint32, const vec4& );
		using getPixel_t = vec4 ( Bitmap::* )( qint32, qint32 ) const;
		setPixel_t setPixelFunc = &Bitmap::setPixelUnsignedByte;
		getPixel_t getPixelFunc = &Bitmap::getPixelUnsignedByte;


		void initGetSetFunctions ();
		void setPixelFloat ( qint32 x, qint32 y, const vec4& c );
		vec4 getPixelFloat ( qint32 x, qint32 y ) const;		
		void setPixelUnsignedByte ( qint32 x, qint32 y, const vec4& c );	
		vec4 getPixelUnsignedByte ( qint32 x, qint32 y ) const;		
	};
}

#endif // !__BITMAP_H__
