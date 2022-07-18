#ifndef GAMEASSETSTRUCT_H
#define GAMEASSETSTRUCT_H
#include"cereal/cereal.hpp"
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
	bool isFullScreen;
	HINSTANCE hInstance = nullptr;
	template<class Archive>
	void serialize(Archive& archive) {
		archive(CEREAL_NVP(appWindowName), CEREAL_NVP(initSceneName));
		archive(CEREAL_NVP(popType));
		archive(CEREAL_NVP(windowWidth), CEREAL_NVP(windowHeight));
		archive(CEREAL_NVP(isFullScreen));
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
		archive(shaderName);
		archive(vertexShaderTag);
		archive(pixelShaderTag);
		archive(geometryShaderTag);
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
		archive(m_materialName);
		archive(m_value);
		archive(m_vec_textures);
		archive(m_shader);
		archive(m_filePath);
		archive(m_isList);
		archive(m_drawSettings);
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
		archive(m_renderTargetName);
		archive(m_filePath);
		archive(m_width);
		archive(m_height);
		archive(m_format);
		archive(m_color);
	}
};
struct DepthStencilAssetData {
	std::string m_depthStencilName;
	std::string m_filePath = "none";
	std::int32_t m_width, m_height;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_depthStencilName);
		archive(m_filePath);
		archive(m_width);
		archive(m_height);
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
		archive(m_rawDataTextureName);
		archive(m_filePath);
		archive(m_width);
		archive(m_height);
		archive(m_format);
		archive(m_color);
	}
};
struct AssetLoadData
{
	//backupdata
	std::vector<std::string> vec_filePathAndDirectory_tex, vec_filePathAndDirectory_ps, vec_filePathAndDirectory_vs, vec_filePathAndDirectory_gs
		, vec_filePathAndDirectory_cs, vec_filePathAndDirectory_shader, vec_filePathAndDirectory_font, vec_filePathAndDirectory_sound, vec_filePathAndDirectory_model
		, vec_filePathAndDirectory_motion, vec_filePathAndDirectory_script, vec_filePathAndDirectory_gameObject, vec_filePathAndDirectory_material;
	
};
}
}

#endif // !GAMEASSETSTRUCT_H
