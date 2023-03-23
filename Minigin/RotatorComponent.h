#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class RotatorComponent : public BaseComponent
	{
	public:
		RotatorComponent(GameObject* pOwner, float radius = 1.f, float angularVelocity = 1.f);
		~RotatorComponent() override = default;

		RotatorComponent(const RotatorComponent&) = delete;
		RotatorComponent(RotatorComponent&&) = delete;
		RotatorComponent& operator= (const RotatorComponent&) = delete;
		RotatorComponent& operator= (const RotatorComponent&&) = delete;

		void Update() override;
		void Render() const override;

		void SetRadius(float radius) { m_Radius = radius; }
		void SetAngularVelocity(float angularVel) { m_AngularVelocity = angularVel; }

	private:
		float m_Radius{};
		float m_CurrentAngle{};
		float m_AngularVelocity{1.f};
	};
	
}

