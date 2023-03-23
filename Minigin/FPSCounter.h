#pragma once
#include "TextComponent.h"
namespace dae {
	//todo: this should only inherit from baseComponent. To solve this make sure that you attach
	class FPSCounter final : public TextComponent
	{
	public:
		FPSCounter(const std::string& text, std::shared_ptr<Font> font, GameObject* pOwner);
		~FPSCounter() = default;

		void Update() override;
	};

}

