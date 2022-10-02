/*****************************************************************//**
 * \file   qopenglfunctions_4_6_core.cpp
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
#include "qopenglfunctions_4_6_core.h"
#include <QOpenGLContext>
#include <QOpenGLVersionFunctions>
//#include <qopenglversionfunctions.h>

QT_BEGIN_NAMESPACE 

#define QT_OPENGL_DECLARE_FUNCTIONS(ret, name, args) \
	ret (QOPENGLF_APIENTRYP name)args;
#define QT_OPENGL_COUNT_FUNCTIONS(ret, name, args) +1

#define QT_OPENGL_DECLARE(FUNCTIONS) \
public: \
	struct Functions { \
		FUNCTIONS(QT_OPENGL_DECLARE_FUNCTIONS) \
	}; \
	union { \
		QFunctionPointer function[FUNCTIONS(QT_OPENGL_COUNT_FUNCTIONS)]; \
		Functions f; \
	}; \
private: \
	void init()

class OpenGLVersionFunctionsBackend : public QOpenGLVersionFunctionsBackend
{
public:
	/*enum Version
	{
		OpenGL_1_0_Core,
		OpenGL_1_1_Core,
		OpenGL_1_2_Core,
		OpenGL_1_3_Core,
		OpenGL_1_4_Core,
		OpenGL_1_5_Core,
		OpenGL_2_0_Core,
		OpenGL_2_1_Core,
		OpenGL_3_0_Core,
		OpenGL_3_1_Core,
		OpenGL_3_2_Core,
		OpenGL_3_3_Core,
		OpenGL_4_0_Core,
		OpenGL_4_1_Core,
		OpenGL_4_2_Core,
		OpenGL_4_3_Core,
		OpenGL_4_4_Core,
		OpenGL_4_5_Core,
		OpenGL_4_6_Core,
		OpenGL_1_0_Deprecated,
		OpenGL_1_1_Deprecated,
		OpenGL_1_2_Deprecated,
		OpenGL_1_3_Deprecated,
		OpenGL_1_4_Deprecated,
		OpenGL_2_0_Deprecated,
		OpenGL_3_0_Deprecated,
		OpenGL_3_3_Deprecated,
		OpenGL_4_5_Deprecated,
		OpenGLVersionBackendCount
	};*/

#define QT_OPENGL_VERSIONS(F) \
        F(1_0_Core) \
        F(1_1_Core) \
        F(1_2_Core) \
        F(1_3_Core) \
        F(1_4_Core) \
        F(1_5_Core) \
        F(2_0_Core) \
        F(2_1_Core) \
        F(3_0_Core) \
        F(3_1_Core) \
        F(3_2_Core) \
        F(3_3_Core) \
        F(4_0_Core) \
        F(4_1_Core) \
        F(4_2_Core) \
        F(4_3_Core) \
        F(4_4_Core) \
        F(4_5_Core) \
		F(4_6_Core) \
        F(1_0_Deprecated) \
        F(1_1_Deprecated) \
        F(1_2_Deprecated) \
        F(1_3_Deprecated) \
        F(1_4_Deprecated) \
        F(2_0_Deprecated) \
        F(3_0_Deprecated) \
        F(3_3_Deprecated) \
        F(4_5_Deprecated) \

#define VERSION_ENUM(X) OpenGL_##X,
	enum Version
	{
		QT_OPENGL_VERSIONS ( VERSION_ENUM )
		OpenGLVersionBackendCount
	};
#undef VERSION_ENUM


	OpenGLVersionFunctionsBackend(QOpenGLContext *ctx) : QOpenGLVersionFunctionsBackend(ctx) {}
};

class QOpenGLFunctions_4_6_CoreBackend : public OpenGLVersionFunctionsBackend
{
public:
	QOpenGLFunctions_4_6_CoreBackend ( QOpenGLContext* c )
		: OpenGLVersionFunctionsBackend ( c )
	{
		init ();
	}

	constexpr static Version versionStatus () { return OpenGL_4_6_Core; }

	// OpenGL 4.6 core functions
#define QT_OPENGL_4_6_FUNCTIONS(F) \
	F(void, SpecializeShader, (GLuint shader, const GLchar* pEntryPoint, GLuint numSpecializationConstants, const GLuint* pConstantIndex, const GLuint* pConstantValue)) \
	F(void, MultiDrawArraysIndirectCount, ( GLenum mode, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride )) \
	F(void, MultiDrawElementsIndirectCount, ( GLenum mode, GLenum type, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride )) \
	F(void, PolygonOffsetClamp, ( GLfloat factor, GLfloat units, GLfloat clamp )) \
	QT_OPENGL_DECLARE(QT_OPENGL_4_6_FUNCTIONS);
};

//#undef QT_OPENGL_DECLARE_FUNCTIONS
//#undef QT_OPENGL_COUNT_FUNCTIONS
//#undef QT_OPENGL_DECLARE

#define QT_OPENGL_COUNT_FUNCTIONS(ret, name, args) +1
#define QT_OPENGL_FUNCTION_NAMES(ret, name, args) \
	"gl"#name"\0"
#define QT_OPENGL_IMPLEMENT(CLASS, FUNCTIONS) \
void CLASS::init() \
{ \
	const char* names = FUNCTIONS(QT_OPENGL_FUNCTION_NAMES); \
	const char* name = names; \
	for (int i = 0; i < FUNCTIONS(QT_OPENGL_COUNT_FUNCTIONS); ++i) { \
		functions[i] = context->getProcAddress(name); \
		name += strlen(name) + 1; \
	} \
}



QT_OPENGL_IMPLEMENT(QOpenGLFunctions_4_6_CoreBackend, QT_OPENGL_4_6_FUNCTIONS)


QT_END_NAMESPACE
