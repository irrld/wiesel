
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

#include "behavior/w_behavior.hpp"
#include "events/w_keyevents.hpp"
#include "events/w_mouseevents.hpp"
#include "scene/w_entity.hpp"
#include "scene/w_scene.hpp"
#include "w_application.hpp"
#include "w_pch.hpp"

namespace WieselDemo {
class DemoApplication : public Wiesel::Application {
 public:
  DemoApplication();
  ~DemoApplication() override;

  void Init() override;
};

class DemoLayer : public Wiesel::Layer {
 public:
  explicit DemoLayer(DemoApplication& app);
  ~DemoLayer() override;

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float_t deltaTime) override;
  void OnEvent(Wiesel::Event& event) override;

  bool OnKeyPress(Wiesel::KeyPressedEvent& event);
  bool OnKeyReleased(Wiesel::KeyReleasedEvent& event);
  bool OnMouseMoved(Wiesel::MouseMovedEvent& event);

 private:
  DemoApplication& m_App;
  Wiesel::Ref<Wiesel::Scene> m_Scene;
  Wiesel::Ref<Wiesel::Renderer> m_Renderer;
};

}  // namespace WieselDemo