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
#include "UtilsMath.h"

namespace jcqt
{
    BoundingBox::BoundingBox ( const vec3& min, const vec3& max )
        : min_ ( glm::min ( min, max ) ), max_ ( glm::max ( min, max ) )
    {}

    BoundingBox::BoundingBox ( const vec3* points, size_t numPoints )
    {
        vec3 vmin ( std::numeric_limits<float>::max () );
        vec3 vmax ( std::numeric_limits<float>::lowest () );

        for ( size_t i = 0; i != numPoints; i++ )
        {
            vmin = glm::min ( vmin, points [ i ] );
            vmax = glm::max ( vmax, points [ i ] );
        }

        min_ = vmin;
        max_ = vmax;
    }

    vec3 BoundingBox::getSize () const
    {
        return vec3 ( max_ [ 0 ] - min_ [ 0 ], max_ [ 1 ] - min_ [ 1 ], max_ [ 2 ] - min_ [ 2 ] );
    }

    vec3 BoundingBox::getCenter () const
    {
        return 0.5f * vec3 ( max_ [ 0 ] + min_ [ 0 ], max_ [ 1 ] + min_ [ 1 ], max_ [ 2 ] + min_ [ 2 ] );
    }

    void BoundingBox::transform ( const mat4& t )
    {
        vec3 corners [] = {
            vec3 ( min_.x, min_.y, min_.z ),
            vec3 ( min_.x, max_.y, min_.z ),
            vec3 ( min_.x, min_.y, max_.z ),
            vec3 ( min_.x, max_.y, max_.z ),
            vec3 ( max_.x, min_.y, min_.z ),
            vec3 ( max_.x, max_.y, min_.z ),
            vec3 ( max_.x, min_.y, max_.z ),
            vec3 ( max_.x, max_.y, max_.z )
        };
        for ( auto& v : corners )
            v = vec3 ( t * vec4 ( v, 1.0f ) );

        *this = BoundingBox ( corners, 8 );
    }

    BoundingBox BoundingBox::getTransformed ( const mat4& t ) const
    {
        BoundingBox b = *this;
        b.transform ( t );
        return b;
    }

    void BoundingBox::combinePoint ( const vec3& p )
    {
        min_ = glm::min ( min_, p );
        max_ = glm::max ( max_, p );
    }
}
