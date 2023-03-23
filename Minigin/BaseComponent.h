#pragma once
#include "Renderer.h"

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent(GameObject* pOwner) : m_Owner(pOwner) {}
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		virtual void Update() = 0;
		virtual void Render() const = 0;

	protected:
		GameObject* GetOwner() const { return m_Owner; }

	private:

		GameObject* m_Owner{nullptr};
	};
}
