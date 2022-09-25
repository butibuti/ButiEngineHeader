#ifndef _GAMEDEVICE_H
#define _GAMEDEVICE_H

#pragma once

#include"ButiInput/ButiInput/ResourceInterface.h"
namespace ButiEngine {
class GameDevice
{
public:
	~GameDevice();
	static void Initialize();
	static void InitializeInput(const HWND& arg_hwnd);
	static float GetWorldSpeed();
	static void SetWorldSpeed(const float arg_speed);
	static ButiInput::IInputManager& GetInput();
	static void SetIsEnd(const bool arg_isEnd);
	static bool GetIsEnd();
	static void SetReturnCode(const std::int32_t arg_returnCode);
	static std::int32_t GetReturnCode();
private:
	GameDevice();
};
}

#endif // !_GAMEDEVICE_H