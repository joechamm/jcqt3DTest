/*****************************************************************//**
 * \file   UtilsMath.h
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
#ifndef __UTILS_MATH_H__
#define __UTILS_MATH_H__

#include "jcqtopengl_global.h"

#include <QList>

#include <glm/glm.hpp>

using glm::mat4;
using glm::vec4;
using glm::vec3;

namespace jcqt
{
	struct JCQTOPENGL_EXPORT BoundingBox
	{
		vec3 min_;
		vec3 max_;
		BoundingBox () = default;
		BoundingBox ( const vec3& min, const vec3& max );
		BoundingBox ( const vec3* points, size_t numPoints );	

		vec3 getSize () const;
		vec3 getCenter () const;
		void transform ( const mat4& t );	

		BoundingBox getTransformed ( const mat4& t ) const;		
		void combinePoint ( const vec3& p );		
	};

	inline void JCQTOPENGL_EXPORT getFrustumPlanes ( const mat4& mvp, vec4* planes )
	{
		const mat4 trMVP = glm::transpose ( mvp );
		planes [ 0 ] = vec4 ( trMVP [ 3 ] + trMVP [ 0 ] ); // left
		planes [ 1 ] = vec4 ( trMVP [ 3 ] - trMVP [ 0 ] ); // right
		planes [ 2 ] = vec4 ( trMVP [ 3 ] + trMVP [ 1 ] ); // bottom
		planes [ 3 ] = vec4 ( trMVP [ 3 ] - trMVP [ 1 ] ); // top
		planes [ 4 ] = vec4 ( trMVP [ 3 ] + trMVP [ 2 ] ); // near
		planes [ 5 ] = vec4 ( trMVP [ 3 ] - trMVP [ 2 ] ); // far
	}

	inline void JCQTOPENGL_EXPORT getFrustumCorners ( const mat4& mvp, vec4* points )
	{
		const vec4 corners [] = {
			vec4 ( -1, -1, -1, 1 ), vec4 ( 1, -1, -1, 1 ),
			vec4 ( 1, 1, -1, 1 ), vec4 ( -1, 1, -1, 1 ),
			vec4 ( -1, -1, 1, 1 ), vec4 ( 1, -1, 1, 1 ),
			vec4 ( 1, 1, 1, 1 ), vec4 ( -1, 1, 1, 1 )
		};

		const mat4 invMVP = glm::inverse ( mvp );

		for ( int i = 0; i != 8; i++ )
		{
			const vec4 q = invMVP * corners [ i ];
			points [ i ] = q / q.w;
		}
	}

	inline bool JCQTOPENGL_EXPORT isBoxInFrustum ( vec4* frustumPlanes, vec4* frustumCorners, const BoundingBox& box )
	{
		using glm::dot;

		for ( int i = 0; i < 6; i++ )
		{
			int r = 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.min_.x, box.min_.y, box.min_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.max_.x, box.min_.y, box.min_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.min_.x, box.max_.y, box.min_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.max_.x, box.max_.y, box.min_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.min_.x, box.min_.y, box.max_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.max_.x, box.min_.y, box.max_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.min_.x, box.max_.y, box.max_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.max_.x, box.max_.y, box.max_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			if ( r == 8 ) return false;
		}

		// check frustum outside/inside box
		int r = 0;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].x > box.max_.x ) ? 1 : 0 ); if ( r == 8 ) return false;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].x < box.min_.x ) ? 1 : 0 ); if ( r == 8 ) return false;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].y > box.max_.y ) ? 1 : 0 ); if ( r == 8 ) return false;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].y < box.min_.y ) ? 1 : 0 ); if ( r == 8 ) return false;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].z > box.max_.z ) ? 1 : 0 ); if ( r == 8 ) return false;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].z > box.min_.z ) ? 1 : 0 ); if ( r == 8 ) return false;

		return true;
	}

	inline BoundingBox JCQTOPENGL_EXPORT combineBoxes ( const QList<BoundingBox>& boxes )
	{
		QList<vec3> allPoints;
		allPoints.reserve ( boxes.size () * 8 );

		foreach ( const BoundingBox & b, boxes )
		{
			allPoints.emplace_back ( b.min_.x, b.min_.y, b.min_.z );
			allPoints.emplace_back ( b.min_.x, b.min_.y, b.max_.z );
			allPoints.emplace_back ( b.min_.x, b.max_.y, b.min_.z );
			allPoints.emplace_back ( b.min_.x, b.max_.y, b.max_.z );

			allPoints.emplace_back ( b.max_.x, b.min_.y, b.min_.z );
			allPoints.emplace_back ( b.max_.x, b.min_.y, b.max_.z );
			allPoints.emplace_back ( b.max_.x, b.max_.y, b.min_.z );
			allPoints.emplace_back ( b.max_.x, b.max_.y, b.max_.z );
		}

		return BoundingBox ( allPoints.data (), allPoints.size () );
	}
}

#endif // !__UTILS_MATH_H__

