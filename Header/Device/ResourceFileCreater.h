#pragma once
#include"stdafx.h"
namespace ButiEngine {
	class ResourceContainer;
	class ResourceFileCreater
	{
	public:
		static void CreateModelFile(const ModelTag& arg_tag, const std::string& arg_filePath, const std::string& arg_fileDirectory = "");

	private:
		ResourceFileCreater() {};
	};

}