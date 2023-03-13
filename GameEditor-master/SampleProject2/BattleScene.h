#pragma once
#include "BaseScene.h"
class BattleScene : public BaseScene
{
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;

public:
	void CardTextureLoad();

public:
	void BattleProcess();
	void TurnStartProcess();
	void TurnEndProcess();
	void CardCheck();
	void UpdateHand(int handSize);

public:
	Camera* MoveCamera;
	Camera* CloseupCamera;

//public:
//	MapComponent* Map;
//	
//public:
//	CharacterComponent* Chara_1P;
//	CharacterComponent* Chara_2P;
//	CharacterComponent* Enemy1;
//	CharacterComponent* Enemy2;

public:
	WidgetObject* TurnEndButton;
	WidgetObject* RemainCardButton;
	WidgetObject* DiscardButton;

public:
	WidgetObject* CardList[3] = { 0, };
	std::vector<DXTexture*> CardTextureList;
	Deck* Dick;

public:
	bool TurnState = true; // true면 내턴, false면 적턴
	bool TurnStart = true;
	int	 TurnNum = 1;
};

