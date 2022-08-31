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
	std::vector<TextureTag> m_vec_rendertarget;
	std::vector<TextureTag> m_vec_shadowTextures;
	std::vector<TextureTag> m_vec_staticShadowTextures;
	TextureTag m_depthStencil;
	bool m_isPlayActive=true, m_isEditActive=false;
	Value_ptr<IRenderingPath> CreateRenderingPath(Value_ptr<IRenderer> arg_vlp_renderer, Value_ptr<GraphicDevice> arg_vlp_graphicDevice, Value_ptr<IScene> arg_vlp_scene)override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_vlp_cameraTransform);
		archive(m_vlp_cameraProp);
		archive(m_layer);
		archive(m_vec_rendertarget);
		archive(m_vec_shadowTextures);
		archive(m_vec_staticShadowTextures);
		archive(m_depthStencil);
		archive(m_isPlayActive);
		archive(m_isEditActive);
	}
};
struct DeferredCameraRenderingPathData :public RenderingPathData {
	Value_ptr<Transform> m_vlp_cameraTransform;
	Value_ptr<CameraProperty> m_vlp_cameraProp;
	std::string m_forwardCameraPathName;
	std::vector<TextureTag> m_vec_rendertarget;
	TextureTag m_depthStencil;
	bool m_isPlayActive = true, m_isEditActive = false;
	Value_ptr<IRenderingPath> CreateRenderingPath(Value_ptr<IRenderer> arg_vlp_renderer, Value_ptr<GraphicDevice> arg_vlp_graphicDevice, Value_ptr<IScene> arg_vlp_scene)override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_vlp_cameraTransform);
		archive(m_vlp_cameraProp);
		archive(m_forwardCameraPathName);
		archive(m_layer);
		archive(m_vec_rendertarget);
		archive(m_depthStencil);
		archive(m_isPlayActive);
		archive(m_isEditActive);
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
