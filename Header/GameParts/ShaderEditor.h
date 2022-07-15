#ifndef SHADEREDITOR_H
#define SHADEREDITOR_H
#include"ButiEngineHeader/Header/GameParts/GamePartsInterface.h"
namespace ButiEngine {
class ShaderEditor {
public:
	ShaderEditor(Value_weak_ptr<IResourceContainer> arg_vwp_resourceContainer);
	~ShaderEditor();
	void CreateShader();
private:
	class Impl;
	Impl* m_p_impl;
};
}
#endif // !SHADEREDITOR_H
