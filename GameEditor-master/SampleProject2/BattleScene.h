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
	WidgetObject* Card1;
	WidgetObject* Card2;
	WidgetObject* Card3;
};

