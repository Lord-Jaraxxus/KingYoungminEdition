#pragma once
#include "BaseScene.h"
#include "LoadingScene.h"
#include "TitleScene.h"
#include "MapScene.h"
#include "BattleScene.h"
#include "CardViewScene.h"

class SampleCore : public EditorCore
{
public:
	SampleCore();
	~SampleCore();

public:
	virtual bool Initialize() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;

public:
	void CardTextureLoad();
	void SceneChange();

public:
	BaseScene* CurrentScene;

	LoadingScene* Loading;
	TitleScene* Title;
	MapScene* Map;
	BattleScene* Battle;
	CardViewScene* CardView;

public:
	Deck* Dick;
	std::vector<DXTexture*> CardTextureList;
};