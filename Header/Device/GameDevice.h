#ifndef _GAMEDEVICE_H
#define _GAMEDEVICE_H

#pragma once

#include"../Device/Input.h"
namespace ButiEngine {
class GameDevice
{
public:
	~GameDevice();
	static void Initialize();
	static float GetWorldSpeed();
	static void SetWorldSpeed(const float arg_speed);
	static std::unique_ptr<Input>& GetInput();
	static void SetIsEnd(const bool arg_isEnd);
	static bool GetIsEnd();
	static void SetReturnCode(const std::int32_t arg_returnCode);
	static std::int32_t GetReturnCode();
private:
	GameDevice();
	static std::unique_ptr<Input> input;
};
}

#endif // !_GAMEDEVICE_H