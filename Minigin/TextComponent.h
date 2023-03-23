#pragma once
#include <string>
#include <memory>
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class Font;
	class TextureComponent;
	class TextComponent: public BaseComponent
	{
	public:
		TextComponent(const std::string& text, std::shared_ptr<Font> font, GameObject* pOwner);
		virtual ~TextComponent() override = default ;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
	protected:
		std::string m_Text;

	private:
		bool m_needsUpdate;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<TextureComponent> m_TextTexture;
	};
}
