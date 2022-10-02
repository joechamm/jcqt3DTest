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
        QFunctionPointer functions[FUNCTIONS(QT_OPENGL_COUNT_FUNCTIONS)]; \
        Functions f; \
    }; \
private: \
    void init()

#define QT_OPENGL_COUNT_FUNCTIONS(ret, name, args) +1
#define QT_OPENGL_FUNCTION_NAMES(ret, name, args) \
    "gl"#name"\0"
#define QT_OPENGL_IMPLEMENT(CLASS, FUNCTIONS) \
void CLASS::init() \
{ \
    const char *names = FUNCTIONS(QT_OPENGL_FUNCTION_NAMES); \
    const char *name = names; \
    for (int i = 0; i < FUNCTIONS(QT_OPENGL_COUNT_FUNCTIONS); ++i) { \
        functions[i] = context->getProcAddress(name); \
        name += strlen(name) + 1; \
    } \
}

class QOpenGLFunctions_4_6_CoreBackend : public QOpenGLVersionFunctionsBackend
{
public:
	QOpenGLFunctions_4_6_CoreBackend ( QOpenGLContext* c )
		: QOpenGLVersionFunctionsBackend ( c )
	{
		init ();
	}

	constexpr static Version versionStatus () { return (Version)(OpenGL_4_5_Core + 1); }

	// OpenGL 4.6 core functions
#define QT_OPENGL_4_6_FUNCTIONS(F) \
	F(void, SpecializeShader, (GLuint shader, const GLchar* pEntryPoint, GLuint numSpecializationConstants, const GLuint* pConstantIndex, const GLuint* pConstantValue)) \
	F(void, MultiDrawArraysIndirectCount, ( GLenum mode, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride )) \
	F(void, MultiDrawElementsIndirectCount, ( GLenum mode, GLenum type, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride )) \
	F(void, PolygonOffsetClamp, ( GLfloat factor, GLfloat units, GLfloat clamp )) \

    QT_OPENGL_DECLARE ( QT_OPENGL_4_6_FUNCTIONS );

};

#define QT_OPENGL_COUNT_FUNCTIONS(ret, name, args) +1
#define QT_OPENGL_FUNCTION_NAMES(ret, name, args) \
    "gl"#name"\0"
#define QT_OPENGL_IMPLEMENT(CLASS, FUNCTIONS) \
void CLASS::init() \
{ \
    const char *names = FUNCTIONS(QT_OPENGL_FUNCTION_NAMES); \
    const char *name = names; \
    for (int i = 0; i < FUNCTIONS(QT_OPENGL_COUNT_FUNCTIONS); ++i) { \
        functions[i] = context->getProcAddress(name); \
        name += strlen(name) + 1; \
    } \
};

QT_OPENGL_IMPLEMENT ( QOpenGLFunctions_4_6_CoreBackend, QT_OPENGL_4_6_FUNCTIONS )

QOpenGLFunctions_4_6_Core::QOpenGLFunctions_4_6_Core ()
    : QAbstractOpenGLFunctions ()
    , d_1_0_Core ( nullptr )
    , d_1_1_Core ( nullptr )
    , d_1_2_Core ( nullptr )
    , d_1_3_Core ( nullptr )
    , d_1_4_Core ( nullptr )
    , d_1_5_Core ( nullptr )
    , d_2_0_Core ( nullptr )
    , d_2_1_Core ( nullptr )
    , d_3_0_Core ( nullptr )
    , d_3_1_Core ( nullptr )
    , d_3_2_Core ( nullptr )
    , d_3_3_Core ( nullptr )
    , d_4_0_Core ( nullptr )
    , d_4_1_Core ( nullptr )
    , d_4_2_Core ( nullptr )
    , d_4_3_Core ( nullptr )
    , d_4_4_Core ( nullptr )
    , d_4_5_Core ( nullptr )
    , d_4_6_Core ( nullptr )
{
}

QOpenGLFunctions_4_6_Core::~QOpenGLFunctions_4_6_Core ()
{
    if ( d_1_0_Core )
    {
        d_1_0_Core->refs.deref ();
        Q_ASSERT ( d_1_0_Core->refs.loadRelaxed () );
    }
    if ( d_1_1_Core )
    {
        d_1_1_Core->refs.deref ();
        Q_ASSERT ( d_1_1_Core->refs.loadRelaxed () );
    }
    if ( d_1_2_Core )
    {
        d_1_2_Core->refs.deref ();
        Q_ASSERT ( d_1_2_Core->refs.loadRelaxed () );
    }
    if ( d_1_3_Core )
    {
        d_1_3_Core->refs.deref ();
        Q_ASSERT ( d_1_3_Core->refs.loadRelaxed () );
    }
    if ( d_1_4_Core )
    {
        d_1_4_Core->refs.deref ();
        Q_ASSERT ( d_1_4_Core->refs.loadRelaxed () );
    }
    if ( d_1_5_Core )
    {
        d_1_5_Core->refs.deref ();
        Q_ASSERT ( d_1_5_Core->refs.loadRelaxed () );
    }
    if ( d_2_0_Core )
    {
        d_2_0_Core->refs.deref ();
        Q_ASSERT ( d_2_0_Core->refs.loadRelaxed () );
    }
    if ( d_2_1_Core )
    {
        d_2_1_Core->refs.deref ();
        Q_ASSERT ( d_2_1_Core->refs.loadRelaxed () );
    }
    if ( d_3_0_Core )
    {
        d_3_0_Core->refs.deref ();
        Q_ASSERT ( d_3_0_Core->refs.loadRelaxed () );
    }
    if ( d_3_1_Core )
    {
        d_3_1_Core->refs.deref ();
        Q_ASSERT ( d_3_1_Core->refs.loadRelaxed () );
    }
    if ( d_3_2_Core )
    {
        d_3_2_Core->refs.deref ();
        Q_ASSERT ( d_3_2_Core->refs.loadRelaxed () );
    }
    if ( d_3_3_Core )
    {
        d_3_3_Core->refs.deref ();
        Q_ASSERT ( d_3_3_Core->refs.loadRelaxed () );
    }
    if ( d_4_0_Core )
    {
        d_4_0_Core->refs.deref ();
        Q_ASSERT ( d_4_0_Core->refs.loadRelaxed () );
    }
    if ( d_4_1_Core )
    {
        d_4_1_Core->refs.deref ();
        Q_ASSERT ( d_4_1_Core->refs.loadRelaxed () );
    }
    if ( d_4_2_Core )
    {
        d_4_2_Core->refs.deref ();
        Q_ASSERT ( d_4_2_Core->refs.loadRelaxed () );
    }
    if ( d_4_3_Core )
    {
        d_4_3_Core->refs.deref ();
        Q_ASSERT ( d_4_3_Core->refs.loadRelaxed () );
    }
    if ( d_4_4_Core )
    {
        d_4_4_Core->refs.deref ();
        Q_ASSERT ( d_4_4_Core->refs.loadRelaxed () );
    }
    if ( d_4_5_Core )
    {
        d_4_5_Core->refs.deref ();
        Q_ASSERT ( d_4_5_Core->refs.loadRelaxed () );
    }
    if ( d_4_6_Core )
    {
        d_4_6_Core->refs.deref ();
        Q_ASSERT ( d_4_6_Core->refs.loadRelaxed () );
    }
}

inline void QOpenGLFunctions_4_6_Core::glSpecializeShader ( GLuint shader, const GLchar* pEntryPoint, GLuint numSpecializationConstants, const GLuint* pConstantIndex, const GLuint* pConstantValue )
{
    d_4_6_Core->f.SpecializeShader ( shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue );
}

inline void QOpenGLFunctions_4_6_Core::glMultiDrawArraysIndirectCount ( GLenum mode, const void* indirect, GLintptr drawCount, GLsizei maxdrawcount, GLsizei stride )
{
    d_4_6_Core->f.MultiDrawArraysIndirectCount ( mode, indirect, drawCount, maxdrawcount, stride );
}

inline void QOpenGLFunctions_4_6_Core::glMultiDrawElementsIndirectCount ( GLenum mode, GLenum type, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride )
{
    d_4_6_Core->f.MultiDrawElementsIndirectCount ( mode, type, indirect, drawcount, maxdrawcount, stride );
}

inline void QOpenGLFunctions_4_6_Core::glPolygonOffsetClamp ( GLfloat factor, GLfloat units, GLfloat clamp )
{
    d_4_6_Core->f.PolygonOffsetClamp ( factor, units, clamp );
}

bool QOpenGLFunctions_4_6_Core::initializeOpenGLFunctions ()
{
    if ( isInitialized () )
        return true;

    QOpenGLContext* context = QOpenGLContext::currentContext ();

    // If owned by a context object make sure it is current.
    // Also check that current context is capable of resolving all needed functions
    if ( ( ( owningContext () && owningContext () == context ) || !owningContext () )
        && QOpenGLFunctions_4_6_Core::isContextCompatible ( context ) )
    {
        // Associate with private implementation, creating if necessary
        // Function pointers in the backends are resolved at creation time
        QOpenGLVersionFunctionsBackend* d = nullptr;
        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_1_0_CoreBackend::versionStatus () );
        d_1_0_Core = static_cast< QOpenGLFunctions_1_0_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_1_1_CoreBackend::versionStatus () );
        d_1_1_Core = static_cast< QOpenGLFunctions_1_1_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_1_2_CoreBackend::versionStatus () );
        d_1_2_Core = static_cast< QOpenGLFunctions_1_2_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_1_3_CoreBackend::versionStatus () );
        d_1_3_Core = static_cast< QOpenGLFunctions_1_3_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_1_4_CoreBackend::versionStatus () );
        d_1_4_Core = static_cast< QOpenGLFunctions_1_4_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_1_5_CoreBackend::versionStatus () );
        d_1_5_Core = static_cast< QOpenGLFunctions_1_5_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_2_0_CoreBackend::versionStatus () );
        d_2_0_Core = static_cast< QOpenGLFunctions_2_0_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_2_1_CoreBackend::versionStatus () );
        d_2_1_Core = static_cast< QOpenGLFunctions_2_1_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_3_0_CoreBackend::versionStatus () );
        d_3_0_Core = static_cast< QOpenGLFunctions_3_0_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_3_1_CoreBackend::versionStatus () );
        d_3_1_Core = static_cast< QOpenGLFunctions_3_1_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_3_2_CoreBackend::versionStatus () );
        d_3_2_Core = static_cast< QOpenGLFunctions_3_2_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_3_3_CoreBackend::versionStatus () );
        d_3_3_Core = static_cast< QOpenGLFunctions_3_3_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_4_0_CoreBackend::versionStatus () );
        d_4_0_Core = static_cast< QOpenGLFunctions_4_0_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_4_1_CoreBackend::versionStatus () );
        d_4_1_Core = static_cast< QOpenGLFunctions_4_1_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_4_2_CoreBackend::versionStatus () );
        d_4_2_Core = static_cast< QOpenGLFunctions_4_2_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_4_3_CoreBackend::versionStatus () );
        d_4_3_Core = static_cast< QOpenGLFunctions_4_3_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_4_4_CoreBackend::versionStatus () );
        d_4_4_Core = static_cast< QOpenGLFunctions_4_4_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_4_5_CoreBackend::versionStatus () );
        d_4_5_Core = static_cast< QOpenGLFunctions_4_5_CoreBackend* >( d );
        d->refs.ref ();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend ( context, QOpenGLFunctions_4_6_CoreBackend::versionStatus () );
        d_4_6_Core = static_cast< QOpenGLFunctions_4_6_CoreBackend* >( d );

        QAbstractOpenGLFunctions::initializeOpenGLFunctions ();
    }

    return isInitialized ();
}

bool QOpenGLFunctions_4_6_Core::isContextCompatible ( QOpenGLContext* context )
{
    Q_ASSERT ( context );
    QSurfaceFormat f = context->format ();
    const QPair<int, int> v = qMakePair ( f.majorVersion (), f.minorVersion () );
    if ( v < qMakePair ( 4, 6 ) )
        return false;

    return true;
}

QOpenGLVersionProfile QOpenGLFunctions_4_6_Core::versionProfile ()
{
    QOpenGLVersionProfile v;
    v.setVersion ( 4, 6 );
    v.setProfile ( QSurfaceFormat::CoreProfile );
    return v;
}

#undef QT_OPENGL_DECLARE_FUNCTIONS
#undef QT_OPENGL_COUNT_FUNCTIONS
#undef QT_OPENGL_DECLARE
#undef QT_OPENGL_IMPLEMENT
#undef QT_OPENGL_4_6_FUNCTIONS

QT_END_NAMESPACE
