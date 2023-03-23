#include <SDL.h>
#include "TextureComponent.h"

#include "GameObject.h"
#include "ResourceManager.h"
dae::TextureComponent::TextureComponent(SDL_Texture* texture)
{
	m_Texture = texture;
}

dae::TextureComponent::TextureComponent(const std::string& filename, GameObject* pOwner)
	:BaseComponent(pOwner)
{
	SetTexture(filename);
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &m_DestRect.w, &m_DestRect.h);
}

dae::TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(m_Texture);
}

void dae::TextureComponent::Update()
{

}

void dae::TextureComponent::Render() const
{
	const auto& pos{ GetOwner()->GetTransform()->GetWorldPosition() };
	Renderer::GetInstance().RenderTexture(*this, pos.x, pos.y, static_cast<float>(m_DestRect.w), static_cast<float>(m_DestRect.h));
}


void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadSDLTexture(filename);
}

glm::ivec2 dae::TextureComponent::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* dae::TextureComponent::GetSDLTexture() const
{
	return m_Texture;
}

void dae::TextureComponent::SetSize(int width, int height)
{
	m_DestRect.w = width;
	m_DestRect.h = height;
}

