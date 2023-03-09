#pragma once
#include "BaseScene.h"
#include "TitleScene.h"
#include "MapScene.h"

class SampleCore : public EditorCore
{
public:
	BaseScene*	CurrentScene;
	TitleScene* Title;
	MapScene*	Map;

public:
	SampleCore();
	~SampleCore();

public:
	virtual bool Initialize() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};