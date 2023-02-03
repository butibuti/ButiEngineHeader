#pragma once
namespace ButiEngine {
class IScene;

class IGameObjectManager :public IObject {
	friend class GameObject;
public:
	virtual void SetScene(Value_weak_ptr<IScene> arg_vwp_scene)=0;
	virtual void Update()=0;
	virtual void RegistNewGameObject()=0;
	virtual void RegistGameObject()=0;
	virtual void ShowGUI()=0;
	virtual void Release()=0;
	virtual void Initialize_cereal()=0;

	virtual Value_weak_ptr<GameObject> GetSelectedUI()=0;

	virtual Value_weak_ptr<GameObject> AddObject(Value_ptr<Transform> arg_transform, std::string arg_objectName = "GameObject")=0;
	virtual Value_weak_ptr<GameObject> AddObject(Value_ptr<GameObject> arg_gameObject) = 0;
	virtual void ObjectUpdate(Value_ptr<GameObject> arg_gameObject,const bool arg_isTransformKeep=false)=0;
	virtual void ChangeObjectIndex(Value_ptr<GameObject> arg_gameObject, const std::uint32_t arg_index)=0;
	virtual Value_weak_ptr<GameObject>AddObjectFromCereal(std::string filePath, Value_ptr<Transform> arg_transform = nullptr)=0;
	virtual Value_weak_ptr<GameObject>AddObjectFromCereal_Insert(std::string filePath, Value_ptr<Transform> arg_transform = nullptr)=0;
	virtual Value_ptr<Transform> GetCerealTransform(std::string filePath)=0;

	virtual Value_weak_ptr<GameObject> GetGameObject(const std::string& arg_objectName)=0;
	virtual Value_weak_ptr<GameObject> GetGameObject(const GameObjectTag& arg_objectTag)=0;
	virtual List<Value_ptr<GameObject>> GetGameObjects(const GameObjectTag& arg_objectTag)=0;

	virtual void Start()=0;
	virtual void End()=0;

	virtual Value_weak_ptr<IScene> GetScene()=0;
	virtual Value_weak_ptr<IApplication> GetApplication()=0;
	virtual void CreateViewGameObjectVector(const std::string& arg_serchStr, const std::vector<ButiEngine::GameObjectTag>& arg_vec_serchTags)=0;
	virtual List<std::string> GetGameObjectList()=0;
	virtual void SetSelectedGameObject(Value_weak_ptr<GameObject> arg_obj)=0;
	virtual std::string GetUniqueName(const std::string& arg_name)=0;
	virtual std::int32_t GetIndex(Value_ptr<GameObject> arg_vlp_gameObject)=0;
private:
	virtual void CreateViewGameObjectVector()=0;
	virtual void CreateViewGameObjectVector_lock()=0;
	virtual void SetSelectedGameObjectCtrl(Value_weak_ptr<GameObject> arg_obj)=0;
	virtual void SetSelectedGameObjectShift(Value_weak_ptr<GameObject> arg_obj)=0;
};
Value_ptr<IGameObjectManager> CreateGameObjectManager();
Value_ptr<IGameObjectManager> CreateGameObjectManager(const std::string& arg_cerealFilePath);
void SaveGameObjectManager(Value_ptr<IGameObjectManager> arg_gameObjectManager, const std::string& arg_cerealFilePath);
}