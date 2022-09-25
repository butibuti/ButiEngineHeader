#ifndef TRIGGERCOMPONENT_H
#define TRIGGERCOMPONENT_H
#include"RigidBodyComponent.h"

namespace ButiEngine {
class TriggerComponent :public GameComponent, public ButiBullet::PhysicsDetail::IPhysicsObjectEventListener {
public:
	std::string GetGameComponentName()const override {
		return "TriggerComponent";
	}

	void OnUpdate()override;
	void OnSet()override;
	void Start()override;
	void OnRemove()override;
	Value_ptr<GameComponent> Clone() override;

	void OnBeforeStepSimulation_Deprecated() override;
	void OnAfterStepSimulation() override;
	void OnCollisionEnter(ButiBullet::PhysicsObject* arg_p_otherObject, ButiBullet::ContactPoint* arg_p_contact)override;
	void OnCollisionLeave(ButiBullet::PhysicsObject* arg_p_otherObject, ButiBullet::ContactPoint* arg_p_contact)override;
	void OnCollisionStay(ButiBullet::PhysicsObject* arg_p_otherObject, ButiBullet::ContactPoint* arg_p_contact) override;

	void OnShowUI()override;

	const RigidBodyComponent::RigidBodyParameter& GetRigidBodyParameter()const { return m_param; }

	void SetGroup(std::int32_t arg_group);
	void SetGroupMask(std::int32_t arg_groupMask);
	Value_ptr<ButiBullet::ITriggerBody> GetRigidBody()const;

	void Regist();
	void UnRegist();

	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(isActive);
		ARCHIVE_BUTI(m_param);
		ARCHIVE_BUTI(m_vlp_shapeParam);
		ARCHIVE_BUTI(m_isAffectedForGravity);
	}
private:
	void CreateTriggerBody();
	void ReleaseTriggerBody();
	void RecreateTriggerBody() {
		ReleaseTriggerBody();
		CreateTriggerBody();
	}
	Value_ptr<ButiBullet::TriggerBody> m_vlp_triggerBody;
	Value_ptr<RigidBodyComponent::ShapeParam> m_vlp_shapeParam;
	RigidBodyComponent::RigidBodyParameter m_param;
	bool m_isAffectedForGravity = true;
};
}

BUTI_REGIST_GAMECOMPONENT(TriggerComponent, true)
#endif // !TRIGGERCOMPONENT_H
