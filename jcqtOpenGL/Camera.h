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

namespace jcqt
{
	using glm::mat4;
	using glm::mat3;
	using glm::mat2;
	using glm::vec4;
	using glm::vec3;
	using glm::vec2;
	using glm::quat;

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
		explicit Camera ( CameraPositionerInterface& positioner );

		Camera ( const Camera& ) = default;
		Camera& operator=( const Camera& ) = default;

		mat4 getViewMatrix () const;	
		vec3 getPosition () const;	
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
		CameraPositioner_FirstPerson ( const vec3& pos, const vec3& target, const vec3& up );
		
		void update ( float deltaSeconds, const vec2& mousePos, bool mousePressed );	
		virtual mat4 getViewMatrix () const override;		
		virtual vec3 getPosition () const override;		
		void setPosition ( const vec3& pos );	
		void resetMousePosition ( const vec2& p );	
		void setUpVector ( const vec3& up );	

		inline void lookAt ( const vec3& pos, const vec3& target, const vec3& up )
		{
			cameraPosition_ = pos;
			cameraOrientation_ = glm::lookAt ( pos, target, up );
		}
	};
}

#endif // !__CAMERA_H__
