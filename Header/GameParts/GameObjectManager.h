#pragma once
#include<mutex>
namespace ButiEngine {
class IScene;
class GameObjectManager :public IObject
{
	friend class GameObject;
public:
	GameObjectManager(Value_weak_ptr<IScene> arg_vwp_scene);
	GameObjectManager() {}
	void SetScene(Value_weak_ptr<IScene> arg_vwp_scene);
	void Update();
	void RegistNewGameObject();
	void RegistGameObject();
	void Initialize()override;
	void PreInitialize()override;
	void ShowGUI();
	void Release();
	void Initialize_cereal();

	Value_weak_ptr<GameObject> GetSelectedUI();

	Value_weak_ptr<GameObject> AddObject(Value_ptr<Transform> arg_transform, std::string arg_objectName = "GameObject");
	Value_weak_ptr<GameObject> AddObject(Value_ptr<GameObject> arg_gameObject);
	Value_weak_ptr<GameObject>AddObjectFromCereal(std::string filePath, Value_ptr<Transform> arg_transform = nullptr);
	Value_weak_ptr<GameObject>AddObjectFromCereal_Insert(std::string filePath, Value_ptr<Transform> arg_transform = nullptr);
	Value_ptr<Transform> GetCerealTransform(std::string filePath);

	Value_weak_ptr<GameObject> GetGameObject(const std::string& arg_objectName);
	Value_weak_ptr<GameObject> GetGameObject(const GameObjectTag& arg_objectTag);
	List<Value_ptr<GameObject>> GetGameObjects(const GameObjectTag& arg_objectTag);

	void Start();
	void End();

	Value_weak_ptr<IScene> GetScene() {
		return m_vwp_scene;
	}

	Value_weak_ptr<IApplication> GetApplication();

	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(m_list_gameObjects);
	}
	void CreateViewGameObjectVector(const std::string& arg_serchStr, const std::vector<ButiEngine::GameObjectTag>& arg_vec_serchTags);
	List<std::string> GetGameObjectList();
	void SetSelectedGameObject(Value_weak_ptr<GameObject> arg_obj);
	std::string GetUniqueName(const std::string& arg_name);
private:
	void CreateViewGameObjectVector();
	void CreateViewGameObjectVector_lock();
	void SetSelectedGameObjectCtrl(Value_weak_ptr<GameObject> arg_obj);
	void SetSelectedGameObjectShift(Value_weak_ptr<GameObject> arg_obj);
	std::mutex m_mtx_addGameObject,m_mtx_update,m_mtx_viewObject,m_mtx_uniqueName;
	List<Value_ptr<GameObject>> m_list_gameObjects,m_list_newGameObjects;
	Value_ptr<List<Value_ptr<GameObject>>> m_vlp_list_viewGameObjects;
	Value_weak_ptr<IScene> m_vwp_scene;
	List<Value_weak_ptr<GameObject>> m_list_selectedGameObject;
	std::string m_eventRegistKey;
};

}