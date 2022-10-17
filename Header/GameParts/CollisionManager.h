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
		ARCHIVE_BUTI(list_checkOtherLayerIndex);
	}
	Vector3 size;
	Vector3 offset;
	std::int32_t level;
	bool isCheckSame;
	List<std::int32_t> list_checkOtherLayerIndex;
};
struct ColiisionLayerLoadData {
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(list_collisionLayerInfo);
	}
	List<CollisionLayerInfo> list_collisionLayerInfo;
};

Value_ptr<ICollisionManager> CreateCollisionManager(const std::int32_t arg_layerCount);

}
}