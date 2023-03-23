#include "TransformComponent.h"

#include "GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* pOwner, float x, float y, float z)
	:BaseComponent(pOwner)
{
	//SetWorldPosition(x, y, z);
	SetLocalPosition(x, y, z);
}

void dae::TransformComponent::SetWorldPosition(float x, float y, float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}

void dae::TransformComponent::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;

	SetDirty();
}

void dae::TransformComponent::SetDirty()
{
	//todo: Alex feedback
	m_PositionIsDirty = true;

	for(auto& child : GetOwner()->GetChildren())
	{
		child->GetTransform()->SetDirty();
	}

}

void dae::TransformComponent::UpdateWorldPosition()
{
	if(m_PositionIsDirty)
	{
		const GameObject* parent{ GetOwner()->GetParent() };

		if (parent == nullptr)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = parent->GetTransform()->GetWorldPosition() + m_LocalPosition;
	}
	m_PositionIsDirty = false;
}

void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::Render() const
{
}

const glm::vec3& dae::TransformComponent::GetWorldPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

