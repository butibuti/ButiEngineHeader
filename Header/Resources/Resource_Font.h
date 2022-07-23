#include"stdafx.h"

namespace ButiEngine {

Value_ptr<IResource_Font> CreateFontFromFile(const std::string& arg_trueTypeFontFilePath, const std::int32_t size, Value_ptr<IResourceContainer> arg_resourceContainer);
Value_ptr<IResource_Font> CreateFontFromMemory(const std::string& arg_trueTypeFontFilePath,const char* arg_data, const std::int64_t arg_dataSize,const std::int32_t size,Value_ptr<IResourceContainer> arg_resourceContainer);

}