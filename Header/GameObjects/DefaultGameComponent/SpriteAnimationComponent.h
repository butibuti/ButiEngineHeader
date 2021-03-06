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
		archive(isActive);
		archive(horizontalNum);
		archive(verticalNum);
		archive(splitScale);
	}
	Value_ptr<GameComponent> Clone()override;
private:
	void UpdateBuffer();
	Vector2 splitScale;
	std::int32_t horizontalSplitScale;
	std::int32_t verticalSplitScale;
	std::int32_t horizontalNum;
	std::int32_t verticalNum;
	Value_ptr<ButiRendering::CBuffer<ButiRendering::ObjectInformation>> vlp_param;
};
}


BUTI_REGIST_GAMECOMPONENT(SpriteAnimationComponent,true)