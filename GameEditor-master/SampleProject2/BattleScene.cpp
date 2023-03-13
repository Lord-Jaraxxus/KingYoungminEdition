#include "BattleScene.h"

bool BattleScene::Init()
{
	UI_Loader Loader;

	// Actor ����
	Actor* UI = new Actor;
	UI->Name = L"Battle";
	auto bc = UI->AddComponent<WidgetComponent>();
	Loader.FileLoad(bc, L"../resource/UI/Save/Battle.txt");
	
	TurnEndButton = bc->FindObj(L"TurnEnd");
	RemainCardButton = bc->FindObj(L"Remain");
	DiscardButton = bc->FindObj(L"Discard");

	// ī�� ������Ʈ ���� �� ����Ʈ�� �־���
	CardList[0] = bc->FindObj(L"Card1");
	CardList[0]->m_bDraggable = true;
	CardList[1] = bc->FindObj(L"Card2");
	CardList[1]->m_bDraggable = true;
	CardList[2] = bc->FindObj(L"Card3");
	CardList[2]->m_bDraggable = true;

	// ī�� �ؽ�ó�� �ε�
	CardTextureLoad();



	// ���Ϳ� ī�޶� �߰�.
	//MainCamera = UI->AddComponent<Camera>(); // UI�� �ϸ����� ī�޶� �ʾ�
	

	// ���� ���忡 ���� �߰�.
	TheWorld.AddEntity(UI);

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

	// ���� ī�� Ȯ�� or ���� ī�� Ȯ�� ��ư Ŭ���� �� ��ȯ (ī�� ���� ������)
	//if (RemainCardButton->m_bClicked) //{ SceneState = cardview; RemainCardButton->m_bClicked = false; }
	//if (DiscardButton->m_bClicked) //{ SceneState = cardview; DiscardButton->m_bClicked = false; }

	//���� ���⼭ ���� ���ư��� �ɼ�������
	BattleProcess();

	return true;
}

bool BattleScene::Release()
{
	BaseScene::Release();
    return true;
}

void BattleScene::CardTextureLoad()
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

void BattleScene::BattleProcess()
{
	if (TurnStart) { TurnStartProcess(); }
	if (TurnEndButton->m_bClicked) { TurnEndProcess(); }
	CardCheck();
}

void BattleScene::TurnStartProcess()
{
	int drawNum = 3;

	for (int i = 0; i < drawNum; i++) { CardList[i]->m_bIsDead = false; }

	Dick->Draw(drawNum);
	UpdateHand(drawNum);

	TurnStart = false;
}

void BattleScene::TurnEndProcess()
{
	Dick->TurnEnd();
	//EnemyTurnProcess();
	TurnStart = true;

	TurnEndButton->m_bClicked = false;
}

void BattleScene::CardCheck()
{
	for (int cardNum=0; cardNum<Dick->HandList.size(); cardNum++) 
	{
		if (CardList[cardNum]->m_bClicked && CardList[cardNum]->m_OriginPos.y >= 0.5)
		{
			CardList[cardNum]->m_bClicked = false;
			CardList[cardNum]->m_OriginPos = CardList[cardNum]->m_OriginalOriginPos;

			switch (Dick->HandList[cardNum])
			{

			case Strike:
			{
				Dick->Use(cardNum);
			}break;

			case Defend:
			{
				Dick->Use(cardNum);
			}break;

			case PommelStrike:
			{
				Dick->Use(cardNum);
				Dick->Draw(1);
			}break;

			case ShrugItOff:
			{
				Dick->Use(cardNum);
				Dick->Draw(1);
			}break;

			case Hemokinesis:
			{
				Dick->Use(cardNum);
			}break;

			case Bludgeon:
			{
				Dick->Use(cardNum);
			}break;

			case IronWave:
			{
				Dick->Use(cardNum);
			}break;

			}

			UpdateHand(Dick->HandList.size());
		}
	}
}

void BattleScene::UpdateHand(int handSize)
{
	for (int card = 0; card < handSize; card++)
	{
		for (int ci = 0; ci < 4; ci++)
		{
			CardList[card]->m_pCutInfoList[ci]->tc = CardTextureList[Dick->HandList[card]];
		}
		CardList[card]->m_bIsDead = false;
	}
	
	for (int card = handSize; card < 3; card++) // for (int card = handSize; card < CardList.size(); card++)
	{
		CardList[card]->m_bIsDead = true;
	}
}
