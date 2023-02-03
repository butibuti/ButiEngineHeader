#ifndef _BUTI_GAMEOBJECT_H
#define _BUTI_GAMEOBJECT_H

#pragma once
#include<functional>
#include"ButiBulletWrap/ButiBulletWrap/Common.h"
namespace ButiEngine {
class GameObject;
}
namespace ButiBullet {
class PhysicsObject;
}

namespace ButiEngine {
using GameObjectTag = ID<GameObject>;
class GameComponent;
class IGameObjectManager;
namespace ButiRendering {
class GraphicDevice;
}
class GameObject :public IObject
{
	friend class GameComponent;
	friend class GameObjectManager;
	friend class InspectorUIObj;
public:
	GameObject();
	GameObject(const GameObject& arg_other);
	GameObject(Value_ptr<Transform> arg_transform, const std::string& arg_objectName, const std::string& arg_tagName);
	GameObject(Value_ptr<Transform> arg_transform);
	GameObject(Value_ptr<Transform> arg_transform, const std::string& arg_objectName);


	void SetActive(const bool arg_isActive);

	void SetGameObjectManager(Value_weak_ptr<IGameObjectManager> arg_vwp_gameObjectManager);
	bool GetActive();

	void SetIsRemove(const bool arg_isRemove);
	bool GetIsRemove();

	void HitStay(ButiBullet::ContactData& arg_contact);
	void HitEnter(ButiBullet::ContactData& arg_contact);
	void HitLeave(ButiBullet::ContactData& arg_contact);


	Value_ptr<GameComponent> AddGameComponent(Value_ptr<GameComponent> arg_vlp_gameComponent);

	template<class T, typename... Ts>
	inline Value_ptr<T> AddGameComponent(Ts&&... params) {
		auto addComponet = ObjectFactory::Create<T>(params...);
		m_list_newGameComponent.push_back(addComponet);
		addComponet->Set(GetThis<GameObject>());
		return addComponet;
	}


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
		for (auto checkComponent : m_list_gameComponents) {
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
	List<GameObjectTag> GetGameObjectTags()const;
	GameObjectTag SetGameObjectTag(const GameObjectTag& arg_tag) {
		if (m_map_gameObjectTags.count(arg_tag)) {
			return arg_tag;
		}
		m_map_gameObjectTags.emplace(arg_tag, m_map_gameObjectTags.size());
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
	void AddCollisionStayReaction(std::function< void(ButiBullet::ContactData&)>  arg_reactionFunc);
	void AddCollisionEnterReaction(std::function< void(ButiBullet::ContactData&)> arg_reactionFunc);
	void AddCollisionLeaveReaction(std::function< void(ButiBullet::ContactData&)> arg_reactionFunc);

	Value_weak_ptr<IGameObjectManager> GetGameObjectManager();
	Value_weak_ptr<IApplication> GetApplication();
	Value_ptr<IResourceContainer> GetResourceContainer();
	Value_ptr<ButiRendering::GraphicDevice> GetGraphicDevice();
	Value_ptr<GameObject> Clone(const bool arg_isTransformSame=false);

	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(transform);
		ARCHIVE_BUTI(m_objectName);
		ARCHIVE_BUTI(m_isActive);
		ARCHIVE_BUTI(m_list_gameComponents);
		ARCHIVE_BUTI(m_map_gameObjectTags);
	}

	Value_weak_ptr<GameObject> AddObject(Value_ptr<Transform> arg_transform, const  std::string& arg_objectName);
	Value_weak_ptr<GameObject> AddObject(Value_ptr<GameObject> arg_gameObject);
	Value_weak_ptr<GameObject>AddObjectFromCereal(const std::string& filePath, Value_ptr<Transform> arg_transform);
	Value_ptr<Transform> GetTransform() {
		return transform;
	}
	Value_ptr<Transform> transform;
protected:

	void Update();
	void Start();
	void End();
	virtual void Release();
	Value_ptr<GameComponent> AddGameComponent_Insert(Value_ptr<GameComponent> arg_vlp_gameComponent);
	void Init_RegistGameComponents();
	Value_ptr<GameComponent> RegisterGameComponent(Value_ptr<GameComponent> arg_vlp_gameComponent);

	void GameComponentUpdate();

	bool m_isActive = true, m_isRemove = false;

	List< Value_ptr<GameComponent>>  m_list_gameComponents, m_list_newGameComponent;

	std::string m_objectName;

	Value_weak_ptr<IGameObjectManager> m_vwp_gameObjManager;
	std::unordered_map<GameObjectTag, std::uint32_t> m_map_gameObjectTags;
	List<std::function< void(ButiBullet::ContactData&)> > m_list_physicsCollisionReactionStay, m_list_physicsCollisionReactionEnter, m_list_physicsCollisionReactionLeave;
	List<ButiBullet::ContactData> m_list_contactDataStay, m_list_contactDataEnter, m_list_contactDataLeave;
	std::mutex m_mtx_collisionAdd;
};
}


#endif // !_BUTI_GAMEOBJECT_H