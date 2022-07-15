#ifndef MATERIALEDITOR_H
#define MATERIALEDITOR_H
#include"ButiEngineHeader/Header/GameParts/GamePartsInterface.h"
namespace ButiEngine {
class MaterialEditor {
public:
	MaterialEditor(Value_weak_ptr<IResourceContainer> arg_vwp_resourceContainer);
	~MaterialEditor();
	void EditMaterial();
	void CreateMaterial();
	void SetEditMaterial(MaterialTag arg_tag);
private:
	class Impl;
	Impl* m_p_impl;
};
}
#endif // !MATERIALEDITOR_H