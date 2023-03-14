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
	CardTextureLoad();

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
	Battle->CardTextureList = CardTextureList;
	CardView = new CardViewScene;
	CardView->Init();
	CardView->Dick = Dick;
	CardView->CardTextureList = CardTextureList;

	CurrentScene = Title;
	//CurrentScene = Battle;
	

	return true;
}

bool SampleCore::Frame()
{
	EditorCore::Frame();
	SceneChange();
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

void SampleCore::CardTextureLoad()
{
	if (DXTextureManager::GetInstance()->Load(L"../resource/UI/Card/0_Strike.png"))
	{
		DXTexture* tc = DXTextureManager::GetInstance()->GetTexture(L"../resource/UI/Card/0_Strike.png");
		CardTextureList.push_back(tc);
	}

	if (DXTextureManager::GetInstance()->Load(L"../resource/UI/Card/1_Defend.png"))
	{
		DXTexture* tc = DXTextureManager::GetInstance()->GetTexture(L"../resource/UI/Card/1_Defend.png");
		CardTextureList.push_back(tc);
	}

	if (DXTextureManager::GetInstance()->Load(L"../resource/UI/Card/2_PommelStrike.png"))
	{
		DXTexture* tc = DXTextureManager::GetInstance()->GetTexture(L"../resource/UI/Card/2_PommelStrike.png");
		CardTextureList.push_back(tc);
	}

	if (DXTextureManager::GetInstance()->Load(L"../resource/UI/Card/3_ShrugItOff.png"))
	{
		DXTexture* tc = DXTextureManager::GetInstance()->GetTexture(L"../resource/UI/Card/3_ShrugItOff.png");
		CardTextureList.push_back(tc);
	}

	if (DXTextureManager::GetInstance()->Load(L"../resource/UI/Card/4_Hemokinesis.png"))
	{
		DXTexture* tc = DXTextureManager::GetInstance()->GetTexture(L"../resource/UI/Card/4_Hemokinesis.png");
		CardTextureList.push_back(tc);
	}

	if (DXTextureManager::GetInstance()->Load(L"../resource/UI/Card/5_Bludgeon.png"))
	{
		DXTexture* tc = DXTextureManager::GetInstance()->GetTexture(L"../resource/UI/Card/5_Bludgeon.png");
		CardTextureList.push_back(tc);
	}


	if (DXTextureManager::GetInstance()->Load(L"../resource/UI/Card/6_IronWave.png"))
	{
		DXTexture* tc = DXTextureManager::GetInstance()->GetTexture(L"../resource/UI/Card/6_IronWave.png");
		CardTextureList.push_back(tc);
	}
}

void SampleCore::SceneChange()
{
	if (CurrentScene->SS != maintain)
	{
		switch (CurrentScene->SS)
		{
		case loading:
		{
			CurrentScene->SS = maintain;
			CurrentScene = Loading;
		}break;

		case title:
		{
			CurrentScene->SS = maintain;
			CurrentScene = Title;
		}break;

		case map:
		{
			CurrentScene->SS = maintain;
			CurrentScene = Map;
		}break;

		case battle:
		{
			CurrentScene->SS = maintain;
			CurrentScene = Battle;
		}break;

		case deckView:
		{
			CardView->BeforeScene = CurrentScene->ID;
			CurrentScene->SS = maintain;
			CurrentScene = CardView;
			CardView->Update(deck);
		}break;

		case remainView:
		{
			CardView->BeforeScene = CurrentScene->ID;
			CurrentScene->SS = maintain;
			CurrentScene = CardView;
			CardView->Update(remain);
		}break;

		case discardView:
		{
			CardView->BeforeScene = CurrentScene->ID;
			CurrentScene->SS = maintain;
			CurrentScene = CardView;
			CardView->Update(discard);
		}break;

		}
	}
}
