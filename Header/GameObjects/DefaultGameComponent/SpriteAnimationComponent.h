#pragma once
#include"MeshDrawComponent.h"
namespace ButiEngine {

class SpriteAnimationComponent :public GameComponent {
public:
	SpriteAnimationComponent() {}
	void OnUpdate()override;
	void OnShowUI()override;
	void Start()override;
	void OnSet()override;
	void UpdateHorizontalAnim(const std::int32_t arg_updatePase);
	void UpdateVerticalAnim(const std::int32_t arg_updatePase);
	void SetHorizontalAnim(const std::int32_t arg_setNum);
	void SetVerticalAnim(const std::int32_t arg_setNum);
	std::int32_t GetHorizontalAnim() const;
	std::int32_t GetVerticalAnim()const;
	std::int32_t GetHorizontalSplitScale()const;
	std::int32_t GetVerticalSplitScale()const;


	std::string GetGameComponentName()const override {
		return "SpriteAnimationComponent";
	}
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(isActive);
		ARCHIVE_BUTI(m_horizontalNum);
		ARCHIVE_BUTI(m_verticalNum);
		ARCHIVE_BUTI(m_splitScale);
		ARCHIVE_BUTI(m_meshDrawIndex);
	}
	Value_ptr<GameComponent> Clone()override;
private:
	void UpdateBuffer();
	void SearchMeshDraw();
	Vector2 m_splitScale;
	std::int32_t m_horizontalSplitScale,m_verticalSplitScale,m_horizontalNum,m_verticalNum,m_meshDrawIndex=0;
	Value_ptr<ButiRendering::CBuffer<ButiRendering::ObjectInformation>> m_vlp_param;
};
}


BUTI_REGIST_GAMECOMPONENT(SpriteAnimationComponent,true)