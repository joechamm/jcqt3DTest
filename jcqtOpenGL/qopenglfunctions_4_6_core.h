/*****************************************************************//**
 * \file   qopenglfunctions_4_6_core.h
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
#ifndef __QOPENGLFUNCTIONS_4_6_CORE_H__
#define __QOPENGLFUNCTIONS_4_6_CORE_H__

#include <QtOpenGL/qtopenglglobal.h>

#if !defined(QT_NO_OPENGL) && !QT_CONFIG(opengles2)

#include <QtOpenGL/QOpenGLVersionProfile>
#include <QtOpenGL/QOpenGLVersionFunctions>
#include <QtGui/qopenglcontext.h>

// MemoryBarrier
#ifdef Q_OS_WIN
#pragma push_macro("MemoryBarrier")
#undef MemoryBarrier
#endif

QT_BEGIN_NAMESPACE

QT_FORWARD_DECLARE_CLASS ( QOpenGLFunctions_4_6_CoreBackend );

class Q_OPENGL_EXPORT QOpenGLFunctions_4_6_Core : public QAbstractOpenGLFunctions
{
public:
	QOpenGLFunctions_4_6_Core ();
	~QOpenGLFunctions_4_6_Core ();


    bool initializeOpenGLFunctions () override;

    // OpenGL 1.0 core functions
    void glViewport ( GLint x, GLint y, GLsizei width, GLsizei height );
    void glDepthRange ( GLdouble nearVal, GLdouble farVal );
    GLboolean glIsEnabled ( GLenum cap );
    void glGetTexLevelParameteriv ( GLenum target, GLint level, GLenum pname, GLint* params );
    void glGetTexLevelParameterfv ( GLenum target, GLint level, GLenum pname, GLfloat* params );
    void glGetTexParameteriv ( GLenum target, GLenum pname, GLint* params );
    void glGetTexParameterfv ( GLenum target, GLenum pname, GLfloat* params );
    void glGetTexImage ( GLenum target, GLint level, GLenum format, GLenum type, void* pixels );
    const GLubyte* glGetString ( GLenum name );
    void glGetIntegerv ( GLenum pname, GLint* data );
    void glGetFloatv ( GLenum pname, GLfloat* data );
    GLenum glGetError ();
    void glGetDoublev ( GLenum pname, GLdouble* data );
    void glGetBooleanv ( GLenum pname, GLboolean* data );
    void glReadPixels ( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels );
    void glReadBuffer ( GLenum src );
    void glPixelStorei ( GLenum pname, GLint param );
    void glPixelStoref ( GLenum pname, GLfloat param );
    void glDepthFunc ( GLenum func );
    void glStencilOp ( GLenum fail, GLenum zfail, GLenum zpass );
    void glStencilFunc ( GLenum func, GLint ref, GLuint mask );
    void glLogicOp ( GLenum opcode );
    void glBlendFunc ( GLenum sfactor, GLenum dfactor );
    void glFlush ();
    void glFinish ();
    void glEnable ( GLenum cap );
    void glDisable ( GLenum cap );
    void glDepthMask ( GLboolean flag );
    void glColorMask ( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha );
    void glStencilMask ( GLuint mask );
    void glClearDepth ( GLdouble depth );
    void glClearStencil ( GLint s );
    void glClearColor ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
    void glClear ( GLbitfield mask );
    void glDrawBuffer ( GLenum buf );
    void glTexImage2D ( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels );
    void glTexImage1D ( GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels );
    void glTexParameteriv ( GLenum target, GLenum pname, const GLint* params );
    void glTexParameteri ( GLenum target, GLenum pname, GLint param );
    void glTexParameterfv ( GLenum target, GLenum pname, const GLfloat* params );
    void glTexParameterf ( GLenum target, GLenum pname, GLfloat param );
    void glScissor ( GLint x, GLint y, GLsizei width, GLsizei height );
    void glPolygonMode ( GLenum face, GLenum mode );
    void glPointSize ( GLfloat size );
    void glLineWidth ( GLfloat width );
    void glHint ( GLenum target, GLenum mode );
    void glFrontFace ( GLenum mode );
    void glCullFace ( GLenum mode );

    // OpenGL 1.1 core functions
    GLboolean glIsTexture ( GLuint texture );
    void glGenTextures ( GLsizei n, GLuint* textures );
    void glDeleteTextures ( GLsizei n, const GLuint* textures );
    void glBindTexture ( GLenum target, GLuint texture );
    void glTexSubImage2D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels );
    void glTexSubImage1D ( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels );
    void glCopyTexSubImage2D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height );
    void glCopyTexSubImage1D ( GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width );
    void glCopyTexImage2D ( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border );
    void glCopyTexImage1D ( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border );
    void glPolygonOffset ( GLfloat factor, GLfloat units );
    void glDrawElements ( GLenum mode, GLsizei count, GLenum type, const void* indices );
    void glDrawArrays ( GLenum mode, GLint first, GLsizei count );

    // OpenGL 1.2 core functions
    void glBlendColor ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
    void glBlendEquation ( GLenum mode );
    void glCopyTexSubImage3D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height );
    void glTexSubImage3D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels );
    void glTexImage3D ( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels );
    void glDrawRangeElements ( GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices );

    // OpenGL 1.3 core functions
    void glGetCompressedTexImage ( GLenum target, GLint level, void* img );
    void glCompressedTexSubImage1D ( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data );
    void glCompressedTexSubImage2D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data );
    void glCompressedTexSubImage3D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data );
    void glCompressedTexImage1D ( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data );
    void glCompressedTexImage2D ( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data );
    void glCompressedTexImage3D ( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data );
    void glSampleCoverage ( GLfloat value, GLboolean invert );
    void glActiveTexture ( GLenum texture );

    // OpenGL 1.4 core functions
    void glPointParameteriv ( GLenum pname, const GLint* params );
    void glPointParameteri ( GLenum pname, GLint param );
    void glPointParameterfv ( GLenum pname, const GLfloat* params );
    void glPointParameterf ( GLenum pname, GLfloat param );
    void glMultiDrawElements ( GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount );
    void glMultiDrawArrays ( GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount );
    void glBlendFuncSeparate ( GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha );

    // OpenGL 1.5 core functions
    void glGetBufferPointerv ( GLenum target, GLenum pname, void** params );
    void glGetBufferParameteriv ( GLenum target, GLenum pname, GLint* params );
    GLboolean glUnmapBuffer ( GLenum target );
    void* glMapBuffer ( GLenum target, GLenum access );
    void glGetBufferSubData ( GLenum target, GLintptr offset, GLsizeiptr size, void* data );
    void glBufferSubData ( GLenum target, GLintptr offset, GLsizeiptr size, const void* data );
    void glBufferData ( GLenum target, GLsizeiptr size, const void* data, GLenum usage );
    GLboolean glIsBuffer ( GLuint buffer );
    void glGenBuffers ( GLsizei n, GLuint* buffers );
    void glDeleteBuffers ( GLsizei n, const GLuint* buffers );
    void glBindBuffer ( GLenum target, GLuint buffer );
    void glGetQueryObjectuiv ( GLuint id, GLenum pname, GLuint* params );
    void glGetQueryObjectiv ( GLuint id, GLenum pname, GLint* params );
    void glGetQueryiv ( GLenum target, GLenum pname, GLint* params );
    void glEndQuery ( GLenum target );
    void glBeginQuery ( GLenum target, GLuint id );
    GLboolean glIsQuery ( GLuint id );
    void glDeleteQueries ( GLsizei n, const GLuint* ids );
    void glGenQueries ( GLsizei n, GLuint* ids );

    // OpenGL 2.0 core functions
    void glVertexAttribPointer ( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer );
    void glVertexAttrib4usv ( GLuint index, const GLushort* v );
    void glVertexAttrib4uiv ( GLuint index, const GLuint* v );
    void glVertexAttrib4ubv ( GLuint index, const GLubyte* v );
    void glVertexAttrib4sv ( GLuint index, const GLshort* v );
    void glVertexAttrib4s ( GLuint index, GLshort x, GLshort y, GLshort z, GLshort w );
    void glVertexAttrib4iv ( GLuint index, const GLint* v );
    void glVertexAttrib4fv ( GLuint index, const GLfloat* v );
    void glVertexAttrib4f ( GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w );
    void glVertexAttrib4dv ( GLuint index, const GLdouble* v );
    void glVertexAttrib4d ( GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w );
    void glVertexAttrib4bv ( GLuint index, const GLbyte* v );
    void glVertexAttrib4Nusv ( GLuint index, const GLushort* v );
    void glVertexAttrib4Nuiv ( GLuint index, const GLuint* v );
    void glVertexAttrib4Nubv ( GLuint index, const GLubyte* v );
    void glVertexAttrib4Nub ( GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w );
    void glVertexAttrib4Nsv ( GLuint index, const GLshort* v );
    void glVertexAttrib4Niv ( GLuint index, const GLint* v );
    void glVertexAttrib4Nbv ( GLuint index, const GLbyte* v );
    void glVertexAttrib3sv ( GLuint index, const GLshort* v );
    void glVertexAttrib3s ( GLuint index, GLshort x, GLshort y, GLshort z );
    void glVertexAttrib3fv ( GLuint index, const GLfloat* v );
    void glVertexAttrib3f ( GLuint index, GLfloat x, GLfloat y, GLfloat z );
    void glVertexAttrib3dv ( GLuint index, const GLdouble* v );
    void glVertexAttrib3d ( GLuint index, GLdouble x, GLdouble y, GLdouble z );
    void glVertexAttrib2sv ( GLuint index, const GLshort* v );
    void glVertexAttrib2s ( GLuint index, GLshort x, GLshort y );
    void glVertexAttrib2fv ( GLuint index, const GLfloat* v );
    void glVertexAttrib2f ( GLuint index, GLfloat x, GLfloat y );
    void glVertexAttrib2dv ( GLuint index, const GLdouble* v );
    void glVertexAttrib2d ( GLuint index, GLdouble x, GLdouble y );
    void glVertexAttrib1sv ( GLuint index, const GLshort* v );
    void glVertexAttrib1s ( GLuint index, GLshort x );
    void glVertexAttrib1fv ( GLuint index, const GLfloat* v );
    void glVertexAttrib1f ( GLuint index, GLfloat x );
    void glVertexAttrib1dv ( GLuint index, const GLdouble* v );
    void glVertexAttrib1d ( GLuint index, GLdouble x );
    void glValidateProgram ( GLuint program );
    void glUniformMatrix4fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glUniformMatrix3fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glUniformMatrix2fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glUniform4iv ( GLint location, GLsizei count, const GLint* value );
    void glUniform3iv ( GLint location, GLsizei count, const GLint* value );
    void glUniform2iv ( GLint location, GLsizei count, const GLint* value );
    void glUniform1iv ( GLint location, GLsizei count, const GLint* value );
    void glUniform4fv ( GLint location, GLsizei count, const GLfloat* value );
    void glUniform3fv ( GLint location, GLsizei count, const GLfloat* value );
    void glUniform2fv ( GLint location, GLsizei count, const GLfloat* value );
    void glUniform1fv ( GLint location, GLsizei count, const GLfloat* value );
    void glUniform4i ( GLint location, GLint v0, GLint v1, GLint v2, GLint v3 );
    void glUniform3i ( GLint location, GLint v0, GLint v1, GLint v2 );
    void glUniform2i ( GLint location, GLint v0, GLint v1 );
    void glUniform1i ( GLint location, GLint v0 );
    void glUniform4f ( GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 );
    void glUniform3f ( GLint location, GLfloat v0, GLfloat v1, GLfloat v2 );
    void glUniform2f ( GLint location, GLfloat v0, GLfloat v1 );
    void glUniform1f ( GLint location, GLfloat v0 );
    void glUseProgram ( GLuint program );
    void glShaderSource ( GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length );
    void glLinkProgram ( GLuint program );
    GLboolean glIsShader ( GLuint shader );
    GLboolean glIsProgram ( GLuint program );
    void glGetVertexAttribPointerv ( GLuint index, GLenum pname, void** pointer );
    void glGetVertexAttribiv ( GLuint index, GLenum pname, GLint* params );
    void glGetVertexAttribfv ( GLuint index, GLenum pname, GLfloat* params );
    void glGetVertexAttribdv ( GLuint index, GLenum pname, GLdouble* params );
    void glGetUniformiv ( GLuint program, GLint location, GLint* params );
    void glGetUniformfv ( GLuint program, GLint location, GLfloat* params );
    GLint glGetUniformLocation ( GLuint program, const GLchar* name );
    void glGetShaderSource ( GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source );
    void glGetShaderInfoLog ( GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog );
    void glGetShaderiv ( GLuint shader, GLenum pname, GLint* params );
    void glGetProgramInfoLog ( GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog );
    void glGetProgramiv ( GLuint program, GLenum pname, GLint* params );
    GLint glGetAttribLocation ( GLuint program, const GLchar* name );
    void glGetAttachedShaders ( GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders );
    void glGetActiveUniform ( GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name );
    void glGetActiveAttrib ( GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name );
    void glEnableVertexAttribArray ( GLuint index );
    void glDisableVertexAttribArray ( GLuint index );
    void glDetachShader ( GLuint program, GLuint shader );
    void glDeleteShader ( GLuint shader );
    void glDeleteProgram ( GLuint program );
    GLuint glCreateShader ( GLenum type );
    GLuint glCreateProgram ();
    void glCompileShader ( GLuint shader );
    void glBindAttribLocation ( GLuint program, GLuint index, const GLchar* name );
    void glAttachShader ( GLuint program, GLuint shader );
    void glStencilMaskSeparate ( GLenum face, GLuint mask );
    void glStencilFuncSeparate ( GLenum face, GLenum func, GLint ref, GLuint mask );
    void glStencilOpSeparate ( GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass );
    void glDrawBuffers ( GLsizei n, const GLenum* bufs );
    void glBlendEquationSeparate ( GLenum modeRGB, GLenum modeAlpha );

    // OpenGL 2.1 core functions
    void glUniformMatrix4x3fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glUniformMatrix3x4fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glUniformMatrix4x2fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glUniformMatrix2x4fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glUniformMatrix3x2fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glUniformMatrix2x3fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );

    // OpenGL 3.0 core functions
    GLboolean glIsVertexArray ( GLuint array );
    void glGenVertexArrays ( GLsizei n, GLuint* arrays );
    void glDeleteVertexArrays ( GLsizei n, const GLuint* arrays );
    void glBindVertexArray ( GLuint array );
    void glFlushMappedBufferRange ( GLenum target, GLintptr offset, GLsizeiptr length );
    void* glMapBufferRange ( GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access );
    void glFramebufferTextureLayer ( GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer );
    void glRenderbufferStorageMultisample ( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height );
    void glBlitFramebuffer ( GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter );
    void glGenerateMipmap ( GLenum target );
    void glGetFramebufferAttachmentParameteriv ( GLenum target, GLenum attachment, GLenum pname, GLint* params );
    void glFramebufferRenderbuffer ( GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer );
    void glFramebufferTexture3D ( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset );
    void glFramebufferTexture2D ( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level );
    void glFramebufferTexture1D ( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level );
    GLenum glCheckFramebufferStatus ( GLenum target );
    void glGenFramebuffers ( GLsizei n, GLuint* framebuffers );
    void glDeleteFramebuffers ( GLsizei n, const GLuint* framebuffers );
    void glBindFramebuffer ( GLenum target, GLuint framebuffer );
    GLboolean glIsFramebuffer ( GLuint framebuffer );
    void glGetRenderbufferParameteriv ( GLenum target, GLenum pname, GLint* params );
    void glRenderbufferStorage ( GLenum target, GLenum internalformat, GLsizei width, GLsizei height );
    void glGenRenderbuffers ( GLsizei n, GLuint* renderbuffers );
    void glDeleteRenderbuffers ( GLsizei n, const GLuint* renderbuffers );
    void glBindRenderbuffer ( GLenum target, GLuint renderbuffer );
    GLboolean glIsRenderbuffer ( GLuint renderbuffer );
    const GLubyte* glGetStringi ( GLenum name, GLuint index );
    void glClearBufferfi ( GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil );
    void glClearBufferfv ( GLenum buffer, GLint drawbuffer, const GLfloat* value );
    void glClearBufferuiv ( GLenum buffer, GLint drawbuffer, const GLuint* value );
    void glClearBufferiv ( GLenum buffer, GLint drawbuffer, const GLint* value );
    void glGetTexParameterIuiv ( GLenum target, GLenum pname, GLuint* params );
    void glGetTexParameterIiv ( GLenum target, GLenum pname, GLint* params );
    void glTexParameterIuiv ( GLenum target, GLenum pname, const GLuint* params );
    void glTexParameterIiv ( GLenum target, GLenum pname, const GLint* params );
    void glUniform4uiv ( GLint location, GLsizei count, const GLuint* value );
    void glUniform3uiv ( GLint location, GLsizei count, const GLuint* value );
    void glUniform2uiv ( GLint location, GLsizei count, const GLuint* value );
    void glUniform1uiv ( GLint location, GLsizei count, const GLuint* value );
    void glUniform4ui ( GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3 );
    void glUniform3ui ( GLint location, GLuint v0, GLuint v1, GLuint v2 );
    void glUniform2ui ( GLint location, GLuint v0, GLuint v1 );
    void glUniform1ui ( GLint location, GLuint v0 );
    GLint glGetFragDataLocation ( GLuint program, const GLchar* name );
    void glBindFragDataLocation ( GLuint program, GLuint color, const GLchar* name );
    void glGetUniformuiv ( GLuint program, GLint location, GLuint* params );
    void glVertexAttribI4usv ( GLuint index, const GLushort* v );
    void glVertexAttribI4ubv ( GLuint index, const GLubyte* v );
    void glVertexAttribI4sv ( GLuint index, const GLshort* v );
    void glVertexAttribI4bv ( GLuint index, const GLbyte* v );
    void glVertexAttribI4uiv ( GLuint index, const GLuint* v );
    void glVertexAttribI3uiv ( GLuint index, const GLuint* v );
    void glVertexAttribI2uiv ( GLuint index, const GLuint* v );
    void glVertexAttribI1uiv ( GLuint index, const GLuint* v );
    void glVertexAttribI4iv ( GLuint index, const GLint* v );
    void glVertexAttribI3iv ( GLuint index, const GLint* v );
    void glVertexAttribI2iv ( GLuint index, const GLint* v );
    void glVertexAttribI1iv ( GLuint index, const GLint* v );
    void glVertexAttribI4ui ( GLuint index, GLuint x, GLuint y, GLuint z, GLuint w );
    void glVertexAttribI3ui ( GLuint index, GLuint x, GLuint y, GLuint z );
    void glVertexAttribI2ui ( GLuint index, GLuint x, GLuint y );
    void glVertexAttribI1ui ( GLuint index, GLuint x );
    void glVertexAttribI4i ( GLuint index, GLint x, GLint y, GLint z, GLint w );
    void glVertexAttribI3i ( GLuint index, GLint x, GLint y, GLint z );
    void glVertexAttribI2i ( GLuint index, GLint x, GLint y );
    void glVertexAttribI1i ( GLuint index, GLint x );
    void glGetVertexAttribIuiv ( GLuint index, GLenum pname, GLuint* params );
    void glGetVertexAttribIiv ( GLuint index, GLenum pname, GLint* params );
    void glVertexAttribIPointer ( GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer );
    void glEndConditionalRender ();
    void glBeginConditionalRender ( GLuint id, GLenum mode );
    void glClampColor ( GLenum target, GLenum clamp );
    void glGetTransformFeedbackVarying ( GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name );
    void glTransformFeedbackVaryings ( GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode );
    void glBindBufferBase ( GLenum target, GLuint index, GLuint buffer );
    void glBindBufferRange ( GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size );
    void glEndTransformFeedback ();
    void glBeginTransformFeedback ( GLenum primitiveMode );
    GLboolean glIsEnabledi ( GLenum target, GLuint index );
    void glDisablei ( GLenum target, GLuint index );
    void glEnablei ( GLenum target, GLuint index );
    void glGetIntegeri_v ( GLenum target, GLuint index, GLint* data );
    void glGetBooleani_v ( GLenum target, GLuint index, GLboolean* data );
    void glColorMaski ( GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a );

    // OpenGL 3.1 core functions
    void glUniformBlockBinding ( GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding );
    void glGetActiveUniformBlockName ( GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName );
    void glGetActiveUniformBlockiv ( GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params );
    GLuint glGetUniformBlockIndex ( GLuint program, const GLchar* uniformBlockName );
    void glGetActiveUniformName ( GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName );
    void glGetActiveUniformsiv ( GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params );
    void glGetUniformIndices ( GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices );
    void glCopyBufferSubData ( GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size );
    void glPrimitiveRestartIndex ( GLuint index );
    void glTexBuffer ( GLenum target, GLenum internalformat, GLuint buffer );
    void glDrawElementsInstanced ( GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount );
    void glDrawArraysInstanced ( GLenum mode, GLint first, GLsizei count, GLsizei instancecount );

    // OpenGL 3.2 core functions
    void glSampleMaski ( GLuint maskNumber, GLbitfield mask );
    void glGetMultisamplefv ( GLenum pname, GLuint index, GLfloat* val );
    void glTexImage3DMultisample ( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations );
    void glTexImage2DMultisample ( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations );
    void glFramebufferTexture ( GLenum target, GLenum attachment, GLuint texture, GLint level );
    void glGetBufferParameteri64v ( GLenum target, GLenum pname, GLint64* params );
    void glGetInteger64i_v ( GLenum target, GLuint index, GLint64* data );
    void glGetSynciv ( GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values );
    void glGetInteger64v ( GLenum pname, GLint64* data );
    void glWaitSync ( GLsync sync, GLbitfield flags, GLuint64 timeout );
    GLenum glClientWaitSync ( GLsync sync, GLbitfield flags, GLuint64 timeout );
    void glDeleteSync ( GLsync sync );
    GLboolean glIsSync ( GLsync sync );
    GLsync glFenceSync ( GLenum condition, GLbitfield flags );
    void glProvokingVertex ( GLenum mode );
    void glMultiDrawElementsBaseVertex ( GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount, const GLint* basevertex );
    void glDrawElementsInstancedBaseVertex ( GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex );
    void glDrawRangeElementsBaseVertex ( GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices, GLint basevertex );
    void glDrawElementsBaseVertex ( GLenum mode, GLsizei count, GLenum type, const void* indices, GLint basevertex );

    // OpenGL 3.3 core functions
    void glVertexAttribP4uiv ( GLuint index, GLenum type, GLboolean normalized, const GLuint* value );
    void glVertexAttribP4ui ( GLuint index, GLenum type, GLboolean normalized, GLuint value );
    void glVertexAttribP3uiv ( GLuint index, GLenum type, GLboolean normalized, const GLuint* value );
    void glVertexAttribP3ui ( GLuint index, GLenum type, GLboolean normalized, GLuint value );
    void glVertexAttribP2uiv ( GLuint index, GLenum type, GLboolean normalized, const GLuint* value );
    void glVertexAttribP2ui ( GLuint index, GLenum type, GLboolean normalized, GLuint value );
    void glVertexAttribP1uiv ( GLuint index, GLenum type, GLboolean normalized, const GLuint* value );
    void glVertexAttribP1ui ( GLuint index, GLenum type, GLboolean normalized, GLuint value );
    void glVertexAttribDivisor ( GLuint index, GLuint divisor );
    void glGetQueryObjectui64v ( GLuint id, GLenum pname, GLuint64* params );
    void glGetQueryObjecti64v ( GLuint id, GLenum pname, GLint64* params );
    void glQueryCounter ( GLuint id, GLenum target );
    void glGetSamplerParameterIuiv ( GLuint sampler, GLenum pname, GLuint* params );
    void glGetSamplerParameterfv ( GLuint sampler, GLenum pname, GLfloat* params );
    void glGetSamplerParameterIiv ( GLuint sampler, GLenum pname, GLint* params );
    void glGetSamplerParameteriv ( GLuint sampler, GLenum pname, GLint* params );
    void glSamplerParameterIuiv ( GLuint sampler, GLenum pname, const GLuint* param );
    void glSamplerParameterIiv ( GLuint sampler, GLenum pname, const GLint* param );
    void glSamplerParameterfv ( GLuint sampler, GLenum pname, const GLfloat* param );
    void glSamplerParameterf ( GLuint sampler, GLenum pname, GLfloat param );
    void glSamplerParameteriv ( GLuint sampler, GLenum pname, const GLint* param );
    void glSamplerParameteri ( GLuint sampler, GLenum pname, GLint param );
    void glBindSampler ( GLuint unit, GLuint sampler );
    GLboolean glIsSampler ( GLuint sampler );
    void glDeleteSamplers ( GLsizei count, const GLuint* samplers );
    void glGenSamplers ( GLsizei count, GLuint* samplers );
    GLint glGetFragDataIndex ( GLuint program, const GLchar* name );
    void glBindFragDataLocationIndexed ( GLuint program, GLuint colorNumber, GLuint index, const GLchar* name );

    // OpenGL 4.0 core functions
    void glGetQueryIndexediv ( GLenum target, GLuint index, GLenum pname, GLint* params );
    void glEndQueryIndexed ( GLenum target, GLuint index );
    void glBeginQueryIndexed ( GLenum target, GLuint index, GLuint id );
    void glDrawTransformFeedbackStream ( GLenum mode, GLuint id, GLuint stream );
    void glDrawTransformFeedback ( GLenum mode, GLuint id );
    void glResumeTransformFeedback ();
    void glPauseTransformFeedback ();
    GLboolean glIsTransformFeedback ( GLuint id );
    void glGenTransformFeedbacks ( GLsizei n, GLuint* ids );
    void glDeleteTransformFeedbacks ( GLsizei n, const GLuint* ids );
    void glBindTransformFeedback ( GLenum target, GLuint id );
    void glPatchParameterfv ( GLenum pname, const GLfloat* values );
    void glPatchParameteri ( GLenum pname, GLint value );
    void glGetProgramStageiv ( GLuint program, GLenum shadertype, GLenum pname, GLint* values );
    void glGetUniformSubroutineuiv ( GLenum shadertype, GLint location, GLuint* params );
    void glUniformSubroutinesuiv ( GLenum shadertype, GLsizei count, const GLuint* indices );
    void glGetActiveSubroutineName ( GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name );
    void glGetActiveSubroutineUniformName ( GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name );
    void glGetActiveSubroutineUniformiv ( GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values );
    GLuint glGetSubroutineIndex ( GLuint program, GLenum shadertype, const GLchar* name );
    GLint glGetSubroutineUniformLocation ( GLuint program, GLenum shadertype, const GLchar* name );
    void glGetUniformdv ( GLuint program, GLint location, GLdouble* params );
    void glUniformMatrix4x3dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glUniformMatrix4x2dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glUniformMatrix3x4dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glUniformMatrix3x2dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glUniformMatrix2x4dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glUniformMatrix2x3dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glUniformMatrix4dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glUniformMatrix3dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glUniformMatrix2dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glUniform4dv ( GLint location, GLsizei count, const GLdouble* value );
    void glUniform3dv ( GLint location, GLsizei count, const GLdouble* value );
    void glUniform2dv ( GLint location, GLsizei count, const GLdouble* value );
    void glUniform1dv ( GLint location, GLsizei count, const GLdouble* value );
    void glUniform4d ( GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w );
    void glUniform3d ( GLint location, GLdouble x, GLdouble y, GLdouble z );
    void glUniform2d ( GLint location, GLdouble x, GLdouble y );
    void glUniform1d ( GLint location, GLdouble x );
    void glDrawElementsIndirect ( GLenum mode, GLenum type, const void* indirect );
    void glDrawArraysIndirect ( GLenum mode, const void* indirect );
    void glBlendFuncSeparatei ( GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha );
    void glBlendFunci ( GLuint buf, GLenum src, GLenum dst );
    void glBlendEquationSeparatei ( GLuint buf, GLenum modeRGB, GLenum modeAlpha );
    void glBlendEquationi ( GLuint buf, GLenum mode );
    void glMinSampleShading ( GLfloat value );

    // OpenGL 4.1 core functions
    void glGetDoublei_v ( GLenum target, GLuint index, GLdouble* data );
    void glGetFloati_v ( GLenum target, GLuint index, GLfloat* data );
    void glDepthRangeIndexed ( GLuint index, GLdouble n, GLdouble f );
    void glDepthRangeArrayv ( GLuint first, GLsizei count, const GLdouble* v );
    void glScissorIndexedv ( GLuint index, const GLint* v );
    void glScissorIndexed ( GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height );
    void glScissorArrayv ( GLuint first, GLsizei count, const GLint* v );
    void glViewportIndexedfv ( GLuint index, const GLfloat* v );
    void glViewportIndexedf ( GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h );
    void glViewportArrayv ( GLuint first, GLsizei count, const GLfloat* v );
    void glGetVertexAttribLdv ( GLuint index, GLenum pname, GLdouble* params );
    void glVertexAttribLPointer ( GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer );
    void glVertexAttribL4dv ( GLuint index, const GLdouble* v );
    void glVertexAttribL3dv ( GLuint index, const GLdouble* v );
    void glVertexAttribL2dv ( GLuint index, const GLdouble* v );
    void glVertexAttribL1dv ( GLuint index, const GLdouble* v );
    void glVertexAttribL4d ( GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w );
    void glVertexAttribL3d ( GLuint index, GLdouble x, GLdouble y, GLdouble z );
    void glVertexAttribL2d ( GLuint index, GLdouble x, GLdouble y );
    void glVertexAttribL1d ( GLuint index, GLdouble x );
    void glGetProgramPipelineInfoLog ( GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog );
    void glValidateProgramPipeline ( GLuint pipeline );
    void glProgramUniformMatrix4x3dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glProgramUniformMatrix3x4dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glProgramUniformMatrix4x2dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glProgramUniformMatrix2x4dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glProgramUniformMatrix3x2dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glProgramUniformMatrix2x3dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glProgramUniformMatrix4x3fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glProgramUniformMatrix3x4fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glProgramUniformMatrix4x2fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glProgramUniformMatrix2x4fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glProgramUniformMatrix3x2fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glProgramUniformMatrix2x3fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glProgramUniformMatrix4dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glProgramUniformMatrix3dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glProgramUniformMatrix2dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value );
    void glProgramUniformMatrix4fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glProgramUniformMatrix3fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glProgramUniformMatrix2fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
    void glProgramUniform4uiv ( GLuint program, GLint location, GLsizei count, const GLuint* value );
    void glProgramUniform4ui ( GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3 );
    void glProgramUniform4dv ( GLuint program, GLint location, GLsizei count, const GLdouble* value );
    void glProgramUniform4d ( GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3 );
    void glProgramUniform4fv ( GLuint program, GLint location, GLsizei count, const GLfloat* value );
    void glProgramUniform4f ( GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 );
    void glProgramUniform4iv ( GLuint program, GLint location, GLsizei count, const GLint* value );
    void glProgramUniform4i ( GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3 );
    void glProgramUniform3uiv ( GLuint program, GLint location, GLsizei count, const GLuint* value );
    void glProgramUniform3ui ( GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2 );
    void glProgramUniform3dv ( GLuint program, GLint location, GLsizei count, const GLdouble* value );
    void glProgramUniform3d ( GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2 );
    void glProgramUniform3fv ( GLuint program, GLint location, GLsizei count, const GLfloat* value );
    void glProgramUniform3f ( GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2 );
    void glProgramUniform3iv ( GLuint program, GLint location, GLsizei count, const GLint* value );
    void glProgramUniform3i ( GLuint program, GLint location, GLint v0, GLint v1, GLint v2 );
    void glProgramUniform2uiv ( GLuint program, GLint location, GLsizei count, const GLuint* value );
    void glProgramUniform2ui ( GLuint program, GLint location, GLuint v0, GLuint v1 );
    void glProgramUniform2dv ( GLuint program, GLint location, GLsizei count, const GLdouble* value );
    void glProgramUniform2d ( GLuint program, GLint location, GLdouble v0, GLdouble v1 );
    void glProgramUniform2fv ( GLuint program, GLint location, GLsizei count, const GLfloat* value );
    void glProgramUniform2f ( GLuint program, GLint location, GLfloat v0, GLfloat v1 );
    void glProgramUniform2iv ( GLuint program, GLint location, GLsizei count, const GLint* value );
    void glProgramUniform2i ( GLuint program, GLint location, GLint v0, GLint v1 );
    void glProgramUniform1uiv ( GLuint program, GLint location, GLsizei count, const GLuint* value );
    void glProgramUniform1ui ( GLuint program, GLint location, GLuint v0 );
    void glProgramUniform1dv ( GLuint program, GLint location, GLsizei count, const GLdouble* value );
    void glProgramUniform1d ( GLuint program, GLint location, GLdouble v0 );
    void glProgramUniform1fv ( GLuint program, GLint location, GLsizei count, const GLfloat* value );
    void glProgramUniform1f ( GLuint program, GLint location, GLfloat v0 );
    void glProgramUniform1iv ( GLuint program, GLint location, GLsizei count, const GLint* value );
    void glProgramUniform1i ( GLuint program, GLint location, GLint v0 );
    void glGetProgramPipelineiv ( GLuint pipeline, GLenum pname, GLint* params );
    GLboolean glIsProgramPipeline ( GLuint pipeline );
    void glGenProgramPipelines ( GLsizei n, GLuint* pipelines );
    void glDeleteProgramPipelines ( GLsizei n, const GLuint* pipelines );
    void glBindProgramPipeline ( GLuint pipeline );
    GLuint glCreateShaderProgramv ( GLenum type, GLsizei count, const GLchar* const* strings );
    void glActiveShaderProgram ( GLuint pipeline, GLuint program );
    void glUseProgramStages ( GLuint pipeline, GLbitfield stages, GLuint program );
    void glProgramParameteri ( GLuint program, GLenum pname, GLint value );
    void glProgramBinary ( GLuint program, GLenum binaryFormat, const void* binary, GLsizei length );
    void glGetProgramBinary ( GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary );
    void glClearDepthf ( GLfloat dd );
    void glDepthRangef ( GLfloat n, GLfloat f );
    void glGetShaderPrecisionFormat ( GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision );
    void glShaderBinary ( GLsizei count, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length );
    void glReleaseShaderCompiler ();

    // OpenGL 4.2 core functions
    void glDrawTransformFeedbackStreamInstanced ( GLenum mode, GLuint id, GLuint stream, GLsizei instancecount );
    void glDrawTransformFeedbackInstanced ( GLenum mode, GLuint id, GLsizei instancecount );
    void glTexStorage3D ( GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth );
    void glTexStorage2D ( GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height );
    void glTexStorage1D ( GLenum target, GLsizei levels, GLenum internalformat, GLsizei width );
    void glMemoryBarrier ( GLbitfield barriers );
    void glBindImageTexture ( GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format );
    void glGetActiveAtomicCounterBufferiv ( GLuint program, GLuint bufferIndex, GLenum pname, GLint* params );
    void glGetInternalformativ ( GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params );
    void glDrawElementsInstancedBaseVertexBaseInstance ( GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance );
    void glDrawElementsInstancedBaseInstance ( GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLuint baseinstance );
    void glDrawArraysInstancedBaseInstance ( GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance );

    // OpenGL 4.3 core functions
    void glGetObjectPtrLabel ( const void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label );
    void glObjectPtrLabel ( const void* ptr, GLsizei length, const GLchar* label );
    void glGetObjectLabel ( GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label );
    void glObjectLabel ( GLenum identifier, GLuint name, GLsizei length, const GLchar* label );
    void glPopDebugGroup ();
    void glPushDebugGroup ( GLenum source, GLuint id, GLsizei length, const GLchar* message );
    GLuint glGetDebugMessageLog ( GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog );
    void glDebugMessageCallback ( GLDEBUGPROC callback, const void* userParam );
    void glDebugMessageInsert ( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf );
    void glDebugMessageControl ( GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled );
    void glVertexBindingDivisor ( GLuint bindingindex, GLuint divisor );
    void glVertexAttribBinding ( GLuint attribindex, GLuint bindingindex );
    void glVertexAttribLFormat ( GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset );
    void glVertexAttribIFormat ( GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset );
    void glVertexAttribFormat ( GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset );
    void glBindVertexBuffer ( GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride );
    void glTextureView ( GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers );
    void glTexStorage3DMultisample ( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations );
    void glTexStorage2DMultisample ( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations );
    void glTexBufferRange ( GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size );
    void glShaderStorageBlockBinding ( GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding );
    GLint glGetProgramResourceLocationIndex ( GLuint program, GLenum programInterface, const GLchar* name );
    GLint glGetProgramResourceLocation ( GLuint program, GLenum programInterface, const GLchar* name );
    void glGetProgramResourceiv ( GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params );
    void glGetProgramResourceName ( GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name );
    GLuint glGetProgramResourceIndex ( GLuint program, GLenum programInterface, const GLchar* name );
    void glGetProgramInterfaceiv ( GLuint program, GLenum programInterface, GLenum pname, GLint* params );
    void glMultiDrawElementsIndirect ( GLenum mode, GLenum type, const void* indirect, GLsizei drawcount, GLsizei stride );
    void glMultiDrawArraysIndirect ( GLenum mode, const void* indirect, GLsizei drawcount, GLsizei stride );
    void glInvalidateSubFramebuffer ( GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height );
    void glInvalidateFramebuffer ( GLenum target, GLsizei numAttachments, const GLenum* attachments );
    void glInvalidateBufferData ( GLuint buffer );
    void glInvalidateBufferSubData ( GLuint buffer, GLintptr offset, GLsizeiptr length );
    void glInvalidateTexImage ( GLuint texture, GLint level );
    void glInvalidateTexSubImage ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth );
    void glGetInternalformati64v ( GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64* params );
    void glGetFramebufferParameteriv ( GLenum target, GLenum pname, GLint* params );
    void glFramebufferParameteri ( GLenum target, GLenum pname, GLint param );
    void glCopyImageSubData ( GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth );
    void glDispatchComputeIndirect ( GLintptr indirect );
    void glDispatchCompute ( GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z );
    void glClearBufferSubData ( GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data );
    void glClearBufferData ( GLenum target, GLenum internalformat, GLenum format, GLenum type, const void* data );

    // OpenGL 4.4 core functions
    void glBindVertexBuffers ( GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides );
    void glBindImageTextures ( GLuint first, GLsizei count, const GLuint* textures );
    void glBindSamplers ( GLuint first, GLsizei count, const GLuint* samplers );
    void glBindTextures ( GLuint first, GLsizei count, const GLuint* textures );
    void glBindBuffersRange ( GLenum target, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizeiptr* sizes );
    void glBindBuffersBase ( GLenum target, GLuint first, GLsizei count, const GLuint* buffers );
    void glClearTexSubImage ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data );
    void glClearTexImage ( GLuint texture, GLint level, GLenum format, GLenum type, const void* data );
    void glBufferStorage ( GLenum target, GLsizeiptr size, const void* data, GLbitfield flags );

    // OpenGL 4.5 core functions
    void glTextureBarrier ();
    void glReadnPixels ( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data );
    void glGetnUniformuiv ( GLuint program, GLint location, GLsizei bufSize, GLuint* params );
    void glGetnUniformiv ( GLuint program, GLint location, GLsizei bufSize, GLint* params );
    void glGetnUniformfv ( GLuint program, GLint location, GLsizei bufSize, GLfloat* params );
    void glGetnUniformdv ( GLuint program, GLint location, GLsizei bufSize, GLdouble* params );
    void glGetnTexImage ( GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels );
    void glGetnCompressedTexImage ( GLenum target, GLint lod, GLsizei bufSize, void* pixels );
    GLenum glGetGraphicsResetStatus ();
    void glGetCompressedTextureSubImage ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels );
    void glGetTextureSubImage ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels );
    void glMemoryBarrierByRegion ( GLbitfield barriers );
    void glCreateQueries ( GLenum target, GLsizei n, GLuint* ids );
    void glCreateProgramPipelines ( GLsizei n, GLuint* pipelines );
    void glCreateSamplers ( GLsizei n, GLuint* samplers );
    void glGetVertexArrayIndexed64iv ( GLuint vaobj, GLuint index, GLenum pname, GLint64* param );
    void glGetVertexArrayIndexediv ( GLuint vaobj, GLuint index, GLenum pname, GLint* param );
    void glGetVertexArrayiv ( GLuint vaobj, GLenum pname, GLint* param );
    void glVertexArrayBindingDivisor ( GLuint vaobj, GLuint bindingindex, GLuint divisor );
    void glVertexArrayAttribLFormat ( GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset );
    void glVertexArrayAttribIFormat ( GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset );
    void glVertexArrayAttribFormat ( GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset );
    void glVertexArrayAttribBinding ( GLuint vaobj, GLuint attribindex, GLuint bindingindex );
    void glVertexArrayVertexBuffers ( GLuint vaobj, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides );
    void glVertexArrayVertexBuffer ( GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride );
    void glVertexArrayElementBuffer ( GLuint vaobj, GLuint buffer );
    void glEnableVertexArrayAttrib ( GLuint vaobj, GLuint index );
    void glDisableVertexArrayAttrib ( GLuint vaobj, GLuint index );
    void glCreateVertexArrays ( GLsizei n, GLuint* arrays );
    void glGetTextureParameteriv ( GLuint texture, GLenum pname, GLint* params );
    void glGetTextureParameterIuiv ( GLuint texture, GLenum pname, GLuint* params );
    void glGetTextureParameterIiv ( GLuint texture, GLenum pname, GLint* params );
    void glGetTextureParameterfv ( GLuint texture, GLenum pname, GLfloat* params );
    void glGetTextureLevelParameteriv ( GLuint texture, GLint level, GLenum pname, GLint* params );
    void glGetTextureLevelParameterfv ( GLuint texture, GLint level, GLenum pname, GLfloat* params );
    void glGetCompressedTextureImage ( GLuint texture, GLint level, GLsizei bufSize, void* pixels );
    void glGetTextureImage ( GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels );
    void glBindTextureUnit ( GLuint unit, GLuint texture );
    void glGenerateTextureMipmap ( GLuint texture );
    void glTextureParameteriv ( GLuint texture, GLenum pname, const GLint* param );
    void glTextureParameterIuiv ( GLuint texture, GLenum pname, const GLuint* params );
    void glTextureParameterIiv ( GLuint texture, GLenum pname, const GLint* params );
    void glTextureParameteri ( GLuint texture, GLenum pname, GLint param );
    void glTextureParameterfv ( GLuint texture, GLenum pname, const GLfloat* param );
    void glTextureParameterf ( GLuint texture, GLenum pname, GLfloat param );
    void glCopyTextureSubImage3D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height );
    void glCopyTextureSubImage2D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height );
    void glCopyTextureSubImage1D ( GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width );
    void glCompressedTextureSubImage3D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data );
    void glCompressedTextureSubImage2D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data );
    void glCompressedTextureSubImage1D ( GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data );
    void glTextureSubImage3D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels );
    void glTextureSubImage2D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels );
    void glTextureSubImage1D ( GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels );
    void glTextureStorage3DMultisample ( GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations );
    void glTextureStorage2DMultisample ( GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations );
    void glTextureStorage3D ( GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth );
    void glTextureStorage2D ( GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height );
    void glTextureStorage1D ( GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width );
    void glTextureBufferRange ( GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizei size );
    void glTextureBuffer ( GLuint texture, GLenum internalformat, GLuint buffer );
    void glCreateTextures ( GLenum target, GLsizei n, GLuint* textures );
    void glGetNamedRenderbufferParameteriv ( GLuint renderbuffer, GLenum pname, GLint* params );
    void glNamedRenderbufferStorageMultisample ( GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height );
    void glNamedRenderbufferStorage ( GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height );
    void glCreateRenderbuffers ( GLsizei n, GLuint* renderbuffers );
    void glGetNamedFramebufferAttachmentParameteriv ( GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params );
    void glGetNamedFramebufferParameteriv ( GLuint framebuffer, GLenum pname, GLint* param );
    GLenum glCheckNamedFramebufferStatus ( GLuint framebuffer, GLenum target );
    void glBlitNamedFramebuffer ( GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter );
    void glClearNamedFramebufferfi ( GLuint framebuffer, GLenum buffer, GLfloat depth, GLint stencil );
    void glClearNamedFramebufferfv ( GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat* value );
    void glClearNamedFramebufferuiv ( GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value );
    void glClearNamedFramebufferiv ( GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value );
    void glInvalidateNamedFramebufferSubData ( GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height );
    void glInvalidateNamedFramebufferData ( GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments );
    void glNamedFramebufferReadBuffer ( GLuint framebuffer, GLenum src );
    void glNamedFramebufferDrawBuffers ( GLuint framebuffer, GLsizei n, const GLenum* bufs );
    void glNamedFramebufferDrawBuffer ( GLuint framebuffer, GLenum buf );
    void glNamedFramebufferTextureLayer ( GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer );
    void glNamedFramebufferTexture ( GLuint framebuffer, GLenum attachment, GLuint texture, GLint level );
    void glNamedFramebufferParameteri ( GLuint framebuffer, GLenum pname, GLint param );
    void glNamedFramebufferRenderbuffer ( GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer );
    void glCreateFramebuffers ( GLsizei n, GLuint* framebuffers );
    void glGetNamedBufferSubData ( GLuint buffer, GLintptr offset, GLsizei size, void* data );
    void glGetNamedBufferPointerv ( GLuint buffer, GLenum pname, void** params );
    void glGetNamedBufferParameteri64v ( GLuint buffer, GLenum pname, GLint64* params );
    void glGetNamedBufferParameteriv ( GLuint buffer, GLenum pname, GLint* params );
    void glFlushMappedNamedBufferRange ( GLuint buffer, GLintptr offset, GLsizei length );
    GLboolean glUnmapNamedBuffer ( GLuint buffer );
    void* glMapNamedBufferRange ( GLuint buffer, GLintptr offset, GLsizei length, GLbitfield access );
    void* glMapNamedBuffer ( GLuint buffer, GLenum access );
    void glClearNamedBufferSubData ( GLuint buffer, GLenum internalformat, GLintptr offset, GLsizei size, GLenum format, GLenum type, const void* data );
    void glClearNamedBufferData ( GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data );
    void glCopyNamedBufferSubData ( GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizei size );
    void glNamedBufferSubData ( GLuint buffer, GLintptr offset, GLsizei size, const void* data );
    void glNamedBufferData ( GLuint buffer, GLsizei size, const void* data, GLenum usage );
    void glNamedBufferStorage ( GLuint buffer, GLsizei size, const void* data, GLbitfield flags );
    void glCreateBuffers ( GLsizei n, GLuint* buffers );
    void glGetTransformFeedbacki64_v ( GLuint xfb, GLenum pname, GLuint index, GLint64* param );
    void glGetTransformFeedbacki_v ( GLuint xfb, GLenum pname, GLuint index, GLint* param );
    void glGetTransformFeedbackiv ( GLuint xfb, GLenum pname, GLint* param );
    void glTransformFeedbackBufferRange ( GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizei size );
    void glTransformFeedbackBufferBase ( GLuint xfb, GLuint index, GLuint buffer );
    void glCreateTransformFeedbacks ( GLsizei n, GLuint* ids );
    void glClipControl ( GLenum origin, GLenum depth );

    // OpenGL 4.6 core functions
    void glSpecializeShader ( GLuint shader, const GLchar* pEntryPoint, GLuint numSpecializationConstants, const GLuint* pConstantIndex, const GLuint* pConstantValue );
    void glMultiDrawArraysIndirectCount ( GLenum mode, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride );
    void glMultiDrawElementsIndirectCount ( GLenum mode, GLenum type, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride );
    void glPolygonOffsetClamp ( GLfloat factor, GLfloat units, GLfloat clamp );

    private:
        friend class QOpenGLVersionFunctionsFactory;

        static bool isContextCompatible ( QOpenGLContext* context );
        static QOpenGLVersionProfile versionProfile ();

        QOpenGLFunctions_1_0_CoreBackend* d_1_0_Core;
        QOpenGLFunctions_1_1_CoreBackend* d_1_1_Core;
        QOpenGLFunctions_1_2_CoreBackend* d_1_2_Core;
        QOpenGLFunctions_1_3_CoreBackend* d_1_3_Core;
        QOpenGLFunctions_1_4_CoreBackend* d_1_4_Core;
        QOpenGLFunctions_1_5_CoreBackend* d_1_5_Core;
        QOpenGLFunctions_2_0_CoreBackend* d_2_0_Core;
        QOpenGLFunctions_2_1_CoreBackend* d_2_1_Core;
        QOpenGLFunctions_3_0_CoreBackend* d_3_0_Core;
        QOpenGLFunctions_3_1_CoreBackend* d_3_1_Core;
        QOpenGLFunctions_3_2_CoreBackend* d_3_2_Core;
        QOpenGLFunctions_3_3_CoreBackend* d_3_3_Core;
        QOpenGLFunctions_4_0_CoreBackend* d_4_0_Core;
        QOpenGLFunctions_4_1_CoreBackend* d_4_1_Core;
        QOpenGLFunctions_4_2_CoreBackend* d_4_2_Core;
        QOpenGLFunctions_4_3_CoreBackend* d_4_3_Core;
        QOpenGLFunctions_4_4_CoreBackend* d_4_4_Core;
        QOpenGLFunctions_4_5_CoreBackend* d_4_5_Core;
        QOpenGLFunctions_4_6_CoreBackend* d_4_6_Core;
};


// OpenGL 1.0 core functions
inline void QOpenGLFunctions_4_6_Core::glViewport ( GLint x, GLint y, GLsizei width, GLsizei height )
{
    d_1_0_Core->f.Viewport ( x, y, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glDepthRange ( GLdouble nearVal, GLdouble farVal )
{
    d_1_0_Core->f.DepthRange ( nearVal, farVal );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsEnabled ( GLenum cap )
{
    return d_1_0_Core->f.IsEnabled ( cap );
}

inline void QOpenGLFunctions_4_6_Core::glGetTexLevelParameteriv ( GLenum target, GLint level, GLenum pname, GLint* params )
{
    d_1_0_Core->f.GetTexLevelParameteriv ( target, level, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetTexLevelParameterfv ( GLenum target, GLint level, GLenum pname, GLfloat* params )
{
    d_1_0_Core->f.GetTexLevelParameterfv ( target, level, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetTexParameteriv ( GLenum target, GLenum pname, GLint* params )
{
    d_1_0_Core->f.GetTexParameteriv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetTexParameterfv ( GLenum target, GLenum pname, GLfloat* params )
{
    d_1_0_Core->f.GetTexParameterfv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetTexImage ( GLenum target, GLint level, GLenum format, GLenum type, void* pixels )
{
    d_1_0_Core->f.GetTexImage ( target, level, format, type, pixels );
}

inline const GLubyte* QOpenGLFunctions_4_6_Core::glGetString ( GLenum name )
{
    return d_1_0_Core->f.GetString ( name );
}

inline void QOpenGLFunctions_4_6_Core::glGetIntegerv ( GLenum pname, GLint* data )
{
    d_1_0_Core->f.GetIntegerv ( pname, data );
}

inline void QOpenGLFunctions_4_6_Core::glGetFloatv ( GLenum pname, GLfloat* data )
{
    d_1_0_Core->f.GetFloatv ( pname, data );
}

inline GLenum QOpenGLFunctions_4_6_Core::glGetError ()
{
    return d_1_0_Core->f.GetError ();
}

inline void QOpenGLFunctions_4_6_Core::glGetDoublev ( GLenum pname, GLdouble* data )
{
    d_1_0_Core->f.GetDoublev ( pname, data );
}

inline void QOpenGLFunctions_4_6_Core::glGetBooleanv ( GLenum pname, GLboolean* data )
{
    d_1_0_Core->f.GetBooleanv ( pname, data );
}

inline void QOpenGLFunctions_4_6_Core::glReadPixels ( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels )
{
    d_1_0_Core->f.ReadPixels ( x, y, width, height, format, type, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glReadBuffer ( GLenum src )
{
    d_1_0_Core->f.ReadBuffer ( src );
}

inline void QOpenGLFunctions_4_6_Core::glPixelStorei ( GLenum pname, GLint param )
{
    d_1_0_Core->f.PixelStorei ( pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glPixelStoref ( GLenum pname, GLfloat param )
{
    d_1_0_Core->f.PixelStoref ( pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glDepthFunc ( GLenum func )
{
    d_1_0_Core->f.DepthFunc ( func );
}

inline void QOpenGLFunctions_4_6_Core::glStencilOp ( GLenum fail, GLenum zfail, GLenum zpass )
{
    d_1_0_Core->f.StencilOp ( fail, zfail, zpass );
}

inline void QOpenGLFunctions_4_6_Core::glStencilFunc ( GLenum func, GLint ref, GLuint mask )
{
    d_1_0_Core->f.StencilFunc ( func, ref, mask );
}

inline void QOpenGLFunctions_4_6_Core::glLogicOp ( GLenum opcode )
{
    d_1_0_Core->f.LogicOp ( opcode );
}

inline void QOpenGLFunctions_4_6_Core::glBlendFunc ( GLenum sfactor, GLenum dfactor )
{
    d_1_0_Core->f.BlendFunc ( sfactor, dfactor );
}

inline void QOpenGLFunctions_4_6_Core::glFlush ()
{
    d_1_0_Core->f.Flush ();
}

inline void QOpenGLFunctions_4_6_Core::glFinish ()
{
    d_1_0_Core->f.Finish ();
}

inline void QOpenGLFunctions_4_6_Core::glEnable ( GLenum cap )
{
    d_1_0_Core->f.Enable ( cap );
}

inline void QOpenGLFunctions_4_6_Core::glDisable ( GLenum cap )
{
    d_1_0_Core->f.Disable ( cap );
}

inline void QOpenGLFunctions_4_6_Core::glDepthMask ( GLboolean flag )
{
    d_1_0_Core->f.DepthMask ( flag );
}

inline void QOpenGLFunctions_4_6_Core::glColorMask ( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha )
{
    d_1_0_Core->f.ColorMask ( red, green, blue, alpha );
}

inline void QOpenGLFunctions_4_6_Core::glStencilMask ( GLuint mask )
{
    d_1_0_Core->f.StencilMask ( mask );
}

inline void QOpenGLFunctions_4_6_Core::glClearDepth ( GLdouble depth )
{
    d_1_0_Core->f.ClearDepth ( depth );
}

inline void QOpenGLFunctions_4_6_Core::glClearStencil ( GLint s )
{
    d_1_0_Core->f.ClearStencil ( s );
}

inline void QOpenGLFunctions_4_6_Core::glClearColor ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
    d_1_0_Core->f.ClearColor ( red, green, blue, alpha );
}

inline void QOpenGLFunctions_4_6_Core::glClear ( GLbitfield mask )
{
    d_1_0_Core->f.Clear ( mask );
}

inline void QOpenGLFunctions_4_6_Core::glDrawBuffer ( GLenum buf )
{
    d_1_0_Core->f.DrawBuffer ( buf );
}

inline void QOpenGLFunctions_4_6_Core::glTexImage2D ( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels )
{
    d_1_0_Core->f.TexImage2D ( target, level, internalformat, width, height, border, format, type, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glTexImage1D ( GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels )
{
    d_1_0_Core->f.TexImage1D ( target, level, internalformat, width, border, format, type, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glTexParameteriv ( GLenum target, GLenum pname, const GLint* params )
{
    d_1_0_Core->f.TexParameteriv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glTexParameteri ( GLenum target, GLenum pname, GLint param )
{
    d_1_0_Core->f.TexParameteri ( target, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glTexParameterfv ( GLenum target, GLenum pname, const GLfloat* params )
{
    d_1_0_Core->f.TexParameterfv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glTexParameterf ( GLenum target, GLenum pname, GLfloat param )
{
    d_1_0_Core->f.TexParameterf ( target, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glScissor ( GLint x, GLint y, GLsizei width, GLsizei height )
{
    d_1_0_Core->f.Scissor ( x, y, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glPolygonMode ( GLenum face, GLenum mode )
{
    d_1_0_Core->f.PolygonMode ( face, mode );
}

inline void QOpenGLFunctions_4_6_Core::glPointSize ( GLfloat size )
{
    d_1_0_Core->f.PointSize ( size );
}

inline void QOpenGLFunctions_4_6_Core::glLineWidth ( GLfloat width )
{
    d_1_0_Core->f.LineWidth ( width );
}

inline void QOpenGLFunctions_4_6_Core::glHint ( GLenum target, GLenum mode )
{
    d_1_0_Core->f.Hint ( target, mode );
}

inline void QOpenGLFunctions_4_6_Core::glFrontFace ( GLenum mode )
{
    d_1_0_Core->f.FrontFace ( mode );
}

inline void QOpenGLFunctions_4_6_Core::glCullFace ( GLenum mode )
{
    d_1_0_Core->f.CullFace ( mode );
}


// OpenGL 1.1 core functions
inline GLboolean QOpenGLFunctions_4_6_Core::glIsTexture ( GLuint texture )
{
    return d_1_1_Core->f.IsTexture ( texture );
}

inline void QOpenGLFunctions_4_6_Core::glGenTextures ( GLsizei n, GLuint* textures )
{
    d_1_1_Core->f.GenTextures ( n, textures );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteTextures ( GLsizei n, const GLuint* textures )
{
    d_1_1_Core->f.DeleteTextures ( n, textures );
}

inline void QOpenGLFunctions_4_6_Core::glBindTexture ( GLenum target, GLuint texture )
{
    d_1_1_Core->f.BindTexture ( target, texture );
}

inline void QOpenGLFunctions_4_6_Core::glTexSubImage2D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels )
{
    d_1_1_Core->f.TexSubImage2D ( target, level, xoffset, yoffset, width, height, format, type, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glTexSubImage1D ( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels )
{
    d_1_1_Core->f.TexSubImage1D ( target, level, xoffset, width, format, type, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glCopyTexSubImage2D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height )
{
    d_1_1_Core->f.CopyTexSubImage2D ( target, level, xoffset, yoffset, x, y, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glCopyTexSubImage1D ( GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width )
{
    d_1_1_Core->f.CopyTexSubImage1D ( target, level, xoffset, x, y, width );
}

inline void QOpenGLFunctions_4_6_Core::glCopyTexImage2D ( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border )
{
    d_1_1_Core->f.CopyTexImage2D ( target, level, internalformat, x, y, width, height, border );
}

inline void QOpenGLFunctions_4_6_Core::glCopyTexImage1D ( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border )
{
    d_1_1_Core->f.CopyTexImage1D ( target, level, internalformat, x, y, width, border );
}

inline void QOpenGLFunctions_4_6_Core::glPolygonOffset ( GLfloat factor, GLfloat units )
{
    d_1_1_Core->f.PolygonOffset ( factor, units );
}

inline void QOpenGLFunctions_4_6_Core::glDrawElements ( GLenum mode, GLsizei count, GLenum type, const void* indices )
{
    d_1_1_Core->f.DrawElements ( mode, count, type, indices );
}

inline void QOpenGLFunctions_4_6_Core::glDrawArrays ( GLenum mode, GLint first, GLsizei count )
{
    d_1_1_Core->f.DrawArrays ( mode, first, count );
}


// OpenGL 1.2 core functions
inline void QOpenGLFunctions_4_6_Core::glBlendColor ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
    d_1_2_Core->f.BlendColor ( red, green, blue, alpha );
}

inline void QOpenGLFunctions_4_6_Core::glBlendEquation ( GLenum mode )
{
    d_1_2_Core->f.BlendEquation ( mode );
}

inline void QOpenGLFunctions_4_6_Core::glCopyTexSubImage3D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height )
{
    d_1_2_Core->f.CopyTexSubImage3D ( target, level, xoffset, yoffset, zoffset, x, y, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glTexSubImage3D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels )
{
    d_1_2_Core->f.TexSubImage3D ( target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glTexImage3D ( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels )
{
    d_1_2_Core->f.TexImage3D ( target, level, internalformat, width, height, depth, border, format, type, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glDrawRangeElements ( GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices )
{
    d_1_2_Core->f.DrawRangeElements ( mode, start, end, count, type, indices );
}


// OpenGL 1.3 core functions
inline void QOpenGLFunctions_4_6_Core::glGetCompressedTexImage ( GLenum target, GLint level, void* img )
{
    d_1_3_Core->f.GetCompressedTexImage ( target, level, img );
}

inline void QOpenGLFunctions_4_6_Core::glCompressedTexSubImage1D ( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data )
{
    d_1_3_Core->f.CompressedTexSubImage1D ( target, level, xoffset, width, format, imageSize, data );
}

inline void QOpenGLFunctions_4_6_Core::glCompressedTexSubImage2D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data )
{
    d_1_3_Core->f.CompressedTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, imageSize, data );
}

inline void QOpenGLFunctions_4_6_Core::glCompressedTexSubImage3D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data )
{
    d_1_3_Core->f.CompressedTexSubImage3D ( target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data );
}

inline void QOpenGLFunctions_4_6_Core::glCompressedTexImage1D ( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data )
{
    d_1_3_Core->f.CompressedTexImage1D ( target, level, internalformat, width, border, imageSize, data );
}

inline void QOpenGLFunctions_4_6_Core::glCompressedTexImage2D ( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data )
{
    d_1_3_Core->f.CompressedTexImage2D ( target, level, internalformat, width, height, border, imageSize, data );
}

inline void QOpenGLFunctions_4_6_Core::glCompressedTexImage3D ( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data )
{
    d_1_3_Core->f.CompressedTexImage3D ( target, level, internalformat, width, height, depth, border, imageSize, data );
}

inline void QOpenGLFunctions_4_6_Core::glSampleCoverage ( GLfloat value, GLboolean invert )
{
    d_1_3_Core->f.SampleCoverage ( value, invert );
}

inline void QOpenGLFunctions_4_6_Core::glActiveTexture ( GLenum texture )
{
    d_1_3_Core->f.ActiveTexture ( texture );
}


// OpenGL 1.4 core functions
inline void QOpenGLFunctions_4_6_Core::glPointParameteriv ( GLenum pname, const GLint* params )
{
    d_1_4_Core->f.PointParameteriv ( pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glPointParameteri ( GLenum pname, GLint param )
{
    d_1_4_Core->f.PointParameteri ( pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glPointParameterfv ( GLenum pname, const GLfloat* params )
{
    d_1_4_Core->f.PointParameterfv ( pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glPointParameterf ( GLenum pname, GLfloat param )
{
    d_1_4_Core->f.PointParameterf ( pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glMultiDrawElements ( GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount )
{
    d_1_4_Core->f.MultiDrawElements ( mode, count, type, indices, drawcount );
}

inline void QOpenGLFunctions_4_6_Core::glMultiDrawArrays ( GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount )
{
    d_1_4_Core->f.MultiDrawArrays ( mode, first, count, drawcount );
}

inline void QOpenGLFunctions_4_6_Core::glBlendFuncSeparate ( GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha )
{
    d_1_4_Core->f.BlendFuncSeparate ( sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha );
}


// OpenGL 1.5 core functions
inline void QOpenGLFunctions_4_6_Core::glGetBufferPointerv ( GLenum target, GLenum pname, void** params )
{
    d_1_5_Core->f.GetBufferPointerv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetBufferParameteriv ( GLenum target, GLenum pname, GLint* params )
{
    d_1_5_Core->f.GetBufferParameteriv ( target, pname, params );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glUnmapBuffer ( GLenum target )
{
    return d_1_5_Core->f.UnmapBuffer ( target );
}

inline void* QOpenGLFunctions_4_6_Core::glMapBuffer ( GLenum target, GLenum access )
{
    return d_1_5_Core->f.MapBuffer ( target, access );
}

inline void QOpenGLFunctions_4_6_Core::glGetBufferSubData ( GLenum target, GLintptr offset, GLsizeiptr size, void* data )
{
    d_1_5_Core->f.GetBufferSubData ( target, offset, size, data );
}

inline void QOpenGLFunctions_4_6_Core::glBufferSubData ( GLenum target, GLintptr offset, GLsizeiptr size, const void* data )
{
    d_1_5_Core->f.BufferSubData ( target, offset, size, data );
}

inline void QOpenGLFunctions_4_6_Core::glBufferData ( GLenum target, GLsizeiptr size, const void* data, GLenum usage )
{
    d_1_5_Core->f.BufferData ( target, size, data, usage );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsBuffer ( GLuint buffer )
{
    return d_1_5_Core->f.IsBuffer ( buffer );
}

inline void QOpenGLFunctions_4_6_Core::glGenBuffers ( GLsizei n, GLuint* buffers )
{
    d_1_5_Core->f.GenBuffers ( n, buffers );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteBuffers ( GLsizei n, const GLuint* buffers )
{
    d_1_5_Core->f.DeleteBuffers ( n, buffers );
}

inline void QOpenGLFunctions_4_6_Core::glBindBuffer ( GLenum target, GLuint buffer )
{
    d_1_5_Core->f.BindBuffer ( target, buffer );
}

inline void QOpenGLFunctions_4_6_Core::glGetQueryObjectuiv ( GLuint id, GLenum pname, GLuint* params )
{
    d_1_5_Core->f.GetQueryObjectuiv ( id, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetQueryObjectiv ( GLuint id, GLenum pname, GLint* params )
{
    d_1_5_Core->f.GetQueryObjectiv ( id, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetQueryiv ( GLenum target, GLenum pname, GLint* params )
{
    d_1_5_Core->f.GetQueryiv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glEndQuery ( GLenum target )
{
    d_1_5_Core->f.EndQuery ( target );
}

inline void QOpenGLFunctions_4_6_Core::glBeginQuery ( GLenum target, GLuint id )
{
    d_1_5_Core->f.BeginQuery ( target, id );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsQuery ( GLuint id )
{
    return d_1_5_Core->f.IsQuery ( id );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteQueries ( GLsizei n, const GLuint* ids )
{
    d_1_5_Core->f.DeleteQueries ( n, ids );
}

inline void QOpenGLFunctions_4_6_Core::glGenQueries ( GLsizei n, GLuint* ids )
{
    d_1_5_Core->f.GenQueries ( n, ids );
}


// OpenGL 2.0 core functions
inline void QOpenGLFunctions_4_6_Core::glVertexAttribPointer ( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer )
{
    d_2_0_Core->f.VertexAttribPointer ( index, size, type, normalized, stride, pointer );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4usv ( GLuint index, const GLushort* v )
{
    d_2_0_Core->f.VertexAttrib4usv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4uiv ( GLuint index, const GLuint* v )
{
    d_2_0_Core->f.VertexAttrib4uiv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4ubv ( GLuint index, const GLubyte* v )
{
    d_2_0_Core->f.VertexAttrib4ubv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4sv ( GLuint index, const GLshort* v )
{
    d_2_0_Core->f.VertexAttrib4sv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4s ( GLuint index, GLshort x, GLshort y, GLshort z, GLshort w )
{
    d_2_0_Core->f.VertexAttrib4s ( index, x, y, z, w );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4iv ( GLuint index, const GLint* v )
{
    d_2_0_Core->f.VertexAttrib4iv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4fv ( GLuint index, const GLfloat* v )
{
    d_2_0_Core->f.VertexAttrib4fv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4f ( GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
    d_2_0_Core->f.VertexAttrib4f ( index, x, y, z, w );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4dv ( GLuint index, const GLdouble* v )
{
    d_2_0_Core->f.VertexAttrib4dv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4d ( GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w )
{
    d_2_0_Core->f.VertexAttrib4d ( index, x, y, z, w );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4bv ( GLuint index, const GLbyte* v )
{
    d_2_0_Core->f.VertexAttrib4bv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4Nusv ( GLuint index, const GLushort* v )
{
    d_2_0_Core->f.VertexAttrib4Nusv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4Nuiv ( GLuint index, const GLuint* v )
{
    d_2_0_Core->f.VertexAttrib4Nuiv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4Nubv ( GLuint index, const GLubyte* v )
{
    d_2_0_Core->f.VertexAttrib4Nubv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4Nub ( GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w )
{
    d_2_0_Core->f.VertexAttrib4Nub ( index, x, y, z, w );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4Nsv ( GLuint index, const GLshort* v )
{
    d_2_0_Core->f.VertexAttrib4Nsv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4Niv ( GLuint index, const GLint* v )
{
    d_2_0_Core->f.VertexAttrib4Niv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib4Nbv ( GLuint index, const GLbyte* v )
{
    d_2_0_Core->f.VertexAttrib4Nbv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib3sv ( GLuint index, const GLshort* v )
{
    d_2_0_Core->f.VertexAttrib3sv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib3s ( GLuint index, GLshort x, GLshort y, GLshort z )
{
    d_2_0_Core->f.VertexAttrib3s ( index, x, y, z );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib3fv ( GLuint index, const GLfloat* v )
{
    d_2_0_Core->f.VertexAttrib3fv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib3f ( GLuint index, GLfloat x, GLfloat y, GLfloat z )
{
    d_2_0_Core->f.VertexAttrib3f ( index, x, y, z );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib3dv ( GLuint index, const GLdouble* v )
{
    d_2_0_Core->f.VertexAttrib3dv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib3d ( GLuint index, GLdouble x, GLdouble y, GLdouble z )
{
    d_2_0_Core->f.VertexAttrib3d ( index, x, y, z );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib2sv ( GLuint index, const GLshort* v )
{
    d_2_0_Core->f.VertexAttrib2sv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib2s ( GLuint index, GLshort x, GLshort y )
{
    d_2_0_Core->f.VertexAttrib2s ( index, x, y );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib2fv ( GLuint index, const GLfloat* v )
{
    d_2_0_Core->f.VertexAttrib2fv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib2f ( GLuint index, GLfloat x, GLfloat y )
{
    d_2_0_Core->f.VertexAttrib2f ( index, x, y );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib2dv ( GLuint index, const GLdouble* v )
{
    d_2_0_Core->f.VertexAttrib2dv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib2d ( GLuint index, GLdouble x, GLdouble y )
{
    d_2_0_Core->f.VertexAttrib2d ( index, x, y );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib1sv ( GLuint index, const GLshort* v )
{
    d_2_0_Core->f.VertexAttrib1sv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib1s ( GLuint index, GLshort x )
{
    d_2_0_Core->f.VertexAttrib1s ( index, x );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib1fv ( GLuint index, const GLfloat* v )
{
    d_2_0_Core->f.VertexAttrib1fv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib1f ( GLuint index, GLfloat x )
{
    d_2_0_Core->f.VertexAttrib1f ( index, x );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib1dv ( GLuint index, const GLdouble* v )
{
    d_2_0_Core->f.VertexAttrib1dv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttrib1d ( GLuint index, GLdouble x )
{
    d_2_0_Core->f.VertexAttrib1d ( index, x );
}

inline void QOpenGLFunctions_4_6_Core::glValidateProgram ( GLuint program )
{
    d_2_0_Core->f.ValidateProgram ( program );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix4fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_2_0_Core->f.UniformMatrix4fv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix3fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_2_0_Core->f.UniformMatrix3fv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix2fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_2_0_Core->f.UniformMatrix2fv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform4iv ( GLint location, GLsizei count, const GLint* value )
{
    d_2_0_Core->f.Uniform4iv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform3iv ( GLint location, GLsizei count, const GLint* value )
{
    d_2_0_Core->f.Uniform3iv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform2iv ( GLint location, GLsizei count, const GLint* value )
{
    d_2_0_Core->f.Uniform2iv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform1iv ( GLint location, GLsizei count, const GLint* value )
{
    d_2_0_Core->f.Uniform1iv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform4fv ( GLint location, GLsizei count, const GLfloat* value )
{
    d_2_0_Core->f.Uniform4fv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform3fv ( GLint location, GLsizei count, const GLfloat* value )
{
    d_2_0_Core->f.Uniform3fv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform2fv ( GLint location, GLsizei count, const GLfloat* value )
{
    d_2_0_Core->f.Uniform2fv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform1fv ( GLint location, GLsizei count, const GLfloat* value )
{
    d_2_0_Core->f.Uniform1fv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform4i ( GLint location, GLint v0, GLint v1, GLint v2, GLint v3 )
{
    d_2_0_Core->f.Uniform4i ( location, v0, v1, v2, v3 );
}

inline void QOpenGLFunctions_4_6_Core::glUniform3i ( GLint location, GLint v0, GLint v1, GLint v2 )
{
    d_2_0_Core->f.Uniform3i ( location, v0, v1, v2 );
}

inline void QOpenGLFunctions_4_6_Core::glUniform2i ( GLint location, GLint v0, GLint v1 )
{
    d_2_0_Core->f.Uniform2i ( location, v0, v1 );
}

inline void QOpenGLFunctions_4_6_Core::glUniform1i ( GLint location, GLint v0 )
{
    d_2_0_Core->f.Uniform1i ( location, v0 );
}

inline void QOpenGLFunctions_4_6_Core::glUniform4f ( GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 )
{
    d_2_0_Core->f.Uniform4f ( location, v0, v1, v2, v3 );
}

inline void QOpenGLFunctions_4_6_Core::glUniform3f ( GLint location, GLfloat v0, GLfloat v1, GLfloat v2 )
{
    d_2_0_Core->f.Uniform3f ( location, v0, v1, v2 );
}

inline void QOpenGLFunctions_4_6_Core::glUniform2f ( GLint location, GLfloat v0, GLfloat v1 )
{
    d_2_0_Core->f.Uniform2f ( location, v0, v1 );
}

inline void QOpenGLFunctions_4_6_Core::glUniform1f ( GLint location, GLfloat v0 )
{
    d_2_0_Core->f.Uniform1f ( location, v0 );
}

inline void QOpenGLFunctions_4_6_Core::glUseProgram ( GLuint program )
{
    d_2_0_Core->f.UseProgram ( program );
}

inline void QOpenGLFunctions_4_6_Core::glShaderSource ( GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length )
{
    d_2_0_Core->f.ShaderSource ( shader, count, string, length );
}

inline void QOpenGLFunctions_4_6_Core::glLinkProgram ( GLuint program )
{
    d_2_0_Core->f.LinkProgram ( program );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsShader ( GLuint shader )
{
    return d_2_0_Core->f.IsShader ( shader );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsProgram ( GLuint program )
{
    return d_2_0_Core->f.IsProgram ( program );
}

inline void QOpenGLFunctions_4_6_Core::glGetVertexAttribPointerv ( GLuint index, GLenum pname, void** pointer )
{
    d_2_0_Core->f.GetVertexAttribPointerv ( index, pname, pointer );
}

inline void QOpenGLFunctions_4_6_Core::glGetVertexAttribiv ( GLuint index, GLenum pname, GLint* params )
{
    d_2_0_Core->f.GetVertexAttribiv ( index, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetVertexAttribfv ( GLuint index, GLenum pname, GLfloat* params )
{
    d_2_0_Core->f.GetVertexAttribfv ( index, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetVertexAttribdv ( GLuint index, GLenum pname, GLdouble* params )
{
    d_2_0_Core->f.GetVertexAttribdv ( index, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetUniformiv ( GLuint program, GLint location, GLint* params )
{
    d_2_0_Core->f.GetUniformiv ( program, location, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetUniformfv ( GLuint program, GLint location, GLfloat* params )
{
    d_2_0_Core->f.GetUniformfv ( program, location, params );
}

inline GLint QOpenGLFunctions_4_6_Core::glGetUniformLocation ( GLuint program, const GLchar* name )
{
    return d_2_0_Core->f.GetUniformLocation ( program, name );
}

inline void QOpenGLFunctions_4_6_Core::glGetShaderSource ( GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source )
{
    d_2_0_Core->f.GetShaderSource ( shader, bufSize, length, source );
}

inline void QOpenGLFunctions_4_6_Core::glGetShaderInfoLog ( GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog )
{
    d_2_0_Core->f.GetShaderInfoLog ( shader, bufSize, length, infoLog );
}

inline void QOpenGLFunctions_4_6_Core::glGetShaderiv ( GLuint shader, GLenum pname, GLint* params )
{
    d_2_0_Core->f.GetShaderiv ( shader, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetProgramInfoLog ( GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog )
{
    d_2_0_Core->f.GetProgramInfoLog ( program, bufSize, length, infoLog );
}

inline void QOpenGLFunctions_4_6_Core::glGetProgramiv ( GLuint program, GLenum pname, GLint* params )
{
    d_2_0_Core->f.GetProgramiv ( program, pname, params );
}

inline GLint QOpenGLFunctions_4_6_Core::glGetAttribLocation ( GLuint program, const GLchar* name )
{
    return d_2_0_Core->f.GetAttribLocation ( program, name );
}

inline void QOpenGLFunctions_4_6_Core::glGetAttachedShaders ( GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders )
{
    d_2_0_Core->f.GetAttachedShaders ( program, maxCount, count, shaders );
}

inline void QOpenGLFunctions_4_6_Core::glGetActiveUniform ( GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name )
{
    d_2_0_Core->f.GetActiveUniform ( program, index, bufSize, length, size, type, name );
}

inline void QOpenGLFunctions_4_6_Core::glGetActiveAttrib ( GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name )
{
    d_2_0_Core->f.GetActiveAttrib ( program, index, bufSize, length, size, type, name );
}

inline void QOpenGLFunctions_4_6_Core::glEnableVertexAttribArray ( GLuint index )
{
    d_2_0_Core->f.EnableVertexAttribArray ( index );
}

inline void QOpenGLFunctions_4_6_Core::glDisableVertexAttribArray ( GLuint index )
{
    d_2_0_Core->f.DisableVertexAttribArray ( index );
}

inline void QOpenGLFunctions_4_6_Core::glDetachShader ( GLuint program, GLuint shader )
{
    d_2_0_Core->f.DetachShader ( program, shader );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteShader ( GLuint shader )
{
    d_2_0_Core->f.DeleteShader ( shader );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteProgram ( GLuint program )
{
    d_2_0_Core->f.DeleteProgram ( program );
}

inline GLuint QOpenGLFunctions_4_6_Core::glCreateShader ( GLenum type )
{
    return d_2_0_Core->f.CreateShader ( type );
}

inline GLuint QOpenGLFunctions_4_6_Core::glCreateProgram ()
{
    return d_2_0_Core->f.CreateProgram ();
}

inline void QOpenGLFunctions_4_6_Core::glCompileShader ( GLuint shader )
{
    d_2_0_Core->f.CompileShader ( shader );
}

inline void QOpenGLFunctions_4_6_Core::glBindAttribLocation ( GLuint program, GLuint index, const GLchar* name )
{
    d_2_0_Core->f.BindAttribLocation ( program, index, name );
}

inline void QOpenGLFunctions_4_6_Core::glAttachShader ( GLuint program, GLuint shader )
{
    d_2_0_Core->f.AttachShader ( program, shader );
}

inline void QOpenGLFunctions_4_6_Core::glStencilMaskSeparate ( GLenum face, GLuint mask )
{
    d_2_0_Core->f.StencilMaskSeparate ( face, mask );
}

inline void QOpenGLFunctions_4_6_Core::glStencilFuncSeparate ( GLenum face, GLenum func, GLint ref, GLuint mask )
{
    d_2_0_Core->f.StencilFuncSeparate ( face, func, ref, mask );
}

inline void QOpenGLFunctions_4_6_Core::glStencilOpSeparate ( GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass )
{
    d_2_0_Core->f.StencilOpSeparate ( face, sfail, dpfail, dppass );
}

inline void QOpenGLFunctions_4_6_Core::glDrawBuffers ( GLsizei n, const GLenum* bufs )
{
    d_2_0_Core->f.DrawBuffers ( n, bufs );
}

inline void QOpenGLFunctions_4_6_Core::glBlendEquationSeparate ( GLenum modeRGB, GLenum modeAlpha )
{
    d_2_0_Core->f.BlendEquationSeparate ( modeRGB, modeAlpha );
}


// OpenGL 2.1 core functions
inline void QOpenGLFunctions_4_6_Core::glUniformMatrix4x3fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_2_1_Core->f.UniformMatrix4x3fv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix3x4fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_2_1_Core->f.UniformMatrix3x4fv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix4x2fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_2_1_Core->f.UniformMatrix4x2fv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix2x4fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_2_1_Core->f.UniformMatrix2x4fv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix3x2fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_2_1_Core->f.UniformMatrix3x2fv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix2x3fv ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_2_1_Core->f.UniformMatrix2x3fv ( location, count, transpose, value );
}


// OpenGL 3.0 core functions
inline GLboolean QOpenGLFunctions_4_6_Core::glIsVertexArray ( GLuint array )
{
    return d_3_0_Core->f.IsVertexArray ( array );
}

inline void QOpenGLFunctions_4_6_Core::glGenVertexArrays ( GLsizei n, GLuint* arrays )
{
    d_3_0_Core->f.GenVertexArrays ( n, arrays );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteVertexArrays ( GLsizei n, const GLuint* arrays )
{
    d_3_0_Core->f.DeleteVertexArrays ( n, arrays );
}

inline void QOpenGLFunctions_4_6_Core::glBindVertexArray ( GLuint array )
{
    d_3_0_Core->f.BindVertexArray ( array );
}

inline void QOpenGLFunctions_4_6_Core::glFlushMappedBufferRange ( GLenum target, GLintptr offset, GLsizeiptr length )
{
    d_3_0_Core->f.FlushMappedBufferRange ( target, offset, length );
}

inline void* QOpenGLFunctions_4_6_Core::glMapBufferRange ( GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access )
{
    return d_3_0_Core->f.MapBufferRange ( target, offset, length, access );
}

inline void QOpenGLFunctions_4_6_Core::glFramebufferTextureLayer ( GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer )
{
    d_3_0_Core->f.FramebufferTextureLayer ( target, attachment, texture, level, layer );
}

inline void QOpenGLFunctions_4_6_Core::glRenderbufferStorageMultisample ( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height )
{
    d_3_0_Core->f.RenderbufferStorageMultisample ( target, samples, internalformat, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glBlitFramebuffer ( GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter )
{
    d_3_0_Core->f.BlitFramebuffer ( srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter );
}

inline void QOpenGLFunctions_4_6_Core::glGenerateMipmap ( GLenum target )
{
    d_3_0_Core->f.GenerateMipmap ( target );
}

inline void QOpenGLFunctions_4_6_Core::glGetFramebufferAttachmentParameteriv ( GLenum target, GLenum attachment, GLenum pname, GLint* params )
{
    d_3_0_Core->f.GetFramebufferAttachmentParameteriv ( target, attachment, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glFramebufferRenderbuffer ( GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer )
{
    d_3_0_Core->f.FramebufferRenderbuffer ( target, attachment, renderbuffertarget, renderbuffer );
}

inline void QOpenGLFunctions_4_6_Core::glFramebufferTexture3D ( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset )
{
    d_3_0_Core->f.FramebufferTexture3D ( target, attachment, textarget, texture, level, zoffset );
}

inline void QOpenGLFunctions_4_6_Core::glFramebufferTexture2D ( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level )
{
    d_3_0_Core->f.FramebufferTexture2D ( target, attachment, textarget, texture, level );
}

inline void QOpenGLFunctions_4_6_Core::glFramebufferTexture1D ( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level )
{
    d_3_0_Core->f.FramebufferTexture1D ( target, attachment, textarget, texture, level );
}

inline GLenum QOpenGLFunctions_4_6_Core::glCheckFramebufferStatus ( GLenum target )
{
    return d_3_0_Core->f.CheckFramebufferStatus ( target );
}

inline void QOpenGLFunctions_4_6_Core::glGenFramebuffers ( GLsizei n, GLuint* framebuffers )
{
    d_3_0_Core->f.GenFramebuffers ( n, framebuffers );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteFramebuffers ( GLsizei n, const GLuint* framebuffers )
{
    d_3_0_Core->f.DeleteFramebuffers ( n, framebuffers );
}

inline void QOpenGLFunctions_4_6_Core::glBindFramebuffer ( GLenum target, GLuint framebuffer )
{
    d_3_0_Core->f.BindFramebuffer ( target, framebuffer );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsFramebuffer ( GLuint framebuffer )
{
    return d_3_0_Core->f.IsFramebuffer ( framebuffer );
}

inline void QOpenGLFunctions_4_6_Core::glGetRenderbufferParameteriv ( GLenum target, GLenum pname, GLint* params )
{
    d_3_0_Core->f.GetRenderbufferParameteriv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glRenderbufferStorage ( GLenum target, GLenum internalformat, GLsizei width, GLsizei height )
{
    d_3_0_Core->f.RenderbufferStorage ( target, internalformat, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glGenRenderbuffers ( GLsizei n, GLuint* renderbuffers )
{
    d_3_0_Core->f.GenRenderbuffers ( n, renderbuffers );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteRenderbuffers ( GLsizei n, const GLuint* renderbuffers )
{
    d_3_0_Core->f.DeleteRenderbuffers ( n, renderbuffers );
}

inline void QOpenGLFunctions_4_6_Core::glBindRenderbuffer ( GLenum target, GLuint renderbuffer )
{
    d_3_0_Core->f.BindRenderbuffer ( target, renderbuffer );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsRenderbuffer ( GLuint renderbuffer )
{
    return d_3_0_Core->f.IsRenderbuffer ( renderbuffer );
}

inline const GLubyte* QOpenGLFunctions_4_6_Core::glGetStringi ( GLenum name, GLuint index )
{
    return d_3_0_Core->f.GetStringi ( name, index );
}

inline void QOpenGLFunctions_4_6_Core::glClearBufferfi ( GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil )
{
    d_3_0_Core->f.ClearBufferfi ( buffer, drawbuffer, depth, stencil );
}

inline void QOpenGLFunctions_4_6_Core::glClearBufferfv ( GLenum buffer, GLint drawbuffer, const GLfloat* value )
{
    d_3_0_Core->f.ClearBufferfv ( buffer, drawbuffer, value );
}

inline void QOpenGLFunctions_4_6_Core::glClearBufferuiv ( GLenum buffer, GLint drawbuffer, const GLuint* value )
{
    d_3_0_Core->f.ClearBufferuiv ( buffer, drawbuffer, value );
}

inline void QOpenGLFunctions_4_6_Core::glClearBufferiv ( GLenum buffer, GLint drawbuffer, const GLint* value )
{
    d_3_0_Core->f.ClearBufferiv ( buffer, drawbuffer, value );
}

inline void QOpenGLFunctions_4_6_Core::glGetTexParameterIuiv ( GLenum target, GLenum pname, GLuint* params )
{
    d_3_0_Core->f.GetTexParameterIuiv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetTexParameterIiv ( GLenum target, GLenum pname, GLint* params )
{
    d_3_0_Core->f.GetTexParameterIiv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glTexParameterIuiv ( GLenum target, GLenum pname, const GLuint* params )
{
    d_3_0_Core->f.TexParameterIuiv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glTexParameterIiv ( GLenum target, GLenum pname, const GLint* params )
{
    d_3_0_Core->f.TexParameterIiv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glUniform4uiv ( GLint location, GLsizei count, const GLuint* value )
{
    d_3_0_Core->f.Uniform4uiv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform3uiv ( GLint location, GLsizei count, const GLuint* value )
{
    d_3_0_Core->f.Uniform3uiv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform2uiv ( GLint location, GLsizei count, const GLuint* value )
{
    d_3_0_Core->f.Uniform2uiv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform1uiv ( GLint location, GLsizei count, const GLuint* value )
{
    d_3_0_Core->f.Uniform1uiv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform4ui ( GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3 )
{
    d_3_0_Core->f.Uniform4ui ( location, v0, v1, v2, v3 );
}

inline void QOpenGLFunctions_4_6_Core::glUniform3ui ( GLint location, GLuint v0, GLuint v1, GLuint v2 )
{
    d_3_0_Core->f.Uniform3ui ( location, v0, v1, v2 );
}

inline void QOpenGLFunctions_4_6_Core::glUniform2ui ( GLint location, GLuint v0, GLuint v1 )
{
    d_3_0_Core->f.Uniform2ui ( location, v0, v1 );
}

inline void QOpenGLFunctions_4_6_Core::glUniform1ui ( GLint location, GLuint v0 )
{
    d_3_0_Core->f.Uniform1ui ( location, v0 );
}

inline GLint QOpenGLFunctions_4_6_Core::glGetFragDataLocation ( GLuint program, const GLchar* name )
{
    return d_3_0_Core->f.GetFragDataLocation ( program, name );
}

inline void QOpenGLFunctions_4_6_Core::glBindFragDataLocation ( GLuint program, GLuint color, const GLchar* name )
{
    d_3_0_Core->f.BindFragDataLocation ( program, color, name );
}

inline void QOpenGLFunctions_4_6_Core::glGetUniformuiv ( GLuint program, GLint location, GLuint* params )
{
    d_3_0_Core->f.GetUniformuiv ( program, location, params );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI4usv ( GLuint index, const GLushort* v )
{
    d_3_0_Core->f.VertexAttribI4usv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI4ubv ( GLuint index, const GLubyte* v )
{
    d_3_0_Core->f.VertexAttribI4ubv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI4sv ( GLuint index, const GLshort* v )
{
    d_3_0_Core->f.VertexAttribI4sv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI4bv ( GLuint index, const GLbyte* v )
{
    d_3_0_Core->f.VertexAttribI4bv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI4uiv ( GLuint index, const GLuint* v )
{
    d_3_0_Core->f.VertexAttribI4uiv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI3uiv ( GLuint index, const GLuint* v )
{
    d_3_0_Core->f.VertexAttribI3uiv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI2uiv ( GLuint index, const GLuint* v )
{
    d_3_0_Core->f.VertexAttribI2uiv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI1uiv ( GLuint index, const GLuint* v )
{
    d_3_0_Core->f.VertexAttribI1uiv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI4iv ( GLuint index, const GLint* v )
{
    d_3_0_Core->f.VertexAttribI4iv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI3iv ( GLuint index, const GLint* v )
{
    d_3_0_Core->f.VertexAttribI3iv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI2iv ( GLuint index, const GLint* v )
{
    d_3_0_Core->f.VertexAttribI2iv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI1iv ( GLuint index, const GLint* v )
{
    d_3_0_Core->f.VertexAttribI1iv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI4ui ( GLuint index, GLuint x, GLuint y, GLuint z, GLuint w )
{
    d_3_0_Core->f.VertexAttribI4ui ( index, x, y, z, w );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI3ui ( GLuint index, GLuint x, GLuint y, GLuint z )
{
    d_3_0_Core->f.VertexAttribI3ui ( index, x, y, z );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI2ui ( GLuint index, GLuint x, GLuint y )
{
    d_3_0_Core->f.VertexAttribI2ui ( index, x, y );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI1ui ( GLuint index, GLuint x )
{
    d_3_0_Core->f.VertexAttribI1ui ( index, x );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI4i ( GLuint index, GLint x, GLint y, GLint z, GLint w )
{
    d_3_0_Core->f.VertexAttribI4i ( index, x, y, z, w );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI3i ( GLuint index, GLint x, GLint y, GLint z )
{
    d_3_0_Core->f.VertexAttribI3i ( index, x, y, z );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI2i ( GLuint index, GLint x, GLint y )
{
    d_3_0_Core->f.VertexAttribI2i ( index, x, y );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribI1i ( GLuint index, GLint x )
{
    d_3_0_Core->f.VertexAttribI1i ( index, x );
}

inline void QOpenGLFunctions_4_6_Core::glGetVertexAttribIuiv ( GLuint index, GLenum pname, GLuint* params )
{
    d_3_0_Core->f.GetVertexAttribIuiv ( index, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetVertexAttribIiv ( GLuint index, GLenum pname, GLint* params )
{
    d_3_0_Core->f.GetVertexAttribIiv ( index, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribIPointer ( GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer )
{
    d_3_0_Core->f.VertexAttribIPointer ( index, size, type, stride, pointer );
}

inline void QOpenGLFunctions_4_6_Core::glEndConditionalRender ()
{
    d_3_0_Core->f.EndConditionalRender ();
}

inline void QOpenGLFunctions_4_6_Core::glBeginConditionalRender ( GLuint id, GLenum mode )
{
    d_3_0_Core->f.BeginConditionalRender ( id, mode );
}

inline void QOpenGLFunctions_4_6_Core::glClampColor ( GLenum target, GLenum clamp )
{
    d_3_0_Core->f.ClampColor ( target, clamp );
}

inline void QOpenGLFunctions_4_6_Core::glGetTransformFeedbackVarying ( GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name )
{
    d_3_0_Core->f.GetTransformFeedbackVarying ( program, index, bufSize, length, size, type, name );
}

inline void QOpenGLFunctions_4_6_Core::glTransformFeedbackVaryings ( GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode )
{
    d_3_0_Core->f.TransformFeedbackVaryings ( program, count, varyings, bufferMode );
}

inline void QOpenGLFunctions_4_6_Core::glBindBufferBase ( GLenum target, GLuint index, GLuint buffer )
{
    d_3_0_Core->f.BindBufferBase ( target, index, buffer );
}

inline void QOpenGLFunctions_4_6_Core::glBindBufferRange ( GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size )
{
    d_3_0_Core->f.BindBufferRange ( target, index, buffer, offset, size );
}

inline void QOpenGLFunctions_4_6_Core::glEndTransformFeedback ()
{
    d_3_0_Core->f.EndTransformFeedback ();
}

inline void QOpenGLFunctions_4_6_Core::glBeginTransformFeedback ( GLenum primitiveMode )
{
    d_3_0_Core->f.BeginTransformFeedback ( primitiveMode );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsEnabledi ( GLenum target, GLuint index )
{
    return d_3_0_Core->f.IsEnabledi ( target, index );
}

inline void QOpenGLFunctions_4_6_Core::glDisablei ( GLenum target, GLuint index )
{
    d_3_0_Core->f.Disablei ( target, index );
}

inline void QOpenGLFunctions_4_6_Core::glEnablei ( GLenum target, GLuint index )
{
    d_3_0_Core->f.Enablei ( target, index );
}

inline void QOpenGLFunctions_4_6_Core::glGetIntegeri_v ( GLenum target, GLuint index, GLint* data )
{
    d_3_0_Core->f.GetIntegeri_v ( target, index, data );
}

inline void QOpenGLFunctions_4_6_Core::glGetBooleani_v ( GLenum target, GLuint index, GLboolean* data )
{
    d_3_0_Core->f.GetBooleani_v ( target, index, data );
}

inline void QOpenGLFunctions_4_6_Core::glColorMaski ( GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a )
{
    d_3_0_Core->f.ColorMaski ( index, r, g, b, a );
}


// OpenGL 3.1 core functions
inline void QOpenGLFunctions_4_6_Core::glUniformBlockBinding ( GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding )
{
    d_3_1_Core->f.UniformBlockBinding ( program, uniformBlockIndex, uniformBlockBinding );
}

inline void QOpenGLFunctions_4_6_Core::glGetActiveUniformBlockName ( GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName )
{
    d_3_1_Core->f.GetActiveUniformBlockName ( program, uniformBlockIndex, bufSize, length, uniformBlockName );
}

inline void QOpenGLFunctions_4_6_Core::glGetActiveUniformBlockiv ( GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params )
{
    d_3_1_Core->f.GetActiveUniformBlockiv ( program, uniformBlockIndex, pname, params );
}

inline GLuint QOpenGLFunctions_4_6_Core::glGetUniformBlockIndex ( GLuint program, const GLchar* uniformBlockName )
{
    return d_3_1_Core->f.GetUniformBlockIndex ( program, uniformBlockName );
}

inline void QOpenGLFunctions_4_6_Core::glGetActiveUniformName ( GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName )
{
    d_3_1_Core->f.GetActiveUniformName ( program, uniformIndex, bufSize, length, uniformName );
}

inline void QOpenGLFunctions_4_6_Core::glGetActiveUniformsiv ( GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params )
{
    d_3_1_Core->f.GetActiveUniformsiv ( program, uniformCount, uniformIndices, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetUniformIndices ( GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices )
{
    d_3_1_Core->f.GetUniformIndices ( program, uniformCount, uniformNames, uniformIndices );
}

inline void QOpenGLFunctions_4_6_Core::glCopyBufferSubData ( GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size )
{
    d_3_1_Core->f.CopyBufferSubData ( readTarget, writeTarget, readOffset, writeOffset, size );
}

inline void QOpenGLFunctions_4_6_Core::glPrimitiveRestartIndex ( GLuint index )
{
    d_3_1_Core->f.PrimitiveRestartIndex ( index );
}

inline void QOpenGLFunctions_4_6_Core::glTexBuffer ( GLenum target, GLenum internalformat, GLuint buffer )
{
    d_3_1_Core->f.TexBuffer ( target, internalformat, buffer );
}

inline void QOpenGLFunctions_4_6_Core::glDrawElementsInstanced ( GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount )
{
    d_3_1_Core->f.DrawElementsInstanced ( mode, count, type, indices, instancecount );
}

inline void QOpenGLFunctions_4_6_Core::glDrawArraysInstanced ( GLenum mode, GLint first, GLsizei count, GLsizei instancecount )
{
    d_3_1_Core->f.DrawArraysInstanced ( mode, first, count, instancecount );
}


// OpenGL 3.2 core functions
inline void QOpenGLFunctions_4_6_Core::glSampleMaski ( GLuint maskNumber, GLbitfield mask )
{
    d_3_2_Core->f.SampleMaski ( maskNumber, mask );
}

inline void QOpenGLFunctions_4_6_Core::glGetMultisamplefv ( GLenum pname, GLuint index, GLfloat* val )
{
    d_3_2_Core->f.GetMultisamplefv ( pname, index, val );
}

inline void QOpenGLFunctions_4_6_Core::glTexImage3DMultisample ( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations )
{
    d_3_2_Core->f.TexImage3DMultisample ( target, samples, internalformat, width, height, depth, fixedsamplelocations );
}

inline void QOpenGLFunctions_4_6_Core::glTexImage2DMultisample ( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations )
{
    d_3_2_Core->f.TexImage2DMultisample ( target, samples, internalformat, width, height, fixedsamplelocations );
}

inline void QOpenGLFunctions_4_6_Core::glFramebufferTexture ( GLenum target, GLenum attachment, GLuint texture, GLint level )
{
    d_3_2_Core->f.FramebufferTexture ( target, attachment, texture, level );
}

inline void QOpenGLFunctions_4_6_Core::glGetBufferParameteri64v ( GLenum target, GLenum pname, GLint64* params )
{
    d_3_2_Core->f.GetBufferParameteri64v ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetInteger64i_v ( GLenum target, GLuint index, GLint64* data )
{
    d_3_2_Core->f.GetInteger64i_v ( target, index, data );
}

inline void QOpenGLFunctions_4_6_Core::glGetSynciv ( GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values )
{
    d_3_2_Core->f.GetSynciv ( sync, pname, bufSize, length, values );
}

inline void QOpenGLFunctions_4_6_Core::glGetInteger64v ( GLenum pname, GLint64* data )
{
    d_3_2_Core->f.GetInteger64v ( pname, data );
}

inline void QOpenGLFunctions_4_6_Core::glWaitSync ( GLsync sync, GLbitfield flags, GLuint64 timeout )
{
    d_3_2_Core->f.WaitSync ( sync, flags, timeout );
}

inline GLenum QOpenGLFunctions_4_6_Core::glClientWaitSync ( GLsync sync, GLbitfield flags, GLuint64 timeout )
{
    return d_3_2_Core->f.ClientWaitSync ( sync, flags, timeout );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteSync ( GLsync sync )
{
    d_3_2_Core->f.DeleteSync ( sync );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsSync ( GLsync sync )
{
    return d_3_2_Core->f.IsSync ( sync );
}

inline GLsync QOpenGLFunctions_4_6_Core::glFenceSync ( GLenum condition, GLbitfield flags )
{
    return d_3_2_Core->f.FenceSync ( condition, flags );
}

inline void QOpenGLFunctions_4_6_Core::glProvokingVertex ( GLenum mode )
{
    d_3_2_Core->f.ProvokingVertex ( mode );
}

inline void QOpenGLFunctions_4_6_Core::glMultiDrawElementsBaseVertex ( GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount, const GLint* basevertex )
{
    d_3_2_Core->f.MultiDrawElementsBaseVertex ( mode, count, type, indices, drawcount, basevertex );
}

inline void QOpenGLFunctions_4_6_Core::glDrawElementsInstancedBaseVertex ( GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex )
{
    d_3_2_Core->f.DrawElementsInstancedBaseVertex ( mode, count, type, indices, instancecount, basevertex );
}

inline void QOpenGLFunctions_4_6_Core::glDrawRangeElementsBaseVertex ( GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices, GLint basevertex )
{
    d_3_2_Core->f.DrawRangeElementsBaseVertex ( mode, start, end, count, type, indices, basevertex );
}

inline void QOpenGLFunctions_4_6_Core::glDrawElementsBaseVertex ( GLenum mode, GLsizei count, GLenum type, const void* indices, GLint basevertex )
{
    d_3_2_Core->f.DrawElementsBaseVertex ( mode, count, type, indices, basevertex );
}


// OpenGL 3.3 core functions
inline void QOpenGLFunctions_4_6_Core::glVertexAttribP4uiv ( GLuint index, GLenum type, GLboolean normalized, const GLuint* value )
{
    d_3_3_Core->f.VertexAttribP4uiv ( index, type, normalized, value );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribP4ui ( GLuint index, GLenum type, GLboolean normalized, GLuint value )
{
    d_3_3_Core->f.VertexAttribP4ui ( index, type, normalized, value );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribP3uiv ( GLuint index, GLenum type, GLboolean normalized, const GLuint* value )
{
    d_3_3_Core->f.VertexAttribP3uiv ( index, type, normalized, value );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribP3ui ( GLuint index, GLenum type, GLboolean normalized, GLuint value )
{
    d_3_3_Core->f.VertexAttribP3ui ( index, type, normalized, value );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribP2uiv ( GLuint index, GLenum type, GLboolean normalized, const GLuint* value )
{
    d_3_3_Core->f.VertexAttribP2uiv ( index, type, normalized, value );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribP2ui ( GLuint index, GLenum type, GLboolean normalized, GLuint value )
{
    d_3_3_Core->f.VertexAttribP2ui ( index, type, normalized, value );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribP1uiv ( GLuint index, GLenum type, GLboolean normalized, const GLuint* value )
{
    d_3_3_Core->f.VertexAttribP1uiv ( index, type, normalized, value );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribP1ui ( GLuint index, GLenum type, GLboolean normalized, GLuint value )
{
    d_3_3_Core->f.VertexAttribP1ui ( index, type, normalized, value );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribDivisor ( GLuint index, GLuint divisor )
{
    d_3_3_Core->f.VertexAttribDivisor ( index, divisor );
}

inline void QOpenGLFunctions_4_6_Core::glGetQueryObjectui64v ( GLuint id, GLenum pname, GLuint64* params )
{
    d_3_3_Core->f.GetQueryObjectui64v ( id, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetQueryObjecti64v ( GLuint id, GLenum pname, GLint64* params )
{
    d_3_3_Core->f.GetQueryObjecti64v ( id, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glQueryCounter ( GLuint id, GLenum target )
{
    d_3_3_Core->f.QueryCounter ( id, target );
}

inline void QOpenGLFunctions_4_6_Core::glGetSamplerParameterIuiv ( GLuint sampler, GLenum pname, GLuint* params )
{
    d_3_3_Core->f.GetSamplerParameterIuiv ( sampler, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetSamplerParameterfv ( GLuint sampler, GLenum pname, GLfloat* params )
{
    d_3_3_Core->f.GetSamplerParameterfv ( sampler, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetSamplerParameterIiv ( GLuint sampler, GLenum pname, GLint* params )
{
    d_3_3_Core->f.GetSamplerParameterIiv ( sampler, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetSamplerParameteriv ( GLuint sampler, GLenum pname, GLint* params )
{
    d_3_3_Core->f.GetSamplerParameteriv ( sampler, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glSamplerParameterIuiv ( GLuint sampler, GLenum pname, const GLuint* param )
{
    d_3_3_Core->f.SamplerParameterIuiv ( sampler, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glSamplerParameterIiv ( GLuint sampler, GLenum pname, const GLint* param )
{
    d_3_3_Core->f.SamplerParameterIiv ( sampler, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glSamplerParameterfv ( GLuint sampler, GLenum pname, const GLfloat* param )
{
    d_3_3_Core->f.SamplerParameterfv ( sampler, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glSamplerParameterf ( GLuint sampler, GLenum pname, GLfloat param )
{
    d_3_3_Core->f.SamplerParameterf ( sampler, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glSamplerParameteriv ( GLuint sampler, GLenum pname, const GLint* param )
{
    d_3_3_Core->f.SamplerParameteriv ( sampler, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glSamplerParameteri ( GLuint sampler, GLenum pname, GLint param )
{
    d_3_3_Core->f.SamplerParameteri ( sampler, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glBindSampler ( GLuint unit, GLuint sampler )
{
    d_3_3_Core->f.BindSampler ( unit, sampler );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsSampler ( GLuint sampler )
{
    return d_3_3_Core->f.IsSampler ( sampler );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteSamplers ( GLsizei count, const GLuint* samplers )
{
    d_3_3_Core->f.DeleteSamplers ( count, samplers );
}

inline void QOpenGLFunctions_4_6_Core::glGenSamplers ( GLsizei count, GLuint* samplers )
{
    d_3_3_Core->f.GenSamplers ( count, samplers );
}

inline GLint QOpenGLFunctions_4_6_Core::glGetFragDataIndex ( GLuint program, const GLchar* name )
{
    return d_3_3_Core->f.GetFragDataIndex ( program, name );
}

inline void QOpenGLFunctions_4_6_Core::glBindFragDataLocationIndexed ( GLuint program, GLuint colorNumber, GLuint index, const GLchar* name )
{
    d_3_3_Core->f.BindFragDataLocationIndexed ( program, colorNumber, index, name );
}


// OpenGL 4.0 core functions
inline void QOpenGLFunctions_4_6_Core::glGetQueryIndexediv ( GLenum target, GLuint index, GLenum pname, GLint* params )
{
    d_4_0_Core->f.GetQueryIndexediv ( target, index, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glEndQueryIndexed ( GLenum target, GLuint index )
{
    d_4_0_Core->f.EndQueryIndexed ( target, index );
}

inline void QOpenGLFunctions_4_6_Core::glBeginQueryIndexed ( GLenum target, GLuint index, GLuint id )
{
    d_4_0_Core->f.BeginQueryIndexed ( target, index, id );
}

inline void QOpenGLFunctions_4_6_Core::glDrawTransformFeedbackStream ( GLenum mode, GLuint id, GLuint stream )
{
    d_4_0_Core->f.DrawTransformFeedbackStream ( mode, id, stream );
}

inline void QOpenGLFunctions_4_6_Core::glDrawTransformFeedback ( GLenum mode, GLuint id )
{
    d_4_0_Core->f.DrawTransformFeedback ( mode, id );
}

inline void QOpenGLFunctions_4_6_Core::glResumeTransformFeedback ()
{
    d_4_0_Core->f.ResumeTransformFeedback ();
}

inline void QOpenGLFunctions_4_6_Core::glPauseTransformFeedback ()
{
    d_4_0_Core->f.PauseTransformFeedback ();
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsTransformFeedback ( GLuint id )
{
    return d_4_0_Core->f.IsTransformFeedback ( id );
}

inline void QOpenGLFunctions_4_6_Core::glGenTransformFeedbacks ( GLsizei n, GLuint* ids )
{
    d_4_0_Core->f.GenTransformFeedbacks ( n, ids );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteTransformFeedbacks ( GLsizei n, const GLuint* ids )
{
    d_4_0_Core->f.DeleteTransformFeedbacks ( n, ids );
}

inline void QOpenGLFunctions_4_6_Core::glBindTransformFeedback ( GLenum target, GLuint id )
{
    d_4_0_Core->f.BindTransformFeedback ( target, id );
}

inline void QOpenGLFunctions_4_6_Core::glPatchParameterfv ( GLenum pname, const GLfloat* values )
{
    d_4_0_Core->f.PatchParameterfv ( pname, values );
}

inline void QOpenGLFunctions_4_6_Core::glPatchParameteri ( GLenum pname, GLint value )
{
    d_4_0_Core->f.PatchParameteri ( pname, value );
}

inline void QOpenGLFunctions_4_6_Core::glGetProgramStageiv ( GLuint program, GLenum shadertype, GLenum pname, GLint* values )
{
    d_4_0_Core->f.GetProgramStageiv ( program, shadertype, pname, values );
}

inline void QOpenGLFunctions_4_6_Core::glGetUniformSubroutineuiv ( GLenum shadertype, GLint location, GLuint* params )
{
    d_4_0_Core->f.GetUniformSubroutineuiv ( shadertype, location, params );
}

inline void QOpenGLFunctions_4_6_Core::glUniformSubroutinesuiv ( GLenum shadertype, GLsizei count, const GLuint* indices )
{
    d_4_0_Core->f.UniformSubroutinesuiv ( shadertype, count, indices );
}

inline void QOpenGLFunctions_4_6_Core::glGetActiveSubroutineName ( GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name )
{
    d_4_0_Core->f.GetActiveSubroutineName ( program, shadertype, index, bufsize, length, name );
}

inline void QOpenGLFunctions_4_6_Core::glGetActiveSubroutineUniformName ( GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name )
{
    d_4_0_Core->f.GetActiveSubroutineUniformName ( program, shadertype, index, bufsize, length, name );
}

inline void QOpenGLFunctions_4_6_Core::glGetActiveSubroutineUniformiv ( GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values )
{
    d_4_0_Core->f.GetActiveSubroutineUniformiv ( program, shadertype, index, pname, values );
}

inline GLuint QOpenGLFunctions_4_6_Core::glGetSubroutineIndex ( GLuint program, GLenum shadertype, const GLchar* name )
{
    return d_4_0_Core->f.GetSubroutineIndex ( program, shadertype, name );
}

inline GLint QOpenGLFunctions_4_6_Core::glGetSubroutineUniformLocation ( GLuint program, GLenum shadertype, const GLchar* name )
{
    return d_4_0_Core->f.GetSubroutineUniformLocation ( program, shadertype, name );
}

inline void QOpenGLFunctions_4_6_Core::glGetUniformdv ( GLuint program, GLint location, GLdouble* params )
{
    d_4_0_Core->f.GetUniformdv ( program, location, params );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix4x3dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_0_Core->f.UniformMatrix4x3dv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix4x2dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_0_Core->f.UniformMatrix4x2dv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix3x4dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_0_Core->f.UniformMatrix3x4dv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix3x2dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_0_Core->f.UniformMatrix3x2dv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix2x4dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_0_Core->f.UniformMatrix2x4dv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix2x3dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_0_Core->f.UniformMatrix2x3dv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix4dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_0_Core->f.UniformMatrix4dv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix3dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_0_Core->f.UniformMatrix3dv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniformMatrix2dv ( GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_0_Core->f.UniformMatrix2dv ( location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform4dv ( GLint location, GLsizei count, const GLdouble* value )
{
    d_4_0_Core->f.Uniform4dv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform3dv ( GLint location, GLsizei count, const GLdouble* value )
{
    d_4_0_Core->f.Uniform3dv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform2dv ( GLint location, GLsizei count, const GLdouble* value )
{
    d_4_0_Core->f.Uniform2dv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform1dv ( GLint location, GLsizei count, const GLdouble* value )
{
    d_4_0_Core->f.Uniform1dv ( location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glUniform4d ( GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w )
{
    d_4_0_Core->f.Uniform4d ( location, x, y, z, w );
}

inline void QOpenGLFunctions_4_6_Core::glUniform3d ( GLint location, GLdouble x, GLdouble y, GLdouble z )
{
    d_4_0_Core->f.Uniform3d ( location, x, y, z );
}

inline void QOpenGLFunctions_4_6_Core::glUniform2d ( GLint location, GLdouble x, GLdouble y )
{
    d_4_0_Core->f.Uniform2d ( location, x, y );
}

inline void QOpenGLFunctions_4_6_Core::glUniform1d ( GLint location, GLdouble x )
{
    d_4_0_Core->f.Uniform1d ( location, x );
}

inline void QOpenGLFunctions_4_6_Core::glDrawElementsIndirect ( GLenum mode, GLenum type, const void* indirect )
{
    d_4_0_Core->f.DrawElementsIndirect ( mode, type, indirect );
}

inline void QOpenGLFunctions_4_6_Core::glDrawArraysIndirect ( GLenum mode, const void* indirect )
{
    d_4_0_Core->f.DrawArraysIndirect ( mode, indirect );
}

inline void QOpenGLFunctions_4_6_Core::glBlendFuncSeparatei ( GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha )
{
    d_4_0_Core->f.BlendFuncSeparatei ( buf, srcRGB, dstRGB, srcAlpha, dstAlpha );
}

inline void QOpenGLFunctions_4_6_Core::glBlendFunci ( GLuint buf, GLenum src, GLenum dst )
{
    d_4_0_Core->f.BlendFunci ( buf, src, dst );
}

inline void QOpenGLFunctions_4_6_Core::glBlendEquationSeparatei ( GLuint buf, GLenum modeRGB, GLenum modeAlpha )
{
    d_4_0_Core->f.BlendEquationSeparatei ( buf, modeRGB, modeAlpha );
}

inline void QOpenGLFunctions_4_6_Core::glBlendEquationi ( GLuint buf, GLenum mode )
{
    d_4_0_Core->f.BlendEquationi ( buf, mode );
}

inline void QOpenGLFunctions_4_6_Core::glMinSampleShading ( GLfloat value )
{
    d_4_0_Core->f.MinSampleShading ( value );
}


// OpenGL 4.1 core functions
inline void QOpenGLFunctions_4_6_Core::glGetDoublei_v ( GLenum target, GLuint index, GLdouble* data )
{
    d_4_1_Core->f.GetDoublei_v ( target, index, data );
}

inline void QOpenGLFunctions_4_6_Core::glGetFloati_v ( GLenum target, GLuint index, GLfloat* data )
{
    d_4_1_Core->f.GetFloati_v ( target, index, data );
}

inline void QOpenGLFunctions_4_6_Core::glDepthRangeIndexed ( GLuint index, GLdouble n, GLdouble f )
{
    d_4_1_Core->f.DepthRangeIndexed ( index, n, f );
}

inline void QOpenGLFunctions_4_6_Core::glDepthRangeArrayv ( GLuint first, GLsizei count, const GLdouble* v )
{
    d_4_1_Core->f.DepthRangeArrayv ( first, count, v );
}

inline void QOpenGLFunctions_4_6_Core::glScissorIndexedv ( GLuint index, const GLint* v )
{
    d_4_1_Core->f.ScissorIndexedv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glScissorIndexed ( GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height )
{
    d_4_1_Core->f.ScissorIndexed ( index, left, bottom, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glScissorArrayv ( GLuint first, GLsizei count, const GLint* v )
{
    d_4_1_Core->f.ScissorArrayv ( first, count, v );
}

inline void QOpenGLFunctions_4_6_Core::glViewportIndexedfv ( GLuint index, const GLfloat* v )
{
    d_4_1_Core->f.ViewportIndexedfv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glViewportIndexedf ( GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h )
{
    d_4_1_Core->f.ViewportIndexedf ( index, x, y, w, h );
}

inline void QOpenGLFunctions_4_6_Core::glViewportArrayv ( GLuint first, GLsizei count, const GLfloat* v )
{
    d_4_1_Core->f.ViewportArrayv ( first, count, v );
}

inline void QOpenGLFunctions_4_6_Core::glGetVertexAttribLdv ( GLuint index, GLenum pname, GLdouble* params )
{
    d_4_1_Core->f.GetVertexAttribLdv ( index, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribLPointer ( GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer )
{
    d_4_1_Core->f.VertexAttribLPointer ( index, size, type, stride, pointer );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribL4dv ( GLuint index, const GLdouble* v )
{
    d_4_1_Core->f.VertexAttribL4dv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribL3dv ( GLuint index, const GLdouble* v )
{
    d_4_1_Core->f.VertexAttribL3dv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribL2dv ( GLuint index, const GLdouble* v )
{
    d_4_1_Core->f.VertexAttribL2dv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribL1dv ( GLuint index, const GLdouble* v )
{
    d_4_1_Core->f.VertexAttribL1dv ( index, v );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribL4d ( GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w )
{
    d_4_1_Core->f.VertexAttribL4d ( index, x, y, z, w );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribL3d ( GLuint index, GLdouble x, GLdouble y, GLdouble z )
{
    d_4_1_Core->f.VertexAttribL3d ( index, x, y, z );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribL2d ( GLuint index, GLdouble x, GLdouble y )
{
    d_4_1_Core->f.VertexAttribL2d ( index, x, y );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribL1d ( GLuint index, GLdouble x )
{
    d_4_1_Core->f.VertexAttribL1d ( index, x );
}

inline void QOpenGLFunctions_4_6_Core::glGetProgramPipelineInfoLog ( GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog )
{
    d_4_1_Core->f.GetProgramPipelineInfoLog ( pipeline, bufSize, length, infoLog );
}

inline void QOpenGLFunctions_4_6_Core::glValidateProgramPipeline ( GLuint pipeline )
{
    d_4_1_Core->f.ValidateProgramPipeline ( pipeline );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix4x3dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniformMatrix4x3dv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix3x4dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniformMatrix3x4dv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix4x2dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniformMatrix4x2dv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix2x4dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniformMatrix2x4dv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix3x2dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniformMatrix3x2dv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix2x3dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniformMatrix2x3dv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix4x3fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniformMatrix4x3fv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix3x4fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniformMatrix3x4fv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix4x2fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniformMatrix4x2fv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix2x4fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniformMatrix2x4fv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix3x2fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniformMatrix3x2fv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix2x3fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniformMatrix2x3fv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix4dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniformMatrix4dv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix3dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniformMatrix3dv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix2dv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniformMatrix2dv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix4fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniformMatrix4fv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix3fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniformMatrix3fv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniformMatrix2fv ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniformMatrix2fv ( program, location, count, transpose, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform4uiv ( GLuint program, GLint location, GLsizei count, const GLuint* value )
{
    d_4_1_Core->f.ProgramUniform4uiv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform4ui ( GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3 )
{
    d_4_1_Core->f.ProgramUniform4ui ( program, location, v0, v1, v2, v3 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform4dv ( GLuint program, GLint location, GLsizei count, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniform4dv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform4d ( GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3 )
{
    d_4_1_Core->f.ProgramUniform4d ( program, location, v0, v1, v2, v3 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform4fv ( GLuint program, GLint location, GLsizei count, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniform4fv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform4f ( GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 )
{
    d_4_1_Core->f.ProgramUniform4f ( program, location, v0, v1, v2, v3 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform4iv ( GLuint program, GLint location, GLsizei count, const GLint* value )
{
    d_4_1_Core->f.ProgramUniform4iv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform4i ( GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3 )
{
    d_4_1_Core->f.ProgramUniform4i ( program, location, v0, v1, v2, v3 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform3uiv ( GLuint program, GLint location, GLsizei count, const GLuint* value )
{
    d_4_1_Core->f.ProgramUniform3uiv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform3ui ( GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2 )
{
    d_4_1_Core->f.ProgramUniform3ui ( program, location, v0, v1, v2 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform3dv ( GLuint program, GLint location, GLsizei count, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniform3dv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform3d ( GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2 )
{
    d_4_1_Core->f.ProgramUniform3d ( program, location, v0, v1, v2 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform3fv ( GLuint program, GLint location, GLsizei count, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniform3fv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform3f ( GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2 )
{
    d_4_1_Core->f.ProgramUniform3f ( program, location, v0, v1, v2 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform3iv ( GLuint program, GLint location, GLsizei count, const GLint* value )
{
    d_4_1_Core->f.ProgramUniform3iv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform3i ( GLuint program, GLint location, GLint v0, GLint v1, GLint v2 )
{
    d_4_1_Core->f.ProgramUniform3i ( program, location, v0, v1, v2 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform2uiv ( GLuint program, GLint location, GLsizei count, const GLuint* value )
{
    d_4_1_Core->f.ProgramUniform2uiv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform2ui ( GLuint program, GLint location, GLuint v0, GLuint v1 )
{
    d_4_1_Core->f.ProgramUniform2ui ( program, location, v0, v1 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform2dv ( GLuint program, GLint location, GLsizei count, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniform2dv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform2d ( GLuint program, GLint location, GLdouble v0, GLdouble v1 )
{
    d_4_1_Core->f.ProgramUniform2d ( program, location, v0, v1 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform2fv ( GLuint program, GLint location, GLsizei count, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniform2fv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform2f ( GLuint program, GLint location, GLfloat v0, GLfloat v1 )
{
    d_4_1_Core->f.ProgramUniform2f ( program, location, v0, v1 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform2iv ( GLuint program, GLint location, GLsizei count, const GLint* value )
{
    d_4_1_Core->f.ProgramUniform2iv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform2i ( GLuint program, GLint location, GLint v0, GLint v1 )
{
    d_4_1_Core->f.ProgramUniform2i ( program, location, v0, v1 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform1uiv ( GLuint program, GLint location, GLsizei count, const GLuint* value )
{
    d_4_1_Core->f.ProgramUniform1uiv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform1ui ( GLuint program, GLint location, GLuint v0 )
{
    d_4_1_Core->f.ProgramUniform1ui ( program, location, v0 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform1dv ( GLuint program, GLint location, GLsizei count, const GLdouble* value )
{
    d_4_1_Core->f.ProgramUniform1dv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform1d ( GLuint program, GLint location, GLdouble v0 )
{
    d_4_1_Core->f.ProgramUniform1d ( program, location, v0 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform1fv ( GLuint program, GLint location, GLsizei count, const GLfloat* value )
{
    d_4_1_Core->f.ProgramUniform1fv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform1f ( GLuint program, GLint location, GLfloat v0 )
{
    d_4_1_Core->f.ProgramUniform1f ( program, location, v0 );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform1iv ( GLuint program, GLint location, GLsizei count, const GLint* value )
{
    d_4_1_Core->f.ProgramUniform1iv ( program, location, count, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramUniform1i ( GLuint program, GLint location, GLint v0 )
{
    d_4_1_Core->f.ProgramUniform1i ( program, location, v0 );
}

inline void QOpenGLFunctions_4_6_Core::glGetProgramPipelineiv ( GLuint pipeline, GLenum pname, GLint* params )
{
    d_4_1_Core->f.GetProgramPipelineiv ( pipeline, pname, params );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glIsProgramPipeline ( GLuint pipeline )
{
    return d_4_1_Core->f.IsProgramPipeline ( pipeline );
}

inline void QOpenGLFunctions_4_6_Core::glGenProgramPipelines ( GLsizei n, GLuint* pipelines )
{
    d_4_1_Core->f.GenProgramPipelines ( n, pipelines );
}

inline void QOpenGLFunctions_4_6_Core::glDeleteProgramPipelines ( GLsizei n, const GLuint* pipelines )
{
    d_4_1_Core->f.DeleteProgramPipelines ( n, pipelines );
}

inline void QOpenGLFunctions_4_6_Core::glBindProgramPipeline ( GLuint pipeline )
{
    d_4_1_Core->f.BindProgramPipeline ( pipeline );
}

inline GLuint QOpenGLFunctions_4_6_Core::glCreateShaderProgramv ( GLenum type, GLsizei count, const GLchar* const* strings )
{
    return d_4_1_Core->f.CreateShaderProgramv ( type, count, strings );
}

inline void QOpenGLFunctions_4_6_Core::glActiveShaderProgram ( GLuint pipeline, GLuint program )
{
    d_4_1_Core->f.ActiveShaderProgram ( pipeline, program );
}

inline void QOpenGLFunctions_4_6_Core::glUseProgramStages ( GLuint pipeline, GLbitfield stages, GLuint program )
{
    d_4_1_Core->f.UseProgramStages ( pipeline, stages, program );
}

inline void QOpenGLFunctions_4_6_Core::glProgramParameteri ( GLuint program, GLenum pname, GLint value )
{
    d_4_1_Core->f.ProgramParameteri ( program, pname, value );
}

inline void QOpenGLFunctions_4_6_Core::glProgramBinary ( GLuint program, GLenum binaryFormat, const void* binary, GLsizei length )
{
    d_4_1_Core->f.ProgramBinary ( program, binaryFormat, binary, length );
}

inline void QOpenGLFunctions_4_6_Core::glGetProgramBinary ( GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary )
{
    d_4_1_Core->f.GetProgramBinary ( program, bufSize, length, binaryFormat, binary );
}

inline void QOpenGLFunctions_4_6_Core::glClearDepthf ( GLfloat dd )
{
    d_4_1_Core->f.ClearDepthf ( dd );
}

inline void QOpenGLFunctions_4_6_Core::glDepthRangef ( GLfloat n, GLfloat f )
{
    d_4_1_Core->f.DepthRangef ( n, f );
}

inline void QOpenGLFunctions_4_6_Core::glGetShaderPrecisionFormat ( GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision )
{
    d_4_1_Core->f.GetShaderPrecisionFormat ( shadertype, precisiontype, range, precision );
}

inline void QOpenGLFunctions_4_6_Core::glShaderBinary ( GLsizei count, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length )
{
    d_4_1_Core->f.ShaderBinary ( count, shaders, binaryformat, binary, length );
}

inline void QOpenGLFunctions_4_6_Core::glReleaseShaderCompiler ()
{
    d_4_1_Core->f.ReleaseShaderCompiler ();
}


// OpenGL 4.2 core functions
inline void QOpenGLFunctions_4_6_Core::glDrawTransformFeedbackStreamInstanced ( GLenum mode, GLuint id, GLuint stream, GLsizei instancecount )
{
    d_4_2_Core->f.DrawTransformFeedbackStreamInstanced ( mode, id, stream, instancecount );
}

inline void QOpenGLFunctions_4_6_Core::glDrawTransformFeedbackInstanced ( GLenum mode, GLuint id, GLsizei instancecount )
{
    d_4_2_Core->f.DrawTransformFeedbackInstanced ( mode, id, instancecount );
}

inline void QOpenGLFunctions_4_6_Core::glTexStorage3D ( GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth )
{
    d_4_2_Core->f.TexStorage3D ( target, levels, internalformat, width, height, depth );
}

inline void QOpenGLFunctions_4_6_Core::glTexStorage2D ( GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height )
{
    d_4_2_Core->f.TexStorage2D ( target, levels, internalformat, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glTexStorage1D ( GLenum target, GLsizei levels, GLenum internalformat, GLsizei width )
{
    d_4_2_Core->f.TexStorage1D ( target, levels, internalformat, width );
}

inline void QOpenGLFunctions_4_6_Core::glMemoryBarrier ( GLbitfield barriers )
{
    d_4_2_Core->f.MemoryBarrier ( barriers );
}

inline void QOpenGLFunctions_4_6_Core::glBindImageTexture ( GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format )
{
    d_4_2_Core->f.BindImageTexture ( unit, texture, level, layered, layer, access, format );
}

inline void QOpenGLFunctions_4_6_Core::glGetActiveAtomicCounterBufferiv ( GLuint program, GLuint bufferIndex, GLenum pname, GLint* params )
{
    d_4_2_Core->f.GetActiveAtomicCounterBufferiv ( program, bufferIndex, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetInternalformativ ( GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params )
{
    d_4_2_Core->f.GetInternalformativ ( target, internalformat, pname, bufSize, params );
}

inline void QOpenGLFunctions_4_6_Core::glDrawElementsInstancedBaseVertexBaseInstance ( GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance )
{
    d_4_2_Core->f.DrawElementsInstancedBaseVertexBaseInstance ( mode, count, type, indices, instancecount, basevertex, baseinstance );
}

inline void QOpenGLFunctions_4_6_Core::glDrawElementsInstancedBaseInstance ( GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLuint baseinstance )
{
    d_4_2_Core->f.DrawElementsInstancedBaseInstance ( mode, count, type, indices, instancecount, baseinstance );
}

inline void QOpenGLFunctions_4_6_Core::glDrawArraysInstancedBaseInstance ( GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance )
{
    d_4_2_Core->f.DrawArraysInstancedBaseInstance ( mode, first, count, instancecount, baseinstance );
}


// OpenGL 4.3 core functions
inline void QOpenGLFunctions_4_6_Core::glGetObjectPtrLabel ( const void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label )
{
    d_4_3_Core->f.GetObjectPtrLabel ( ptr, bufSize, length, label );
}

inline void QOpenGLFunctions_4_6_Core::glObjectPtrLabel ( const void* ptr, GLsizei length, const GLchar* label )
{
    d_4_3_Core->f.ObjectPtrLabel ( ptr, length, label );
}

inline void QOpenGLFunctions_4_6_Core::glGetObjectLabel ( GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label )
{
    d_4_3_Core->f.GetObjectLabel ( identifier, name, bufSize, length, label );
}

inline void QOpenGLFunctions_4_6_Core::glObjectLabel ( GLenum identifier, GLuint name, GLsizei length, const GLchar* label )
{
    d_4_3_Core->f.ObjectLabel ( identifier, name, length, label );
}

inline void QOpenGLFunctions_4_6_Core::glPopDebugGroup ()
{
    d_4_3_Core->f.PopDebugGroup ();
}

inline void QOpenGLFunctions_4_6_Core::glPushDebugGroup ( GLenum source, GLuint id, GLsizei length, const GLchar* message )
{
    d_4_3_Core->f.PushDebugGroup ( source, id, length, message );
}

inline GLuint QOpenGLFunctions_4_6_Core::glGetDebugMessageLog ( GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog )
{
    return d_4_3_Core->f.GetDebugMessageLog ( count, bufSize, sources, types, ids, severities, lengths, messageLog );
}

inline void QOpenGLFunctions_4_6_Core::glDebugMessageCallback ( GLDEBUGPROC callback, const void* userParam )
{
    d_4_3_Core->f.DebugMessageCallback ( callback, userParam );
}

inline void QOpenGLFunctions_4_6_Core::glDebugMessageInsert ( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf )
{
    d_4_3_Core->f.DebugMessageInsert ( source, type, id, severity, length, buf );
}

inline void QOpenGLFunctions_4_6_Core::glDebugMessageControl ( GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled )
{
    d_4_3_Core->f.DebugMessageControl ( source, type, severity, count, ids, enabled );
}

inline void QOpenGLFunctions_4_6_Core::glVertexBindingDivisor ( GLuint bindingindex, GLuint divisor )
{
    d_4_3_Core->f.VertexBindingDivisor ( bindingindex, divisor );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribBinding ( GLuint attribindex, GLuint bindingindex )
{
    d_4_3_Core->f.VertexAttribBinding ( attribindex, bindingindex );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribLFormat ( GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset )
{
    d_4_3_Core->f.VertexAttribLFormat ( attribindex, size, type, relativeoffset );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribIFormat ( GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset )
{
    d_4_3_Core->f.VertexAttribIFormat ( attribindex, size, type, relativeoffset );
}

inline void QOpenGLFunctions_4_6_Core::glVertexAttribFormat ( GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset )
{
    d_4_3_Core->f.VertexAttribFormat ( attribindex, size, type, normalized, relativeoffset );
}

inline void QOpenGLFunctions_4_6_Core::glBindVertexBuffer ( GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride )
{
    d_4_3_Core->f.BindVertexBuffer ( bindingindex, buffer, offset, stride );
}

inline void QOpenGLFunctions_4_6_Core::glTextureView ( GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers )
{
    d_4_3_Core->f.TextureView ( texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers );
}

inline void QOpenGLFunctions_4_6_Core::glTexStorage3DMultisample ( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations )
{
    d_4_3_Core->f.TexStorage3DMultisample ( target, samples, internalformat, width, height, depth, fixedsamplelocations );
}

inline void QOpenGLFunctions_4_6_Core::glTexStorage2DMultisample ( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations )
{
    d_4_3_Core->f.TexStorage2DMultisample ( target, samples, internalformat, width, height, fixedsamplelocations );
}

inline void QOpenGLFunctions_4_6_Core::glTexBufferRange ( GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size )
{
    d_4_3_Core->f.TexBufferRange ( target, internalformat, buffer, offset, size );
}

inline void QOpenGLFunctions_4_6_Core::glShaderStorageBlockBinding ( GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding )
{
    d_4_3_Core->f.ShaderStorageBlockBinding ( program, storageBlockIndex, storageBlockBinding );
}

inline GLint QOpenGLFunctions_4_6_Core::glGetProgramResourceLocationIndex ( GLuint program, GLenum programInterface, const GLchar* name )
{
    return d_4_3_Core->f.GetProgramResourceLocationIndex ( program, programInterface, name );
}

inline GLint QOpenGLFunctions_4_6_Core::glGetProgramResourceLocation ( GLuint program, GLenum programInterface, const GLchar* name )
{
    return d_4_3_Core->f.GetProgramResourceLocation ( program, programInterface, name );
}

inline void QOpenGLFunctions_4_6_Core::glGetProgramResourceiv ( GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params )
{
    d_4_3_Core->f.GetProgramResourceiv ( program, programInterface, index, propCount, props, bufSize, length, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetProgramResourceName ( GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name )
{
    d_4_3_Core->f.GetProgramResourceName ( program, programInterface, index, bufSize, length, name );
}

inline GLuint QOpenGLFunctions_4_6_Core::glGetProgramResourceIndex ( GLuint program, GLenum programInterface, const GLchar* name )
{
    return d_4_3_Core->f.GetProgramResourceIndex ( program, programInterface, name );
}

inline void QOpenGLFunctions_4_6_Core::glGetProgramInterfaceiv ( GLuint program, GLenum programInterface, GLenum pname, GLint* params )
{
    d_4_3_Core->f.GetProgramInterfaceiv ( program, programInterface, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glMultiDrawElementsIndirect ( GLenum mode, GLenum type, const void* indirect, GLsizei drawcount, GLsizei stride )
{
    d_4_3_Core->f.MultiDrawElementsIndirect ( mode, type, indirect, drawcount, stride );
}

inline void QOpenGLFunctions_4_6_Core::glMultiDrawArraysIndirect ( GLenum mode, const void* indirect, GLsizei drawcount, GLsizei stride )
{
    d_4_3_Core->f.MultiDrawArraysIndirect ( mode, indirect, drawcount, stride );
}

inline void QOpenGLFunctions_4_6_Core::glInvalidateSubFramebuffer ( GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height )
{
    d_4_3_Core->f.InvalidateSubFramebuffer ( target, numAttachments, attachments, x, y, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glInvalidateFramebuffer ( GLenum target, GLsizei numAttachments, const GLenum* attachments )
{
    d_4_3_Core->f.InvalidateFramebuffer ( target, numAttachments, attachments );
}

inline void QOpenGLFunctions_4_6_Core::glInvalidateBufferData ( GLuint buffer )
{
    d_4_3_Core->f.InvalidateBufferData ( buffer );
}

inline void QOpenGLFunctions_4_6_Core::glInvalidateBufferSubData ( GLuint buffer, GLintptr offset, GLsizeiptr length )
{
    d_4_3_Core->f.InvalidateBufferSubData ( buffer, offset, length );
}

inline void QOpenGLFunctions_4_6_Core::glInvalidateTexImage ( GLuint texture, GLint level )
{
    d_4_3_Core->f.InvalidateTexImage ( texture, level );
}

inline void QOpenGLFunctions_4_6_Core::glInvalidateTexSubImage ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth )
{
    d_4_3_Core->f.InvalidateTexSubImage ( texture, level, xoffset, yoffset, zoffset, width, height, depth );
}

inline void QOpenGLFunctions_4_6_Core::glGetInternalformati64v ( GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64* params )
{
    d_4_3_Core->f.GetInternalformati64v ( target, internalformat, pname, bufSize, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetFramebufferParameteriv ( GLenum target, GLenum pname, GLint* params )
{
    d_4_3_Core->f.GetFramebufferParameteriv ( target, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glFramebufferParameteri ( GLenum target, GLenum pname, GLint param )
{
    d_4_3_Core->f.FramebufferParameteri ( target, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glCopyImageSubData ( GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth )
{
    d_4_3_Core->f.CopyImageSubData ( srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth );
}

inline void QOpenGLFunctions_4_6_Core::glDispatchComputeIndirect ( GLintptr indirect )
{
    d_4_3_Core->f.DispatchComputeIndirect ( indirect );
}

inline void QOpenGLFunctions_4_6_Core::glDispatchCompute ( GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z )
{
    d_4_3_Core->f.DispatchCompute ( num_groups_x, num_groups_y, num_groups_z );
}

inline void QOpenGLFunctions_4_6_Core::glClearBufferSubData ( GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data )
{
    d_4_3_Core->f.ClearBufferSubData ( target, internalformat, offset, size, format, type, data );
}

inline void QOpenGLFunctions_4_6_Core::glClearBufferData ( GLenum target, GLenum internalformat, GLenum format, GLenum type, const void* data )
{
    d_4_3_Core->f.ClearBufferData ( target, internalformat, format, type, data );
}


// OpenGL 4.4 core functions
inline void QOpenGLFunctions_4_6_Core::glBindVertexBuffers ( GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides )
{
    d_4_4_Core->f.BindVertexBuffers ( first, count, buffers, offsets, strides );
}

inline void QOpenGLFunctions_4_6_Core::glBindImageTextures ( GLuint first, GLsizei count, const GLuint* textures )
{
    d_4_4_Core->f.BindImageTextures ( first, count, textures );
}

inline void QOpenGLFunctions_4_6_Core::glBindSamplers ( GLuint first, GLsizei count, const GLuint* samplers )
{
    d_4_4_Core->f.BindSamplers ( first, count, samplers );
}

inline void QOpenGLFunctions_4_6_Core::glBindTextures ( GLuint first, GLsizei count, const GLuint* textures )
{
    d_4_4_Core->f.BindTextures ( first, count, textures );
}

inline void QOpenGLFunctions_4_6_Core::glBindBuffersRange ( GLenum target, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizeiptr* sizes )
{
    d_4_4_Core->f.BindBuffersRange ( target, first, count, buffers, offsets, sizes );
}

inline void QOpenGLFunctions_4_6_Core::glBindBuffersBase ( GLenum target, GLuint first, GLsizei count, const GLuint* buffers )
{
    d_4_4_Core->f.BindBuffersBase ( target, first, count, buffers );
}

inline void QOpenGLFunctions_4_6_Core::glClearTexSubImage ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data )
{
    d_4_4_Core->f.ClearTexSubImage ( texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data );
}

inline void QOpenGLFunctions_4_6_Core::glClearTexImage ( GLuint texture, GLint level, GLenum format, GLenum type, const void* data )
{
    d_4_4_Core->f.ClearTexImage ( texture, level, format, type, data );
}

inline void QOpenGLFunctions_4_6_Core::glBufferStorage ( GLenum target, GLsizeiptr size, const void* data, GLbitfield flags )
{
    d_4_4_Core->f.BufferStorage ( target, size, data, flags );
}


// OpenGL 4.5 core functions
inline void QOpenGLFunctions_4_6_Core::glTextureBarrier ()
{
    d_4_5_Core->f.TextureBarrier ();
}

inline void QOpenGLFunctions_4_6_Core::glReadnPixels ( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data )
{
    d_4_5_Core->f.ReadnPixels ( x, y, width, height, format, type, bufSize, data );
}

inline void QOpenGLFunctions_4_6_Core::glGetnUniformuiv ( GLuint program, GLint location, GLsizei bufSize, GLuint* params )
{
    d_4_5_Core->f.GetnUniformuiv ( program, location, bufSize, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetnUniformiv ( GLuint program, GLint location, GLsizei bufSize, GLint* params )
{
    d_4_5_Core->f.GetnUniformiv ( program, location, bufSize, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetnUniformfv ( GLuint program, GLint location, GLsizei bufSize, GLfloat* params )
{
    d_4_5_Core->f.GetnUniformfv ( program, location, bufSize, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetnUniformdv ( GLuint program, GLint location, GLsizei bufSize, GLdouble* params )
{
    d_4_5_Core->f.GetnUniformdv ( program, location, bufSize, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetnTexImage ( GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels )
{
    d_4_5_Core->f.GetnTexImage ( target, level, format, type, bufSize, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glGetnCompressedTexImage ( GLenum target, GLint lod, GLsizei bufSize, void* pixels )
{
    d_4_5_Core->f.GetnCompressedTexImage ( target, lod, bufSize, pixels );
}

inline GLenum QOpenGLFunctions_4_6_Core::glGetGraphicsResetStatus ()
{
    return d_4_5_Core->f.GetGraphicsResetStatus ();
}

inline void QOpenGLFunctions_4_6_Core::glGetCompressedTextureSubImage ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels )
{
    d_4_5_Core->f.GetCompressedTextureSubImage ( texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glGetTextureSubImage ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels )
{
    d_4_5_Core->f.GetTextureSubImage ( texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glMemoryBarrierByRegion ( GLbitfield barriers )
{
    d_4_5_Core->f.MemoryBarrierByRegion ( barriers );
}

inline void QOpenGLFunctions_4_6_Core::glCreateQueries ( GLenum target, GLsizei n, GLuint* ids )
{
    d_4_5_Core->f.CreateQueries ( target, n, ids );
}

inline void QOpenGLFunctions_4_6_Core::glCreateProgramPipelines ( GLsizei n, GLuint* pipelines )
{
    d_4_5_Core->f.CreateProgramPipelines ( n, pipelines );
}

inline void QOpenGLFunctions_4_6_Core::glCreateSamplers ( GLsizei n, GLuint* samplers )
{
    d_4_5_Core->f.CreateSamplers ( n, samplers );
}

inline void QOpenGLFunctions_4_6_Core::glGetVertexArrayIndexed64iv ( GLuint vaobj, GLuint index, GLenum pname, GLint64* param )
{
    d_4_5_Core->f.GetVertexArrayIndexed64iv ( vaobj, index, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glGetVertexArrayIndexediv ( GLuint vaobj, GLuint index, GLenum pname, GLint* param )
{
    d_4_5_Core->f.GetVertexArrayIndexediv ( vaobj, index, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glGetVertexArrayiv ( GLuint vaobj, GLenum pname, GLint* param )
{
    d_4_5_Core->f.GetVertexArrayiv ( vaobj, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glVertexArrayBindingDivisor ( GLuint vaobj, GLuint bindingindex, GLuint divisor )
{
    d_4_5_Core->f.VertexArrayBindingDivisor ( vaobj, bindingindex, divisor );
}

inline void QOpenGLFunctions_4_6_Core::glVertexArrayAttribLFormat ( GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset )
{
    d_4_5_Core->f.VertexArrayAttribLFormat ( vaobj, attribindex, size, type, relativeoffset );
}

inline void QOpenGLFunctions_4_6_Core::glVertexArrayAttribIFormat ( GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset )
{
    d_4_5_Core->f.VertexArrayAttribIFormat ( vaobj, attribindex, size, type, relativeoffset );
}

inline void QOpenGLFunctions_4_6_Core::glVertexArrayAttribFormat ( GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset )
{
    d_4_5_Core->f.VertexArrayAttribFormat ( vaobj, attribindex, size, type, normalized, relativeoffset );
}

inline void QOpenGLFunctions_4_6_Core::glVertexArrayAttribBinding ( GLuint vaobj, GLuint attribindex, GLuint bindingindex )
{
    d_4_5_Core->f.VertexArrayAttribBinding ( vaobj, attribindex, bindingindex );
}

inline void QOpenGLFunctions_4_6_Core::glVertexArrayVertexBuffers ( GLuint vaobj, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides )
{
    d_4_5_Core->f.VertexArrayVertexBuffers ( vaobj, first, count, buffers, offsets, strides );
}

inline void QOpenGLFunctions_4_6_Core::glVertexArrayVertexBuffer ( GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride )
{
    d_4_5_Core->f.VertexArrayVertexBuffer ( vaobj, bindingindex, buffer, offset, stride );
}

inline void QOpenGLFunctions_4_6_Core::glVertexArrayElementBuffer ( GLuint vaobj, GLuint buffer )
{
    d_4_5_Core->f.VertexArrayElementBuffer ( vaobj, buffer );
}

inline void QOpenGLFunctions_4_6_Core::glEnableVertexArrayAttrib ( GLuint vaobj, GLuint index )
{
    d_4_5_Core->f.EnableVertexArrayAttrib ( vaobj, index );
}

inline void QOpenGLFunctions_4_6_Core::glDisableVertexArrayAttrib ( GLuint vaobj, GLuint index )
{
    d_4_5_Core->f.DisableVertexArrayAttrib ( vaobj, index );
}

inline void QOpenGLFunctions_4_6_Core::glCreateVertexArrays ( GLsizei n, GLuint* arrays )
{
    d_4_5_Core->f.CreateVertexArrays ( n, arrays );
}

inline void QOpenGLFunctions_4_6_Core::glGetTextureParameteriv ( GLuint texture, GLenum pname, GLint* params )
{
    d_4_5_Core->f.GetTextureParameteriv ( texture, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetTextureParameterIuiv ( GLuint texture, GLenum pname, GLuint* params )
{
    d_4_5_Core->f.GetTextureParameterIuiv ( texture, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetTextureParameterIiv ( GLuint texture, GLenum pname, GLint* params )
{
    d_4_5_Core->f.GetTextureParameterIiv ( texture, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetTextureParameterfv ( GLuint texture, GLenum pname, GLfloat* params )
{
    d_4_5_Core->f.GetTextureParameterfv ( texture, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetTextureLevelParameteriv ( GLuint texture, GLint level, GLenum pname, GLint* params )
{
    d_4_5_Core->f.GetTextureLevelParameteriv ( texture, level, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetTextureLevelParameterfv ( GLuint texture, GLint level, GLenum pname, GLfloat* params )
{
    d_4_5_Core->f.GetTextureLevelParameterfv ( texture, level, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetCompressedTextureImage ( GLuint texture, GLint level, GLsizei bufSize, void* pixels )
{
    d_4_5_Core->f.GetCompressedTextureImage ( texture, level, bufSize, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glGetTextureImage ( GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels )
{
    d_4_5_Core->f.GetTextureImage ( texture, level, format, type, bufSize, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glBindTextureUnit ( GLuint unit, GLuint texture )
{
    d_4_5_Core->f.BindTextureUnit ( unit, texture );
}

inline void QOpenGLFunctions_4_6_Core::glGenerateTextureMipmap ( GLuint texture )
{
    d_4_5_Core->f.GenerateTextureMipmap ( texture );
}

inline void QOpenGLFunctions_4_6_Core::glTextureParameteriv ( GLuint texture, GLenum pname, const GLint* param )
{
    d_4_5_Core->f.TextureParameteriv ( texture, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glTextureParameterIuiv ( GLuint texture, GLenum pname, const GLuint* params )
{
    d_4_5_Core->f.TextureParameterIuiv ( texture, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glTextureParameterIiv ( GLuint texture, GLenum pname, const GLint* params )
{
    d_4_5_Core->f.TextureParameterIiv ( texture, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glTextureParameteri ( GLuint texture, GLenum pname, GLint param )
{
    d_4_5_Core->f.TextureParameteri ( texture, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glTextureParameterfv ( GLuint texture, GLenum pname, const GLfloat* param )
{
    d_4_5_Core->f.TextureParameterfv ( texture, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glTextureParameterf ( GLuint texture, GLenum pname, GLfloat param )
{
    d_4_5_Core->f.TextureParameterf ( texture, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glCopyTextureSubImage3D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height )
{
    d_4_5_Core->f.CopyTextureSubImage3D ( texture, level, xoffset, yoffset, zoffset, x, y, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glCopyTextureSubImage2D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height )
{
    d_4_5_Core->f.CopyTextureSubImage2D ( texture, level, xoffset, yoffset, x, y, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glCopyTextureSubImage1D ( GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width )
{
    d_4_5_Core->f.CopyTextureSubImage1D ( texture, level, xoffset, x, y, width );
}

inline void QOpenGLFunctions_4_6_Core::glCompressedTextureSubImage3D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data )
{
    d_4_5_Core->f.CompressedTextureSubImage3D ( texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data );
}

inline void QOpenGLFunctions_4_6_Core::glCompressedTextureSubImage2D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data )
{
    d_4_5_Core->f.CompressedTextureSubImage2D ( texture, level, xoffset, yoffset, width, height, format, imageSize, data );
}

inline void QOpenGLFunctions_4_6_Core::glCompressedTextureSubImage1D ( GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data )
{
    d_4_5_Core->f.CompressedTextureSubImage1D ( texture, level, xoffset, width, format, imageSize, data );
}

inline void QOpenGLFunctions_4_6_Core::glTextureSubImage3D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels )
{
    d_4_5_Core->f.TextureSubImage3D ( texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glTextureSubImage2D ( GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels )
{
    d_4_5_Core->f.TextureSubImage2D ( texture, level, xoffset, yoffset, width, height, format, type, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glTextureSubImage1D ( GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels )
{
    d_4_5_Core->f.TextureSubImage1D ( texture, level, xoffset, width, format, type, pixels );
}

inline void QOpenGLFunctions_4_6_Core::glTextureStorage3DMultisample ( GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations )
{
    d_4_5_Core->f.TextureStorage3DMultisample ( texture, samples, internalformat, width, height, depth, fixedsamplelocations );
}

inline void QOpenGLFunctions_4_6_Core::glTextureStorage2DMultisample ( GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations )
{
    d_4_5_Core->f.TextureStorage2DMultisample ( texture, samples, internalformat, width, height, fixedsamplelocations );
}

inline void QOpenGLFunctions_4_6_Core::glTextureStorage3D ( GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth )
{
    d_4_5_Core->f.TextureStorage3D ( texture, levels, internalformat, width, height, depth );
}

inline void QOpenGLFunctions_4_6_Core::glTextureStorage2D ( GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height )
{
    d_4_5_Core->f.TextureStorage2D ( texture, levels, internalformat, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glTextureStorage1D ( GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width )
{
    d_4_5_Core->f.TextureStorage1D ( texture, levels, internalformat, width );
}

inline void QOpenGLFunctions_4_6_Core::glTextureBufferRange ( GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizei size )
{
    d_4_5_Core->f.TextureBufferRange ( texture, internalformat, buffer, offset, size );
}

inline void QOpenGLFunctions_4_6_Core::glTextureBuffer ( GLuint texture, GLenum internalformat, GLuint buffer )
{
    d_4_5_Core->f.TextureBuffer ( texture, internalformat, buffer );
}

inline void QOpenGLFunctions_4_6_Core::glCreateTextures ( GLenum target, GLsizei n, GLuint* textures )
{
    d_4_5_Core->f.CreateTextures ( target, n, textures );
}

inline void QOpenGLFunctions_4_6_Core::glGetNamedRenderbufferParameteriv ( GLuint renderbuffer, GLenum pname, GLint* params )
{
    d_4_5_Core->f.GetNamedRenderbufferParameteriv ( renderbuffer, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glNamedRenderbufferStorageMultisample ( GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height )
{
    d_4_5_Core->f.NamedRenderbufferStorageMultisample ( renderbuffer, samples, internalformat, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glNamedRenderbufferStorage ( GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height )
{
    d_4_5_Core->f.NamedRenderbufferStorage ( renderbuffer, internalformat, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glCreateRenderbuffers ( GLsizei n, GLuint* renderbuffers )
{
    d_4_5_Core->f.CreateRenderbuffers ( n, renderbuffers );
}

inline void QOpenGLFunctions_4_6_Core::glGetNamedFramebufferAttachmentParameteriv ( GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params )
{
    d_4_5_Core->f.GetNamedFramebufferAttachmentParameteriv ( framebuffer, attachment, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetNamedFramebufferParameteriv ( GLuint framebuffer, GLenum pname, GLint* param )
{
    d_4_5_Core->f.GetNamedFramebufferParameteriv ( framebuffer, pname, param );
}

inline GLenum QOpenGLFunctions_4_6_Core::glCheckNamedFramebufferStatus ( GLuint framebuffer, GLenum target )
{
    return d_4_5_Core->f.CheckNamedFramebufferStatus ( framebuffer, target );
}

inline void QOpenGLFunctions_4_6_Core::glBlitNamedFramebuffer ( GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter )
{
    d_4_5_Core->f.BlitNamedFramebuffer ( readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter );
}

inline void QOpenGLFunctions_4_6_Core::glClearNamedFramebufferfi ( GLuint framebuffer, GLenum buffer, GLfloat depth, GLint stencil )
{
    d_4_5_Core->f.ClearNamedFramebufferfi ( framebuffer, buffer, depth, stencil );
}

inline void QOpenGLFunctions_4_6_Core::glClearNamedFramebufferfv ( GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat* value )
{
    d_4_5_Core->f.ClearNamedFramebufferfv ( framebuffer, buffer, drawbuffer, value );
}

inline void QOpenGLFunctions_4_6_Core::glClearNamedFramebufferuiv ( GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value )
{
    d_4_5_Core->f.ClearNamedFramebufferuiv ( framebuffer, buffer, drawbuffer, value );
}

inline void QOpenGLFunctions_4_6_Core::glClearNamedFramebufferiv ( GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value )
{
    d_4_5_Core->f.ClearNamedFramebufferiv ( framebuffer, buffer, drawbuffer, value );
}

inline void QOpenGLFunctions_4_6_Core::glInvalidateNamedFramebufferSubData ( GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height )
{
    d_4_5_Core->f.InvalidateNamedFramebufferSubData ( framebuffer, numAttachments, attachments, x, y, width, height );
}

inline void QOpenGLFunctions_4_6_Core::glInvalidateNamedFramebufferData ( GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments )
{
    d_4_5_Core->f.InvalidateNamedFramebufferData ( framebuffer, numAttachments, attachments );
}

inline void QOpenGLFunctions_4_6_Core::glNamedFramebufferReadBuffer ( GLuint framebuffer, GLenum src )
{
    d_4_5_Core->f.NamedFramebufferReadBuffer ( framebuffer, src );
}

inline void QOpenGLFunctions_4_6_Core::glNamedFramebufferDrawBuffers ( GLuint framebuffer, GLsizei n, const GLenum* bufs )
{
    d_4_5_Core->f.NamedFramebufferDrawBuffers ( framebuffer, n, bufs );
}

inline void QOpenGLFunctions_4_6_Core::glNamedFramebufferDrawBuffer ( GLuint framebuffer, GLenum buf )
{
    d_4_5_Core->f.NamedFramebufferDrawBuffer ( framebuffer, buf );
}

inline void QOpenGLFunctions_4_6_Core::glNamedFramebufferTextureLayer ( GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer )
{
    d_4_5_Core->f.NamedFramebufferTextureLayer ( framebuffer, attachment, texture, level, layer );
}

inline void QOpenGLFunctions_4_6_Core::glNamedFramebufferTexture ( GLuint framebuffer, GLenum attachment, GLuint texture, GLint level )
{
    d_4_5_Core->f.NamedFramebufferTexture ( framebuffer, attachment, texture, level );
}

inline void QOpenGLFunctions_4_6_Core::glNamedFramebufferParameteri ( GLuint framebuffer, GLenum pname, GLint param )
{
    d_4_5_Core->f.NamedFramebufferParameteri ( framebuffer, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glNamedFramebufferRenderbuffer ( GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer )
{
    d_4_5_Core->f.NamedFramebufferRenderbuffer ( framebuffer, attachment, renderbuffertarget, renderbuffer );
}

inline void QOpenGLFunctions_4_6_Core::glCreateFramebuffers ( GLsizei n, GLuint* framebuffers )
{
    d_4_5_Core->f.CreateFramebuffers ( n, framebuffers );
}

inline void QOpenGLFunctions_4_6_Core::glGetNamedBufferSubData ( GLuint buffer, GLintptr offset, GLsizei size, void* data )
{
    d_4_5_Core->f.GetNamedBufferSubData ( buffer, offset, size, data );
}

inline void QOpenGLFunctions_4_6_Core::glGetNamedBufferPointerv ( GLuint buffer, GLenum pname, void** params )
{
    d_4_5_Core->f.GetNamedBufferPointerv ( buffer, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetNamedBufferParameteri64v ( GLuint buffer, GLenum pname, GLint64* params )
{
    d_4_5_Core->f.GetNamedBufferParameteri64v ( buffer, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glGetNamedBufferParameteriv ( GLuint buffer, GLenum pname, GLint* params )
{
    d_4_5_Core->f.GetNamedBufferParameteriv ( buffer, pname, params );
}

inline void QOpenGLFunctions_4_6_Core::glFlushMappedNamedBufferRange ( GLuint buffer, GLintptr offset, GLsizei length )
{
    d_4_5_Core->f.FlushMappedNamedBufferRange ( buffer, offset, length );
}

inline GLboolean QOpenGLFunctions_4_6_Core::glUnmapNamedBuffer ( GLuint buffer )
{
    return d_4_5_Core->f.UnmapNamedBuffer ( buffer );
}

inline void* QOpenGLFunctions_4_6_Core::glMapNamedBufferRange ( GLuint buffer, GLintptr offset, GLsizei length, GLbitfield access )
{
    return d_4_5_Core->f.MapNamedBufferRange ( buffer, offset, length, access );
}

inline void* QOpenGLFunctions_4_6_Core::glMapNamedBuffer ( GLuint buffer, GLenum access )
{
    return d_4_5_Core->f.MapNamedBuffer ( buffer, access );
}

inline void QOpenGLFunctions_4_6_Core::glClearNamedBufferSubData ( GLuint buffer, GLenum internalformat, GLintptr offset, GLsizei size, GLenum format, GLenum type, const void* data )
{
    d_4_5_Core->f.ClearNamedBufferSubData ( buffer, internalformat, offset, size, format, type, data );
}

inline void QOpenGLFunctions_4_6_Core::glClearNamedBufferData ( GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data )
{
    d_4_5_Core->f.ClearNamedBufferData ( buffer, internalformat, format, type, data );
}

inline void QOpenGLFunctions_4_6_Core::glCopyNamedBufferSubData ( GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizei size )
{
    d_4_5_Core->f.CopyNamedBufferSubData ( readBuffer, writeBuffer, readOffset, writeOffset, size );
}

inline void QOpenGLFunctions_4_6_Core::glNamedBufferSubData ( GLuint buffer, GLintptr offset, GLsizei size, const void* data )
{
    d_4_5_Core->f.NamedBufferSubData ( buffer, offset, size, data );
}

inline void QOpenGLFunctions_4_6_Core::glNamedBufferData ( GLuint buffer, GLsizei size, const void* data, GLenum usage )
{
    d_4_5_Core->f.NamedBufferData ( buffer, size, data, usage );
}

inline void QOpenGLFunctions_4_6_Core::glNamedBufferStorage ( GLuint buffer, GLsizei size, const void* data, GLbitfield flags )
{
    d_4_5_Core->f.NamedBufferStorage ( buffer, size, data, flags );
}

inline void QOpenGLFunctions_4_6_Core::glCreateBuffers ( GLsizei n, GLuint* buffers )
{
    d_4_5_Core->f.CreateBuffers ( n, buffers );
}

inline void QOpenGLFunctions_4_6_Core::glGetTransformFeedbacki64_v ( GLuint xfb, GLenum pname, GLuint index, GLint64* param )
{
    d_4_5_Core->f.GetTransformFeedbacki64_v ( xfb, pname, index, param );
}

inline void QOpenGLFunctions_4_6_Core::glGetTransformFeedbacki_v ( GLuint xfb, GLenum pname, GLuint index, GLint* param )
{
    d_4_5_Core->f.GetTransformFeedbacki_v ( xfb, pname, index, param );
}

inline void QOpenGLFunctions_4_6_Core::glGetTransformFeedbackiv ( GLuint xfb, GLenum pname, GLint* param )
{
    d_4_5_Core->f.GetTransformFeedbackiv ( xfb, pname, param );
}

inline void QOpenGLFunctions_4_6_Core::glTransformFeedbackBufferRange ( GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizei size )
{
    d_4_5_Core->f.TransformFeedbackBufferRange ( xfb, index, buffer, offset, size );
}

inline void QOpenGLFunctions_4_6_Core::glTransformFeedbackBufferBase ( GLuint xfb, GLuint index, GLuint buffer )
{
    d_4_5_Core->f.TransformFeedbackBufferBase ( xfb, index, buffer );
}

inline void QOpenGLFunctions_4_6_Core::glCreateTransformFeedbacks ( GLsizei n, GLuint* ids )
{
    d_4_5_Core->f.CreateTransformFeedbacks ( n, ids );
}

inline void QOpenGLFunctions_4_6_Core::glClipControl ( GLenum origin, GLenum depth )
{
    d_4_5_Core->f.ClipControl ( origin, depth );
}

QT_END_NAMESPACE

#ifdef Q_OS_WIN
#pragma pop_macro("MemoryBarrier")
#endif

#endif // QT_NO_OPENGL && !QT_CONFIG(opengles2)

#endif // !__QOPENGLFUNCTIONS_4_6_CORE_H__
