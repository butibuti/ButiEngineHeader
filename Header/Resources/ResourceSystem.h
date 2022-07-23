#ifndef RESOURCE_SYSTEM_H
#define RESOURCE_SYSTEM_H
#include<string>
#include"ButiUtil/ButiUtil/BinaryObject.h"
namespace ButiEngine {
namespace GameAssetData {
struct AssetLoadData;
}
namespace ResourceSystem {
void Start();
void ReadChunkData();
void CreateChunkData();
bool ExistResource(const std::string& arg_path);
Value_ptr<IBinaryReader> GetResourceBinary(const std::string& arg_resourceName);
const char* GetResourcePtr(const std::string& arg_resourceName);
std::uint64_t GetResourceSize(const std::string& arg_resourceName);
void GetAssetLoadData(GameAssetData::AssetLoadData& arg_ref_loadData);
void End();
}
}

#endif // !RESOURCE_SYSTEM_H
