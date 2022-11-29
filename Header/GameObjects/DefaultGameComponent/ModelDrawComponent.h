#pragma once
#include"MeshDrawComponent.h"

namespace ButiEngine {
namespace ButiRendering {
class ModelAnimation;
class IModelObject;
}
	class ModelDrawComponent :public MeshDrawComponent
	{
	public:
		ModelDrawComponent(const ModelTag& arg_modelTag,  Value_ptr< ButiRendering::ObjectDrawData >arg_vlp_drawInfo,  Value_ptr<Transform> arg_vlp_transform = nullptr);
		ModelDrawComponent() {}
		std::string GetGameComponentName()const override {
			return "ModelDraw";
		}

		virtual Value_ptr<ButiRendering::IModelObject> GetModelData();
		Value_ptr<GameComponent> Clone()override;
		Value_ptr<ButiRendering::IBoneObject> GetBone();
		void OnShowUI()override;


		template<class Archive>
		void serialize(Archive& archive)
		{
			ARCHIVE_BUTI(m_meshTag);
			ARCHIVE_BUTI(m_modelTag);
			ARCHIVE_BUTI(m_materialTag);
			ARCHIVE_BUTI(isActive);
			BeforeTransformSave();
			ARCHIVE_BUTI(m_vlp_transform);
			AfterTransformSave();
			ARCHIVE_BUTI(m_vlp_drawInfo);
			ARCHIVE_BUTI(m_layer);
		}


	protected:
		Value_ptr<ButiRendering::IBoneObject> vlp_bone;
		void CreateData()override;
		Value_ptr<ButiRendering::IModelObject> vlp_modelData;
	private:
	};

}

BUTI_REGIST_GAMECOMPONENT(ModelDrawComponent,true)

CEREAL_REGISTER_POLYMORPHIC_RELATION(ButiEngine::MeshDrawComponent, ButiEngine::ModelDrawComponent);