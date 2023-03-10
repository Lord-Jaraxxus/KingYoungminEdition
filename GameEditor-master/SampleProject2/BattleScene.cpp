#include "BattleScene.h"

bool BattleScene::Init()
{
	UI_Loader Loader;

	// Actor 생성
	Actor* Battle = new Actor;
	Battle->Name = L"Battle";
	auto bc = Battle->AddComponent<WidgetComponent>();
	Loader.FileLoad(bc, L"Battle.txt");

	// 액터에 카메라 추가.
	DebugCamera = Battle->AddComponent<Camera>();
	DebugCamera->CreateViewMatrix(Vector3(0.0f, 0.0f, -100.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0, 0.0f));
	DebugCamera->CreateProjectionMatrix(1.0f, 500.0f, PI * 0.25, (DXDevice::g_ViewPort.Width) / (DXDevice::g_ViewPort.Height));

	// 메인 월드에 액터 추가.
	TheWorld.AddEntity(Battle);

	// 카메라 시스템 및 랜더링 시스템 추가.
	TheWorld.AddSystem(new CameraSystem);
	TheWorld.AddSystem(new RenderSystem);
	TheWorld.AddSystem(new WidgetRenderSystem);

	return true;
}

bool BattleScene::Frame()
{
	BaseScene::Frame();
	return true;
}

bool BattleScene::Render()
{
	BaseScene::Render();
	return true;
}

bool BattleScene::Release()
{
	BaseScene::Release();
    return true;
}
