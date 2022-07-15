#ifndef RESOURCE_EXPLORER
#define RESOURCE_EXPLORER
namespace ButiEngine {
class ResourceExplorer {
public:
	ResourceExplorer(Value_ptr<ButiRendering::GraphicDevice> arg_vlp_graphicDevice, Value_weak_ptr<IResourceContainer>arg_vwp_resourceContainer);
	~ResourceExplorer();
	void GUI();
private:
	class Impl;
	Impl* m_p_impl=nullptr;
};
}
#endif // !RESOURCE_EXPLORER
