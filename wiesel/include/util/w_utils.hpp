
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

#define PI 3.14
#define BIT(x) (1 << x)

#include <glm/gtx/hash.hpp>

#include "w_pch.hpp"

namespace Wiesel {

#define WIESEL_SHADOW_CASCADE_COUNT 4
#define WIESEL_SSAO_KERNEL_SIZE 24
#define WIESEL_SSAO_RADIUS 0.5
#define WIESEL_SSAO_NOISE_DIM 8
#define WIESEL_SHADOWMAP_DIM 4096

std::string GetNameFromVulkanResult(VkResult errorCode);

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool IsComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

enum BakeResult { SUCCESS };

using Index = uint32_t;



enum Vertex3DFlag {
  VertexFlagHasTexture = BIT(0),
  VertexFlagHasNormalMap = BIT(1),
  VertexFlagHasSpecularMap = BIT(2),
  VertexFlagHasHeightMap = BIT(3),
  VertexFlagHasAlbedoMap = BIT(4),
  VertexFlagHasRoughnessMap = BIT(5),
  VertexFlagHasMetallicMap = BIT(6),
};

struct Vertex3D {
  glm::vec3 Pos;
  glm::vec3 Color;
  glm::vec2 UV;
  glm::vec3 Normal;
  glm::vec3 Tangent;
  glm::vec3 BiTangent;
  uint32_t Flags;

  static VkVertexInputBindingDescription GetBindingDescription() {
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex3D);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
  }

  static std::vector<VkVertexInputAttributeDescription>
  GetAttributeDescriptions() {
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};

    attributeDescriptions.push_back(
        {0, 0, VK_FORMAT_R32G32B32_SFLOAT, (uint32_t) offsetof(Vertex3D, Pos)});
    attributeDescriptions.push_back(
        {1, 0, VK_FORMAT_R32G32B32_SFLOAT, (uint32_t) offsetof(Vertex3D, Color)});
    attributeDescriptions.push_back(
        {2, 0, VK_FORMAT_R32G32_SFLOAT, (uint32_t) offsetof(Vertex3D, UV)});
    attributeDescriptions.push_back(
        {3, 0, VK_FORMAT_R32G32B32_SFLOAT, (uint32_t) offsetof(Vertex3D, Normal)});
    attributeDescriptions.push_back(
        {4, 0, VK_FORMAT_R32G32B32_SFLOAT, (uint32_t) offsetof(Vertex3D, Tangent)});
    attributeDescriptions.push_back(
        {5, 0, VK_FORMAT_R32G32B32_SFLOAT, (uint32_t) offsetof(Vertex3D, BiTangent)});
    attributeDescriptions.push_back(
        {6, 0, VK_FORMAT_R32_UINT, (uint32_t) offsetof(Vertex3D, Flags)});

    return attributeDescriptions;
  }

  bool operator==(const Vertex3D& other) const {
    return Pos == other.Pos && Color == other.Color && UV == other.UV;
  }
};

struct Vertex2DNoColor {
  glm::vec2 Pos;
  glm::vec2 UV;

  static VkVertexInputBindingDescription GetBindingDescription() {
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex2DNoColor);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
  }

  static std::vector<VkVertexInputAttributeDescription>
  GetAttributeDescriptions() {
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};

    attributeDescriptions.push_back(
        {0, 0, VK_FORMAT_R32G32_SFLOAT, (uint32_t) offsetof(Vertex2DNoColor, Pos)});
    attributeDescriptions.push_back(
        {1, 0, VK_FORMAT_R32G32_SFLOAT, (uint32_t) offsetof(Vertex2DNoColor, UV)});

    return attributeDescriptions;
  }

  bool operator==(const Vertex2DNoColor& other) const {
    return Pos == other.Pos && UV == other.UV;
  }
};

struct VertexSprite {
  glm::vec2 UV;

  static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions() {
    std::vector<VkVertexInputBindingDescription> bindingDescriptions{};

    bindingDescriptions.push_back(
        {0, sizeof(VertexSprite), VK_VERTEX_INPUT_RATE_VERTEX});

    return bindingDescriptions;
  }

  static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions() {
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};

    attributeDescriptions.push_back(
        {0, 0, VK_FORMAT_R32G32_SFLOAT, (uint32_t) offsetof(VertexSprite, UV)});

    return attributeDescriptions;
  }

  bool operator==(const VertexSprite& other) const {
    return UV == other.UV;
  }
};

struct alignas(16) MatricesUniformData {
  alignas(16) glm::mat4 ModelMatrix;
  alignas(16) glm::mat3 NormalMatrix;
};

struct alignas(16) SpriteUniformData {
  alignas(16) glm::mat4 ModelMatrix;
};

struct alignas(16) CameraUniformData {
  alignas(16) glm::mat4 ViewMatrix;
  alignas(16) glm::mat4 Projection;
  alignas(16) glm::mat4 InvProjection;
  alignas(16) glm::vec3 Position;
  float NearPlane;
  float FarPlane;
  float _pad1[2];
  glm::vec4 CascadeSplits;
  uint32_t EnableSSAO;
};

struct alignas(16) ShadowMapMatricesUniformData {
  alignas(16) glm::mat4 ViewProjectionMatrix[WIESEL_SHADOW_CASCADE_COUNT];
  alignas(16) int32_t EnableShadows;
};

struct alignas(16) SSAOKernelUniformData {
  alignas(16) glm::vec4 Samples[WIESEL_SSAO_KERNEL_SIZE];
};

struct SSAOSpecializationData {
  uint32_t kernelSize = WIESEL_SSAO_KERNEL_SIZE;
  float radius = WIESEL_SSAO_RADIUS;

  std::vector<VkSpecializationMapEntry> GetSpecializationMapEntries() {
    std::vector<VkSpecializationMapEntry> entries;
    entries.push_back(VkSpecializationMapEntry{
        .constantID = 0,
        .offset = (uint32_t)offsetof(SSAOSpecializationData, kernelSize),
        .size = sizeof(SSAOSpecializationData::kernelSize)});
    entries.push_back(VkSpecializationMapEntry{
        .constantID = 1,
        .offset = (uint32_t)offsetof(SSAOSpecializationData, radius),
        .size = sizeof(SSAOSpecializationData::radius)});
    return entries;
  }
};

template <typename T>
using Weak = std::weak_ptr<T>;

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>

using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> CreateReference(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename A, typename B>
using Pair = std::pair<A, B>;

class Time {
 public:
  static float_t GetTime();
};

std::vector<char> ReadFile(const std::string& filename);
std::vector<uint32_t> ReadFileUint32(const std::string& filename);

std::string FormatVariableName(const std::string& name);

inline void TrimLeft(std::string& s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}
}  // namespace Wiesel

#define WIESEL_CONCAT_IMPL(x, y) x##y
#define WIESEL_CONCAT(x, y) WIESEL_CONCAT_IMPL(x, y)

#define WIESEL_UNIQUE_NAME(base) WIESEL_CONCAT(base, __LINE__)

#define WIESEL_CHECK_VKRESULT_NAMED(f, name)                         \
  do {                                                               \
    VkResult name = (f);                                             \
    if (name != VK_SUCCESS) {                                        \
      std::cout << "Fatal : VkResult is \""                          \
                << Wiesel::GetNameFromVulkanResult(name) << "\" in " \
                << __FILE__ << " at line " << __LINE__ << "\n";      \
      assert(name == VK_SUCCESS);                                    \
    }                                                                \
  } while (0)

#define WIESEL_CHECK_VKRESULT(f) \
  WIESEL_CHECK_VKRESULT_NAMED(f, WIESEL_UNIQUE_NAME(res))

// https://github.com/TheCherno/Hazel
#define WIESEL_BIND_FN(fn)                                  \
  [this](auto&&... args) -> decltype(auto) {                \
    return this->fn(std::forward<decltype(args)>(args)...); \
  }

#define WIESEL_BIND_GLOBAL_FN(fn)                     \
  [](auto&&... args) -> decltype(auto) {              \
    return fn(std::forward<decltype(args)>(args)...); \
  }
