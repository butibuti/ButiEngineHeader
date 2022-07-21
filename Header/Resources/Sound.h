#pragma once
#include"WaveDatas.h"
#include"ButiUtil/ButiUtil/BinaryObject.h"
namespace ButiEngine {

class SoundHelper
{
public:
	~SoundHelper();

	static Value_ptr<WaveDatas> CreateFromBinary(Value_ptr<IBinaryReader> arg_reader);
	static Value_ptr<WaveDatas> CreateFromFile(const std::string& arg_filePath){
		if (!Util::ExistFile(arg_filePath)) {
			return nullptr;
		}
		auto reader = make_value<BinaryReader_File>(arg_filePath);
		auto output = CreateFromBinary(reader);
		reader->ReadEnd();
		return output;
	}
private:
	SoundHelper();
};
}

