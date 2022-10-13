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
#include "Camera.h"

namespace jcqt
{
    Camera::Camera(CameraPositionerInterface& positioner) : positioner_(&positioner) {}

    mat4 Camera::getViewMatrix () const
    {
        return positioner_->getViewMatrix ();
    }

    vec3 Camera::getPosition () const
    {
        return positioner_->getPosition ();
    }

    CameraPositioner_FirstPerson::CameraPositioner_FirstPerson ( const vec3& pos, const vec3& target, const vec3& up )
        : cameraPosition_ ( pos )
        , cameraOrientation_ ( glm::lookAt ( pos, target, up ) )
        , up_ ( up )
    {}

    void CameraPositioner_FirstPerson::update ( float deltaSeconds, const vec2& mousePos, bool mousePressed )
    {
        if ( mousePressed )
        {
            const vec2 delta = mousePos - mousePos_;
            const quat deltaQuat = quat ( vec3 ( mouseSpeed_ * delta.y, mouseSpeed_ * delta.x, 0.0f ) );
            cameraOrientation_ = glm::normalize ( deltaQuat * cameraOrientation_ );
        }

        mousePos_ = mousePos;

        const mat4 v = glm::mat4_cast ( cameraOrientation_ );
        const vec3 forward = -vec3 ( v [ 0 ][ 2 ], v [ 1 ][ 2 ], v [ 2 ][ 2 ] );
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

    mat4 CameraPositioner_FirstPerson::getViewMatrix () const
    {
        const mat4 t = glm::translate ( mat4 ( 1.0f ), -cameraPosition_ );
        const mat4 r = glm::mat4_cast ( cameraOrientation_ );
        return r * t;
    }

    vec3 CameraPositioner_FirstPerson::getPosition () const
    {
        return cameraPosition_;
    }

    void CameraPositioner_FirstPerson::setPosition ( const vec3& pos )
    {
        cameraPosition_ = pos;
    }

    void CameraPositioner_FirstPerson::resetMousePosition ( const vec2& p )
    {
        mousePos_ = p;
    }

    void CameraPositioner_FirstPerson::setUpVector ( const vec3& up )
    {
        const mat4 view = getViewMatrix ();
        const vec3 dir = -vec3 ( view [ 0 ][ 2 ], view [ 1 ][ 2 ], view [ 2 ][ 2 ] );
        cameraOrientation_ = glm::lookAt ( cameraPosition_, cameraPosition_ + dir, up );
    }
}
