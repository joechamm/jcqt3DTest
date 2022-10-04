/*****************************************************************//**
 * \file   Camera.h
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
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "jcqtopengl_global.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

using glm::mat4;
using glm::mat3;
using glm::mat2;
using glm::vec4;
using glm::vec3;
using glm::vec2;
using glm::quat;

namespace jcqt
{
	class JCQTOPENGL_EXPORT CameraPositionerInterface
	{
	public:
		virtual ~CameraPositionerInterface () = default;
		virtual mat4 getViewMatrix () const = 0;
		virtual vec3 getPosition () const = 0;
	};

	class JCQTOPENGL_EXPORT Camera final
	{
	public:
		explicit Camera(CameraPositionerInterface& positioner) : positioner_(&positioner)
		{}

		Camera ( const Camera& ) = default;
		Camera& operator=( const Camera& ) = default;

		mat4 getViewMatrix () const
		{
			return positioner_->getViewMatrix ();
		}

		vec3 getPosition () const
		{
			return positioner_->getPosition ();
		}

	private:
		const CameraPositionerInterface* positioner_;
	};

	class JCQTOPENGL_EXPORT CameraPositioner_FirstPerson final : public CameraPositionerInterface
	{
	public:
		struct Movement
		{
			bool forward_ = false;
			bool backward_ = false;
			bool left_ = false;
			bool right_ = false;
			bool up_ = false;
			bool down_ = false;
			bool fastSpeed_ = false;
		} movement_;

		float mouseSpeed_ = 4.0f;
		float acceleration_ = 150.0f;
		float damping_ = 0.2f;
		float maxSpeed_ = 10.0f;
		float fastCoef_ = 10.0f;

	private:
		vec2 mousePos_ = vec2 ( 0.0f );
		vec3 cameraPosition_ = vec3 ( 0.0f, 10.0f, 10.0f );
		quat cameraOrientation_ = quat ( vec3 ( 0.0f ) );
		vec3 moveSpeed_ = vec3 ( 0.0f );
		vec3 up_ = vec3 ( 0.0f, 0.0f, 1.0f );

	public:
		CameraPositioner_FirstPerson () = default;
		CameraPositioner_FirstPerson ( const vec3& pos, const vec3& target, const vec3& up )
			: cameraPosition_ ( pos )
			, cameraOrientation_ ( glm::lookAt ( pos, target, up ) )
			, up_ ( up )
		{
		}

		void update ( float deltaSeconds, const vec2& mousePos, bool mousePressed )
		{
			if ( mousePressed )
			{
				const vec2 delta = mousePos - mousePos_;
				const quat deltaQuat = quat ( vec3 ( mouseSpeed_ * delta.y, mouseSpeed_ * delta.x, 0.0f ) );
				cameraOrientation_ = glm::normalize ( deltaQuat * cameraOrientation_ );
			}

			mousePos_ = mousePos;

			const mat4 v = glm::mat4_cast ( cameraOrientation_ );
			const vec3 forward = - vec3 ( v [ 0 ][ 2 ], v [ 1 ][ 2 ], v [ 2 ][ 2 ] );
			vec3 right = vec3 ( v [ 0 ][ 0 ], v [ 1 ][ 0 ], v [ 2 ][ 0 ] );
			vec3 up = glm::cross ( right, forward );

			vec3 accel ( 0.0f );
			if ( movement_.forward_ ) accel += forward;
			if ( movement_.backward_ ) accel -= forward;
			if ( movement_.left_ ) accel -= right;
			if ( movement_.right_ ) accel += right;
			if ( movement_.up_ ) accel += up;
			if ( movement_.down_ ) accel -= up;
			if ( movement_.fastSpeed_ ) accel *= fastCoef_;

			if ( accel == vec3 ( 0.0f ) )
			{
				moveSpeed_ -= moveSpeed_ * std::min ( ( 1.0f / damping_ ) * deltaSeconds, 1.0f );
			}
			else
			{
				moveSpeed_ += accel * acceleration_ * deltaSeconds;
				const float maxSpeed = movement_.fastSpeed_ ? maxSpeed_ * fastCoef_ : maxSpeed_;
				if ( glm::length ( moveSpeed_ ) > maxSpeed )
				{
					moveSpeed_ = glm::normalize ( moveSpeed_ ) * maxSpeed;
				}
			}

			cameraPosition_ += moveSpeed_ * deltaSeconds;
		}

		virtual mat4 getViewMatrix () const override
		{
			const mat4 t = glm::translate ( mat4 ( 1.0f ), -cameraPosition_ );
			const mat4 r = glm::mat4_cast ( cameraOrientation_ );
			return r * t;
		}

		virtual vec3 getPosition () const override
		{
			return cameraPosition_;
		}

		void setPosition ( const vec3& pos )
		{
			cameraPosition_ = pos;
		}

		void resetMousePosition ( const vec2& p )
		{
			mousePos_ = p;
		}

		void setUpVector ( const vec3& up )
		{
			const mat4 view = getViewMatrix ();
			const vec3 dir = -vec3 ( view [ 0 ][ 2 ], view [ 1 ][ 2 ], view [ 2 ][ 2 ] );
			cameraOrientation_ = glm::lookAt ( cameraPosition_, cameraPosition_ + dir, up );
		}

		inline void lookAt ( const vec3& pos, const vec3& target, const vec3& up )
		{
			cameraPosition_ = pos;
			cameraOrientation_ = glm::lookAt ( pos, target, up );
		}
	};
}

#endif // !__CAMERA_H__
