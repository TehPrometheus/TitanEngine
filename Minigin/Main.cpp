#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "FPSCounter.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "Timer.h"
#include "RotatorComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	
	auto go =  new dae::GameObject();
	go->AddComponent<dae::TextureComponent>(new dae::TextureComponent("background.tga",go));
	scene.Add(go);

	go = new dae::GameObject(216.f, 180.f);
	go->AddComponent<dae::TextureComponent>(new dae::TextureComponent("logo.tga", go));
	scene.Add(go);

	auto font1 = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = new dae::GameObject(80.f, 20.f);
	go->AddComponent<dae::TextComponent>(new dae::TextComponent("Programming 4 Assignment", font1, go));
	scene.Add(go);

	auto font2 = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	go = new dae::GameObject(5.f, 5.f);
	const std::string text{ std::to_string(TIMER.GetFPS()) + " FPS" };
	go->AddComponent<dae::FPSCounter>(new dae::FPSCounter(text, font2, go));
	scene.Add(go);

	//auto center{ new dae::GameObject(316.f, 350.f) };
	//scene.Add(center);

	auto pacman{ new dae::GameObject(300.f,300.f)};
	pacman->AddComponent<dae::TextureComponent>(new dae::TextureComponent("PacMan.png", pacman));
	//pacman->AddComponent<dae::RotatorComponent>(new dae::RotatorComponent(pacman, 25.f,4.f));
	scene.Add(pacman);
	auto textureComponent{ pacman->GetComponent<dae::TextureComponent>() };
	textureComponent->SetSize(30, 30);
	//pacman->SetParent(center, true);

	//auto ghost{ new dae::GameObject() };
	//ghost->AddComponent<dae::TextureComponent>(new dae::TextureComponent("ghost.png", ghost));
	//ghost->AddComponent<dae::RotatorComponent>(new dae::RotatorComponent(ghost, 30.f,-7.f));
	//scene.Add(ghost);
	//textureComponent = ghost->GetComponent<dae::TextureComponent>();
	//textureComponent->SetSize(30, 30);
	//ghost->SetParent(pacman, true);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}