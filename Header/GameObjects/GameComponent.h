#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#pragma once
namespace ButiEngine {
class GameComponent :public IObject
{
public:
	void Update();
	virtual void Start() {}
	virtual void End() {}
	void Set(Value_weak_ptr<GameObject> arg_vwp_gameObj);
	void SetIsRemove(bool arg_isRemove) {
		isRemove = arg_isRemove;
	}
	void SetIsActive(bool arg_isActive) {
		isActive = arg_isActive;
	}
	void ShowUI() {

		GUI::Checkbox("IsActive", &isActive);
		OnShowUI();
	}
	virtual void OnShowUI() {}
	virtual void OnSet();
	virtual void OnRemove();
	virtual std::string GetGameComponentName()const = 0;
	virtual Value_ptr<GameComponent> Clone() = 0;
	/// <summary>
	/// 型+名前でゲームコンポーネントの検索をするときに使う
	/// </summary>
	virtual bool CheckByName(const std::string&)const { return false; }

	Value_weak_ptr<GameObject> AddObject(Value_ptr<Transform> arg_transform, std::string arg_objectName = "GameObject");
	Value_weak_ptr<GameObject> AddObject(Value_ptr<GameObject> arg_gameObject);
	Value_weak_ptr<GameObject>AddObjectFromCereal(std::string filePath, Value_ptr<Transform> arg_transform = nullptr);

	Value_ptr<ButiSound::ISoundObject> PlaySE(const std::string& arg_seTagName, const float arg_volume);
	Value_ptr<ButiSound::ISoundObject> PlayBGM(const std::string& arg_seTagName, const float arg_volume);

	bool IsRemove() {
		return isRemove;
	}
	bool IsActive() {
		return isActive;
	}
	bool IsOverrideOnUpdate();
protected:
	virtual void OnUpdate(){}
	Value_ptr<ButiRendering::ICamera> GetCamera();
	Value_ptr<ButiRendering::ICamera> GetCamera(const std::uint32_t arg_camNum);
	Value_ptr<ButiRendering::ICamera> GetCamera(const std::string& arg_camName);
	Value_weak_ptr<IGameObjectManager> GetManager();
	Value_weak_ptr<GameObject> gameObject;

	bool isActive = true;
	bool isRemove = false;
private:
};

template<typename T>
Value_ptr<GameComponent> GenerateGameComponent() {
	auto component = ObjectFactory::Create<T>();
	return component;
}

using GameComponentGenerateFunctionType= Value_ptr<GameComponent>(*)();
extern void RegistGenerateGameComponentFunction(GameComponentGenerateFunctionType arg_function,const std::string& arg_name);

extern void RegistGameComponentOverrideOnUpdate(const std::string& arg_componentName,const bool isOverride);

template<typename T, bool IsUpdate>
struct GameComponentRegister {
	GameComponentRegister(const std::string& arg_name) {
		RegistGenerateGameComponentFunction(GenerateGameComponent<T>, arg_name);
		RegistGameComponentOverrideOnUpdate(arg_name, IsUpdate);
	}
};
}
#endif