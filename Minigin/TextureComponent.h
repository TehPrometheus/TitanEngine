#pragma once
#include <string>
#include <glm/vec2.hpp>
#include "BaseComponent.h"

struct SDL_Texture;
namespace dae
{
	class TextureComponent final: public BaseComponent
	{
	public:
		explicit TextureComponent(SDL_Texture* texture);
		explicit TextureComponent(const std::string& filename, GameObject* pOwner);
		~TextureComponent() override;

		TextureComponent(const TextureComponent &) = delete;
		TextureComponent(TextureComponent &&) = delete;
		TextureComponent & operator= (const TextureComponent &) = delete;
		TextureComponent & operator= (const TextureComponent &&) = delete;

		void Render() const override;
		void Update() override;
		void SetTexture(const std::string& filename);

		[[nodiscard]] glm::ivec2 GetSize() const;
		[[nodiscard]] SDL_Texture* GetSDLTexture() const;

		void SetSize(int width, int height);
	private:
		SDL_Rect m_DestRect{};
		SDL_Texture* m_Texture{nullptr};
	};
}
