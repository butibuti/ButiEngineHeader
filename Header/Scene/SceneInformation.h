#ifndef SCENEINFORMATION_H
#define SCENEINFORMATION_H

#pragma once
#include"Header/Scene/RenderingPathData.h"
namespace ButiEngine {
namespace ButiRendering {
}
	struct SceneInformation :public IObject
	{
	public:
		SceneInformation(const std::string& arg_sceneName) {
			sceneName = arg_sceneName;
		}
		std::string GetSceneName() {
			return sceneName;
		}
		void Initialize()override {}
		void PreInitialize()override {}
	private:
		std::string sceneName;
	};
	struct SceneChangeInformation :public IObject
	{
	public:
		SceneChangeInformation() {
		}
		void Initialize()override {}
		void PreInitialize()override {}
	private:
	};
	struct SceneRenderingInformation 
	{
	public:
		SceneRenderingInformation() {
		}

		template<class Archive>
		void serialize(Archive& archive)
		{
			ARCHIVE_BUTI(list_renderingPathInfo);
			ARCHIVE_BUTI(layerCount);
		}
		std::vector<Value_ptr<ButiRendering::RenderingPathData>> list_renderingPathInfo;
		std::int32_t layerCount = 1;
	private:
	};


}

#endif // !SCENEINFORMATION_H