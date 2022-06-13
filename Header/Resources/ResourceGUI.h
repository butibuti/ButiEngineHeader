#ifndef RESOURCEGUI_H
#define RESOURCEGUI_H
namespace ButiEngine {
namespace ButiRendering {
class IResource_Shader;
class IResource_Texture;
}
bool ResourceGUI(Value_ptr<ButiRendering::IResource_Shader> arg_vlp_shader);
class TextureGUIObject :public IObject{
public:
	TextureGUIObject(Value_ptr<ButiRendering::IResource_Texture> arg_vlp_texture,const std::string& arg_windowName="") :m_vlp_texture(arg_vlp_texture),m_windowName(arg_windowName) {}
	void ShowGUI()override;
private:
	Value_ptr<ButiRendering::IResource_Texture> m_vlp_texture;
	std::string m_windowName;
};
}
#endif // !RESOURCEGUI_H
