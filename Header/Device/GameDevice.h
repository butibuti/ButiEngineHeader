#ifndef _GAMEDEVICE_H
#define _GAMEDEVICE_H

#pragma once

#include"ButiInput/ButiInput/ResourceInterface.h"
#include"ButiVive/ButiVive/Common.h"
namespace ButiEngine {
class GameDevice
{
public:
	~GameDevice();
	static void Initialize();
	static void InitializeInput(const HWND& arg_hwnd,const bool arg_isUseVRTracker);
	static float GetWorldSpeed();
	static void SetWorldSpeed(const float arg_speed);
	static ButiInput::IInputManager& GetInput();
	static ButiVive::ITracker& GetVRTrackerInput();
	static void SetIsEnd(const bool arg_isEnd);
	static bool GetIsEnd();
	static void SetReturnCode(const std::int32_t arg_returnCode);
	static std::int32_t GetReturnCode();
	static bool IsExceptionThrow();
	static void SetIsExceptionThrow(const bool arg_isExThrow);
	static std::chrono::system_clock::time_point GetBootTime();
private:
	GameDevice();
};
}

#endif // !_GAMEDEVICE_H