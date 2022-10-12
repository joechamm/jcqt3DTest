#include <QGuiApplication>

#include "ShadowMapWindow.h"

int main ( int argc, char** argv )
{
	QGuiApplication app ( argc, argv );

	QSurfaceFormat format;
	format.setMajorVersion ( 4 );
	format.setMinorVersion ( 6 );
	format.setProfile ( QSurfaceFormat::CoreProfile );
#ifndef NDEBUG
	format.setOption ( QSurfaceFormat::DebugContext, true );
#else 
	format.setOption ( QSurfaceFormat::DebugContext, false );
#endif
	format.setSwapBehavior ( QSurfaceFormat::DoubleBuffer );
	format.setRenderableType ( QSurfaceFormat::OpenGL );
	format.setDepthBufferSize ( 24 );
	format.setSwapInterval ( 1 );
	format.setSamples ( 4 );

	QSurfaceFormat::setDefaultFormat ( format );

	ShadowMapWindow window;
	window.setFormat ( format );
	window.resize ( 1280, 720 );
	window.show ();

	return app.exec ();
}
