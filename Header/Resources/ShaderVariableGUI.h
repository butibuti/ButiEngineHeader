#ifndef SHADERVARIABLEGUI_H
#define SHADERVARIABLEGUI_H

namespace ButiEngine {
namespace ButiRendering {

struct Matrices;
struct RendererState;
struct ObjectInformation;
struct GausParameter;
struct MaterialValue;
struct MaterialValue_Deferred;
struct ParticleParameter;
}

bool ShowUI(ButiRendering::Matrices& arg_v);
bool ShowUI(ButiRendering::RendererState& arg_v);
bool ShowUI(ButiRendering::ObjectInformation& arg_v);
bool ShowUI(ButiRendering::GausParameter& arg_v);
bool ShowUI(ButiRendering::MaterialValue& arg_v);
bool ShowUI(ButiRendering::MaterialValue_Deferred& arg_v);
bool ShowUI(ButiRendering::ParticleParameter& arg_v);
}

#endif // !SHADERVARIABLEGUI_H