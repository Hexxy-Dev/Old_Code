#pragma once

#include "glm.hpp"
#include "gtx/transform.hpp"

#include "../Primitives/Transform.h"
#include "../Primitives/Lights.h"

#include "../Model/Mesh.h"

#include "../Physics/Colliders/Collider.h"
#include "../Physics/Colliders/Sphere collider.h"
#include "../Physics/Colliders/AABB.h"

#include "../Physics/RigidBody.h"

struct Entity {
public:
	Entity();

	~Entity()
	{
		delete collider;
	}

	glm::mat4 createModelMatrix() const;

	glm::mat4 getModelMatrix() const;

	void addChild(Entity* entity);

	void addSphereCollider()
	{
		collider = new SphereCollider(0.5f); // NEEDS SOME WAY TO AUTOMATICALLY CALCULATE THE RADIUS!!!!!
		collider->position = &Transform.Position;
	}

	void addAABB()
	{
		collider = new AABB();
		collider->position = &Transform.Position;
		AABB* col =  static_cast<AABB*>(collider);

		glm::mat4 model = getModelMatrix();

		glm::vec3 c1 = model * glm::vec4(mesh->vertices[0].Position, 1.0f);
		glm::vec3 c2 = model * glm::vec4(mesh->vertices[1].Position, 1.0f);
		glm::vec3 c3 = model * glm::vec4(mesh->vertices[2].Position, 1.0f);
		glm::vec3 c4 = model * glm::vec4(mesh->vertices[3].Position, 1.0f);

		col->max.x = std::max(std::max(c1.x, c2.x), std::max(c3.x, c4.x));
		col->max.y = std::max(std::max(c1.y, c2.y), std::max(c3.y, c4.y));
		col->max.z = std::max(std::max(c1.z, c2.z), std::max(c3.z, c4.z));

		col->min.x = std::min(std::min(c1.x, c2.x), std::min(c3.x, c4.x));
		col->min.y = std::min(std::min(c1.y, c2.y), std::min(c3.y, c4.y));
		col->min.z = std::min(std::min(c1.z, c2.z), std::min(c3.z, c4.z));
	}

	Transform Transform;
	Mesh* mesh;
	PointLight* pointLight;
	SpotLight* spotLight;
	DirectionalLight* directionalLight;

	std::vector<Entity*> children;
	Entity* parent;

	Collider* collider;

	RigidBody* rigidBody;

	bool isEnabled;

	void (*OnTriggerEnter)(Entity* coll);

private:
	mutable glm::mat4 model;
	mutable bool cached;
	mutable ::Transform LastTransform;
};