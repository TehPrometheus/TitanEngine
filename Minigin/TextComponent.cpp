#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Timer.h"

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, GameObject* pOwner)
	:	BaseComponent(pOwner),
		m_Text(text),
		m_needsUpdate(true),
		m_Font(std::move(font)),
		m_TextTexture(nullptr)
{ }

void dae::TextComponent::Update()
{
	if (m_needsUpdate)
	{
		constexpr SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<TextureComponent>(texture);
		m_needsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_TextTexture != nullptr)
	{
		const auto& pos = GetOwner()->GetTransform()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::SetPosition(const float x, const float y)
{
	GetOwner()->SetWorldPosition(x, y);
}


