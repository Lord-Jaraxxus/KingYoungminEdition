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
	cardview,
};

class BaseScene
{
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	ECS::World TheWorld;
	Camera* MainCamera;

public:
	SceneState SceneState = maintain; // 0�̸� ����, 1�̸� Ÿ��Ʋ��, 2�� ������, 3�̸� ������.. �� ���� �׷���?
};

