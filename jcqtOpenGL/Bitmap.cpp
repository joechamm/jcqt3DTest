/*
 * Copyright 2022 joechamm
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include "Bitmap.h"

namespace jcqt
{
    Bitmap::Bitmap ( qint32 w, qint32 h, qint32 comp, eBitmapFormat fmt )
        : w_ ( w ), h_ ( h ), comp_ ( comp ), fmt_ ( fmt ), data_ ( static_cast< qsizetype >( w* h* comp* getBytesPerComponent ( fmt ) ) )
    {
        initGetSetFunctions ();
    }

    Bitmap::Bitmap ( qint32 w, qint32 h, qint32 d, qint32 comp, eBitmapFormat fmt )
        : w_ ( w ), h_ ( h ), d_ ( d ), comp_ ( comp ), fmt_ ( fmt ), data_ ( static_cast< qsizetype >( w* h* d* comp* getBytesPerComponent ( fmt ) ) )
    {
        initGetSetFunctions ();
    }

    Bitmap::Bitmap ( qint32 w, qint32 h, qint32 comp, eBitmapFormat fmt, const void* ptr )
        : w_ ( w ), h_ ( h ), comp_ ( comp ), fmt_ ( fmt ), data_ ( static_cast< qsizetype >( w* h* comp* getBytesPerComponent ( fmt ) ) )
    {
        initGetSetFunctions ();
        memcpy ( data_.data (), ptr, data_.size () );
    }

    void Bitmap::setPixel ( qint32 x, qint32 y, const vec4& c )
    {
        ( *this.*setPixelFunc )( x, y, c );
    }

    vec4 Bitmap::getPixel ( qint32 x, qint32 y ) const
    {
        return ( ( *this.*getPixelFunc )( x, y ) );
    }

    void Bitmap::initGetSetFunctions ()
    {
        switch ( fmt_ )
        {
        case jcqt::eBitmapFormat::eBitmapFormat_UNSIGNED_BYTE:
            setPixelFunc = &Bitmap::setPixelUnsignedByte;
            getPixelFunc = &Bitmap::getPixelUnsignedByte;
            break;
        case jcqt::eBitmapFormat::eBitmapFormat_FLOAT:
            setPixelFunc = &Bitmap::setPixelFloat;
            getPixelFunc = &Bitmap::getPixelFloat;
            break;
        default:
            break;
        }
    }

    void Bitmap::setPixelFloat ( qint32 x, qint32 y, const vec4& c )
    {
        const qint32 ofs = comp_ * ( y * w_ + x );
        float* data = reinterpret_cast< float* >( data_.data () );
        if ( comp_ > 0 ) data [ ofs + 0 ] = c.x;
        if ( comp_ > 1 ) data [ ofs + 1 ] = c.y;
        if ( comp_ > 2 ) data [ ofs + 2 ] = c.z;
        if ( comp_ > 3 ) data [ ofs + 3 ] = c.w;
    }

    vec4 Bitmap::getPixelFloat ( qint32 x, qint32 y ) const
    {
        const qint32 ofs = comp_ * ( y * w_ + x );
        const float* data = reinterpret_cast< const float* >( data_.constData () );
        return vec4 ( comp_ > 0 ? data [ ofs + 0 ] : 0.0f,
            comp_ > 1 ? data [ ofs + 1 ] : 0.0f,
            comp_ > 2 ? data [ ofs + 2 ] : 0.0f,
            comp_ > 3 ? data [ ofs + 3 ] : 0.0f
        );
    }

    void Bitmap::setPixelUnsignedByte ( qint32 x, qint32 y, const vec4& c )
    {
        const qint32 ofs = comp_ * ( y * w_ + x );
        if ( comp_ > 0 ) data_ [ ofs + 0 ] = static_cast< quint8 > ( c.x * 255.0f );
        if ( comp_ > 1 ) data_ [ ofs + 1 ] = static_cast< quint8 >( c.y * 255.0f );
        if ( comp_ > 2 ) data_ [ ofs + 2 ] = static_cast< quint8 > ( c.z * 255.0f );
        if ( comp_ > 3 ) data_ [ ofs + 3 ] = static_cast< quint8 > ( c.w * 255.0f );
    }

    vec4 Bitmap::getPixelUnsignedByte ( qint32 x, qint32 y ) const
    {
        const int ofs = comp_ * ( y * w_ + x );
        return vec4 (
            comp_ > 0 ? static_cast< float >( data_ [ ofs + 0 ] ) / 255.0f : 0.0f,
            comp_ > 1 ? static_cast< float >( data_ [ ofs + 1 ] ) / 255.0f : 0.0f,
            comp_ > 2 ? static_cast< float >( data_ [ ofs + 2 ] ) / 255.0f : 0.0f,
            comp_ > 3 ? static_cast< float >( data_ [ ofs + 3 ] ) / 255.0f : 0.0f
        );
    }
}
