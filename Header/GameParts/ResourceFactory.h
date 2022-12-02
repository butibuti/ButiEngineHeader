#pragma once
#include"stdafx.h"

namespace ButiEngine {

class ResourceFactory :public IObject {
public:
	virtual Value_ptr<ButiRendering::IResource_Texture> CreateTextureFromPixelData(Value_ptr<ImageFileIO::TextureResourceData> arg_data) = 0;
	virtual Value_ptr<ButiRendering::IResource_Texture> CreateTextureFromPixelData(void* arg_p_pixelSrc, const std::int32_t arg_width, const std::int32_t arg_height, const std::int32_t arg_pixelSize, const std::int32_t arg_format) = 0;
	virtual Value_ptr<ButiRendering::IResource_Texture> CreateEmptyTexture(const std::uint32_t width, const std::uint32_t height) = 0;
	virtual Value_ptr<ButiRendering::Resource_DynamicMesh> CreateDynamicMesh(const std::string& arg_meshName, const List< ButiEngine::Value_ptr< ButiRendering::MeshPrimitiveBase>>& arg_list_vlp_inputMeshData) = 0;

	Value_ptr<ButiRendering::IResource_Model>CreateModel(Value_ptr<IBinaryReader> arg_reader, const std::string& arg_modelPath);
	Value_ptr<ButiRendering::IResource_Model>CreateModel(const std::string& arg_modelPath) {
		auto reader = make_value<BinaryReader_File>(GlobalSettings::GetResourceDirectory() + arg_modelPath);
		auto output = CreateModel(reader,arg_modelPath);
		return output;
	}
	Value_ptr<ButiRendering::IResource_Motion>CreateMotion(Value_ptr<IBinaryReader> arg_reader);
	Value_ptr<ButiRendering::IResource_Motion>CreateMotion(const std::string& arg_modelPath) {
		auto reader = make_value<BinaryReader_File>(GlobalSettings::GetResourceDirectory() + arg_modelPath);
		auto output = CreateMotion(reader);
		return output;
	}
protected:
	ResourceFactory(Value_weak_ptr<ButiRendering::GraphicDevice> arg_vwp_graphicDevice, Value_weak_ptr<IResourceContainer> arg_vwp_resourceContainer) {
		vwp_graphicDevice = arg_vwp_graphicDevice;
		vwp_resourceContainer = arg_vwp_resourceContainer;
	}
	Value_weak_ptr<ButiRendering::GraphicDevice> vwp_graphicDevice;
	Value_weak_ptr<IResourceContainer> vwp_resourceContainer;
private:
};
}