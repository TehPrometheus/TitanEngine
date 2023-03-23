#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent(GameObject* pOwner, float x = 0, float y = 0, float z = 0);
		~TransformComponent() override = default;

		TransformComponent(const TransformComponent&) = delete;
		TransformComponent(TransformComponent&&) = delete;
		TransformComponent& operator= (const TransformComponent&) = delete;
		TransformComponent& operator= (const TransformComponent&&) = delete;

		void Update() override;
		void Render() const override;

		[[nodiscard]] const glm::vec3& GetWorldPosition();
		[[nodiscard]] const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		[[nodiscard]] bool GetPositionFlag() const { return m_PositionIsDirty; }
		void SetWorldPosition(float x, float y, float z = 0);
		void SetLocalPosition(float x, float y, float z = 0);
		void SetDirty();

	private:
		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};
		bool  m_PositionIsDirty{false};


		void UpdateWorldPosition();
	};
}
