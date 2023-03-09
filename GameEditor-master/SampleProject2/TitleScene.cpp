#include "TitleScene.h"

bool TitleScene::Init()
{
	UI_Loader Loader;

	// 1. Actor ����
	Actor* TitleUI = new Actor;
	TitleUI->Name = L"Title";
	auto tc = TitleUI->AddComponent<WidgetComponent>();
	Loader.FileLoad(tc, L"newfile.txt");
	StartButton = tc->FindObj(L"Button_Start");


	// 8. ���Ϳ� ī�޶� �߰�.
	DebugCamera = TitleUI->AddComponent<Camera>();
	DebugCamera->CreateViewMatrix(Vector3(0.0f, 0.0f, -100.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0, 0.0f));
	DebugCamera->CreateProjectionMatrix(1.0f, 500.0f, PI * 0.25, (DXDevice::g_ViewPort.Width) / (DXDevice::g_ViewPort.Height));

	// 9. ���� ���忡 ���� �߰�.
	TheWorld.AddEntity(TitleUI);

	// 10. ī�޶� �ý��� �� ������ �ý��� �߰�.
	TheWorld.AddSystem(new CameraSystem);
	TheWorld.AddSystem(new RenderSystem);
	TheWorld.AddSystem(new WidgetRenderSystem);

	return true;
}

bool TitleScene::Frame()
{
	if (StartButton->m_bClicked) 
	{ 
		StartButton->m_bClicked = false;
		SceneState = 2; 
	}
	BaseScene::Frame();
	return true;
}

bool TitleScene::Render()
{
	BaseScene::Render();
	return true;
}

bool TitleScene::Release()
{
	return true;
}