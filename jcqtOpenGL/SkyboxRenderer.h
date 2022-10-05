/*****************************************************************//**
 * \file   SkyboxRenderer.h
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
#ifndef __SKYBOX_RENDERER_H__
#define __SKYBOX_RENDERER_H__

#include "jcqtopengl_global.h"
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QSharedPointer>

namespace jcqt 
{
	class JCQTOPENGL_EXPORT SkyboxRenderer
	{
		QSharedPointer<QOpenGLTexture>			m_envMap;
		QSharedPointer<QOpenGLTexture>			m_envMapIrradiance;
		QSharedPointer<QOpenGLTexture>			m_brdfLUT;
		QSharedPointer<QOpenGLShaderProgram>	m_program;
		GLuint									m_dummyVAO;

	public:
		SkyboxRenderer ( const char* envMap = ":/textures/immenstadter_horn_2k.hdr", 
			const char* envMapIrradiance = ":/textures/immenstadter_horn_2k_irradiance.hdr" );
		~SkyboxRenderer ();

		void draw () const;
	};
}
#endif // !__SKYBOX_RENDERER_H__
