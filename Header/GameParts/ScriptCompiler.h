#ifndef SCRIPTCOMPILER_H
#define SCRIPTCOMPILER_H
#include<string>
namespace ButiEngine {

struct EditHistory {
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_map_lastEdit);
	}
	std::unordered_map<std::string, std::int64_t> m_map_lastEdit;
};
class ScriptCompiler {
public:
	ScriptCompiler(Value_weak_ptr<IResourceContainer> arg_vwp_container):m_vwp_container(arg_vwp_container){
		if (ResourceSystem::ExistResource("Application/ScriptEditHistory.rsh")) {
			InputCereal(m_editSecData, "Application/ScriptEditHistory.rsh");
		}
	}
	void Compile(const std::string& arg_compilePath);
	void Compile(const std::vector< std::string>& arg_vec_compilePath);
	void EditCheck();
private:
	void Compile(std::string& arg_compilePath, std::int32_t& arg_ref_compileCount, std::int32_t& arg_ref_successCount, std::int32_t& arg_ref_throughCount);
	std::string m_currentInput;
	EditHistory m_editSecData;
	Value_weak_ptr<IResourceContainer> m_vwp_container;
};
}
#endif // !SCRIPTCOMPILER_H
