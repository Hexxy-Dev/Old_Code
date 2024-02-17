#pragma once

#include "Collider.h"

class SphereCollider : public Collider {
public:
	SphereCollider(const float& radius)
		: radius(radius)
	{}

	bool Intersect(Collider*& other);
public:
	float radius;
};