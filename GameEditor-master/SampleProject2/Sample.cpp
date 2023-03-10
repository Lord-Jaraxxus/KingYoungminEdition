#include "Sample.h"


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	WindowsClient sampleWindow;
	sampleWindow.Create(hInstance, L"Window Name", 1024, 768);

	SampleCore core;
	core.SetWindowHandle(sampleWindow.GetHandle());
	core.CoreInitialize();
	bool isRun = true;
	while (isRun)
	{
		if (!sampleWindow.Run())
		{
			isRun = false;
		}
		else
		{
			core.CoreFrame();
			core.CoreRender();
		}
	}

	core.CoreRelease();

	return 1;
}

SampleCore::SampleCore()
{
}

SampleCore::~SampleCore()
{
}

bool SampleCore::Initialize()
{
	EditorCore::Initialize();

	Title = new TitleScene;
	Title->Init();
	Map = new MapScene;
	Map->Init();	
	Battle = new BattleScene;
	Battle->Init();

	CurrentScene = Title;

	return true;
}

bool SampleCore::Frame()
{
	EditorCore::Frame();

	if (CurrentScene->SceneState != 0) 
	{
		switch (CurrentScene->SceneState)
		{
		case 1 : 
		{
			CurrentScene->SceneState = 0;
			CurrentScene = Title;
		}break;

		case 2:
		{
			CurrentScene->SceneState = 0;
			CurrentScene = Map;
		}break;

		case 3:
		{	CurrentScene->SceneState = 0;
			CurrentScene = Battle;
		}break;

		}
	}

	CurrentScene->Frame();

	return true;
}

bool SampleCore::Render()
{
	EditorCore::Render();
	CurrentScene->Render();

	return true;
}

bool SampleCore::Release()
{
	return EditorCore::Release();
}
