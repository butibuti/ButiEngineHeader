#pragma once
#include<memory>
#include<vector>
#include<functional>
namespace ButiEngine {
class GameObject;
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
	GameObject(const GameObject& arg_other);

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
	void CollisionUpdate();
	virtual void OnUpdate();

	void Hit(Value_ptr<GameObject> arg_vlp_other);

	virtual void Release();

	virtual void Initialize();

	virtual void PreInitialize();
	Value_ptr<GameComponent> AddGameComponent(Value_ptr<GameComponent> arg_vlp_gameComponent);

	template<class T, typename... Ts>
	inline Value_ptr<T> AddGameComponent(Ts&&... params) {
		auto addComponet = ObjectFactory::Create<T>(params...);
		m_vec_newGameComponent.push_back(addComponet);
		addComponet->Set(GetThis<GameObject>());
		return addComponet;
	}

	template<class T, typename... Ts>
	inline Value_ptr<T> AddGameComponent_Insert(Ts&&... params) {
		auto addComponet = ObjectFactory::Create<T>(params...);
		m_vec_gameComponents.push_back(addComponet);
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
	template <typename T>
	inline List< Value_ptr<T>> GetGameComponents() const {
		List< Value_ptr<T>> output;
		for (auto checkComponent : m_vec_gameComponents) {
			if (checkComponent->IsThis<T>()) {
				output.Add(checkComponent->GetThis<T>());
			}
		}
		return output;
	}


	void RemoveGameComponent(const std::string& arg_key);



	void ShowUI();


	const std::string& GetGameObjectName() const {
		return m_objectName;
	}


	std::string SetObjectName(const std::string& arg_objectName);

	GameObjectTag SetGameObjectTag(GameObjectTag& arg_tag) {
		if (m_map_gameObjectTags.count(arg_tag)) {
			return arg_tag;
		}
		m_map_gameObjectTags.emplace(arg_tag, 0);
		return arg_tag;
	}
	void RemoveGameObjectTag(const GameObjectTag& arg_tag) {
		if (m_map_gameObjectTags.count(arg_tag)) {
			m_map_gameObjectTags.erase(arg_tag);
		}
	}

	bool HasGameObjectTag(const GameObjectTag& arg_tag) const {
		return (arg_tag.IsEmpty() && !m_map_gameObjectTags.size()) ? true : m_map_gameObjectTags.count(arg_tag);
	}
	inline std::int32_t HasGameObjectTag(const std::string& arg_tagName)const {
		return HasGameObjectTag(GameObjectTag(arg_tagName));
	}
	void AddCollisionStayReaction(std::function< void(Value_ptr<GameObject>&)>  arg_reactionFunc);
	void AddCollisionEnterReaction(std::function< void(Value_ptr<GameObject>&)> arg_reactionFunc);
	void AddCollisionLeaveReaction(std::function< void(Value_ptr<GameObject>&)> arg_reactionFunc);

	Value_weak_ptr<GameObjectManager> GetGameObjectManager();
	Value_weak_ptr<IApplication> GetApplication();
	Value_ptr<IResourceContainer> GetResourceContainer();
	Value_ptr<ButiRendering::GraphicDevice> GetGraphicDevice();
	Value_ptr<GameObject> Clone();

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(transform);
		archive(m_objectName);
		archive(m_isActive);
		archive(m_vec_gameComponents);
		archive(m_map_gameObjectTags);
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

	bool m_isActive = true;
	bool m_isRemove = false;

	std::vector< Value_ptr<GameComponent>>  m_vec_gameComponents;
	std::vector<Value_ptr<GameComponent>> m_vec_newGameComponent;

	std::string m_objectName;

	Value_weak_ptr<GameObjectManager> m_vwp_gameObjManager;
	std::unordered_map<GameObjectTag, std::uint32_t> m_map_gameObjectTags;
	//List<std::function< void(ButiBullet::ContactData&)> > m_list_physicsCollisionStayReaction, m_list_physicsCollisionEnterReaction, m_list_physicsCollisionLeaveReaction;
	List<std::function< void(Value_ptr<GameObject>&)> > m_list_collisionStayReaction,m_list_collisionEnterReaction,m_list_collisionLeaveReaction;
	List<Value_ptr<GameObject>> m_list_vwp_currentCollisionObject, m_list_vwp_beforeCollisionObject, m_list_vwp_delayAddCurrentCollisionObject;
	std::mutex mtx_collisionAdd;
};


void OutputCereal(const Value_ptr<GameObject>& v);

void InputCereal(Value_ptr<GameObject>& v, const std::string& path);
}