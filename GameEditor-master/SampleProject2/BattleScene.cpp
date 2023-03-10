#include "BattleScene.h"

bool BattleScene::Init()
{
	UI_Loader Loader;

	// Actor ����
	Actor* Battle = new Actor;
	Battle->Name = L"Battle";
	auto bc = Battle->AddComponent<WidgetComponent>();
	Loader.FileLoad(bc, L"Battle.txt");

	// ���Ϳ� ī�޶� �߰�.
	DebugCamera = Battle->AddComponent<Camera>();
	DebugCamera->CreateViewMatrix(Vector3(0.0f, 0.0f, -100.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0, 0.0f));
	DebugCamera->CreateProjectionMatrix(1.0f, 500.0f, PI * 0.25, (DXDevice::g_ViewPort.Width) / (DXDevice::g_ViewPort.Height));

	// ���� ���忡 ���� �߰�.
	TheWorld.AddEntity(Battle);

	// ī�޶� �ý��� �� ������ �ý��� �߰�.
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
