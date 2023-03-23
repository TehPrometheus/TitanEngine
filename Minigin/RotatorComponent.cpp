#include "Timer.h"
#include "RotatorComponent.h"
#include "GameObject.h"

dae::RotatorComponent::RotatorComponent(GameObject* pOwner, float radius, float angularVelocity)
	:BaseComponent(pOwner)
	,m_Radius(radius)
	,m_AngularVelocity(angularVelocity)
{
}

void dae::RotatorComponent::Update()
{
	//todo: Alex feedback
	m_CurrentAngle += m_AngularVelocity * static_cast<float>(TIMER.GetDt());
	GetOwner()->GetTransform()->SetLocalPosition(m_Radius * glm::cos(m_CurrentAngle), m_Radius * glm::sin(m_CurrentAngle));
}

void dae::RotatorComponent::Render() const
{
}