#pragma once
#include"../Device/Keys.h"
#include"../Device/MouseButtons.h"
#include"../Device/PadButtons.h"
namespace ButiEngine {
	class IApplication;
	class Input
	{
		class InputInstance;
	public:
		Input();
		~Input();
		void Initialize(Value_weak_ptr<IApplication> arg_vwp_app);
		bool CheckKey(const std::uint32_t arg_index);
		bool TriggerKey(const std::uint32_t arg_index);
		bool ReleaseKey(const std::uint32_t arg_index);
		bool CheckKey(const Keys arg_index);
		bool TriggerKey(const Keys arg_index);
		bool ReleaseKey(const Keys arg_index);
		bool CheckAnyKey();
		bool TriggerAnyKey();
		void PadUpdate();
		void MouseUpdate();
		bool GetAnyButton();
		bool GetAnyButtonTrigger();
		bool GetPadButton(const PadButtons arg_button);
		bool GetPadButtonTrigger(const PadButtons arg_button);
		bool GetPadButtonRelease(const PadButtons arg_button);
		bool GetMouseButton(const MouseButtons arg_button);
		bool GetMouseTrigger(const MouseButtons arg_button);
		bool GetMouseReleaseTrigger(const MouseButtons arg_button);
		bool GetMouseWheel();
		float GetMouseWheelMove();
		void SetCursorHide(const bool arg_isCursorHide);
		void Vibration_L(const float arg_power);
		void Vibration_R(const float arg_power);
		Vector2 GetLeftStick();
		Vector2 GetRightStick();
		float GetLeftTrigger();
		float GetRightTrigger();
		Vector2 GetMouseMove();
		Vector2 GetMousePos();
		void SetMouseCursor(const Vector2& arg_position);
	private:
		HRESULT CreateInput();
		HRESULT CreateKey();
		HRESULT CreateMouse();
		HRESULT SetKeyFormat();
		HRESULT SetMouseFormat();
		HRESULT SetKeyCooperative(Value_weak_ptr<IApplication> arg_vwp_app);
		HRESULT SetMouseCooperative(Value_weak_ptr<IApplication> arg_vwp_app);



		HRESULT m_result;
		std::unique_ptr<InputInstance> m_unq_instance;
		Value_weak_ptr<IApplication> m_vwp_app;

	};
}
