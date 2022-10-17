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
			ARCHIVE_BUTI(m_meshTag);
			ARCHIVE_BUTI(m_modelTag);
			ARCHIVE_BUTI(m_outlineMeshTag);
			ARCHIVE_BUTI(m_outlineModelTag);
			ARCHIVE_BUTI(m_materialTag);
			ARCHIVE_BUTI(m_outlineMaterialTag);
			ARCHIVE_BUTI(isActive);
			BeforeTransformSave();
			ARCHIVE_BUTI(m_vlp_transform);
			AfterTransformSave();
			ARCHIVE_BUTI(m_vlp_drawInfo);
			ARCHIVE_BUTI(m_vlp_outlineDrawInfo);
			ARCHIVE_BUTI(m_layer);
		}

		void CreateData()override;
	protected:
		MeshTag m_outlineMeshTag;
		ModelTag m_outlineModelTag;
		List<MaterialTag>m_outlineMaterialTag;

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
			ARCHIVE_BUTI(m_meshTag);
			ARCHIVE_BUTI(m_modelTag);
			ARCHIVE_BUTI(m_outlineMeshTag);
			ARCHIVE_BUTI(m_outlineModelTag);
			ARCHIVE_BUTI(m_outlineMaterialTag);
			ARCHIVE_BUTI(m_materialTag);
			ARCHIVE_BUTI(isActive);
			BeforeTransformSave();
			ARCHIVE_BUTI(m_vlp_transform);
			AfterTransformSave();
			ARCHIVE_BUTI(m_vlp_drawInfo);
			ARCHIVE_BUTI(m_vlp_outlineDrawInfo);
		}

		void CreateData()override;
	protected:
		MeshTag m_outlineMeshTag;
		ModelTag m_outlineModelTag;
		List<MaterialTag>m_outlineMaterialTag;

		Value_ptr<ButiRendering::ObjectDrawData >m_vlp_outlineDrawInfo = nullptr;

	};
}


BUTI_REGIST_GAMECOMPONENT(OutlineModelDrawComponent,true)
BUTI_REGIST_GAMECOMPONENT(OutlineMeshDrawComponent,true)