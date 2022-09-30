#include "Material.h"
#include "Utils.h"
#include <QFile>
#include <QHash>

namespace jcqt
{
	void saveStringList ( QFile* f, const QByteArrayList& lines )
	{
		if ( nullptr == f )
		{
			qWarning ( "File pointer is null. Cannot save string list to file.\nExiting...\n" );
			exit ( EXIT_FAILURE );
		}

		quint32 sz = ( quint32 ) lines.size ();

		f->write ( ( const char* ) &sz, sizeof ( quint32 ) );

		foreach ( const QByteArray& l, lines )
		{
			sz = static_cast< quint32 >( l.size () );
			f->write ( ( const char* ) &sz, sizeof ( quint32 ) );
			f->write ( l.constData (), sz + 1 );
		}		
	}

	void loadStringList ( QFile* f, QByteArrayList& lines )
	{
		quint32 sz = 0;
		f->read ( ( char* ) &sz, sizeof ( quint32 ) );
		lines.resize ( sz );

		QByteArray inBytes;
		for ( auto& l : lines )
		{
			quint32 sz = 0;
			f->read ( ( char* ) &sz, sizeof ( quint32 ) );
			l = f->read ( sz + 1 );
		}
	}

	void saveMaterials ( const char* filename, const QList<MaterialDescription>& materials, const QByteArrayList& files )
	{
		QFile f ( filename );

		if ( !f.open ( QIODeviceBase::WriteOnly ) )
		{
			qWarning ( "Failed to open %s.\nCannot save materials.\nExiting...\n" );
			exit ( EXIT_FAILURE );
		}

		quint32 sz = static_cast< quint32 >( materials.size () );
		f.write ( ( const char* ) &sz, sizeof ( quint32 ) );
		f.write ( ( const char* ) materials.constData (), sizeof ( MaterialDescription ) * sz );
		saveStringList ( &f, files );
		f.close ();
	}

	void loadMaterials ( const char* filename, QList<MaterialDescription>& materials, QByteArrayList& files )
	{
		QFile f ( filename );

		if ( !f.open ( QIODeviceBase::ReadOnly ) )
		{
			qWarning ( "Failed to open %s.\nCannot load materials.\nExiting...\n" );
			exit ( EXIT_FAILURE );
		}

		quint32 sz;
		f.read ( ( char* ) &sz, sizeof ( quint32 ) );
		materials.resize ( sz );
		f.read ( ( char* ) materials.data (), sizeof ( MaterialDescription ) * sz );
		loadStringList ( &f, files );
		f.close ();
	}

	// TODO
	void mergeMaterialLists ( const QList<QList<MaterialDescription>*>& oldMaterials, const QList<QByteArrayList*>& oldTextures, QList<MaterialDescription>& allMaterials, QByteArrayList& newTextures )
	{
		// map texture names to indices in newTexturesList (calculated as we fill the newTexturesList
		QHash<QByteArray, qint32> newTextureNames;
		// direct MaterialDescription usage as a key is impossible, so we use its index in the allMaterials array
		QHash<qint32, qint32> materialToTextureList;

		// create combined material list [no hashing of materials, just straightforward merging of all lists]
		qint32 midx = 0;
		for ( const QList<MaterialDescription>* ml : oldMaterials )
		{
			for ( const MaterialDescription& m : *ml )
			{
				allMaterials.push_back ( m );
				materialToTextureList [ allMaterials.size () - 1 ] = midx;
			}

			midx++;
		}

		// create one combined texture list
		for ( const QByteArrayList* tl : oldTextures )
		{
			for ( const QByteArray& file : *tl )
			{
				newTextureNames [ file ] = addUnique ( newTextures, file ); // addUnique() is in SceneConverter/MaterialConv.inl
			}
		}

		// Lambda to replace textureID by a new "version" (from global list)
		auto replaceTexture = [&materialToTextureList, &oldTextures, &newTextureNames] ( qint32 m, uint64_t* textureID )
		{
			if ( *textureID < INVALID_TEXTURE )
			{
				auto listIdx = materialToTextureList [ m ];
				auto texList = oldTextures [ listIdx ];
				const auto& texFile = ( *texList ) [ *textureID ];
				*textureID = ( uint64_t ) ( newTextureNames [ texFile ] );
			}
		};

		for ( qsizetype i = 0; i < allMaterials.size (); i++ )
		{
			auto& m = allMaterials [ i ];
			replaceTexture ( i, &m.ambientOcclusionMap_ );
			replaceTexture ( i, &m.emissiveMap_ );
			replaceTexture ( i, &m.normalMap_ );
			replaceTexture ( i, &m.albedoMap_ );
			replaceTexture ( i, &m.metallicRoughnessMap_ );
		}
	}

}
