#pragma once
#include"MeshDrawComponent.h"
namespace ButiEngine {
namespace ButiRendering {
struct GausParameter;
}
class BloomComponent :public GameComponent {
public:
	BloomComponent() {}
	void OnShowUI()override;
	void Start()override;
	void OnSet()override;
	std::string GetGameComponentName()const override {
		return "BloomComponent";
	}
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(isActive);
		ARCHIVE_BUTI(m_deviation);
		ARCHIVE_BUTI(m_direction);
		ARCHIVE_BUTI(m_scale);
		ARCHIVE_BUTI(m_meshDrawIndex);
	}
	Value_ptr<GameComponent> Clone()override;
	void AcquisitionGausParam();
private:
	void UpdateBuffer();
	Value_ptr<ButiRendering::CBuffer<ButiRendering::GausParameter>> m_vlp_param;
	float m_deviation = 0.0f;
	Vector2 m_direction = Vector2(1, 0);
	Vector2 m_scale = Vector2(480, 270);
	std::int8_t m_meshDrawIndex=0;
};
}


BUTI_REGIST_GAMECOMPONENT(BloomComponent, true)