#ifndef GAMEASSETSTRUCT_H
#define GAMEASSETSTRUCT_H

#include "../../ButiCereal/include/cereal/cereal.hpp"
namespace ButiEngine {
enum class WindowPopType {
	normal = SW_SHOWNORMAL, max = SW_SHOWMAXIMIZED
};
namespace GameAssetData {
//アプリケーション初期化用構造体
struct ApplicationInitData {
	std::string appWindowName = "ButiEngine";
	std::string initSceneName = "Default";
	WindowPopType popType = WindowPopType::normal;
	std::int32_t windowWidth = 1920, windowHeight = 1080;
	bool isFullScreen=false,isUseVRTracker=false;
	Vector4 backGroundColor = Vector4(0, 0, 0, 1);
	HINSTANCE hInstance = nullptr;
	template<class Archive>
	void serialize(Archive& archive) {
		ARCHIVE_BUTI(appWindowName);
		ARCHIVE_BUTI(initSceneName);
		ARCHIVE_BUTI(popType);
		ARCHIVE_BUTI(windowWidth);
		ARCHIVE_BUTI(windowHeight);
		ARCHIVE_BUTI(isFullScreen);
		ARCHIVE_BUTI(isUseVRTracker);
		ARCHIVE_BUTI(backGroundColor);
	}
};

struct ShaderAssetData {
	std::string shaderName;
	VertexShaderTag vertexShaderTag;
	PixelShaderTag pixelShaderTag;
	GeometryShaderTag geometryShaderTag;
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(shaderName);
		ARCHIVE_BUTI(vertexShaderTag);
		ARCHIVE_BUTI(pixelShaderTag);
		ARCHIVE_BUTI(geometryShaderTag);
	}
};
struct MaterialAssetData {
	MaterialAssetData() {}
	std::string m_materialName;
	std::string m_filePath = "none";
	ButiRendering::MaterialValue m_value;
	std::vector<TextureTag> m_vec_textures;
	ShaderTag m_shader;
	bool m_isList = false;
	ButiRendering::DrawSettings m_drawSettings;
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(m_materialName);
		ARCHIVE_BUTI(m_value);
		ARCHIVE_BUTI(m_vec_textures);
		ARCHIVE_BUTI(m_shader);
		ARCHIVE_BUTI(m_filePath);
		ARCHIVE_BUTI(m_isList);
		ARCHIVE_BUTI(m_drawSettings);
	}
};
struct RenderTargetAssetData {
	std::string m_renderTargetName;
	std::string m_filePath = "none";
	std::int32_t m_width, m_height, m_format = static_cast<std::int32_t>(ButiRendering::Format::R8G8B8A8_UNORM);
	Vector4 m_color;
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(m_renderTargetName);
		ARCHIVE_BUTI(m_filePath);
		ARCHIVE_BUTI(m_width);
		ARCHIVE_BUTI(m_height);
		ARCHIVE_BUTI(m_format);
		ARCHIVE_BUTI(m_color);
	}
};
struct DepthStencilAssetData {
	std::string m_depthStencilName;
	std::string m_filePath = "none";
	std::int32_t m_width, m_height;
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(m_depthStencilName);
		ARCHIVE_BUTI(m_filePath);
		ARCHIVE_BUTI(m_width);
		ARCHIVE_BUTI(m_height);
	}
};
struct RawDataTextureAssetData {
	std::string m_rawDataTextureName;
	std::string m_filePath = "none";
	std::int32_t m_width, m_height, m_format;
	Vector4 m_color;
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(m_rawDataTextureName);
		ARCHIVE_BUTI(m_filePath);
		ARCHIVE_BUTI(m_width);
		ARCHIVE_BUTI(m_height);
		ARCHIVE_BUTI(m_format);
		ARCHIVE_BUTI(m_color);
	}
};
struct AssetLoadData
{
	//backupdata
	List<std::string> vec_filePathAndDirectory_tex, vec_filePathAndDirectory_ps, vec_filePathAndDirectory_vs, vec_filePathAndDirectory_gs
		, vec_filePathAndDirectory_cs, vec_filePathAndDirectory_shader, vec_filePathAndDirectory_font, vec_filePathAndDirectory_sound, vec_filePathAndDirectory_model
		, vec_filePathAndDirectory_motion, vec_filePathAndDirectory_script, vec_filePathAndDirectory_gameObject, vec_filePathAndDirectory_material,vec_scriptSource;
	
};
}
}

#endif // !GAMEASSETSTRUCT_H
