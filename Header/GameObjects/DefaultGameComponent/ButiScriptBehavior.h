#ifndef BUTISCRIPTBEHAVIOR_H
#define BUTISCRIPTBEHAVIOR_H

#include "../../GameComponentHeader.h"
#include<mutex>

namespace ButiEngine{

class ButiScriptBehavior :public GameComponent
{
public:
	ButiScriptBehavior() {}
	ButiScriptBehavior(ScriptTag arg_tag):scriptTag(arg_tag){}
	ButiScriptBehavior(const ButiScriptBehavior& arg_other);
	void OnUpdate()override;
	void OnSet()override;
	void OnShowUI()override;
	void Start();

	void SetScriptTag(ScriptTag arg_tag);

	template <typename T>
	T Execute(const std::string& arg_entryPoint);
	template<>
	void Execute(const std::string& arg_entryPoint);
	template <typename T, typename ... U>
	T Execute(const std::string& arg_entryPoint, U... argments);
	template < typename ... U>
	void Execute_void(const std::string& arg_entryPoint, U... argments);
	
	std::string GetGameComponentName()const override {
		return "ButiScriptBehavior";
	}
	Value_ptr<GameComponent> Clone()override;
	void OnRemove()override;

	void GlobalValueSave();
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(isActive);
		ARCHIVE_BUTI(scriptTag);
		ARCHIVE_BUTI(updateEntryPoint);
		GlobalValueSave();
		ARCHIVE_BUTI(list_pair_saveObject_typeIndex);
	}
	void VirtualMachineInitialize(const ScriptTag arg_scriptTag);
	void VirtualMachineHotReload();
	bool CheckByName(const std::string& arg_name)const override {
		return scriptTag.GetID() == arg_name;
	}
private:

	List<std::pair< Value_ptr<IValuePtrRestoreObject>,std::int32_t>> list_pair_saveObject_typeIndex;
	Value_ptr<ButiScript::VirtualMachine> vlp_VM;
	std::mutex mtx_vm;
	ScriptTag scriptTag;
	std::string updateEntryPoint = "main";


#ifdef _EDITORBUILD
	std::string hotReloadEventName;
#endif
};

}

BUTI_REGIST_GAMECOMPONENT(ButiScriptBehavior, true)
#endif