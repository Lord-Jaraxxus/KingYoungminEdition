#include "World.hpp"

void ECS::World::Tick(float time)
{
	for (auto& system : Systems)
	{
		system.get()->Tick(this, time);
	}
}

void ECS::World::AddEntity(ECS::Entity* entity)
{
	std::shared_ptr<Entity> newEntity(entity);
	Entities.push_back(newEntity);
	EntityMap.insert(std::make_pair(entity->Name, entity));
}

std::vector<std::shared_ptr<ECS::Entity>>& ECS::World::GetAllEntities()
{
	return Entities;
}

ECS::Entity* ECS::World::FindEntity(std::wstring EntityName)
{
	return EntityMap.find(EntityName)->second;
}

ECS::System* ECS::World::AddSystem(ECS::System* system)
{
	std::shared_ptr<System> newSystem(system);
	Systems.push_back(newSystem);
	return system;
}

void ECS::World::EnableSystem(ECS::System* system)
{
	std::shared_ptr<System> enableSystem(system);
	auto it = std::find(DisableSystems.begin(), DisableSystems.end(), enableSystem);
	if (it != DisableSystems.end())
	{
		DisableSystems.erase(it);
		Systems.push_back(enableSystem);
	}
}

void ECS::World::DisableSystem(ECS::System* system)
{
	std::shared_ptr<System> disableSystem(system);
	auto it = std::find(Systems.begin(), Systems.end(), disableSystem);
	if (it != Systems.end())
	{
		Systems.erase(it);
		DisableSystems.push_back(disableSystem);
	}
}