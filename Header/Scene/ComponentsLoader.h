#pragma once

#include "../GameObjects/GameComponent.h"
namespace ButiEngine {
class ComponentsLoader :public IObject {
public:

	static void CreateInstance();

	static  Value_ptr< ComponentsLoader> GetInstance();
	void Release();
	void AddGameComponentGenerateFunctionType(GameComponentGenerateFunctionType arg_function,const std::string&arg_name);

	Value_ptr<GameComponent> ShowAddGameComponentUI();

private:
	std::map<std::string, GameComponentGenerateFunctionType> m_map_gameComponentGenerateFunctions;
	std::int32_t m_index=-1;
	static Value_ptr< ComponentsLoader> instance;
};
}