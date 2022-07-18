#ifndef TEXTUREEDITOR_H
#define TEXTUREEDITOR_H
#include"ButiEngineHeader/Header/GameParts/GamePartsInterface.h"
namespace ButiEngine {
class TextureEditor {
public:
	TextureEditor(Value_weak_ptr<IResourceContainer> arg_vwp_resourceContainer);
	~TextureEditor();
	void CreateTexture();
	void EditTexture();
	void SetEditTexture(TextureTag arg_tag);
private:
	class Impl;
	Impl* m_p_impl;
};
}
#endif // !TEXTUREEDITOR_H
