#pragma once
#ifndef _SceneManager_H_
#define _SceneManager_H_

#include"stdafx.h"
#include<mutex>
namespace ButiEngine {
class IApplication;
Value_ptr<ISceneManager> CreateSceneManager(Value_ptr<IApplication> arg_vlp_app);

}
#endif // !_SceneManager_H_


