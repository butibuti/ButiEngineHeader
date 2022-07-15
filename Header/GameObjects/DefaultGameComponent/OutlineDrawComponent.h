#pragma once
#include"Header/GameObjects/DefaultGameComponent/ModelDrawComponent.h"

namespace ButiEngine {

	class OutlineMeshDrawComponent :public MeshDrawComponent
	{
	public:
		OutlineMeshDrawComponent();
		std::string GetGameComponentName()const override {
			return "OutlineMeshDrawComponent";
		}

		Value_ptr<GameComponent> Clone()override;
		void OnShowUI()override;
		void OnSet()override;

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(m_meshTag);
			archive(m_modelTag);
			archive(m_outlineMeshTag);
			archive(m_outlineModelTag);
			archive(m_materialTag);
			archive(m_outlineMaterialTag);
			archive(isActive);
			BeforeTransformSave();
			archive(m_vlp_transform);
			AfterTransformSave();
			archive(m_vlp_drawInfo);
			archive(m_vlp_outlineDrawInfo);
		}

		void CreateData()override;
	protected:
		MeshTag m_outlineMeshTag;
		ModelTag m_outlineModelTag;
		std::vector<MaterialTag>m_outlineMaterialTag;

		Value_ptr<ButiRendering::ObjectDrawData >m_vlp_outlineDrawInfo = nullptr;

	}; 
	class OutlineModelDrawComponent :public ModelDrawComponent
	{
	public:
		OutlineModelDrawComponent();
		std::string GetGameComponentName() const override {
			return "OutlineModelDrawComponent";
		}

		Value_ptr<GameComponent> Clone()override;
		void OnShowUI()override;
		void OnSet()override;
		Value_ptr<ButiRendering::IModelObject> GetModelData()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(m_meshTag);
			archive(m_modelTag);
			archive(m_outlineMeshTag);
			archive(m_outlineModelTag);
			archive(m_outlineMaterialTag);
			archive(m_materialTag);
			archive(isActive);
			BeforeTransformSave();
			archive(m_vlp_transform);
			AfterTransformSave();
			archive(m_vlp_drawInfo);
			archive(m_vlp_outlineDrawInfo);
		}

		void CreateData()override;
	protected:
		MeshTag m_outlineMeshTag;
		ModelTag m_outlineModelTag;
		std::vector<MaterialTag>m_outlineMaterialTag;

		Value_ptr<ButiRendering::ObjectDrawData >m_vlp_outlineDrawInfo = nullptr;

	};
}


BUTI_REGIST_GAMECOMPONENT(OutlineModelDrawComponent,true)
BUTI_REGIST_GAMECOMPONENT(OutlineMeshDrawComponent,true)