#pragma once
#ifndef CollisionPrim_H
#define CollisionPrim_H
#include<memory>

#include"ButiMath/Geometry.h"
namespace ButiEngine {
namespace Collision {
class CollisionPrimitive_Point;
class CollisionPrimitive_Sphere;
class CollisionPrimitive_Box_AABB;
class CollisionPrimitive_Box_OBB;
class CollisionPrimitive_Polygon;
class CollisionPrimitive_Surface;
class CollisionPrimitive_PLane;
class CollisionPrimitive_Ray;
class CollisionPrimitive_Segment;
class CollisionPrimitive_Capsule;
class CollisionPrimitive :public IObject
{
public:
	void Initialize() override {}
	void PreInitialize()override {}
	virtual void Update() = 0;
	virtual bool IsHit(Value_weak_ptr< CollisionPrimitive> other) = 0;

	virtual bool IsHitPoint(CollisionPrimitive_Point* other) { return false; }
	virtual bool IsHitPolygon(CollisionPrimitive_Polygon* other) { return false; }
	virtual bool IsHitSurface(CollisionPrimitive_Surface* other) { return false; }
	virtual bool IsHitSphere(CollisionPrimitive_Sphere* other) { return false; }
	virtual bool IsHitBox_AABB(CollisionPrimitive_Box_AABB* other) { return false; }
	virtual bool IsHitBox_OBB(CollisionPrimitive_Box_OBB* other) { return false; }
	virtual bool IsHitRay(CollisionPrimitive_Ray* other) { return false; }
	virtual bool IsHitSegment(CollisionPrimitive_Segment* other) { return false; }
	virtual bool IsHitCapsule(CollisionPrimitive_Capsule* other) { return false; }
	virtual void GetMaxPointAndMinPoint(Vector3& arg_outputMax, Vector3& arg_outputMin) const = 0;
	virtual Value_ptr<CollisionPrimitive> Clone() = 0;
	virtual void ShowUI() = 0;
	Value_ptr<Transform> vlp_transform;
};
class CollisionPrimitive_Point :public CollisionPrimitive
{
public:
	inline CollisionPrimitive_Point(Value_ptr<Transform> arg_vlp_transform)
	{
		vlp_transform = arg_vlp_transform;
	}
	CollisionPrimitive_Point() {}
	inline void Update()override {
	}
	inline Vector3 GetPosition() {
		return vlp_transform->GetWorldPosition();
	}
	inline bool IsHit(Value_weak_ptr< CollisionPrimitive> other)override
	{
		return other.lock()->IsHitPoint(this);


	}
	inline void GetMaxPointAndMinPoint(Vector3& arg_outputMax, Vector3& arg_outputMin) const override {
		auto point = vlp_transform->GetWorldPosition();
		arg_outputMax = point;
		arg_outputMin = point;
	}
	bool IsHitPoint(CollisionPrimitive_Point* other)override;
	bool IsHitSphere(CollisionPrimitive_Sphere* other)override;
	bool IsHitBox_AABB(CollisionPrimitive_Box_AABB* other)override;
	bool IsHitBox_OBB(CollisionPrimitive_Box_OBB* other)override;
	bool IsHitPolygon(CollisionPrimitive_Polygon* other)override;
	bool IsHitSurface(CollisionPrimitive_Surface* other)override;

	Value_ptr<CollisionPrimitive> Clone()override {
		return ObjectFactory::Create<CollisionPrimitive_Point>();
	}

	void ShowUI() override {
#ifdef BUTIENGINEBUILD
		GUI::BulletText("Point");
#endif // BUTIENGINEBUILD

	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(vlp_transform);
	}

private:
};
class CollisionPrimitive_Ray :public CollisionPrimitive, public Line
{
public:
	inline CollisionPrimitive_Ray(Value_ptr<Transform> arg_vlp_transform, const Vector3& arg_velocity)
	{
		vlp_transform = arg_vlp_transform;
		initVelocity = arg_velocity;
	}
	CollisionPrimitive_Ray() {}


	bool IsHitSphere(CollisionPrimitive_Sphere* other)override;
	bool IsHitPolygon(CollisionPrimitive_Polygon* other)override;
	bool IsHitSurface(CollisionPrimitive_Surface* other)override;
	bool IsHitBox_AABB(CollisionPrimitive_Box_AABB* other)override;
	bool IsHitBox_OBB(CollisionPrimitive_Box_OBB* other)override;
	inline void Update()override {
		point = vlp_transform->GetWorldPosition();
		velocity = initVelocity;
		vlp_transform->GetRotatedVector(velocity);
	}
	inline bool IsHit(Value_weak_ptr< CollisionPrimitive> other)override
	{
		return other.lock()->IsHitRay(this);


	}
	inline void GetMaxPointAndMinPoint(Vector3& arg_outputMax, Vector3& arg_outputMin) const override {
		arg_outputMax = Vector3(0, 0, 0);
		arg_outputMin = Vector3(0, 0, 0);
	}

	Value_ptr<CollisionPrimitive> Clone()override {
		auto ret = ObjectFactory::Create< CollisionPrimitive_Ray>();
		ret->initVelocity = initVelocity;
		ret->vlp_transform = vlp_transform;
		return ret;
	}

	void ShowUI() override {
#ifdef BUTIENGINEBUILD
		GUI::BulletText("Ray");
		if (GUI::DragFloat3("##rayVelocity", &initVelocity.x, 0.01f, -500, 500)) {
			initVelocity.Normalize();
		}
#endif
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(vlp_transform);
		archive(initVelocity);
	}

private:
	Vector3 initVelocity;
};
class CollisionPrimitive_Segment :public CollisionPrimitive, public Segment
{
public:
	inline CollisionPrimitive_Segment(Value_ptr<Transform> arg_vlp_transform, const Vector3& arg_endPoint)
	{
		vlp_transform = arg_vlp_transform;
		point = vlp_transform->GetWorldPosition();
		endPos = arg_endPoint;
		velocity = ((Vector3)(endPos - point)).GetNormalize();
	}
	inline CollisionPrimitive_Segment()
	{
	}
	inline void Update()override {
		point = vlp_transform->GetWorldPosition();
		velocity = ((Vector3)(endPos - point)).GetNormalize();
	}
	inline bool IsHit(Value_weak_ptr< CollisionPrimitive> other)override
	{
		return other.lock()->IsHitSegment(this);


	}
	inline void GetMaxPointAndMinPoint(Vector3& arg_outputMax, Vector3& arg_outputMin) const override {/*
		arg_outputMax = Vector3(max(point.x,endPos.x) , max(point.y, endPos.y), max(point.z, endPos.z));
		arg_outputMin = Vector3(min(point.x, endPos.x), min(point.y, endPos.y), min(point.z, endPos.z));*/
		arg_outputMax = Vector3();
		arg_outputMin = Vector3();
	}


	bool IsHitBox_AABB(CollisionPrimitive_Box_AABB* other)override;
	bool IsHitBox_OBB(CollisionPrimitive_Box_OBB* other)override;

	Value_ptr<CollisionPrimitive> Clone()override {
		auto ret = ObjectFactory::Create< CollisionPrimitive_Segment>();
		ret->endPos = endPos;
		ret->vlp_transform = vlp_transform;
		return ret;
	}

	void ShowUI() override {

#ifdef BUTIENGINEBUILD
		GUI::BulletText("Ray");
		if (GUI::DragFloat3("##EndPoint", endPos, 0.01f, -500, 500)) {
		}
#endif
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(vlp_transform);
		archive(endPos);
	}

private:
};
class CollisionPrimitive_Sphere :public CollisionPrimitive, public Geometry::Sphere
{
public:
	inline CollisionPrimitive_Sphere(const float arg_radius, Value_ptr<Transform> arg_vlp_transform)
		:Geometry::Sphere(arg_radius) {
		vlp_transform = arg_vlp_transform;
	}
	CollisionPrimitive_Sphere() {}
	inline void Update()override {
		position = vlp_transform->GetWorldPosition();
		radius =originRadius* vlp_transform->GetWorldScale().x;
	}
	inline bool IsHit(Value_weak_ptr< CollisionPrimitive> other)override
	{
		return other.lock()->IsHitSphere(this);
	}
	inline void GetMaxPointAndMinPoint(Vector3& arg_outputMax, Vector3& arg_outputMin) const {
		arg_outputMax = position + Vector3(radius, radius, radius);
		arg_outputMin = position - Vector3(radius, radius, radius);
	}
	bool IsHitPoint(CollisionPrimitive_Point* other)override;
	bool IsHitSphere(CollisionPrimitive_Sphere* other)override;
	bool IsHitBox_AABB(CollisionPrimitive_Box_AABB* other)override;
	bool IsHitBox_OBB(CollisionPrimitive_Box_OBB* other)override;
	bool IsHitPolygon(CollisionPrimitive_Polygon* other)override;
	bool IsHitSurface(CollisionPrimitive_Surface* other)override;
	bool IsHitCapsule(CollisionPrimitive_Capsule* other)override;
	bool IsHitRay(CollisionPrimitive_Ray* other)override;
	Value_ptr<CollisionPrimitive> Clone()override {
		auto ret = ObjectFactory::Create<CollisionPrimitive_Sphere>();
		ret->originRadius = originRadius;
		return ret;
	}
	void ShowUI() override {

#ifdef BUTIENGINEBUILD
		if (GUI::TreeNode("Sphere")) {
			GUI::BulletText("radius");
			GUI::DragFloat("##radius", &originRadius, 0.01, 0, 500);
			GUI::TreePop();
		}
#endif
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(vlp_transform);
		archive(originRadius);
	}
private:
	float originRadius = 0.5f;
};
class CollisionPrimitive_Capsule :public CollisionPrimitive, public Geometry::Capsule
{
public:
	inline CollisionPrimitive_Capsule(const float arg_radius, const Segment& arg_segment, Value_ptr<Transform> arg_vlp_transform)
		:Geometry::Capsule(arg_segment, arg_radius) {
		vlp_transform = arg_vlp_transform;
		length = arg_segment.velocity.y;
	}
	CollisionPrimitive_Capsule() :Geometry::Capsule(Segment(), 0) {}
	inline void Update()override {
		auto pos = vlp_transform->GetWorldPosition();
		auto rotation = vlp_transform->GetWorldRotation();
		s.endPos = pos + (Vector3Const::YAxis * length * 0.5) * rotation;
		s.point = pos - (Vector3Const::YAxis * length * 0.5) * rotation;
		r = initR * vlp_transform->GetWorldScale().x;
	}
	inline bool IsHit(Value_weak_ptr< CollisionPrimitive> other)override
	{
		return other.lock()->IsHitCapsule(this);


	}
	inline void GetMaxPointAndMinPoint(Vector3& arg_outputMax, Vector3& arg_outputMin) const {
		arg_outputMax = s.point + Vector3(r, r, r);
		arg_outputMin = s.endPos - Vector3(r, r, r);
	}
	bool IsHitSphere(CollisionPrimitive_Sphere* other)override;
	Value_ptr<CollisionPrimitive> Clone()override {
		auto ret = ObjectFactory::Create<CollisionPrimitive_Capsule>();
		ret->r = r;
		ret->initR = initR;
		ret->length = length;
		ret->s = s;
		return ret;
	}
	void ShowUI() override {

#ifdef BUTIENGINEBUILD
		if (GUI::TreeNode("Capsule")) {
			GUI::BulletText("radius");
			GUI::DragFloat("##radius", initR, 0.01f, 0.0f, 500.0f);
			GUI::BulletText("height");

			GUI::DragFloat("##length", length, 0.01f, 0.0f, 500.0f);
			GUI::TreePop();
		}
#endif
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(vlp_transform);
		archive(initR);
		archive(length);
	}
private:
	float length;
	float initR;
};


class CollisionPrimitive_Polygon :public CollisionPrimitive
{
public:
	inline CollisionPrimitive_Polygon(const Vector3& arg_vertex1, const Vector3& arg_vertex2, const Vector3& arg_vertex3, Value_ptr<Transform> arg_vlp_transform)
	{
		vlp_transform = arg_vlp_transform;
		points.push_back(arg_vertex1);
		points.push_back(arg_vertex2);
		points.push_back(arg_vertex3);

		initPoints = points;
		Update();
	}
	CollisionPrimitive_Polygon() {}
	void Initialize()override {
		points.resize(initPoints.size());
	}
	inline void Update()override {
		for (std::int32_t i = 0; i < 3; i++) {
			points[i] = initPoints[i] + vlp_transform->GetWorldPosition();
		}
	}
	inline Vector3 GetPosition() {
		return vlp_transform->GetWorldPosition();
	}
	inline bool IsHit(Value_weak_ptr< CollisionPrimitive> other)override
	{
		return other.lock()->IsHitPolygon(this);


	}
	inline void GetMaxPointAndMinPoint(Vector3& arg_outputMax, Vector3& arg_outputMin) const override {
		auto point = vlp_transform->GetWorldPosition();

		float maxX = max(points[2].x, max(points[0].x, points[1].x));
		float maxY = max(points[2].y, max(points[0].y, points[1].y));
		float maxZ = max(points[2].z, max(points[0].z, points[1].z));

		float minX = min(points[2].x, min(points[0].x, points[1].x));
		float minY = min(points[2].y, min(points[0].y, points[1].y));
		float minZ = min(points[2].z, min(points[0].z, points[1].z));

		arg_outputMax = point + Vector3(maxX, maxY, maxZ);
		arg_outputMin = point + Vector3(minX, minY, minZ);
	}
	bool IsHitPoint(CollisionPrimitive_Point* other)override;
	bool IsHitSphere(CollisionPrimitive_Sphere* other)override;
	bool IsHitBox_AABB(CollisionPrimitive_Box_AABB* other)override;
	bool IsHitBox_OBB(CollisionPrimitive_Box_OBB* other)override;
	bool IsHitPolygon(CollisionPrimitive_Polygon* other)override;
	bool IsHitSurface(CollisionPrimitive_Surface* other)override;
	bool IsHitRay(CollisionPrimitive_Ray* other)override;
	Value_ptr<CollisionPrimitive> Clone()override {
		return ObjectFactory::Create<CollisionPrimitive_Polygon>();
	}

	void ShowUI() override {

#ifdef BUTIENGINEBUILD
		GUI::BulletText("Polygon");
		for (std::int32_t i = 0; i < 3; i++) {
			GUI::DragFloat3(("point##" + std::to_string(i)).c_str(), &initPoints[i].x, 0.01f, -100, 100);
		}
#endif
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(vlp_transform);
		archive(initPoints);
	}

	std::vector<Vector3 >initPoints;
	std::vector<Vector3 >points;
private:
};
class CollisionPrimitive_Surface :public CollisionPrimitive
{
public:
	inline CollisionPrimitive_Surface(const Vector3& arg_normal, Value_ptr<Transform> arg_vlp_transform)
	{
		vlp_transform = arg_vlp_transform;
		normal = arg_normal;
	}
	CollisionPrimitive_Surface() {}
	inline void Update()override {
	}
	inline bool IsHit(Value_weak_ptr< CollisionPrimitive> other)override
	{
		return other.lock()->IsHitSurface(this);


	}
	inline void GetMaxPointAndMinPoint(Vector3& arg_outputMax, Vector3& arg_outputMin) const {
		arg_outputMax = Vector3(100, 100, 100);
		arg_outputMin = Vector3(-100, -100, -100);
	}
	bool IsHitPoint(CollisionPrimitive_Point* other)override;
	bool IsHitSphere(CollisionPrimitive_Sphere* other)override;
	bool IsHitPolygon(CollisionPrimitive_Polygon* other)override;
	bool IsHitBox_AABB(CollisionPrimitive_Box_AABB* other)override;
	bool IsHitBox_OBB(CollisionPrimitive_Box_OBB* other)override;
	bool IsHitSurface(CollisionPrimitive_Surface* other)override;
	bool IsHitRay(CollisionPrimitive_Ray* other)override;
	Value_ptr<CollisionPrimitive> Clone()override {
		auto ret = ObjectFactory::Create<CollisionPrimitive_Surface>();
		ret->normal = normal;
		return ret;
	}
	void ShowUI() override {
#ifdef BUTIENGINEBUILD
		if (GUI::TreeNode("Surface")) {
			GUI::BulletText("Normal");
			if (GUI::DragFloat3("##normal", &normal.x, 0.01, 0, 500)) {
				normal.Normalize();
			}
			GUI::TreePop();
		}
#endif
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(vlp_transform);
		archive(normal);

	}
	Vector3 normal;
private:
};

class CollisionPrimitive_Box_AABB : public CollisionPrimitive, public Geometry::Box_AABB {
public:
	inline CollisionPrimitive_Box_AABB(const Vector3& arg_length, Value_ptr<Transform> arg_vlp_transform)
		:Geometry::Box_AABB(arg_length) {
		vlp_transform = arg_vlp_transform;
		initLengthes = arg_length / 2;
	}
	CollisionPrimitive_Box_AABB() {}
	inline void Update()override {
		position = vlp_transform->GetWorldPosition();
		halfLengthes = initLengthes * vlp_transform->GetWorldScale();
	}
	inline bool IsHit(Value_weak_ptr< CollisionPrimitive> other)override {
		return other.lock()->IsHitBox_AABB(this);
	}

	inline void GetMaxPointAndMinPoint(Vector3& arg_outputMax, Vector3& arg_outputMin) const {
		arg_outputMax = position + halfLengthes;
		arg_outputMin = position - halfLengthes;
	}
	bool IsHitPoint(CollisionPrimitive_Point* other)override;
	bool IsHitSphere(CollisionPrimitive_Sphere* other)override;
	bool IsHitBox_AABB(CollisionPrimitive_Box_AABB* other)override;
	bool IsHitBox_OBB(CollisionPrimitive_Box_OBB* other)override;
	bool IsHitPolygon(CollisionPrimitive_Polygon* other)override;
	bool IsHitSurface(CollisionPrimitive_Surface* other)override;
	bool IsHitRay(CollisionPrimitive_Ray* other)override;
	bool IsHitSegment(CollisionPrimitive_Segment* other)override;
	void ShowUI() override {

#ifdef BUTIENGINEBUILD
		if (GUI::TreeNode("Box_AABB")) {
			GUI::BulletText("Length");
			GUI::DragFloat3("##length", &initLengthes.x, 0.01f, 0.0f, 500.0f);
			GUI::TreePop();
		}
#endif
	}

	Value_ptr<CollisionPrimitive> Clone()override {
		auto ret = ObjectFactory::Create<CollisionPrimitive_Box_AABB>();
		ret->halfLengthes = halfLengthes;
		ret->initLengthes = initLengthes;
		return ret;
	}
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(vlp_transform);
		archive(initLengthes);
		archive(halfLengthes);
	}
private:
	Vector3 initLengthes;
};
class CollisionPrimitive_Box_OBB : public CollisionPrimitive, public Geometry::Box_OBB_Static {
public:
	inline CollisionPrimitive_Box_OBB(const Vector3& arg_length, Value_ptr<Transform> arg_vlp_transform)
		:Geometry::Box_OBB_Static(arg_length) {
		vlp_transform = arg_vlp_transform;
		initLengthes = arg_length * 0.5f;
	}
	CollisionPrimitive_Box_OBB() {}
	inline void Update()override {
		position = vlp_transform->GetWorldPosition();

		directs[0] = vlp_transform->GetRight();
		directs[1] = vlp_transform->GetUp();
		directs[2] = vlp_transform->GetFront();
		halfLengthes = initLengthes * vlp_transform->GetWorldScale();
	}
	inline bool IsHit(Value_weak_ptr< CollisionPrimitive> other)override {
		return other.lock()->IsHitBox_OBB(this);
	}

	inline void GetMaxPointAndMinPoint(Vector3& arg_outputMax, Vector3& arg_outputMin) const {
		auto aabb_legthes = Geometry::BoxHit::GetBox_OBBContainAABBLength(*this);
		arg_outputMax = position + aabb_legthes;
		arg_outputMin = position - aabb_legthes;
	}
	bool IsHitPoint(CollisionPrimitive_Point* other)override;
	bool IsHitSphere(CollisionPrimitive_Sphere* other)override;
	bool IsHitBox_AABB(CollisionPrimitive_Box_AABB* other)override;
	bool IsHitBox_OBB(CollisionPrimitive_Box_OBB* other)override;
	bool IsHitPolygon(CollisionPrimitive_Polygon* other)override;
	bool IsHitSurface(CollisionPrimitive_Surface* other)override;
	bool IsHitRay(CollisionPrimitive_Ray* other)override;
	bool IsHitSegment(CollisionPrimitive_Segment* other)override;

	Geometry::Box_AABB ToAABB();

	void ShowUI() override {

#ifdef BUTIENGINEBUILD
		if (GUI::TreeNode("Box_OBB")) {
			GUI::BulletText("Length");
			GUI::DragFloat3("##length", &initLengthes.x, 0.01f, 0.0f, 500.0f);
			GUI::TreePop();
		}
#endif
	}

	Value_ptr<CollisionPrimitive> Clone()override {
		auto ret = ObjectFactory::Create<CollisionPrimitive_Box_OBB>();
		ret->halfLengthes = halfLengthes;
		ret->initLengthes = initLengthes;
		return ret;
	}
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(vlp_transform);
		archive(initLengthes);
		archive(halfLengthes);
	}
	Vector3 initLengthes;
private:
};
}
}


#endif // !CollisionPrim_H