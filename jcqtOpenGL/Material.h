/*****************************************************************//**
 * \file   Material.h
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
 * \date   September 2022
 *********************************************************************/
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "jcqtopengl_global.h"

#include <QList>
#include <QByteArrayList>
#include <glm/glm.hpp>

using glm::mat4;
using glm::vec4;

namespace jcqt
{
	enum eMaterialFlags
	{
		eMaterialFlags_CastShadow = 0x1,
		eMaterialFlags_ReceiveShadow = 0x2,
		eMaterialFlags_Transparent = 0x4,
	};

	constexpr const quint64 INVALID_TEXTURE = 0xFFFFFFFF;

	/**
	*	@struct						MaterialDescription
	*	@brief						The material description contains both the numeric values that define the lighting properties of the material and the set of texture indices for use in Vulkan or OpenGL. Since OpenGL texture handles are an opaque 64-bit handle, we use that type rather than a 32-bit integer. For empty textures a special guard value is used with all bits set to 1.
	*	@var emissiveColor_			for light emitting materials
	*	@var albedoColor_			ambient material color
	*	@var roughness_				roughness factor can use x or both x and y components for anisotropic roughness
	*	@var transparencyFactor_	for use with alpha-blended materials
	*	@var alphaTest_				threshold for using simple-punch through transparency rendering
	*	@var flags_					placeholder for differentiating different types of material properties
	*	@var ambientOcclusionMap_	ambient occlusion texture handle
	*	@var emissiveMap_			emissive texture handle
	*	@var albedoMap_				albedo texture handle
	*	@var metallicRoughnessMap_	metallic roughness texture handle
	*	@var normalMap_				normal map texture handle
	*	@var opacityMap_			used during conversion
	*/
	struct JCQTOPENGL_EXPORT MaterialDescription final
	{
		vec4 emissiveColor_ = { 0.5f, 0.5f, 0.5f, 0.5f };
		vec4 albedoColor_ = { 1.5f, 1.0f, 1.0f, 1.5f };

		vec4 roughness_ = { 1.5f, 1.50f, 0.5f, 5.0f };
		float transparencyFactor_ = 1.0f;
		float alphaTest_ = 0.0f;
		float metallicFactor_ = 1.0f;

		quint32 flags_ = eMaterialFlags_CastShadow | eMaterialFlags_ReceiveShadow;

		quint64 ambientOcclusionMap_ = INVALID_TEXTURE;
		quint64 emissiveMap_ = INVALID_TEXTURE;
		quint64 albedoMap_ = INVALID_TEXTURE;
		quint64 metallicRoughnessMap_ = INVALID_TEXTURE;
		quint64 normalMap_ = INVALID_TEXTURE;
		quint64 opacityMap_ = INVALID_TEXTURE;
	};

	static_assert ( sizeof ( MaterialDescription ) % 16 == 0, "MaterialDescription should be padded to 16 bytes" );

	/**
	 * @brief Save the converted material data to file.
	 * @param filename name of the file to save the material data.
	 * @param materials array of material data to be saved
	 * @param files names of the texture files associated the material data
	*/
	void saveMaterials ( const char* filename, const QList<MaterialDescription>& materials, const QByteArrayList& files );

	/**
	 * @brief Load material data from a file.
	 * @param filename name of the file where the material data is stored.
	 * @param materials array of material data to load the file contents into.
	 * @param files array to load the texture filenames into.
	*/
	void loadMaterials ( const char* filename, QList<MaterialDescription>& materials, QByteArrayList& files );

	/**
	 * @brief Merge material lists from multiple scenes following the logic of merging in mergeScenes
	 * @param oldMaterials vector of pointers to all the materials from the input scenes
	 * @param oldTextures vector of pointers to all the texture files from the input scenes
	 * @param allMaterials output vector of all the material lists from all the input scenes
	 * @param newTextures out vector of all the texture filenames from all the input scenes
	*/
	void mergeMaterialLists (
		const QList<QList<MaterialDescription>* >& oldMaterials,
		const QList<QByteArrayList* >& oldTextures,
		QList<MaterialDescription>& allMaterials,
		QByteArrayList& newTextures
	);
}

#endif // !__MATERIAL_H__