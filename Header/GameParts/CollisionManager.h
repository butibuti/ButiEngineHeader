#pragma once

#include"stdafx.h"

namespace ButiEngine {
namespace Collision {
struct CollisionLayerInfo {

	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(size);
		ARCHIVE_BUTI(offset);
		ARCHIVE_BUTI(level);
		ARCHIVE_BUTI(isCheckSame);
		ARCHIVE_BUTI(vec_checkOtherLayerIndex);
	}
	Vector3 size;
	Vector3 offset;
	std::int32_t level;
	bool isCheckSame;
	std::vector<std::int32_t> vec_checkOtherLayerIndex;
};
struct ColiisionLayerLoadData {
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(vec_collisionLayerInfo);
	}
	std::vector<CollisionLayerInfo> vec_collisionLayerInfo;
};

Value_ptr<ICollisionManager> CreateCollisionManager(const std::int32_t arg_layerCount);

}
}