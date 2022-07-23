#pragma once
#include"stdafx.h"
#include"Resource_Sound.h"
namespace ButiEngine {
	class Resource_Sound_XAudio2:public Resource_Sound
	{
	public:
		Resource_Sound_XAudio2(Value_ptr<IBinaryReader> arg_reader);
	private:
	};

}