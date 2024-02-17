#include "Sphere collider.h"

#include "AABB.h"

bool SphereVsPoint(SphereCollider* sphere, Collider* other);
bool SphereVSSphere(SphereCollider* sphere, SphereCollider* other);
bool SphereVSAABB(SphereCollider* sphere, AABB* other);

bool SphereCollider::Intersect(Collider*& other)
{
	if (dynamic_cast<SphereCollider*>(other) != nullptr)
	{
		return SphereVSSphere(this, static_cast<SphereCollider*>(other));
	}

	if (dynamic_cast<AABB*>(other) != nullptr)
	{
		return SphereVSAABB(this, static_cast<AABB*>(other));
	}

	return SphereVsPoint(this, other);
}

bool SphereVsPoint(SphereCollider* sphere, Collider* other)
{
	float distance = sqrtf(
		(sphere->position->x - other->position->x) * (sphere->position->x - other->position->x) +
		(sphere->position->y - other->position->y) * (sphere->position->y - other->position->y) +
		(sphere->position->z - other->position->z) * (sphere->position->z - other->position->z));

	return distance < sphere->radius;
}

bool SphereVSSphere(SphereCollider* sphere, SphereCollider* other)
{
	float distance = sqrtf(
		(sphere->position->x - other->position->x) * (sphere->position->x - other->position->x) +
		(sphere->position->y - other->position->y) * (sphere->position->y - other->position->y) +
		(sphere->position->z - other->position->z) * (sphere->position->z - other->position->z));

	return distance < (sphere->radius + other->radius);
}

bool SphereVSAABB(SphereCollider* sphere, AABB* other)
{
	float x = std::max(other->min.x, std::min(sphere->position->x, other->max.x));
	float y = std::max(other->min.y, std::min(sphere->position->y, other->max.y));
	float z = std::max(other->min.z, std::min(sphere->position->z, other->max.z));

	float distance = sqrtf(
		(x - sphere->position->x) * (x - sphere->position->x) +
		(y - sphere->position->y) * (y - sphere->position->y) +
		(z - sphere->position->z) * (z - sphere->position->z));

	return distance < sphere->radius;
}