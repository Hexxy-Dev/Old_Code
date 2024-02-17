#include "Entity.h"

#include "../Profiler.h"

Entity::Entity()
	: mesh(nullptr), cached(false), parent(nullptr), model(1.0f), pointLight(nullptr), directionalLight(nullptr), spotLight(nullptr),
	collider(nullptr), rigidBody(nullptr), isEnabled(true)
{
	Transform.Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	OnTriggerEnter = [](Entity* coll) { return; };
}

glm::mat4 Entity::createModelMatrix() const
{
	PROFILE_FUNCTION();
	if (LastTransform.Position == Transform.Position && LastTransform.Rotation == Transform.Rotation && LastTransform.Scale == Transform.Scale)
		if (cached)
			return model; // this caching doubles the space required :/

	LastTransform.Position = Transform.Position;
	LastTransform.Rotation = Transform.Rotation;
	LastTransform.Scale = Transform.Scale;

	model = glm::mat4(1.0f);
	model = glm::scale(model, Transform.Scale);
	model = glm::rotate(model, glm::radians(Transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, Transform.Position);

	cached = true;

	return model;
}

glm::mat4 Entity::getModelMatrix() const
{
	PROFILE_FUNCTION();
	glm::mat4 model = glm::mat4(1.0f);

	if (this->parent)
		model = this->parent->getModelMatrix();

	model *= createModelMatrix();

	return model;
}

void Entity::addChild(Entity* entity)
{
	PROFILE_FUNCTION();
	entity->parent = this;
	children.push_back(entity);
}