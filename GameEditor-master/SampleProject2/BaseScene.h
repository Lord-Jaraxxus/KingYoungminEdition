#pragma once
#include "EditorCore.h"
#include "World.hpp"
#include "Camera.h"
#include "UI_Loader.h"
#include "WindowsClient.h"
#include "Actor.h"
#include "PlaneComponent.h"
#include "CameraSystem.h"
#include "RenderSystem.h"
#include "WidgetRenderSystem.h"
#include "Deck.h"

enum SceneState
{
	maintain,
	loading,
	title,
	map,
	battle,
	deckView,
	remainView,
	discardView,
};

class BaseScene
{
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	void CardTextureLoad();

public:
	ECS::World TheWorld;
	Camera* MainCamera;

public:
	SceneState SS = maintain; // 0이면 유지, 1이면 타이틀로, 2면 맵으로, 3이면 전투로.. 뭐 대충 그런식?
	SceneState ID = maintain; // 씬마다 자기가 뭔지 붙여놓기위함

public:
	std::vector<DXTexture*> CardTextureList;
};

