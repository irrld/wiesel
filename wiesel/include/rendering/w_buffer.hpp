
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

#include "util/w_utils.hpp"
#include "w_pch.hpp"

namespace Wiesel {
enum MemoryType {
  MemoryTypeVertexBuffer,
  MemoryTypeIndexBuffer,
  MemoryTypeUniformBuffer
};

class MemoryBuffer {
 public:
  explicit MemoryBuffer(MemoryType type);
  virtual ~MemoryBuffer();

  MemoryType m_Type;
  VkBuffer m_Buffer;
  VkDeviceMemory m_BufferMemory;
};

class UniformBuffer : public MemoryBuffer {
 public:
  UniformBuffer();
  ~UniformBuffer() override;

  void* m_Data;
};

}  // namespace Wiesel