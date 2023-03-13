#include "Sample.h"


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	WindowsClient sampleWindow;
	sampleWindow.Create(hInstance, L"Window Name", 1600, 900);

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
	
	Dick = new Deck;

	// 초기 로딩중에 로딩화면 바로 띄우기.. 인데 뭔가 원하는 그림이 안나오네..
	Loading = new LoadingScene;
	Loading->Init();
	Loading->Frame();
	Loading->Render();

	Title = new TitleScene;
	Title->Init();
	Map = new MapScene;
	Map->Init();	
	Battle = new BattleScene;
	Battle->Init();
	Battle->Dick = Dick;

	CurrentScene = Title;
	//CurrentScene = Battle;
	

	return true;
}

bool SampleCore::Frame()
{
	EditorCore::Frame();

	if (CurrentScene->SceneState != maintain) 
	{
		switch (CurrentScene->SceneState)
		{
		case loading : 
		{
			CurrentScene->SceneState = maintain;
			CurrentScene = Loading;
		}break;

		case title:
		{
			CurrentScene->SceneState = maintain;
			CurrentScene = Title;
		}break;

		case map:
		{	
			CurrentScene->SceneState = maintain;
			CurrentScene = Map;
		}break;

		case battle:
		{	
			CurrentScene->SceneState = maintain;
			CurrentScene = Battle;
		}break;

		case cardview:
		{
			CurrentScene->SceneState = maintain;
			CurrentScene = CardView;
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
