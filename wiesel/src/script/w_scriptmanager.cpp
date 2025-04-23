//
//    Copyright 2023 Metehan Gezer
//
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//

#include "script/w_scriptmanager.hpp"

#include <direct.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/object.h>
#include "input/w_input.hpp"
#include "mono_util.h"
#include "scene/w_entity.hpp"
#include "scene/w_scene.hpp"
#include "script/mono/w_monobehavior.hpp"
#include "util/w_logger.hpp"
#include "w_engine.hpp"

namespace Wiesel {

#define WIESEL_ADD_INTERNAL_CALL(name)                     \
  mono_add_internal_call("WieselEngine.Internals::" #name, \
                         reinterpret_cast<void*>(Internals_##name))

// todo move these bindings to script glue
void Internals_Log_Info(MonoString* str) {
  const char* cstr = mono_string_to_utf8(str);
  LOG_INFO("{}", cstr);
  mono_free((void*)cstr);
}

float Internals_Input_GetAxis(MonoString* str) {
  const char* cstr = mono_string_to_utf8(str);
  float value = InputManager::GetAxis(cstr);
  mono_free((void*)cstr);
  return value;
}

bool Internals_Input_GetKey(MonoString* str) {
  const char* cstr = mono_string_to_utf8(str);
  bool value = InputManager::GetKey(cstr);
  mono_free((void*)cstr);
  return value;
}

void Internals_Input_SetCursorMode(uint16_t mode) {
  Engine::GetWindow()->SetCursorMode((CursorMode)mode);
}

uint16_t Internals_Input_GetCursorMode() {
  uint16_t cursorMode = Engine::GetWindow()->GetCursorMode();
  return cursorMode;
}

MonoObject* Internals_Behavior_GetComponent(Scene* scene, entt::entity entity,
                                            MonoString* str) {
  const char* cstr = mono_string_to_utf8(str);
  MonoObject* component =
      ScriptManager::GetComponentByName(scene, entity, cstr);
  mono_free((void*)cstr);
  return component;
}

bool Internals_Behavior_HasComponent(Scene* scene, entt::entity entity,
                                     MonoString* str) {
  const char* cstr = mono_string_to_utf8(str);
  bool hasComponent = ScriptManager::HasComponentByName(scene, entity, cstr);
  mono_free((void*)cstr);
  return hasComponent;
}

float Internals_TransformComponent_GetPositionX(Scene* scene,
                                                entt::entity entity) {
  return scene->GetComponent<TransformComponent>(entity).Position.x;
}

void Internals_TransformComponent_SetPositionX(Scene* scene,
                                               entt::entity entity,
                                               float value) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  if (c.Position.x == value) {
    return;
  }
  c.Position.x = value;
  c.IsChanged = true;
}

float Internals_TransformComponent_GetPositionY(Scene* scene,
                                                entt::entity entity) {
  return scene->GetComponent<TransformComponent>(entity).Position.y;
}

void Internals_TransformComponent_SetPositionY(Scene* scene,
                                               entt::entity entity,
                                               float value) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  if (c.Position.y == value) {
    return;
  }
  c.Position.y = value;
  c.IsChanged = true;
}

float Internals_TransformComponent_GetPositionZ(Scene* scene,
                                                entt::entity entity) {
  return scene->GetComponent<TransformComponent>(entity).Position.z;
}

void Internals_TransformComponent_SetPositionZ(Scene* scene,
                                               entt::entity entity,
                                               float value) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  if (c.Position.z == value) {
    return;
  }
  c.Position.z = value;
  c.IsChanged = true;
}

float Internals_TransformComponent_GetRotationX(Scene* scene,
                                                entt::entity entity) {
  return scene->GetComponent<TransformComponent>(entity).Rotation.x;
}

void Internals_TransformComponent_SetRotationX(Scene* scene,
                                               entt::entity entity,
                                               float value) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  if (c.Rotation.x == value) {
    return;
  }
  c.Rotation.x = value;
  c.IsChanged = true;
}

float Internals_TransformComponent_GetRotationY(Scene* scene,
                                                entt::entity entity) {
  return scene->GetComponent<TransformComponent>(entity).Rotation.y;
}

void Internals_TransformComponent_SetRotationY(Scene* scene,
                                               entt::entity entity,
                                               float value) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  if (c.Rotation.y == value) {
    return;
  }
  c.Rotation.y = value;
  c.IsChanged = true;
}

float Internals_TransformComponent_GetRotationZ(Scene* scene,
                                                entt::entity entity) {
  return scene->GetComponent<TransformComponent>(entity).Rotation.z;
}

void Internals_TransformComponent_SetRotationZ(Scene* scene,
                                               entt::entity entity,
                                               float value) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  if (c.Rotation.z == value) {
    return;
  }
  c.Rotation.z = value;
  c.IsChanged = true;
}

float Internals_TransformComponent_GetScaleX(Scene* scene,
                                             entt::entity entity) {
  return scene->GetComponent<TransformComponent>(entity).Scale.x;
}

void Internals_TransformComponent_SetScaleX(Scene* scene, entt::entity entity,
                                            float value) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  if (c.Scale.x == value) {
    return;
  }
  c.Scale.x = value;
  c.IsChanged = true;
}

float Internals_TransformComponent_GetScaleY(Scene* scene,
                                             entt::entity entity) {
  return scene->GetComponent<TransformComponent>(entity).Scale.y;
}

void Internals_TransformComponent_SetScaleY(Scene* scene, entt::entity entity,
                                            float value) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  if (c.Scale.y == value) {
    return;
  }
  c.Scale.y = value;
  c.IsChanged = true;
}

float Internals_TransformComponent_GetScaleZ(Scene* scene,
                                             entt::entity entity) {
  return scene->GetComponent<TransformComponent>(entity).Scale.z;
}

void Internals_TransformComponent_SetScaleZ(Scene* scene, entt::entity entity,
                                            float value) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  if (c.Scale.z == value) {
    return;
  }
  c.Scale.z = value;
  c.IsChanged = true;
}

MonoObject* CreateVector3fWithValues(float x, float y, float z) {
  MonoObject* obj = mono_object_new(ScriptManager::GetAppDomain(),
                                    ScriptManager::GetVector3fClass());
  void* args[3];
  args[0] = &x;
  args[1] = &y;
  args[2] = &z;
  MonoMethod* method = mono_class_get_method_from_name(
      ScriptManager::GetVector3fClass(), ".ctor", 3);
  mono_runtime_invoke(method, obj, args, nullptr);
  return obj;
}

MonoObject* Internals_TransformComponent_GetForward(Scene* scene,
                                                    entt::entity entity) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  glm::vec3 val = c.GetForward();
  return CreateVector3fWithValues(val.x, val.y, val.z);
}

MonoObject* Internals_TransformComponent_GetBackward(Scene* scene,
                                                     entt::entity entity) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  glm::vec3 val = c.GetBackward();
  return CreateVector3fWithValues(val.x, val.y, val.z);
}

MonoObject* Internals_TransformComponent_GetLeft(Scene* scene,
                                                 entt::entity entity) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  glm::vec3 val = c.GetLeft();
  return CreateVector3fWithValues(val.x, val.y, val.z);
}

MonoObject* Internals_TransformComponent_GetRight(Scene* scene,
                                                  entt::entity entity) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  glm::vec3 val = c.GetRight();
  return CreateVector3fWithValues(val.x, val.y, val.z);
}

MonoObject* Internals_TransformComponent_GetUp(Scene* scene,
                                               entt::entity entity) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  glm::vec3 val = c.GetUp();
  return CreateVector3fWithValues(val.x, val.y, val.z);
}

MonoObject* Internals_TransformComponent_GetDown(Scene* scene,
                                                 entt::entity entity) {
  auto& c = scene->GetComponent<TransformComponent>(entity);
  glm::vec3 val = c.GetDown();
  return CreateVector3fWithValues(val.x, val.y, val.z);
}

ScriptInstance::ScriptInstance(ScriptData* data, MonoBehavior* behavior) {
  m_Behavior = behavior;
  m_ScriptData = data;
  m_Instance = mono_object_new(ScriptManager::GetAppDomain(), data->GetClass());
  mono_runtime_object_init(m_Instance);

  uint64_t behaviorPtr = (uint64_t)behavior;
  uint64_t scenePtr = (uint64_t)behavior->GetScene();
  uint64_t entityId = (uint64_t)behavior->GetEntityHandle();
  MonoClass* baseClass = ScriptManager::GetMonoBehaviorClass();
  MonoClassField* field =
      mono_class_get_field_from_name(baseClass, "behaviorPtr");
  mono_field_set_value(m_Instance, field, &behaviorPtr);
  field = mono_class_get_field_from_name(baseClass, "scenePtr");
  mono_field_set_value(m_Instance, field, &scenePtr);
  field = mono_class_get_field_from_name(baseClass, "entityId");
  mono_field_set_value(m_Instance, field, &entityId);
  m_GCHandle = mono_gchandle_new(m_Instance, true);
}

ScriptInstance::~ScriptInstance() {
  mono_gchandle_free(m_GCHandle);
}

void ScriptInstance::OnStart() {
  UpdateAttachments();
  mono_runtime_invoke(m_ScriptData->GetOnStartMethod(), m_Instance, nullptr,
                      nullptr);
}

void ScriptInstance::OnUpdate(float_t deltaTime) {
  if (!m_StartRan) {
    OnStart();
    m_StartRan = true;
  }

  mono_domain_set(ScriptManager::GetAppDomain(), true);
  void* args[1];
  args[0] = &deltaTime;
  mono_runtime_invoke(m_ScriptData->GetOnUpdateMethod(), m_Instance, args,
                      nullptr);
}

bool ScriptInstance::OnKeyPressed(KeyPressedEvent& event) {
  if (!m_ScriptData->GetOnKeyPressedMethod()) {
    return false;
  }
  mono_domain_set(ScriptManager::GetAppDomain(), true);
  void* args[2];
  int32_t keyCode = event.GetKeyCode();
  bool repeat = event.IsRepeat();
  args[0] = &keyCode;
  args[1] = &repeat;
  MonoObject* data = mono_runtime_invoke(m_ScriptData->GetOnKeyPressedMethod(),
                                         m_Instance, args, nullptr);
  bool value = *(bool*)mono_object_unbox(data);
  return value;
}

bool ScriptInstance::OnKeyReleased(KeyReleasedEvent& event) {
  if (!m_ScriptData->GetOnKeyReleasedMethod()) {
    return false;
  }
  mono_domain_set(ScriptManager::GetAppDomain(), true);
  void* args[1];
  int32_t keyCode = event.GetKeyCode();
  args[0] = &keyCode;
  MonoObject* data = mono_runtime_invoke(m_ScriptData->GetOnKeyReleasedMethod(),
                                         m_Instance, args, nullptr);
  bool value = *(bool*)mono_object_unbox(data);
  return value;
}

bool ScriptInstance::OnMouseMoved(MouseMovedEvent& event) {
  if (!m_ScriptData->GetOnMouseMovedMethod()) {
    return false;
  }
  mono_domain_set(ScriptManager::GetAppDomain(), true);
  void* args[3];
  float x = event.GetX();
  float y = event.GetY();
  int32_t cursorMode = event.GetCursorMode();
  args[0] = &x;
  args[1] = &y;
  args[2] = &cursorMode;
  MonoObject* data = mono_runtime_invoke(m_ScriptData->GetOnMouseMovedMethod(),
                                         m_Instance, args, nullptr);
  bool value = *(bool*)mono_object_unbox(data);
  return value;
}

// explicitly instantiate needed types, this is required:
template void ScriptInstance::AttachExternComponent<TransformComponent>(std::string, entt::entity);

template <class T>
void ScriptInstance::AttachExternComponent(std::string variable,
                                           entt::entity entity) {
  Scene* scene = m_Behavior->GetScene();
  m_AttachedVariables.insert(std::pair(variable, [scene, entity]() {
    return ScriptManager::GetComponent<T>(scene, entity);
  }));

  if (m_StartRan) {
    UpdateAttachments();
  }
}

void ScriptInstance::UpdateAttachments() {
  for (const auto& item : m_AttachedVariables) {
    MonoObject* object = item.second();
    if (!object) {
      continue;
    }
    MonoClassField* field = mono_class_get_field_from_name(
        m_ScriptData->GetClass(), item.first.c_str());
    if (!field) {
      continue;
    }
    mono_field_set_value(m_Instance, field, object);
  }
}

MonoDomain* ScriptManager::m_RootDomain = nullptr;
MonoAssembly* ScriptManager::m_CoreAssembly = nullptr;
MonoImage* ScriptManager::m_CoreAssemblyImage = nullptr;
MonoDomain* ScriptManager::m_AppDomain = nullptr;
MonoAssembly* ScriptManager::m_AppAssembly = nullptr;
MonoImage* ScriptManager::m_AppAssemblyImage = nullptr;
MonoClass* ScriptManager::m_MonoBehaviorClass = nullptr;
MonoClass* ScriptManager::m_MonoTransformComponentClass = nullptr;
MonoClass* ScriptManager::m_MonoVector3fClass = nullptr;
MonoMethod* ScriptManager::m_SetHandleMethod = nullptr;

std::map<std::string, ScriptManager::ComponentGetter>
    ScriptManager::m_ComponentGetters;
std::map<std::type_index, ScriptManager::ComponentGetter>
    ScriptManager::m_ComponentGettersByType;
std::map<std::string, ScriptManager::ComponentChecker>
    ScriptManager::m_ComponentCheckers;
std::map<std::string, ScriptData*> ScriptManager::m_ScriptData;
std::vector<std::string> ScriptManager::m_ScriptNames;
bool ScriptManager::m_EnableDebugger;

MonoObject* ScriptManager::GetComponentByName(Scene* scene, entt::entity entity,
                                              const std::string& name) {
  auto& fn = m_ComponentGetters[name];
  if (fn == nullptr) {
    return nullptr;
  }
  return fn(scene, entity);
}

template <class T>
MonoObject* ScriptManager::GetComponent(Wiesel::Scene* scene, entt::entity entity) {
  auto& fn = m_ComponentGettersByType[std::type_index(typeid(T))];
  if (fn == nullptr) {
    return nullptr;
  }
  return fn(scene, entity);
}

bool ScriptManager::HasComponentByName(Scene* scene, entt::entity entity,
                                       const std::string& name) {
  auto& fn = m_ComponentCheckers[name];
  if (fn == nullptr) {
    return false;
  }
  return fn(scene, entity);
}

void ScriptManager::Init(const ScriptManagerProperties&& props) {
  m_EnableDebugger = props.EnableDebugger;
  LOG_INFO("Initializing mono...");

  mono_set_dirs("mono/lib", "mono/etc");
  mono_config_parse("mono/etc/mono/config");

  if (m_EnableDebugger) {
    const char* opt[] = {
        "--debugger-agent=transport=dt_socket,address=0.0.0.0:50000,server=y,suspend=n"
    };
    mono_jit_parse_options(1, reinterpret_cast<char**>(&opt));
    mono_debug_init(MONO_DEBUG_FORMAT_MONO);
  }

  m_RootDomain = mono_jit_init("WieselJITRuntime");

  RegisterComponents();
  RegisterInternals();
  LoadCore();
  LoadApp();
}

void ScriptManager::Destroy() {
  LOG_INFO("Cleaning up script manager...");
  // mono_domain_set(m_RootDomain, true);
  //mono_domain_unload(m_EngineDomain);
  //mono_domain_free(m_EngineDomain, true);
  //mono_jit_cleanup(m_RootDomain);
}

void ScriptManager::Reload() {
  LOG_INFO("Reloading scripts...");

  mono_domain_set(m_RootDomain, true);
  mono_domain_unload(m_AppDomain);

  for (const auto& [first, second] : m_ScriptData) {
    delete second;
  }
  m_ScriptData.clear();
  m_ScriptNames.clear();

  RegisterComponents();
  RegisterInternals();
  LoadCore();
  LoadApp();

  ScriptsReloadedEvent event{};
  Application::Get()->OnEvent(event);
}

void ScriptManager::LoadCore() {
  LOG_INFO("Compiling core scripts...");
  std::vector<std::string> sourceFiles;
  for (const auto& entry : std::filesystem::recursive_directory_iterator(
           "assets/internal_scripts")) {
    if (entry.is_regular_file() && entry.path().extension() == ".cs") {
      std::string name = entry.path().string();
      LOG_INFO("Found internal script {}", name);
      sourceFiles.push_back(name);
    }
  }
  CompileToDLL("obj/Core.dll", sourceFiles, "", {}, m_EnableDebugger);

  m_CoreAssembly = mono_domain_assembly_open(m_RootDomain, "obj/Core.dll");
  assert(m_CoreAssembly);

  m_CoreAssemblyImage = mono_assembly_get_image(m_CoreAssembly);
  m_MonoBehaviorClass =
      mono_class_from_name(m_CoreAssemblyImage, "WieselEngine", "MonoBehavior");
  m_SetHandleMethod =
      mono_class_get_method_from_name(m_MonoBehaviorClass, "SetHandle", 1);

  // Component classes
  m_MonoTransformComponentClass = mono_class_from_name(
      m_CoreAssemblyImage, "WieselEngine", "TransformComponent");
  m_MonoVector3fClass =
      mono_class_from_name(m_CoreAssemblyImage, "WieselEngine", "Vector3f");
}

void ScriptManager::LoadApp() {
  // todo load files from project file when project system is added
  std::vector<std::string> sourceFiles;
  for (const auto& entry :
       std::filesystem::recursive_directory_iterator("assets/scripts")) {
    if (entry.is_regular_file() && entry.path().extension() == ".cs") {
      std::string name = entry.path().string();
      LOG_INFO("Found user script {}", name);
      sourceFiles.push_back(name);
    }
  }
  std::vector<std::string> linkLibs;
  for (const auto& entry :
       std::filesystem::recursive_directory_iterator("obj")) {
    if (entry.is_regular_file() && entry.path().extension() == ".dll") {
      std::string name = entry.path().string();
      linkLibs.push_back(name);
      LOG_INFO("Found DLL to link {}", name);
    }
  }
  if (!CompileToDLL("obj/App.dll", sourceFiles, "obj", linkLibs, m_EnableDebugger)) {
    return;
  }
  m_AppDomain = mono_domain_create_appdomain(const_cast<char*>("WieselApp"), nullptr);
  mono_domain_set(m_AppDomain, true);
  //mono_domain_assembly_open(m_AppDomain, "obj/Core.dll");
  m_AppAssembly = mono_domain_assembly_open(m_AppDomain, "obj/App.dll");
  assert(m_AppAssembly);

  m_AppAssemblyImage = mono_assembly_get_image(m_AppAssembly);

  const MonoTableInfo* tableInfo =
      mono_image_get_table_info(m_AppAssemblyImage, MONO_TABLE_TYPEDEF);
  int rows = mono_table_info_get_rows(tableInfo);

  for (int i = 0; i < rows; i++) {
    uint32_t cols[MONO_TYPEDEF_SIZE];
    mono_metadata_decode_row(tableInfo, i, cols, MONO_TYPEDEF_SIZE);
    std::string className =
        mono_metadata_string_heap(m_AppAssemblyImage, cols[MONO_TYPEDEF_NAME]);
    if (className == "<Module>") {
      continue;
    }
    std::string classNamespace = mono_metadata_string_heap(
        m_AppAssemblyImage, cols[MONO_TYPEDEF_NAMESPACE]);
    // this is needed to load the class, facepalm Microsoft
    mono_class_from_name(m_AppAssemblyImage, classNamespace.c_str(),
                         className.c_str());

    LOG_INFO("Found class {} in namespace {}", className, classNamespace);
    MonoClass* klass = mono_class_from_name(
        m_AppAssemblyImage, classNamespace.c_str(), className.c_str());
    if (!klass) {
      LOG_ERROR("Class {} in namespace {} not found!", className,
                classNamespace);
      continue;
    }
    std::unordered_map<std::string, FieldData> fields;
    MonoClassField* field;
    void* iter = nullptr;
    while ((field = mono_class_get_fields(klass, &iter))) {
      std::string fieldName = mono_field_get_name(field);
      uint32_t fieldFlags = mono_field_get_flags(field);
      // fieldFlags & FIELD_ATTRIBUTE_FIELD_ACCESS_MASK == FIELD_ATTRIBUTE_PUBLIC
      if ((fieldFlags & 0x0007) != 0x0006) {
        continue;
      }
      //LOG_INFO("Public field: {}, flags {}", fieldName, fieldFlags);
      fields.insert(
          std::pair(fieldName, FieldData(field, fieldName, fieldFlags)));
    }
    MonoMethod* onStartMethod =
        mono_class_get_method_from_name(klass, "OnStart", 0);
    MonoMethod* onUpdateMethod =
        mono_class_get_method_from_name(klass, "OnUpdate", 1);
    MonoMethod* onKeyPressedMethod = mono_class_get_method_from_name(
        klass, "OnKeyPressed", 2);  // KeyCode, bool isRepeat
    MonoMethod* onKeyReleasedMethod =
        mono_class_get_method_from_name(klass, "OnKeyReleased", 1);  // KeyCode
    MonoMethod* onMouseMovedMethod = mono_class_get_method_from_name(
        klass, "OnMouseMoved", 3);  // x, y, cursorMode
    m_ScriptData.insert(std::pair(
        className,
        new ScriptData(klass, onStartMethod, onUpdateMethod, m_SetHandleMethod,
                       onKeyPressedMethod, onKeyReleasedMethod,
                       onMouseMovedMethod, fields)));
    m_ScriptNames.push_back(className);
  }
}

void ScriptManager::RegisterInternals() {
  WIESEL_ADD_INTERNAL_CALL(Log_Info);
  WIESEL_ADD_INTERNAL_CALL(Input_GetAxis);
  WIESEL_ADD_INTERNAL_CALL(Input_GetKey);
  WIESEL_ADD_INTERNAL_CALL(Input_SetCursorMode);
  WIESEL_ADD_INTERNAL_CALL(Input_GetCursorMode);
  WIESEL_ADD_INTERNAL_CALL(Behavior_GetComponent);
  WIESEL_ADD_INTERNAL_CALL(Behavior_HasComponent);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetPositionX);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetPositionY);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetPositionZ);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_SetPositionX);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_SetPositionY);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_SetPositionZ);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetRotationX);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetRotationY);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetRotationZ);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_SetRotationX);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_SetRotationY);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_SetRotationZ);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetScaleX);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetScaleY);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetScaleZ);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_SetScaleX);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_SetScaleY);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_SetScaleZ);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetForward);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetBackward);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetLeft);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetRight);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetUp);
  WIESEL_ADD_INTERNAL_CALL(TransformComponent_GetDown);
}

void ScriptManager::RegisterComponents() {
  m_ComponentGetters.clear();
  m_ComponentCheckers.clear();

  RegisterComponent<TransformComponent>(
      "TransformComponent",
      [](Scene* scene, entt::entity entity) -> MonoObject* {
        // todo add macro for this
        MonoObject* obj =
            mono_object_new(m_AppDomain, m_MonoTransformComponentClass);
        void* args[2];
        uint64_t scenePtr = (uint64_t)scene;
        uint64_t entityId = (uint64_t)entity;
        args[0] = &scenePtr;
        args[1] = &entityId;

        MonoMethod* method = mono_class_get_method_from_name(
            m_MonoTransformComponentClass, ".ctor", 2);
        mono_runtime_invoke(method, obj, args, nullptr);
        return obj;
      },
      [](Scene* scene, entt::entity entity) -> bool {
        return scene->HasComponent<TransformComponent>(entity);
      });
}

ScriptInstance* ScriptManager::CreateScriptInstance(MonoBehavior* behavior) {
  if (!m_ScriptData.contains(behavior->GetName())) {
    return nullptr;
  }
  ScriptData* data = m_ScriptData[behavior->GetName()];
  return new ScriptInstance(data, behavior);
}

template <class T>
void ScriptManager::RegisterComponent(std::string name, ComponentGetter getter,
                                      ComponentChecker checker) {
  m_ComponentGetters.insert(std::pair(name, getter));
  m_ComponentGettersByType.insert(std::pair(std::type_index(typeid(T)), getter));
  m_ComponentCheckers.insert(std::pair(name, checker));
}
}  // namespace Wiesel