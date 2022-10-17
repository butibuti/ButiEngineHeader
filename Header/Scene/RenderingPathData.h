#ifndef _RENDERINGPATHDATA_H
#define _RENDERINGPATHDATA_H
#include"Header/Common/CerealUtil.h"
namespace ButiEngine {
namespace ButiRendering {

/// <summary>
/// RendererÇÃGUIÇÃåƒÇ—èoÇµ
/// </summary>
void RendererGUI(Value_ptr<IRenderer> arg_vlp_renderer, Value_ptr<IScene> arg_vlp_scene);

struct RenderingPathData :public IObject {
	virtual Value_ptr<IRenderingPath> CreateRenderingPath(Value_ptr<IRenderer> arg_vlp_renderer, Value_ptr<GraphicDevice> arg_vlp_graphicDevice, Value_ptr<IScene> arg_vlp_scene) = 0;
	std::int32_t m_layer=0;
};
struct ForwardCameraRenderingPathData :public RenderingPathData {
	Value_ptr<Transform> m_vlp_cameraTransform;
	Value_ptr<CameraProperty> m_vlp_cameraProp;
	List<TextureTag> m_list_rendertarget;
	List<TextureTag> m_list_shadowTextures;
	List<TextureTag> m_list_staticShadowTextures;
	TextureTag m_depthStencil;
	bool m_isPlayActive=true, m_isEditActive=false;
	Value_ptr<IRenderingPath> CreateRenderingPath(Value_ptr<IRenderer> arg_vlp_renderer, Value_ptr<GraphicDevice> arg_vlp_graphicDevice, Value_ptr<IScene> arg_vlp_scene)override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(m_vlp_cameraTransform);
		ARCHIVE_BUTI(m_vlp_cameraProp);
		ARCHIVE_BUTI(m_layer);
		ARCHIVE_BUTI(m_list_rendertarget);
		ARCHIVE_BUTI(m_list_shadowTextures);
		ARCHIVE_BUTI(m_list_staticShadowTextures);
		ARCHIVE_BUTI(m_depthStencil);
		ARCHIVE_BUTI(m_isPlayActive);
		ARCHIVE_BUTI(m_isEditActive);
	}
};
struct DeferredCameraRenderingPathData :public RenderingPathData {
	Value_ptr<Transform> m_vlp_cameraTransform;
	Value_ptr<CameraProperty> m_vlp_cameraProp;
	std::string m_forwardCameraPathName;
	List<TextureTag> m_list_rendertarget;
	TextureTag m_depthStencil;
	bool m_isPlayActive = true, m_isEditActive = false;
	Value_ptr<IRenderingPath> CreateRenderingPath(Value_ptr<IRenderer> arg_vlp_renderer, Value_ptr<GraphicDevice> arg_vlp_graphicDevice, Value_ptr<IScene> arg_vlp_scene)override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		ARCHIVE_BUTI(m_vlp_cameraTransform);
		ARCHIVE_BUTI(m_vlp_cameraProp);
		ARCHIVE_BUTI(m_forwardCameraPathName);
		ARCHIVE_BUTI(m_layer);
		ARCHIVE_BUTI(m_list_rendertarget);
		ARCHIVE_BUTI(m_depthStencil);
		ARCHIVE_BUTI(m_isPlayActive);
		ARCHIVE_BUTI(m_isEditActive);
	}
};
Value_ptr<RenderingPathData> CreateRenderingPathData(Value_ptr<IRenderingPath> arg_vlp_renderingPath);

bool CameraEditGUI(Value_ptr<IRenderingPath> arg_renderingPath, Value_ptr<IResourceContainer> arg_container);



}
}


CEREAL_REGISTER_TYPE(ButiEngine::ButiRendering::RenderingPathData);
CEREAL_REGISTER_TYPE(ButiEngine::ButiRendering::ForwardCameraRenderingPathData);
CEREAL_REGISTER_TYPE(ButiEngine::ButiRendering::DeferredCameraRenderingPathData);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ButiEngine::ButiRendering::RenderingPathData, ButiEngine::ButiRendering::ForwardCameraRenderingPathData);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ButiEngine::ButiRendering::RenderingPathData, ButiEngine::ButiRendering::DeferredCameraRenderingPathData);
#endif // !_RENDERINGPATHDATA_H
