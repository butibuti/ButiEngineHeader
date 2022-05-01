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
			archive(m_meshTag);
			archive(m_shaderTag);
			archive(m_modelTag);
			archive(m_materialTag);
			archive(isActive);
			archive(m_vlp_transform);
			archive(m_vlp_drawInfo);
			archive(vlp_meshDrawComponent);
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