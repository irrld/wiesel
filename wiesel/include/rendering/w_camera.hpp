
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

#include "events/w_appevents.hpp"
#include "util/w_uuid.hpp"
#include "w_pch.hpp"
#include "w_texture.hpp"

namespace Wiesel {

struct CameraComponent {
  CameraComponent() = default;
  CameraComponent(const CameraComponent&) = default;
  ~CameraComponent() = default;

  float m_FieldOfView = 60;
  float m_NearPlane = 0.1f;
  float m_FarPlane = 1000.0f;
  float m_AspectRatio = 1.0;
  Ref<AttachmentTexture> m_TargetTexture;

  glm::mat4 m_ViewMatrix;
  glm::mat4 m_Projection;
  bool m_IsChanged = true;
  bool m_IsEnabled = true;

  void UpdateProjection();
  void UpdateView(glm::vec3& position, glm::vec3& rotation);
};

struct CameraData {
  CameraData() = default;
  CameraData(glm::vec3 position, glm::mat4 viewMatrix, glm::mat4 projection)
      : Position(position), ViewMatrix(viewMatrix), Projection(projection){};
  CameraData(const CameraData&) = default;
  ~CameraData() = default;

  glm::vec3 Position;
  glm::mat4 ViewMatrix;
  glm::mat4 Projection;
  Ref<AttachmentTexture> TargetTexture;
  bool Available;
};

}  // namespace Wiesel
