#pragma once
#include<memory>
#include<vector>
#include<functional>
namespace ButiEngine {
class GameObject;
}
namespace ButiBullet {
class PhysicsObject;
class ContactPoint;
struct ContactData;
}

namespace ButiEngine {
using GameObjectTag = ID<GameObject>;
class GameComponent;
class GameObjectManager;
class Application;
class ResourceContainer;
namespace ButiRendering {
class GraphicDevice;
}
class GameObject :public IObject
{
	friend class GameComponent;
public:
	GameObject();

	GameObject(Value_ptr<Transform> arg_transform, const std::string& arg_objectName, const std::string& arg_tagName);
	GameObject(Value_ptr<Transform> arg_transform);
	GameObject(Value_ptr<Transform> arg_transform, const std::string& arg_objectName);

	void Update();
	void Translate(const Vector3& velocity);
	void ScaleChange(const Vector3& changePase);
	void Rotation(const Vector3& rotationPase);

	void Start();
	void End();

	void SetActive(const bool arg_isActive);

	void SetGameObjectManager(Value_weak_ptr<GameObjectManager> arg_vwp_gameObjectManager);
	bool GetActive();

	void SetIsRemove(const bool arg_isRemove);
	bool GetIsRemove();

	virtual void OnUpdate();

	void Hit(Value_ptr<GameObject> arg_vlp_other);

	void HitStay(ButiBullet::ContactData& arg_contact);
	void HitEnter(ButiBullet::ContactData& arg_contact);
	void HitLeave(ButiBullet::ContactData& arg_contact);

	virtual void Release();

	virtual void Initialize();

	virtual void PreInitialize();
	Value_ptr<GameComponent> AddGameComponent(Value_ptr<GameComponent> arg_vlp_gameComponent);

	template<class T, typename... Ts>
	inline Value_ptr<T> AddGameComponent(Ts&&... params) {
		auto addComponet = ObjectFactory::Create<T>(params...);
		vec_newGameComponent.push_back(addComponet);
		addComponet->Set(GetThis<GameObject>());
		return addComponet;
	}

	template<class T, typename... Ts>
	inline Value_ptr<T> AddGameComponent_Insert(Ts&&... params) {
		auto addComponet = ObjectFactory::Create<T>(params...);
		vec_gameComponents.push_back(addComponet);
		addComponet->Set(GetThis<GameObject>());
		return addComponet;
	}


	Value_ptr<GameComponent> AddGameComponent_Insert(Value_ptr<GameComponent> arg_vlp_gameComponent);

	Value_ptr<GameComponent> GetGameComponent(const std::string& arg_gameComponentName, const std::uint32_t arg_index)const;
	Value_ptr<GameComponent> GetGameComponent(const std::string& arg_gameComponentName, const std::string& arg_serchName)const;

	template <typename T>
	static const std::string& GetComponentName() {
		static std::string arg_gameComponentName = T().GetGameComponentName();
		return arg_gameComponentName;
	}

	template <typename T>
	inline Value_ptr<T> GetGameComponent(const std::uint32_t arg_index) const {

		auto ret = GetGameComponent(GetComponentName<T>(), arg_index);

		return ret ? ret->GetThis<T>() : nullptr;
	}

	template <typename T>
	inline Value_ptr<T> GetGameComponent(const std::string& arg_name)const {
		auto ret = GetGameComponent(GetComponentName<T>(), arg_name);

		return ret ? ret->GetThis<T>() : nullptr;
	}
	template <typename T>
	inline Value_ptr<T> GetGameComponent() const {
		return GetGameComponent<T>(0);
	}


	void RemoveGameComponent(const std::string& arg_key);



	void ShowUI();


	const std::string& GetGameObjectName() const {
		return objectName;
	}


	std::string SetObjectName(const std::string& arg_objectName);

	GameObjectTag SetGameObjectTag(GameObjectTag& arg_tag) {
		if (map_gameObjectTags.count(arg_tag)) {
			return arg_tag;
		}
		map_gameObjectTags.emplace(arg_tag, 0);
		return arg_tag;
	}
	void RemoveGameObjectTag(const GameObjectTag& arg_tag) {
		if (map_gameObjectTags.count(arg_tag)) {
			map_gameObjectTags.erase(arg_tag);
		}
	}

	bool HasGameObjectTag(const GameObjectTag& arg_tag) const {
		return (arg_tag.IsEmpty() && !map_gameObjectTags.size()) ? true : map_gameObjectTags.count(arg_tag);
	}
	inline std::int32_t HasGameObjectTag(const std::string& arg_tagName)const {
		return HasGameObjectTag(GameObjectTag(arg_tagName));
	}
	void AddCollisionStayReaction(std::function< void(ButiBullet::ContactData&)>  arg_reactionFunc);
	void AddCollisionEnterReaction(std::function< void(ButiBullet::ContactData&)> arg_reactionFunc);
	void AddCollisionLeaveReaction(std::function< void(ButiBullet::ContactData&)> arg_reactionFunc);

	Value_weak_ptr<GameObjectManager> GetGameObjectManager();
	Value_weak_ptr<IApplication> GetApplication();
	Value_ptr<IResourceContainer> GetResourceContainer();
	Value_ptr<ButiRendering::GraphicDevice> GetGraphicDevice();
	Value_ptr<GameObject> Clone();

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(transform);
		archive(objectName);
		archive(isActive);
		archive(vec_gameComponents);
		archive(map_gameObjectTags);
	}
	void Init_RegistGameComponents();

	Value_weak_ptr<GameObject> AddObject(Value_ptr<Transform> arg_transform, const  std::string& arg_objectName);
	Value_weak_ptr<GameObject> AddObject(Value_ptr<GameObject> arg_gameObject);
	Value_weak_ptr<GameObject>AddObjectFromCereal(const std::string& filePath, Value_ptr<Transform> arg_transform);
	inline Value_ptr<Transform> GetTransform() {
		return transform;
	}
	Value_ptr<Transform> transform;
protected:

	Value_ptr<GameComponent> RegisterGameComponent(Value_ptr<GameComponent> arg_vlp_gameComponent);

	void GameComponentUpdate();
	void BehaviorHit();

	bool isActive = true;
	bool isRemove = false;

	std::vector< Value_ptr<GameComponent>>  vec_gameComponents;
	std::vector<Value_ptr<GameComponent>> vec_newGameComponent;

	std::string objectName;

	Value_weak_ptr<GameObjectManager> vwp_gameObjManager;
	std::unordered_map<GameObjectTag, std::uint32_t> map_gameObjectTags;
	List<std::function< void(ButiBullet::ContactData&)> > list_collisionStayReaction;
	List<std::function< void(ButiBullet::ContactData&)> > list_collisionEnterReaction;
	List<std::function< void(ButiBullet::ContactData&)> > list_collisionLeaveReaction;
};


void OutputCereal(const Value_ptr<GameObject>& v);

void InputCereal(Value_ptr<GameObject>& v, const std::string& path);
}