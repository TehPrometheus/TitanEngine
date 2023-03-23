#pragma once
#include <string>
#include <memory>
#include "Singleton.h"
#include <SDL.h>

namespace dae
{
	class TextureComponent;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		[[nodiscard]] std::shared_ptr<TextureComponent> LoadTexture(const std::string& file) const;
		[[nodiscard]] SDL_Texture* LoadSDLTexture(const std::string& file) const;
		[[nodiscard]] std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
	};
}
