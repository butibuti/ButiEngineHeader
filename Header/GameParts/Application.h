#ifndef _BUTI_APPLICATION_H
#define _BUTI_APPLICATION_H

#pragma once
#include"stdafx.h"
namespace ButiEngine {

class ISceneManager;
class Window;
class ResourceContainer;



class Application :public IApplication
{
public:
	Application() {};
	void CreateInstances(GameAssetData::ApplicationInitData& arg_data);
	Value_ptr<IWindow> GetWindow()override;
	Value_ptr<ISceneManager> GetSceneManager()override;
	Value_ptr<ButiRendering::GraphicDevice> GetGraphicDevice()override;
	Value_ptr<IResourceContainer> GetResourceContainer()override;
	Value_ptr<ButiSound::ISoundManager> GetSoundManager()override;
	bool Update()override;
	std::int32_t Run()override;
	void InitLoadResources()override;
	void InitLoadResources_async()override;
	void PreLoadResources()override;
	void Exit()override;
	std::int64_t GetBefFrame()const override;
	const GameAssetData::ApplicationInitData* GetAppInitData()const override;
private:
	Value_ptr<ButiRendering::GraphicDevice>vlp_graphicDevice;
	Value_ptr<IWindow> vlp_window;
	Value_ptr< ISceneManager> vlp_sceneManager;
	Value_ptr<IResourceContainer>vlp_resourceContainer;
	Value_ptr<ButiSound::ISoundManager>vlp_soundManager;
	std::timespec currentTs;
	std::int64_t befFrameTime=0;
	std::int32_t frameTimesBuffIndex=0;
	float frameTimesBuff[60];
	GameAssetData::ApplicationInitData appInitData;
	FrameRateInformation frameInfo;
#ifdef _EDITORBUILD

	const FrameRateInformation& GetFrameInformation()const override;
#endif // _EDITORBUILD


	
};

}

#endif // !_BUTI_APPLICATION_H