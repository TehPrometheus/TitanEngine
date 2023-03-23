#pragma once
#include "TransformComponent.h"
#include "BaseComponent.h"
#include "ComponentMap.h"
#include "Exceptions.h"
#include <vector>
#include <set>

namespace dae
{
	class TextureComponent;
	class BaseComponent;
	class GameObject 
	{
	public:
		GameObject(float x = 0, float y = 0, float z = 0);
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// General Methods
		virtual void Update();
		virtual void Render() const; //todo: make this a render component
		void SetWorldPosition(float x, float y);
		[[nodiscard]] TransformComponent* GetTransform() const;

		// Scenegraph related methods
		void SetParent(GameObject* parent, bool keepWorldPosition = true);
		[[nodiscard]] GameObject* GetParent() const { return m_pParent; }
		[[nodiscard]] std::set<GameObject*> GetChildren() const { return m_Children; }

		// Component related methods
		template <typename ComponentType>
		void AddComponent(BaseComponent* c);

		template <typename ComponentType>
		[[nodiscard]] ComponentType* GetComponent() const;

		template <typename ComponentType>
		bool RemoveComponent(bool freeMemory);

	private:
		GameObject* m_pParent{ nullptr };
		std::set<GameObject*> m_Children{};
		ComponentMap<BaseComponent*> m_Components{};
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
	};

	template <typename ComponentType>
	void GameObject::AddComponent(BaseComponent* c)
	{
		m_Components.add<ComponentType, BaseComponent*>(c);
	}

	template <typename ComponentType>
	ComponentType* dae::GameObject::GetComponent() const
	{
		auto it{ m_Components.find<ComponentType>() };

		if (it == m_Components.end())
		{
			throw ComponentNotFoundException();
		}

		return static_cast<ComponentType*>(it->second);
	}

	// Returns true if removal took place, frees component memory
	template <typename ComponentType>
	bool dae::GameObject::RemoveComponent(bool freeMemory)
	{
		return m_Components.erase<ComponentType>(freeMemory);
	}

}
