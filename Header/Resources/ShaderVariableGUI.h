#ifndef SHADERVARIABLEGUI_H
#define SHADERVARIABLEGUI_H

namespace ButiEngine {
namespace ButiRendering {

struct ShaderVariable;
struct RenderingSceneInfo;
struct ObjectInformation;
struct GausVariable;
struct MaterialValue;
struct MaterialValue_Deferred;
struct ParticleParameter;
}

bool ShowUI(ButiRendering::ShaderVariable& arg_v);
bool ShowUI(ButiRendering::RenderingSceneInfo& arg_v);
bool ShowUI(ButiRendering::ObjectInformation& arg_v);
bool ShowUI(ButiRendering::GausVariable& arg_v);
bool ShowUI(ButiRendering::MaterialValue& arg_v);
bool ShowUI(ButiRendering::MaterialValue_Deferred& arg_v);
bool ShowUI(ButiRendering::ParticleParameter& arg_v);
}

#endif // !SHADERVARIABLEGUI_H