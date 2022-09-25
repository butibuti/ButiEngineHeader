
#include "../../GameComponentHeader.h"
namespace ButiEngine {

	class PositionAnimation :public GameComponent
	{
	public:
		std::string GetGameComponentName()const override {
			return "PositionAnimation";
		}
		void OnUpdate()override;
		Vector3 GetInitPosition()const;
		Vector3 GetTargetPosition()const;
		virtual void SetInitPosition(const Vector3 & arg_position);
		virtual void _cdecl SetTargetPosition(const Vector3& arg_position);
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
			ARCHIVE_BUTI(targetPosition);
			ARCHIVE_BUTI(initPosition);
			ARCHIVE_BUTI(easeType);
			ARCHIVE_BUTI(isReverse);
		}
		void OnShowUI()override;
		virtual void PositionSet();
		void OnSet()override;
	protected:
		std::int32_t direction = 1;
		float t = 0;
		Vector3 targetPosition;
		Vector3 initPosition;
		float speed = 0.002f;;
		Easing::EasingType easeType = Easing::EasingType::EaseIn;
		bool isReverse = false;
	};
}

BUTI_REGIST_GAMECOMPONENT(PositionAnimation,true)