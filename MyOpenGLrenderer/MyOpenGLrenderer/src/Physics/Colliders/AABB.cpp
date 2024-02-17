#include "AABB.h"

#include "Sphere collider.h"

bool AABBVSPoint(AABB* aabb, Collider* other);
bool AABBVSAABB(AABB* aabb, AABB* other);
bool AABBVSSphere(AABB* aabb, SphereCollider* other);

bool AABB::Intersect(Collider*& other)
{
	if (dynamic_cast<AABB*>(other))
	{
		return AABBVSAABB(this, static_cast<AABB*>(other));
	}

	if (dynamic_cast<SphereCollider*>(other))
	{
		return AABBVSSphere(this, static_cast<SphereCollider*>(other));
	}

	return AABBVSPoint(this, other);
}

bool AABBVSPoint(AABB* aabb, Collider* other)
{
	return
		(other->position->x >= aabb->min.x && other->position->x <= aabb->max.x) &&
		(other->position->y >= aabb->min.y && other->position->y <= aabb->max.y) &&
		(other->position->z >= aabb->min.z && other->position->z <= aabb->max.z);
}

bool AABBVSAABB(AABB* aabb, AABB* other)
{
	return
		(aabb->min.x <= other->max.x && aabb->max.x >= other->min.x) &&
		(aabb->min.y <= other->max.y && aabb->max.y >= other->min.y) &&
		(aabb->min.z <= other->max.z && aabb->max.z >= other->min.z);
}

bool AABBVSSphere(AABB* aabb, SphereCollider* other)
{
	float x = std::max(aabb->min.x, std::min(other->position->x, aabb->max.x));
	float y = std::max(aabb->min.y, std::min(other->position->y, aabb->max.y));
	float z = std::max(aabb->min.z, std::min(other->position->z, aabb->max.z));

	float distance = sqrtf(
		(x - other->position->x) * (x - other->position->x) +
		(y - other->position->y) * (y - other->position->y) +
		(z - other->position->z) * (z - other->position->z));

	return distance < other->radius;
}