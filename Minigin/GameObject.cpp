#include "GameObject.h"
#include <functional>
#include "Exceptions.h"
#include "TextureComponent.h"

dae::GameObject::GameObject(float x, float y, float z)
{
	AddComponent<dae::TransformComponent>(new TransformComponent(this, x, y, z));
}

dae::GameObject::~GameObject()
{
	for (auto c: m_Components)
	{
		delete c.second;
	}
}

void dae::GameObject::Update()
{
	//todo: if the game object owns it's children, it should also update it
	// If it doesn't own its children then your scene should be updating them, and your gameobject does not own the children
	// ask yourself: should a parent own it's children
	for (auto& c: m_Components)
	{
		c.second->Update();
	}

}

void dae::GameObject::Render() const
{
	for (auto c: m_Components)
	{
		c.second->Render();
	}
}


void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	auto transform{ GetTransform() };
	if (parent == nullptr)
		transform->SetLocalPosition(transform->GetWorldPosition().x, transform->GetWorldPosition().y, transform->GetWorldPosition().z);
	else
	{
		if (keepWorldPosition)
		{
			auto pos{ transform->GetLocalPosition() - parent->GetTransform()->GetWorldPosition() };
			transform->SetLocalPosition(pos.x, pos.y, pos.z);
		}
		transform->SetDirty();
	}

	if(m_pParent)
		m_pParent->RemoveChild(this);
	m_pParent = parent;
	if (m_pParent)
		m_pParent->AddChild(this);
}

void dae::GameObject::SetWorldPosition(float x, float y)
{
	GetTransform()->SetWorldPosition(x, y, 0.0f);
}

dae::TransformComponent* dae::GameObject::GetTransform() const
{
	return GetComponent<TransformComponent>();
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	const size_t numElementsErased{ m_Children.erase(child) };
	if(numElementsErased == 0)
		throw ChildNotFoundException();
}

void dae::GameObject::AddChild(GameObject* child)
{
	// No need to check if child is already in m_Children since it's a set.
	const auto pair{ m_Children.insert(child) };
	if (pair.second == false)
		throw GameObjectIsAlreadyChildException();
}
