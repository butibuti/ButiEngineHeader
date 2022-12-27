#ifndef SHADEREDITOR_H
#define SHADEREDITOR_H
#include"ButiEngineHeader/Header/GameParts/GamePartsInterface.h"
namespace ButiEngine {
class ShaderEditor {
public:
	ShaderEditor(Value_weak_ptr<IResourceContainer> arg_vwp_resourceContainer);
	~ShaderEditor();
	void CreateShader();
	void Compile(const std::string& arg_compilePath);
	void Compile_async(const std::string& arg_compilePath);
	void Compile(const List< std::string>& arg_list_compilePath);
	void EditCheck();
	void EditCheck_async();
private:
	void Compile(std::string arg_compilePath, std::int32_t& arg_ref_compileCount, std::int32_t& arg_ref_successCount, std::int32_t& arg_ref_throughCount);
	class Impl;
	Impl* m_p_impl;
};
}
#endif // !SHADEREDITOR_H
