
//
//    Copyright 2023 Metehan Gezer
//
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//

#pragma once

#include "w_pch.hpp"
#include "util/w_utils.hpp"

namespace Wiesel {
class ImageView;

// taken from assimp
enum TextureType {
  /** Dummy value.
		   *
		   *  No texture, but the value to be used as 'texture semantic'
		   *  (#aiMaterialProperty::mSemantic) for all material properties
		   *  *not* related to textures.o
		   */
  TextureTypeNone = 0,

  /** LEGACY API MATERIALS
		 * Legacy refers to materials which
		 * Were originally implemented in the specifications around 2000.
		 * These must never be removed, as most engines support them.
		 */

  /** The texture is combined with the result of the diffuse
		 *  lighting equation.
		 *  OR
		 *  PBR Specular/Glossiness
		 */
  TextureTypeDiffuse = 1,

  /** The texture is combined with the result of the specular
		 *  lighting equation.
		 *  OR
		 *  PBR Specular/Glossiness
		 */
  TextureTypeSpecular = 2,

  /** The texture is combined with the result of the ambient
		 *  lighting equation.
		 */
  TextureTypeAmbient = 3,

  /** The texture is added to the result of the lighting
		 *  calculation. It isn't influenced by incoming light.
		 */
  TextureTypeEmissive = 4,

  /** The texture is a height map.
		 *
		 *  By convention, higher gray-scale values stand for
		 *  higher elevations from the base height.
		 */
  TextureTypeHeight = 5,

  /** The texture is a (tangent space) normal-map.
		 *
		 *  Again, there are several conventions for tangent-space
		 *  normal maps. Assimp does (intentionally) not
		 *  distinguish here.
		 */
  TextureTypeNormals = 6,

  /** The texture defines the glossiness of the material.
		 *
		 *  The glossiness is in fact the exponent of the specular
		 *  (phong) lighting equation. Usually there is a conversion
		 *  function defined to map the linear color values in the
		 *  texture to a suitable exponent. Have fun.
		*/
  TextureTypeShininess = 7,

  /** The texture defines per-pixel opacity.
		 *
		 *  Usually 'white' means opaque and 'black' means
		 *  'transparency'. Or quite the opposite. Have fun.
		*/
  TextureTypeOpacty = 8,

  /** Displacement texture
		 *
		 *  The exact purpose and format is application-dependent.
		 *  Higher color values stand for higher vertex displacements.
		*/
  TextureTypeDisplacement = 9,

  /** Lightmap texture (aka Ambient Occlusion)
		 *
		 *  Both 'Lightmaps' and dedicated 'ambient occlusion maps' are
		 *  covered by this material property. The texture contains a
		 *  scaling value for the final color value of a pixel. Its
		 *  intensity is not affected by incoming light.
		*/
  TextureTypeLightmap = 10,

  /** Reflection texture
		 *
		 * Contains the color of a perfect mirror reflection.
		 * Rarely used, almost never for real-time applications.
		*/
  TextureTypeReflection = 11,

  /** PBR Materials
		 * PBR definitions from maya and other modelling packages now use this standard.
		 * This was originally introduced around 2012.
		 * Support for this is in game engines like Godot, Unreal or Unity3D.
		 * Modelling packages which use this are very common now.
		 */

  TextureTypeBaseColor = 12,
  TextureTypeNormalCamera = 13,
  TextureTypeEmissionColor = 14,
  TextureTypeMetalness = 15,
  TextureTypeDiffuseRoughness = 16,
  TextureTypeAmbientOcclusion = 17,

  /** PBR Material Modifiers
		* Some modern renderers have further PBR modifiers that may be overlaid
		* on top of the 'base' PBR materials for additional realism.
		* These use multiple texture maps, so only the base type is directly defined
		*/

  /** Sheen
		* Generally used to simulate textiles that are covered in a layer of microfibers
		* eg velvet
		* https://github.com/KhronosGroup/glTF/tree/master/extensions/2.0/Khronos/KHR_materials_sheen
		*/
  TextureTypeSheen = 19,

  /** Clearcoat
		* Simulates a layer of 'polish' or 'lacquer' layered on top of a PBR substrate
		* https://autodesk.github.io/standard-surface/#closures/coating
		* https://github.com/KhronosGroup/glTF/tree/master/extensions/2.0/Khronos/KHR_materials_clearcoat
		*/
  TextureTypeClearcoat = 20,

  /** Transmission
		* Simulates transmission through the surface
		* May include further information such as wall thickness
		*/
  TextureTypeTransmission = 21
};

struct SamplerProps {
  SamplerProps()
      : MagFilter(VK_FILTER_LINEAR),
        MinFilter(VK_FILTER_LINEAR),
        MaxAnisotropy(-1.0f) {}

  SamplerProps(VkFilter magFilter, VkFilter minFilter, float anisotropy)
      : MagFilter(magFilter), MinFilter(minFilter), MaxAnisotropy(anisotropy) {}

  VkFilter MagFilter;
  VkFilter MinFilter;
  float MaxAnisotropy;
};

struct TextureProps {
  TextureProps()
      : Type(TextureTypeDiffuse),
        GenerateMipmaps(true),
        ImageFormat(VK_FORMAT_R8G8B8A8_UNORM) {}

  TextureProps(TextureType type)
      : Type(type),
        GenerateMipmaps(true),
        ImageFormat(VK_FORMAT_R8G8B8A8_UNORM) {}

  TextureProps(TextureType type, bool generateMipmaps, VkFormat imageFormat)
      : Type(type),
        GenerateMipmaps(generateMipmaps),
        ImageFormat(imageFormat) {}

  TextureType Type;
  bool GenerateMipmaps;
  VkFormat ImageFormat;
  uint32_t Width;
  uint32_t Height;
};

class Texture {
 public:
  Texture(TextureType textureType, const std::string& path);
  ~Texture();

  TextureType m_Type;
  VkImage m_Image;
  VkFormat m_Format;
  VkDeviceMemory m_DeviceMemory;
  Ref<ImageView> m_ImageView;
  VkSampler m_Sampler;
  uint32_t m_MipLevels;

  uint32_t m_Width;
  uint32_t m_Height;
  int32_t m_Channels;
  VkDeviceSize m_Size;

  bool m_IsAllocated;
  std::string m_Path;
};

enum class AttachmentTextureType {
  Color,
  DepthStencil,
  SwapChain,
  Offscreen,
  Resolve
};

struct AttachmentTextureProps {
  AttachmentTextureProps(uint32_t width, uint32_t height, AttachmentTextureType type, uint32_t count = 1, VkFormat imageFormat = VK_FORMAT_R8G8B8A8_UNORM,
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT, bool sampled = false, uint32_t layerCount = 1)
        : Width(width), Height(height), ImageCount(count), ImageFormat(imageFormat), Type(type), MsaaSamples(msaaSamples), Sampled(sampled), LayerCount(layerCount) {}

  uint32_t Width;
  uint32_t Height;
  VkFormat ImageFormat;
  AttachmentTextureType Type;
  VkSampleCountFlagBits MsaaSamples;
  uint32_t ImageCount;
  uint32_t LayerCount;
  bool Sampled;

};

class DescriptorData;

struct AttachmentTextureInfo {
  AttachmentTextureType Type;
  VkFormat Format;
  VkSampleCountFlagBits MsaaSamples;
  /*VkAttachmentLoadOp LoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  VkAttachmentStoreOp StoreOp = VK_ATTACHMENT_STORE_OP_STORE;
  VkAttachmentLoadOp StencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  VkAttachmentStoreOp StencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;*/
};


class AttachmentTexture {
 public:
  AttachmentTexture() = default;
  ~AttachmentTexture();

  AttachmentTextureType m_Type;
  std::vector<VkImage> m_Images;
  std::vector<Ref<ImageView>> m_ImageViews;
  std::vector<VkSampler> m_Samplers;
  std::vector<VkDeviceMemory> m_DeviceMemories;
  VkFormat m_Format;
  uint32_t m_Width;
  uint32_t m_Height;
  VkSampleCountFlagBits m_MsaaSamples;
  Ref<DescriptorData> m_Descriptors;
  VkImageAspectFlags m_AspectFlags;
  uint32_t m_MipLevels;

  bool m_IsAllocated;

};

class ImageView {
 public:
  ImageView() = default;
  ~ImageView();

  VkImageView m_Handle;
  uint32_t m_Layer;
  uint32_t m_LayerCount;
};

}  // namespace Wiesel