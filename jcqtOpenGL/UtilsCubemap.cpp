#include "UtilsCubemap.h"
#include <QPixmap>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::ivec2;

namespace jcqt
{
	static vec3 faceCoordsToXYZ ( qint32 i, qint32 j, qint32 faceID, qint32 faceSize )
	{
		const float A = 2.0f * static_cast< float >( i ) / faceSize;
		const float B = 2.0f * static_cast< float >( j ) / faceSize;

		if ( faceID == 0 ) return vec3 ( -1.0f, A - 1.0f, B - 1.0f );
		if ( faceID == 1 ) return vec3 ( A - 1.0f, -1.0f, 1.0f - B );
		if ( faceID == 2 ) return vec3 ( 1.0f, A - 1.0f, 1.0f - B );
		if ( faceID == 3 ) return vec3 ( 1.0f - A, 1.0f, 1.0f - B );
		if ( faceID == 4 ) return vec3 ( B - 1.0f, A - 1.0f, 1.0f );
		if ( faceID == 5 ) return vec3 ( 1.0f - B, A - 1.0f, -1.0f );

		return vec3 ();
	}

	Bitmap JCQTOPENGL_EXPORT convertEquirectangularMapToVerticalCross ( const Bitmap& b )
	{
		if ( b.type_ != eBitmapType::eBitmapType_2D ) return Bitmap ();

		const qint32 faceSize = b.w_ / 4;

		const qint32 w = faceSize * 3;
		const qint32 h = faceSize * 4;

		Bitmap result ( w, h, b.comp_, b.fmt_ );

		const ivec2 kFaceOffsets [] =
		{
			ivec2 ( faceSize, faceSize * 3 ),
			ivec2 ( 0, faceSize ),
			ivec2 ( faceSize, faceSize ),
			ivec2 ( faceSize * 2, faceSize ),
			ivec2 ( faceSize, 0 ),
			ivec2 ( faceSize, faceSize * 2 )
		};

		const qint32 clampW = b.w_ - 1;
		const qint32 clampH = b.h_ - 1;

		for ( qint32 face = 0; face != 6; face++ )
		{
			for ( qint32 i = 0; i != faceSize; i++ )
			{
				for ( qint32 j = 0; j != faceSize; j++ )
				{
					const vec3 P = faceCoordsToXYZ ( i, j, face, faceSize );
					const float R = hypot ( P.x, P.y );
					const float theta = atan2 ( P.y, P.x );
					const float phi = atan2 ( P.z, R );
					// float point source coordinates
					const float Uf = static_cast< float >( 2.0f * faceSize * ( theta + glm::pi<float> () ) / glm::pi<float> () );
					const float Vf = static_cast< float >( 2.0f * faceSize * ( glm::pi<float> () / 2.0f - phi ) / glm::pi<float> () );
					// 4-samples for bilinear interpolation
					const qint32 U1 = glm::clamp ( qint32 ( glm::floor ( Uf ) ), 0, clampW );
					const qint32 V1 = glm::clamp ( qint32 ( glm::floor ( Vf ) ), 0, clampH );
					const qint32 U2 = glm::clamp ( U1 + 1, 0, clampW );
					const qint32 V2 = glm::clamp ( V1 + 1, 0, clampH );
					// fractional part
					const float s = Uf - U1;
					const float t = Vf - V1;
					// fetch 4-samples
					const vec4 A = b.getPixel ( U1, V1 );
					const vec4 B = b.getPixel ( U2, V1 );
					const vec4 C = b.getPixel ( U1, V2 );
					const vec4 D = b.getPixel ( U2, V2 );
					// bilinear interpolation
					const vec4 color = A * ( 1 - s ) * ( 1 - t ) + B * ( s ) * ( 1 - t ) + C * ( 1 - s ) * t + D * ( s ) * ( t );
					result.setPixel ( i + kFaceOffsets [ face ].x, j + kFaceOffsets [ face ].y, color );
				}
			}
		}

		return result;
	}

	Bitmap JCQTOPENGL_EXPORT convertVerticalCrossToCubeMapFaces ( const Bitmap& b )
	{
		const qint32 faceWidth = b.w_ / 3;
		const qint32 faceHeight = b.h_ / 4;

		Bitmap cubemap ( faceWidth, faceHeight, 6, b.comp_, b.fmt_ );
		cubemap.type_ = eBitmapType::eBitmapType_CUBE;

		const quint8* src = b.data_.constData ();
		quint8* dst = cubemap.data_.data ();

		/*
			------
			| +Y |
	 ----------------
	 | -X | -Z | +X |
	 ----------------
			| -Y |
			------
			| +Z |
			------
	*/


		const qint32 pixelSize = cubemap.comp_ * Bitmap::getBytesPerComponent ( cubemap.fmt_ );

		for ( qint32 face = 0; face != 6; ++face )
		{
			for ( qint32 j = 0; j != faceHeight; ++j )
			{
				for ( qint32 i = 0; i != faceWidth; ++i )
				{
					qint32 x = 0;
					qint32 y = 0;

					switch ( face )
					{
					case 0: // GL_TEXTURE_CUBE_MAP_POSITION_X
						x = i;
						y = faceHeight + j;
						break;
					case 1: // GL_TEXTURE_CUBE_MAP_NEGATIVE_X
						x = 2 * faceWidth + i;
						y = 1 * faceHeight + j;
						break;
					case 2: // GL_TEXTURE_CUBE_MAP_POSITIVE_Y
						x = 2 * faceWidth - ( i + 1 );
						y = 1 * faceHeight - ( j + 1 );
						break;
					case 3: // GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
						x = 2 * faceWidth - ( i + 1 );
						y = 3 * faceHeight - ( j + 1 );
						break;
					case 4: // GL_TEXTURE_CUBE_MAP_POSITIVE_Z
						x = 2 * faceWidth - ( i + 1 );
						y = b.h_ - ( j + 1 );
						break;
					case 5: // GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
						x = faceWidth + i;
						y = faceHeight + j;
						break;
					default:
						break;
					}

					memcpy ( dst, src + ( y * b.w_ + x ) * pixelSize, pixelSize );

					dst += pixelSize;
				}
			}
		}

		return cubemap;
	}

	Bitmap JCQTOPENGL_EXPORT convertQImageToBitmap ( const QImage& img )
	{
		const qint32 w = img.width ();
		const qint32 h = img.height ();
		const qint32 d = img.depth ();
		qint32 comp = 0;

		QImage::Format fmt = img.format ();
		eBitmapFormat bfmt = eBitmapFormat::eBitmapFormat_UNSIGNED_BYTE;

		switch ( fmt )
		{
		case QImage::Format_Invalid:
			break;
		case QImage::Format_Mono:
			comp = 1;
			break;
		case QImage::Format_MonoLSB:
			comp = 1;
			break;
		case QImage::Format_Indexed8:
			comp = 1;
			break;
		case QImage::Format_RGB32:
			comp = 3;
			break;
		case QImage::Format_ARGB32:
			comp = 4;
			break;
		case QImage::Format_ARGB32_Premultiplied:
			comp = 4;
			break;
		case QImage::Format_RGB16:
			comp = 3;
			break;
		case QImage::Format_ARGB8565_Premultiplied:
			comp = 4;
			break;
		case QImage::Format_RGB666:
			comp = 3;
			break;
		case QImage::Format_ARGB6666_Premultiplied:
			comp = 4;
			break;
		case QImage::Format_RGB555:
			comp = 3;
			break;
		case QImage::Format_ARGB8555_Premultiplied:
			comp = 4;
			break;
		case QImage::Format_RGB888:
			comp = 3;
			break;
		case QImage::Format_RGB444:
			comp = 3;
			break;
		case QImage::Format_ARGB4444_Premultiplied:
			comp = 4;
			break;
		case QImage::Format_RGBX8888:
			comp = 4;
			break;
		case QImage::Format_RGBA8888:
			comp = 4;
			break;
		case QImage::Format_RGBA8888_Premultiplied:
			comp = 4;
			break;
		case QImage::Format_BGR30:
			comp = 3;
			break;
		case QImage::Format_A2BGR30_Premultiplied:
			comp = 4;
			break;
		case QImage::Format_RGB30:
			comp = 3;
			break;
		case QImage::Format_A2RGB30_Premultiplied:
			comp = 4;
			break;
		case QImage::Format_Alpha8:
			comp = 1;
			break;
		case QImage::Format_Grayscale8:
			comp = 1;
			break;
		case QImage::Format_RGBX64:
			comp = 4;
			break;
		case QImage::Format_RGBA64:
			comp = 4;
			break;
		case QImage::Format_RGBA64_Premultiplied:
			comp = 4;
			break;
		case QImage::Format_Grayscale16:
			comp = 1;
			break;
		case QImage::Format_BGR888:
			comp = 3;
			break;
		case QImage::Format_RGBX16FPx4:
			bfmt = eBitmapFormat::eBitmapFormat_FLOAT;
			comp = 4;
			break;
		case QImage::Format_RGBA16FPx4:
			bfmt = eBitmapFormat::eBitmapFormat_FLOAT;
			comp = 4;
			break;
		case QImage::Format_RGBA16FPx4_Premultiplied:
			bfmt = eBitmapFormat::eBitmapFormat_FLOAT;
			comp = 4;
			break;
		case QImage::Format_RGBX32FPx4:
			bfmt = eBitmapFormat::eBitmapFormat_FLOAT;
			comp = 4;
			break;
		case QImage::Format_RGBA32FPx4:
			comp = 4;
			bfmt = eBitmapFormat::eBitmapFormat_FLOAT;
			break;
		case QImage::Format_RGBA32FPx4_Premultiplied:
			comp = 4;
			bfmt = eBitmapFormat::eBitmapFormat_FLOAT;
			break;
		case QImage::NImageFormats:
			break;
		default:
			break;
		}


		Bitmap result ( w, h, comp, bfmt, img.constBits () );

		return result;
	}

	QImage JCQTOPENGL_EXPORT convertBitmapToQImage ( const Bitmap& b )
	{
		if ( b.type_ != eBitmapType::eBitmapType_2D ) return QImage ();

		const qint32 w = b.w_;
		const qint32 h = b.h_;
		const qint32 comp = b.comp_;
		QImage::Format fmt;
		if ( b.fmt_ == eBitmapFormat::eBitmapFormat_FLOAT )
		{
			fmt = QImage::Format_RGBA32FPx4;
		}
		else
		{
			fmt = QImage::Format_ARGB32;
		}

		QImage image ( w, h, fmt );
		for ( qint32 row = 0; row < h; ++row )
		{
			QRgb* line = reinterpret_cast< QRgb* >( image.scanLine ( row ) );
			for ( qint32 col = 0; col < w; ++col )
			{
				vec4 color = b.getPixel ( col, row );
				QRgb& rgb = line [ col ];
				rgb = qRgba ( ( int ) color.r * 255.0f, ( int ) color.g * 255.0f, ( int ) color.b * 255.0f, ( int ) color.a * 255.0f );
			}
		}

		return image;
	}
}
