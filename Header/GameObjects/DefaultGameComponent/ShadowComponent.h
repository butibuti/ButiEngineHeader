#pragma once
#include"MeshDrawComponent.h"

namespace ButiEngine {

	class ShadowComponent :public MeshDrawComponent
	{
	public:
		ShadowComponent() {}
		std::string GetGameComponentName() {
			return "ShadowComponent";
		}

		void OnSet()override;
		void Start()override;
		Value_ptr<GameComponent> Clone()override;
		void OnShowUI()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			ARCHIVE_BUTI(m_meshTag);
			ARCHIVE_BUTI(m_modelTag);
			ARCHIVE_BUTI(m_materialTag);
			ARCHIVE_BUTI(isActive);
			ARCHIVE_BUTI(m_vlp_transform);
			ARCHIVE_BUTI(m_vlp_drawInfo);
			ARCHIVE_BUTI(vlp_meshDrawComponent);
		}
		void Regist()override;
		void UnRegist()override;
		void CreateData()override;
	protected:
		void RegistShadowDrop(Value_ptr<MeshDrawComponent> arg_vlp_shadowDrop = nullptr);
		Value_ptr<MeshDrawComponent> vlp_meshDrawComponent;

		Value_ptr<ButiRendering::IBoneObject> vlp_bone;
	};
}


BUTI_REGIST_GAMECOMPONENT(ShadowComponent,true)