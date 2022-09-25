
#include "../../GameComponentHeader.h"
namespace ButiEngine {

class ScaleAnimation :public GameComponent
{
public:
	std::string GetGameComponentName()const override {
		return "ScaleAnimation";
	}
	void OnUpdate()override;
	Vector3 GetInitScale()const;
	Vector3 GetTargetScale()const;
	virtual void SetInitScale(const Vector3& arg_scale);
	virtual void _cdecl SetTargetScale(const Vector3& arg_scale);
	void SetEaseType(const Easing::EasingType type);
	void SetSpeed(const float arg_speed);
	void SetTime(const float arg_time);
	void SetReverse(const bool arg_isReverse);
	bool GetIsReverse()const;
	Value_ptr<GameComponent> Clone()override;

	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(isActive);
		ARCHIVE_BUTI(speed);
		ARCHIVE_BUTI(t);
		ARCHIVE_BUTI(targetScale);
		ARCHIVE_BUTI(initScale);
		ARCHIVE_BUTI(easeType);
		ARCHIVE_BUTI(isReverse);
	}
	void OnShowUI()override;
	virtual void ScaleSet();
	void OnSet()override;
protected:
	std::int32_t direction = 1;
	float t = 0;
	Vector3 targetScale;
	Vector3 initScale;
	float speed = 0.002f;;
	Easing::EasingType easeType = Easing::EasingType::EaseIn;
	bool isReverse = false;
};
}

BUTI_REGIST_GAMECOMPONENT(ScaleAnimation,true)