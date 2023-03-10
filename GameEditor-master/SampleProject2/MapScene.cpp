#include "MapScene.h"

bool MapScene::Init()
{
	UI_Loader Loader;

	// Actor ����
	Actor* MapUI = new Actor;
	MapUI->Name = L"Map";
	auto mc = MapUI->AddComponent<WidgetComponent>();
	Loader.FileLoad(mc, L"Map.txt");
	BackButton = mc->FindObj(L"Back");
	Mon1 = mc->FindObj(L"Mon1");

	// ���Ϳ� ī�޶� �߰�.
	DebugCamera = MapUI->AddComponent<Camera>();
	DebugCamera->CreateViewMatrix(Vector3(0.0f, 0.0f, -100.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0, 0.0f));
	DebugCamera->CreateProjectionMatrix(1.0f, 500.0f, PI * 0.25, (DXDevice::g_ViewPort.Width) / (DXDevice::g_ViewPort.Height));

	// ���� ���忡 ���� �߰�.
	TheWorld.AddEntity(MapUI);

	// ī�޶� �ý��� �� ������ �ý��� �߰�.
	TheWorld.AddSystem(new CameraSystem);
	TheWorld.AddSystem(new RenderSystem);
	TheWorld.AddSystem(new WidgetRenderSystem);

	return true;
}

bool MapScene::Frame()
{
	if (BackButton->m_bClicked) 
	{
		BackButton->m_bClicked = false;
		SceneState = 1; 
	}
	else if (Mon1->m_bClicked) 
	{
		Mon1->m_bClicked = false;
		SceneState = 3;
	}

	BaseScene::Frame();
	return true;
}

bool MapScene::Render()
{
	BaseScene::Render();
	return true;
}

bool MapScene::Release()
{
	return true;
}
