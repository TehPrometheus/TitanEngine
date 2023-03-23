#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

void Scene::Add( GameObject* object)
{
	m_objects.emplace_back(std::unique_ptr<GameObject>(object));
}

void Scene::DeleteGameObject(GameObject* object)
{
	if (object->GetParent())
		object->SetParent(nullptr);

	//todo: refactor this with algorithms
	for(auto& obj : m_objects)
	{
		if(obj.get() == object)
		{
			for(auto& child: obj.get()->GetChildren())
			{
				DeleteGameObject(child);
			}
			m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), obj), m_objects.end());
		}
	}
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}