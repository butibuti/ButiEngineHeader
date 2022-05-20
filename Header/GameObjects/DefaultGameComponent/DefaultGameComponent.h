#pragma once
#ifndef DEFAULTGAMECOMPONENT_H_
#define DEFAULTGAMECOMPONENT_H_

#include "../../GameComponentHeader.h"
#include"Header/Common/CollisionPrimitive.h"
#include"ButiRendering_Dx12/Header/MeshPrimitive.h""
#include"ButiRendering_Dx12/Header/DrawData/IDrawData.h"
namespace ButiScript {
class CompiledData;
class VirtualMachine;
}
namespace ButiEngine {
enum class TextJustified {
	left,right,center
};
namespace ButiRendering {
class Resource_RealTimeMesh;
class ModelAnimation;
class IModelObject;
}
class CameraMan :public  GameComponent {
public:
	void Start() override;
	void OnUpdate()override;
	std::string GetGameComponentName()const override {
		return "CameraMan";
	}
	void ShakeVertical(const float power);
	void ShakeHorizontal(const float power);
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(isActive);
		archive(m_cameraName);
	}
	Value_ptr<GameComponent> Clone()override {
		return ObjectFactory::Create<CameraMan>();
	}
	void OnShowUI()override;
private:
	float m_vertQuake;
	float m_horizonQuake;
	Value_ptr<Transform> m_child;
	std::string m_cameraName = "main";
};
namespace Collision {
enum class CollisionPrimType {
	cube, sphere, capsule
};
class ColliderComponent :public GameComponent
{
public:
	ColliderComponent(Value_ptr<CollisionPrimitive> arg_vlp_collisionPrim, const std::uint32_t arg_layerNum = 0);
	ColliderComponent() {}
	void Initialize()override;
	void OnSet()override;
	void OnUpdate()override;
	void OnRemove()override;
	void Start()override;
	void CollisionStart();
	void CollisionStop();
	std::string GetGameComponentName()const override {
		return "ColliderComponent";
	}
	Value_ptr<GameComponent> Clone()override;
	Value_ptr<CollisionPrimitive> GetCollisionPrimitive();
	void SetCollisionPrimitive(Value_ptr<CollisionPrimitive> arg_vlp_collisionPrim);
	void OnShowUI()override;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_vlp_collisionPrim);
		archive(m_layerNum);
		archive(isActive);
	}
private:
	std::uint32_t m_layerNum = 0;
	Value_ptr<CollisionPrimitive> m_vlp_collisionPrim;
};
}


class TransformAnimation :public GameComponent
{
public:
	std::string GetGameComponentName()const override {
		return "TransformAnimation";
	}
	void OnUpdate()override;
	Value_ptr<Transform> GetInitTransform();
	Value_ptr<Transform> GetTargetTransform();
	virtual void SetInitTransform(Value_ptr<Transform> arg_vlp_InitTransform);
	void SetEaseType(const Easing::EasingType arg_type);
	void SetSpeed(const float arg_speed);
	void SetTime(const float arg_time);
	void SetReverse(const bool arg_isReverse);
	Value_ptr<GameComponent> Clone()override;

	virtual void _cdecl SetTargetTransform(Value_ptr<Transform> arg_vlp_targetTransform);
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(isActive);
		archive(m_speed);
		archive(m_t);
		archive(m_vlp_targetTransform);
		archive(m_vlp_initTransform);
		archive(m_easeType);
		archive(m_isReverse);
	}
	void OnShowUI()override;
	virtual void PositionSet();
	void OnSet()override;
protected:
	std::int32_t m_direction = 1;
	float m_t = 0;
	Value_ptr<Transform> m_vlp_targetTransform;
	Quat m_initRotate;
	Quat m_targetRotate;
	Value_ptr<Transform> m_vlp_initTransform;
	float m_speed = 0.002f;
	Easing::EasingType m_easeType = Easing::EasingType::EaseIn;
	bool m_isReverse = false;
};
class UIAnimation :public TransformAnimation
{
public:
	std::string GetGameComponentName()const override {
		return "UIAnimation";
	}
	void SetInitTransform(Value_ptr<Transform> arg_vlp_InitTransform)override;
	void SetTargetTransform(Value_ptr<Transform> arg_vlp_targetTransform)override;
	Value_ptr<GameComponent> Clone()override;
	void PositionSet()override;
	void OnShowUI()override;
	void OnSet()override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(isActive);
		archive(m_speed);
		archive(m_t);
		archive(m_vlp_targetTransform);
		archive(m_vlp_initTransform);
		archive(m_easeType);
		archive(m_isReverse);
	}
protected:
	Vector2 m_size;
};
class CubeTransformAnimation :public TransformAnimation
{
public:
	std::string GetGameComponentName()const override {
		return "CubeTransformAnimation";
	}
	void SetXEaseType(const Easing::EasingType type);
	void SetYEaseType(const Easing::EasingType type);
	void SetZEaseType(const Easing::EasingType type);
	Value_ptr<GameComponent> Clone()override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(isActive);
		archive(m_speed);
		archive(m_t);
		archive(m_vlp_targetTransform);
		archive(m_vlp_initTransform);
		archive(m_easeType);
		archive(m_xEaseType);
		archive(m_yEaseType);
		archive(m_zEaseType);
		archive(m_isReverse);
	}
	void OnShowUI()override;
	void PositionSet()override;
protected:
	Easing::EasingType m_xEaseType = Easing::EasingType::none;
	Easing::EasingType m_yEaseType = Easing::EasingType::none;
	Easing::EasingType m_zEaseType = Easing::EasingType::none;
};

class FPSViewBehavior :public GameComponent
{
public:
	void Start()override;
	void OnUpdate() override;
	void OnSet()override;
	std::string GetGameComponentName()const override {
		return "FPSViewBehavior";
	};
	Value_ptr<GameComponent> Clone()override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(isActive);
	}
private:
	bool m_isCenter = true;
};
class ChaseComponent :public GameComponent
{
public:
	ChaseComponent(Value_ptr<Transform> arg_vlp_target, const float arg_speed = 0.1f);
	ChaseComponent() {}
	void OnUpdate() override;
	void OnSet()override;
	std::string GetGameComponentName()const override {
		return "ChaseComponent";
	};
	void OnShowUI()override;

	Value_ptr<GameComponent> Clone()override;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_vlp_target);
		archive(m_speed);
		archive(isActive);
	}

private:
	Value_ptr<Transform> m_vlp_target;
	float m_speed;
};
class IKComponent :public GameComponent
{
public:
	IKComponent() {}
	std::string GetGameComponentName()const override {
		return "IKComponent";
	}
	void OnRemove()override;
	void OnSet()override;
	void Start()override;
	Value_ptr<GameComponent> Clone()override;

	void OnShowUI()override;

	void OnUpdate()override;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(isActive);
		archive(m_vec_ikData);
	}


protected:
	void RegistIK();
private:
	Value_ptr<ButiRendering::IModelObject> m_vlp_modelData;
	std::vector<Value_ptr<ButiRendering::Bone>> m_vec_endBones;
	std::vector<Value_ptr<ButiRendering::IKData>> m_vec_ikData;
};


struct Particle2D {
	Vector3 position = Vector3();
	Vector4 color = Vector4(1, 1, 1, 1);
	float size = 5.0f;
	float angle = 0.0f;
	float anglePase = 0.0f;
	Vector3 velocity = Vector3();
	Vector3 force = Vector3();
	float accelation = 0;
	float life = 60.0f,frame=0.0f;
	float sizePase = 0;
	Vector4 colorPase = Vector4();
	std::int8_t currenthorizontal = 0,currentVertcal = 0;
	Value_ptr<Transform> m_parentTransform = nullptr;
};
struct Particle3D {
	Vector3 position = Vector3();
	Vector3 axis = Vector3(1, 0, 0);

	Vector4 color = Vector4(1, 1, 1, 1);
	float size = 5.0f;
	float angle = 0.0f;
	float anglePase = 0.0f;
	Vector3 velocity = Vector3();
	Vector3 force = Vector3();
	float accelation = 0;
	float life = 60;
	Vector4 colorPase = Vector4();
	float sizePase = 0;
	Value_ptr<Transform> m_parentTransform = nullptr;
};


class ImmediateParticleController :public GameComponent
{
public:

	void OnUpdate()override;
	void OnSet()override;
	void Start();
	std::string GetGameComponentName()const override {
		return "ImmediateParticleController";
	}
	void AddParticle(const Particle3D& arg_particle);
	void AddParticle(const Particle3D& arg_particle, Value_ptr<Transform> arg_particleTransform);
	Value_ptr<GameComponent> Clone()override;
	void OnRemove()override;
	List<Particle3D>& GetParticles();
	const List<Particle3D>& GetParticles()const;
	void OnShowUI()override;
	void CreateParticleBuffer();
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(isActive);
		archive(m_meshTag);
	}
private:
	List<Particle3D> m_list_particleInfo;
	MeshTag m_meshTag;
	Value_ptr<ButiRendering::MeshPrimitive<Vertex::Vertex_UV_Normal_Color>> m_vlp_backUp;
	Value_ptr<ButiRendering::Resource_RealTimeMesh> m_vlp_mesh;
	std::int32_t m_addParticleCount = 0;
};
class SpriteParticleController :public GameComponent
{
public:

	void OnUpdate()override;
	void OnSet()override;
	void Start();
	std::string GetGameComponentName()const override {
		return "SpriteParticleController";
	}
	void AddParticle(const Particle2D& arg_particle);
	void AddParticle(const Particle2D& arg_particle, Value_ptr<Transform> arg_particleTransform);
	Value_ptr<GameComponent> Clone()override;
	void OnRemove()override;
	List<Particle2D>& GetParticles();
	const List<Particle2D>& GetParticles()const;
	void OnShowUI()override;
	void CreateParticleBuffer();
	void UpdateBuffer();
	void SetSplitScaleDiv(const std::int32_t arg_horizontalSplitScale, const std::int32_t arg_verticalSplitScale) {
		splitScale.x = 1.0f / arg_horizontalSplitScale;
		splitScale.y = 1.0f / arg_verticalSplitScale;
	}
	void SetHorizontalSplitScale(const std::int32_t arg_horizontalSplitScale, const std::int32_t arg_verticalIndex) {
		if (arg_verticalIndex >= vec_splitCountAndRequiredFrame.size()) {
			vec_splitCountAndRequiredFrame.resize(arg_verticalIndex + 1);
		}

		vec_splitCountAndRequiredFrame[arg_verticalIndex].first = arg_horizontalSplitScale;
	}
	std::int32_t GetHorizontalSplitScale(const std::int32_t arg_verticalIndex) const {
		if (arg_verticalIndex >= vec_splitCountAndRequiredFrame.size()) {
			return -1;
		}
		return vec_splitCountAndRequiredFrame[arg_verticalIndex].first;
	}
	void SetHorizontalRequiredFrame(const std::int32_t arg_frame, const std::int32_t arg_verticalIndex) {
		if (arg_verticalIndex >= vec_splitCountAndRequiredFrame.size()) {
			vec_splitCountAndRequiredFrame.resize(arg_verticalIndex + 1);
		}

		vec_splitCountAndRequiredFrame[arg_verticalIndex].second= arg_frame;
	}
	std::int32_t GetHorizontalRequiredFrame(const std::int32_t arg_verticalIndex) const {
		if (arg_verticalIndex >= vec_splitCountAndRequiredFrame.size()) {
			return -1;
		}
		return vec_splitCountAndRequiredFrame[arg_verticalIndex].second;
	}
	std::int32_t GetVerticalSplitScale() const {
		return vec_splitCountAndRequiredFrame.size();
	}
	Vector2 GetSplitScale()const {
		return splitScale;
	}
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(isActive);
		archive(m_meshTag);
		archive(vec_splitCountAndRequiredFrame);
		archive(splitScale);
	}
private:
	List<Particle2D> m_list_particleInfo;
	MeshTag m_meshTag;
	Value_ptr<ButiRendering::MeshPrimitive<Vertex::Vertex_UV_Normal_Color>> m_vlp_backUp;
	Value_ptr<ButiRendering::Resource_RealTimeMesh> m_vlp_mesh;
	std::int32_t m_addParticleCount = 0;
	std::vector<std::pair< std::int32_t,std::int32_t>> vec_splitCountAndRequiredFrame;
	Value_ptr<ButiRendering::CBuffer<ButiRendering::ObjectInformation>> vlp_param;
	Vector2 splitScale = Vector2(1, 1);
};
class LookAtComponent :public GameComponent
{
public:
	LookAtComponent(Value_ptr<Transform> arg_vlp_lookTarget);
	LookAtComponent() {}

	void OnUpdate()override;
	void OnSet()override;
	void Detach();
	std::string GetGameComponentName()const override {
		return "LookAtComponent";
	}
	Value_ptr<GameComponent> Clone()override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_vlp_lookTarget);
		archive(m_speed);
		archive(isActive);
	}
	void OnShowUI();
	Value_ptr<Transform> GetLookTarget()const;
	void SetLookTarget(Value_ptr<Transform> arg_vlp_target);
	float GetSpeed()const;
	void SetSpeed(const float arg_speed);
private:
	Value_ptr<Transform> m_vlp_lookTarget;
	float m_speed=0.01f;
};
class PostEffectParamUpdater :public GameComponent
{
public:
	PostEffectParamUpdater(const Vector4& pase);
	PostEffectParamUpdater();
	void OnUpdate()override;
	std::string GetGameComponentName()const override {
		return "PostEffectParamUpdater";
	}
	void OnSet();
	void Start();
	Value_ptr<GameComponent> Clone()override;
	void OnShowUI()override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_pase);
		archive(isActive);
	}
private:
	Vector4 m_pase;
	Value_ptr<ButiRendering::CBuffer<ButiRendering::ObjectInformation>> m_vlp_param;
};
class SplineCurveMover :public GameComponent
{
public:
	std::string GetGameComponentName()const override {
		return "SplineCurveMover";
	}
	void OnUpdate()override;
	Value_ptr<GameComponent> Clone()override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(isActive);
		archive(m_speed);
		archive(m_t);
		archive(m_splineCurve);
	}
	void OnShowUI()override;
	void PositionSet();
	void SetSplineCurve(const SplineCurve& arg_curve);
	void SetSpeed(const float spped);
private:

	SplineCurve m_splineCurve;
	float m_t = 0;
	float m_speed = 0.0025f;;
};
class SucideComponent :public GameComponent
{
public:
	SucideComponent(const float arg_count);
	SucideComponent();
	void OnUpdate()override;
	std::string GetGameComponentName()const override {
		return "SucideComponent";
	}
	Value_ptr<GameComponent> Clone()override;
	void OnShowUI()override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_count);
		archive(m_vlp_timer);
		archive(isActive);
	}
private:
	Value_ptr<RelativeTimer> m_vlp_timer;
	float m_count;
};
class UIComponent :public GameComponent
{
public:
	std::string GetGameComponentName()const override {
		return "UIComponent";
	}
	Value_ptr<GameComponent> Clone()override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(isActive);
		archive(m_relativePos);
		archive(m_relativeScale);
	}
	void OnShowUI()override;
	void OnUpdate()override {}
	void OnSet()override;
	void Start()override;
	void SetPosision(const Vector2& arg_relativePos);
	void SetScalse(const Vector2& arg_relativeScale);
protected:
	void SetRelativeTransform();
	Vector2 m_relativePos;
	Vector2 m_relativeScale = Vector2(1, 1);
};

class MeshDrawComponent :public GameComponent
{
public:
	MeshDrawComponent(const MeshTag& arg_meshTag, const ShaderTag& arg_shaderTag, const MaterialTag& arg_materialTag, Value_ptr<ButiRendering::DrawInformation >arg_vlp_drawInfo = nullptr, Value_ptr<Transform> arg_vlp_transform = nullptr);
	MeshDrawComponent(const MeshTag& arg_meshTag, const ShaderTag& arg_shaderTag, const std::vector< MaterialTag>& arg_materialTag, Value_ptr< ButiRendering::DrawInformation >arg_vlp_drawInfo = nullptr, Value_ptr<Transform> arg_vlp_transform = nullptr);
	MeshDrawComponent(const ModelTag& arg_modelTag, const ShaderTag& arg_shaderTag, Value_ptr<ButiRendering::DrawInformation >arg_vlp_drawInfo = nullptr, Value_ptr<Transform> arg_vlp_transform = nullptr);
	MeshDrawComponent(const MeshTag& arg_meshTag, const ModelTag& arg_modelTag, const ShaderTag& arg_shaderTag, const std::vector< MaterialTag>& arg_materialTag, Value_ptr<ButiRendering::DrawInformation >arg_vlp_drawInfo = nullptr, Value_ptr<Transform> arg_vlp_transform = nullptr);
	MeshDrawComponent() {}
	std::string GetGameComponentName()const override {
		return "MeshDraw";
	}
	void OnUpdate()override;
	void OnSet()override;
	void OnRemove() override;
	void SetBlendMode(const ButiRendering::BlendMode& arg_blendMode);
	void SetMaterialTag(MaterialTag  arg_materialTag, const std::int32_t arg_index);
	void SetMeshTag(MeshTag  arg_meshTag);
	void SetModelTag(ModelTag  arg_modelTag);
	void SetShaderTag(ShaderTag  arg_shaderTag);
	const MeshTag& GetMeshTag();
	const ShaderTag& GetShaderTag();
	const ModelTag& GetModelTag();
	const std::vector<MaterialTag>& GetMaterialTag();
	Value_ptr<GameComponent> Clone()override;
	virtual void Regist();
	void ReRegist();
	virtual void UnRegist();
	Value_ptr< ButiRendering::DrawInformation > GetDrawInformation();
	void OnShowUI()override;
	Value_ptr<Transform> GetTransform();

	template <class T>
	Value_ptr<ButiRendering::CBuffer< T>> CreateCBuffer(const std::string& arg_cBufferName, const std::uint32_t arg_slot, Value_weak_ptr<ButiRendering::GraphicDevice> arg_vwp_graphicDevice);
	template <class T>
	Value_ptr<ButiRendering::CBuffer<T>> GetCBuffer(const std::string& arg_cBufferName) {
		return m_data->GetDrawData().GetCBuffer<T>(arg_cBufferName);
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_meshTag);
		archive(m_shaderTag);
		archive(m_modelTag);
		archive(m_materialTag);
		archive(isActive);
		BeforeTransformSave();
		archive(m_vlp_transform);
		AfterTransformSave();
		archive(m_vlp_drawInfo);
	}
protected:
	void ShowDrawSettingsUI(Value_ptr< ButiRendering::DrawInformation >vlp_arg_drawInfo = nullptr, const std::string& arg_settingsName = "");
	void ShowExCBufferUI(Value_ptr<ButiRendering::DrawInformation >vlp_arg_drawInfo = nullptr, const std::string& arg_settingsName = "");
	void BeforeTransformSave();
	void AfterTransformSave();
	Value_ptr< ButiRendering::DrawObject > m_data;
	virtual void CreateData();
	MeshTag m_meshTag;
	ShaderTag m_shaderTag;
	ModelTag m_modelTag;
	Value_ptr<Transform> m_vlp_transform;
	Value_ptr< ButiRendering::DrawInformation >m_vlp_drawInfo = nullptr;
	std::vector<MaterialTag> m_materialTag;

	bool isCereal = true;
};
class MeshDrawComponent_Static :public MeshDrawComponent
{
public:
	MeshDrawComponent_Static(const MeshTag& arg_meshTag, const ShaderTag& arg_shaderTag, const MaterialTag& arg_materialTag, Value_ptr< ButiRendering::DrawInformation >arg_vlp_drawInfo = nullptr, Value_ptr<Transform> arg_vlp_transform = nullptr);
	MeshDrawComponent_Static(const MeshTag& arg_meshTag, const ShaderTag& arg_shaderTag, const std::vector< MaterialTag>& arg_materialTag, Value_ptr< ButiRendering::DrawInformation >arg_vlp_drawInfo = nullptr, Value_ptr<Transform> arg_vlp_transform = nullptr);
	MeshDrawComponent_Static(const ModelTag& arg_modelTag, const ShaderTag& arg_shaderTag, Value_ptr<ButiRendering::DrawInformation >arg_vlp_drawInfo = nullptr, Value_ptr<Transform> arg_vlp_transform = nullptr);
	MeshDrawComponent_Static(const MeshTag& arg_meshTag, const ModelTag& arg_modelTag, const ShaderTag& arg_shaderTag, const std::vector< MaterialTag>& arg_materialTag, Value_ptr< ButiRendering::DrawInformation >arg_vlp_drawInfo = nullptr, Value_ptr<Transform> arg_vlp_transform = nullptr);
	MeshDrawComponent_Static() {}
	std::string GetGameComponentName()const override {
		return "MeshDraw_Static";
	}
	void OnUpdate()override;
	Value_ptr<GameComponent> Clone()override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_meshTag);
		archive(m_shaderTag);
		archive(m_modelTag);
		archive(m_materialTag);
		archive(isActive);
		BeforeTransformSave();
		archive(m_vlp_transform);
		AfterTransformSave();
		archive(m_vlp_drawInfo);
	}
protected:
};
class TextDrawComponent :public MeshDrawComponent
{
public:
	TextDrawComponent() {}
	std::string GetGameComponentName()const override {
		return "TextDrawComponent";
	}
	void OnSet()override;

	Value_ptr<GameComponent> Clone()override;
	void OnShowUI()override;
	const std::string& GetText()const {
		return m_text;
	}
	void OnRemove()override;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(m_fontTag);
		archive(m_text);
		archive(m_shaderTag);
		archive(m_modelTag);
		archive(m_materialTag);
		archive(isActive);
		archive(m_vlp_transform);
		archive(m_vlp_drawInfo);
		archive(m_map_size);
		archive(m_map_color);
		archive(m_textMeshSize);
		archive(m_just);
	}
	void SetText(const std::string& arg_text);
	void SetText(const std::string& arg_text,const Vector4& arg_color);

	void SetSize( const float arg_size);
	void SetSize(const std::int32_t  arg_index, const float arg_size);
	void SetSize(const std::string& arg_text, const float arg_size);
	float GetSize(const std::int32_t arg_index)const;

	void SetColor(const std::int32_t arg_index, const Vector4& arg_color);
	void SetColor(const Vector4& arg_color);
	void SetColor(const std::string& arg_text, const Vector4& arg_color);
	Vector4 GetColor(const std::int32_t arg_index)const;

	void CreateTextMesh();
protected:
	FontTag m_fontTag;
	std::map< std::int32_t, float > m_map_size;
	std::map< std::int32_t, Vector4> m_map_color;
	std::string m_text;
	std::int32_t m_textMeshSize = 256;
	TextJustified m_just=TextJustified::left;
	Value_ptr<ButiRendering::Resource_RealTimeMesh> m_vlp_mesh;
};




}


BUTI_REGIST_GAMECOMPONENT(MeshDrawComponent,true)
BUTI_REGIST_GAMECOMPONENT(MeshDrawComponent_Static,true)
BUTI_REGIST_GAMECOMPONENT(TextDrawComponent,false)

BUTI_REGIST_GAMECOMPONENT(UIComponent, true)

CEREAL_REGISTER_POLYMORPHIC_RELATION(ButiEngine::MeshDrawComponent, ButiEngine::MeshDrawComponent_Static);

BUTI_REGIST_GAMECOMPONENT(Collision::ColliderComponent,true)
BUTI_REGIST_GAMECOMPONENT(SucideComponent,true)
BUTI_REGIST_GAMECOMPONENT(TransformAnimation,true)


BUTI_REGIST_GAMECOMPONENT(CameraMan,true)
BUTI_REGIST_GAMECOMPONENT(CubeTransformAnimation,true)

BUTI_REGIST_GAMECOMPONENT(FPSViewBehavior,true);

BUTI_REGIST_GAMECOMPONENT(IKComponent,true)

BUTI_REGIST_GAMECOMPONENT(ImmediateParticleController, true)
BUTI_REGIST_GAMECOMPONENT(SpriteParticleController,true)
BUTI_REGIST_GAMECOMPONENT(LookAtComponent,true)
BUTI_REGIST_GAMECOMPONENT(PostEffectParamUpdater,true)
BUTI_REGIST_GAMECOMPONENT(SplineCurveMover,true)
BUTI_REGIST_GAMECOMPONENT(UIAnimation,true)
BUTI_REGIST_GAMECOMPONENT(ChaseComponent,true)


#endif // !DEFAULTGAMECOMPONENT_H_