#pragma once

#pragma once

#include "../ECS/Entity.h"
#include "../ECS/Camera.h"

#include "../Physics/Colliders/Collider.h" // not used
#include "../Physics/RigidBody.h"

class Scene {
public:

	void Sort();


	void CalculateClosestLights(const Entity* object);

	void PhisycsPass(const float& deltaTime);

	glm::vec3 gravity;


	std::vector<Entity*> Entities;

	std::vector<Entity*> solidsSorted;
	std::vector<Entity*> transparentsSorted;

	std::vector<Entity*> pointLightsSorted;
	std::vector<Entity*> spotLightsSorted;
	std::vector<Entity*> directionalLights;
	std::vector<Entity*> directionalLightsSorted;

	std::vector<Entity*> EntitiesWithColliders;
	std::vector<Entity*> EntitiesWithRigidBodyes;

	Light* ambientLight;

	Camera* Camera;
private:
	std::vector<Entity*> solids;
	std::vector<Entity*> transparents;
	
	std::vector<Entity*> pointLights;
	std::vector<Entity*> spotLights;

	struct poz {
		float dist;
		int index;
	};
	std::vector<poz> solidsPositions;
	std::vector<poz> transparentsPositions;

	std::vector<poz> pointLightsPositions;
	std::vector<poz> spotLightsPositions;
	std::vector<poz> directionalLightsPositions;

	uint32_t lastEntitiesSize;
private:
	void SortByZ();

	void entityRecursive(Entity* entity, std::vector<Entity*>& solids, std::vector<Entity*>& transparents);
};