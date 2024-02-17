#include "Scene.h"

#include <vector>
#include <algorithm>

#include "../Profiler.h"

#include <iostream> // TEMPORARY

#include <future>

void Scene::PhisycsPass(const float& deltaTime)
{
	PROFILE_FUNCTION();
	for (int i = 0; i < EntitiesWithRigidBodyes.size(); i++)
	{
		EntitiesWithRigidBodyes[i]->rigidBody->force += EntitiesWithRigidBodyes[i]->rigidBody->mass * gravity;

		EntitiesWithRigidBodyes[i]->rigidBody->velocity += EntitiesWithRigidBodyes[i]->rigidBody->force / EntitiesWithRigidBodyes[i]->rigidBody->mass * deltaTime;
		EntitiesWithRigidBodyes[i]->Transform.Position += EntitiesWithRigidBodyes[i]->rigidBody->velocity * deltaTime;

		EntitiesWithRigidBodyes[i]->rigidBody->force = glm::vec3(0.0f);
	}

	for (int i = 0; i < EntitiesWithColliders.size(); i++)
	{
		for (int j = i + 1; j < EntitiesWithColliders.size(); j++)
		{
			if (EntitiesWithColliders[i]->collider->Intersect(EntitiesWithColliders[j]->collider))
			{
				printf("Coll: %d %d; %f, %f, %f; %f, %f, %f \n", i, j, EntitiesWithColliders[i]->collider->position->x, EntitiesWithColliders[i]->collider->position->y, EntitiesWithColliders[i]->collider->position->z, EntitiesWithColliders[j]->collider->position->x, EntitiesWithColliders[j]->collider->position->y, EntitiesWithColliders[j]->collider->position->z);

				if (EntitiesWithColliders[i]->collider->isTrigger)
				{
					EntitiesWithColliders[i]->OnTriggerEnter(EntitiesWithColliders[j]);
					continue;
				}

				if (!EntitiesWithColliders[i]->rigidBody)
				{

					continue;
				}
			}
		}
	}
}

void Scene::Sort()
{
	PROFILE_FUNCTION();

	if (lastEntitiesSize == Entities.size())
	{
		SortByZ();
		return;
	}

	lastEntitiesSize = Entities.size();

	solids.clear();
	transparents.clear();
	pointLights.clear();
	spotLights.clear();
	directionalLights.clear();
	EntitiesWithColliders.clear();
	EntitiesWithRigidBodyes.clear();

	for (auto entity : Entities)
	{
		entityRecursive(entity, solids, transparents);
	}

	SortByZ();
}

void Scene::CalculateClosestLights(const Entity* object)
{
	PROFILE_FUNCTION();

	auto thread1 = std::async(std::launch::async, [&]() {
		pointLightsPositions.clear();
		pointLightsSorted.clear();

		for (int i = 0; i < pointLights.size(); i++)
		{
			Entity* entity = pointLights[i];
			glm::vec3 lightPosition = entity->getModelMatrix() * glm::vec4(entity->pointLight->lightPos, 1.0f);
			glm::vec3 objectPosition = object->getModelMatrix() * glm::vec4(object->Transform.Position, 1.0f);
			poz poz;
			poz.dist = glm::distance(objectPosition, lightPosition);
			poz.index = i;
			pointLightsPositions.push_back(poz);
		}
		std::sort(pointLightsPositions.begin(), pointLightsPositions.end(), [](poz left, poz right) { return left.dist < right.dist; });
		for (int i = 0; i < pointLightsPositions.size(); i++)
		{
			pointLightsSorted.push_back(pointLights[pointLightsPositions[i].index]);
		}
	});

	auto thread2 = std::async(std::launch::async, [&]() {
		spotLightsPositions.clear();
		spotLightsSorted.clear();

		for (int i = 0; i < spotLights.size(); i++)
		{
			Entity* entity = spotLights[i];
			glm::vec3 lightPosition = entity->getModelMatrix() * glm::vec4(entity->spotLight->lightPos, 1.0f);
			glm::vec3 objectPosition = object->getModelMatrix() * glm::vec4(object->Transform.Position, 1.0f);
			poz poz;
			poz.dist = glm::distance(objectPosition, lightPosition);
			poz.index = i;
			spotLightsPositions.push_back(poz);
		}
		std::sort(spotLightsPositions.begin(), spotLightsPositions.end(), [](poz left, poz right) { return left.dist < right.dist; });
		for (int i = 0; i < spotLightsPositions.size(); i++)
		{
			spotLightsSorted.push_back(spotLights[spotLightsPositions[i].index]);
		}
	});

	thread1.wait();
	thread2.wait();
}

void Scene::SortByZ()
{
	PROFILE_FUNCTION();

	glm::mat4 projection = Camera->createPerspective();
	glm::mat4 view = Camera->createViewMatrix();

	auto thread1 = std::async(std::launch::async, [&](){
		solidsSorted.clear();
		solidsPositions.clear();

		for (int i = 0; i < solids.size(); i++)  // TODO: make this a function that takes in a lambda and the vector ... idk about performance
		{
			Entity* entity = solids[i];
			glm::vec3 position = projection * view * entity->getModelMatrix() * glm::vec4(entity->Transform.Position, 1.0f);
			poz poz;
			poz.dist = position.z;
			poz.index = i;
			solidsPositions.push_back(poz);
		}
		std::sort(solidsPositions.begin(), solidsPositions.end(), [](poz left, poz right) { return left.dist < right.dist; });
		for (int i = 0; i < solidsPositions.size(); i++)
		{
			solidsSorted.push_back(solids[solidsPositions[i].index]);
		}
	});

	auto thread2 = std::async(std::launch::async, [&](){
		transparentsSorted.clear();
		transparentsPositions.clear();

		for (int i = 0; i < transparents.size(); i++)
		{
			Entity* entity = transparents[i];
			glm::vec3 position = projection * view * entity->getModelMatrix() * glm::vec4(entity->Transform.Position, 1.0f);
			poz poz;
			poz.dist = position.z;
			poz.index = i;
			transparentsPositions.push_back(poz);
		}
		std::sort(transparentsPositions.begin(), transparentsPositions.end(), [](poz left, poz right) { return left.dist > right.dist; });
		for (int i = 0; i < transparentsPositions.size(); i++)
		{
			transparentsSorted.push_back(transparents[transparentsPositions[i].index]);
		}
	});

	thread1.wait();
	thread2.wait();
}

void Scene::entityRecursive(Entity* entity, std::vector<Entity*>& solids, std::vector<Entity*>& transparents)
{
	PROFILE_FUNCTION();
	if (!entity || !entity->isEnabled)
		return;

	if (entity->mesh)
		if (entity->mesh->is_Transparent)
			transparents.push_back(entity);
		else
			solids.push_back(entity);

	if (entity->pointLight)
		pointLights.push_back(entity);

	if (entity->spotLight)
		spotLights.push_back(entity);

	if (entity->directionalLight)
		directionalLights.push_back(entity);

	if (entity->collider)
		EntitiesWithColliders.push_back(entity);

	if (entity->rigidBody)
		EntitiesWithRigidBodyes.push_back(entity);

	for (auto child : entity->children)
	{
		entityRecursive(child, solids, transparents);
		// TODO: ?? if multiple entities have a child in common that child's branch will be repeated
		// will not affect visuals but will affect performance and memory :/
	}
}

// Z SORTING GETS MESSED UP IN THE LEFT AND RIGHT MOST PARTS OF THE CAMERA
// I THINK THE PROBLEM IS WITH THE CAMERA ORIENTING AND Z DISTANCE

/*
0.000000 0.000000 0.000000
0.000000 0.000000 -1.720000
0.000000 0.000000 -1.710000
0.000000 0.000000 -1.700000
0.000000 0.000000 -1.600000
0.000000 0.000000 0.000000
0.000000 0.000000 0.100000
0.000000 0.000000 0.200000
0.000000 0.000000 0.500000
0.000000 0.000000 0.700000
0.000000 1.000000 -0.500000
0.000000 1.000000 0.000000
0.000000 1.000000 0.000000
0.000000 1.000000 0.500000
*/
/*
0.000000 0.000000 0.000000
0.000000 0.000000 0.700000
0.000000 0.000000 0.500000
0.000000 0.000000 0.200000
0.000000 0.000000 0.100000
0.000000 0.000000 0.000000
0.000000 0.000000 -1.600000
0.000000 0.000000 -1.700000
0.000000 0.000000 -1.710000
0.000000 0.000000 -1.720000
0.000000 1.000000 0.500000
0.000000 1.000000 0.000000
0.000000 1.000000 0.000000
0.000000 1.000000 -0.500000
*/