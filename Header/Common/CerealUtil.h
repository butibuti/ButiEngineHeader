#ifndef CEREALUTIL_H
#define CEREALUTIL_H
//cerial
#include "../../cereal/include/cereal/cereal.hpp"
#include "../../cereal/include/cereal/archives/binary.hpp"
#include "../../cereal/include/cereal/archives/portable_binary.hpp"
#include "../../cereal/include/cereal/archives/json.hpp"
#include "../../cereal/include/cereal/types/polymorphic.hpp"
#include "../../cereal/include/cereal/types/utility.hpp"
#include "../../cereal/include/cereal/types/string.hpp"
#include "../../cereal/include/cereal/types/unordered_map.hpp"
#include "../../cereal/include/cereal/types/map.hpp"
#include "../../cereal/include/cereal/types/tuple.hpp"
#include "../../cereal/include/cereal/types/vector.hpp"
#include "../../cereal/include/cereal/types/array.hpp"
#include"GlobalSettings.h"
#define BUTI_REGIST_CBUFFER(T)\
CEREAL_REGISTER_TYPE(ButiEngine::ButiRendering::CBuffer<T>);\
CEREAL_REGISTER_POLYMORPHIC_RELATION(ButiEngine::ButiRendering::ICBuffer, ButiEngine::ButiRendering::CBuffer<T>);\


#define BUTI_REGIST_BUTISCRIPTSHAREDTYPE(T)\
CEREAL_REGISTER_TYPE(ButiEngine::ValuePtrRestoreObject <Value_ptr< T >>); \
CEREAL_REGISTER_POLYMORPHIC_RELATION(ButiEngine::IValuePtrRestoreObject,ButiEngine::ValuePtrRestoreObject <Value_ptr< T >>); \


#define BUTI_REGIST_GAMECOMPONENT(T , IsOverrideOnUpdate)\
	CEREAL_REGISTER_TYPE(ButiEngine:: T);\
	CEREAL_REGISTER_POLYMORPHIC_RELATION(ButiEngine::GameComponent, ButiEngine:: T);\
namespace ComponentRegister{ namespace T {\
	static const ButiEngine::GameComponentRegister  componentregister = ButiEngine::GameComponentRegister(ButiEngine::ObjectFactory::Create<ButiEngine:: T>(),IsOverrideOnUpdate);\
	\
}}

#define BUTI_REGIST_BUTISCRIPTTYPE(T)\
	CEREAL_REGISTER_TYPE(ButiEngine::ValuePtrRestoreObject < T >);\
	CEREAL_REGISTER_POLYMORPHIC_RELATION(ButiEngine::IValuePtrRestoreObject, ButiEngine::ValuePtrRestoreObject< T >);\

namespace ButiEngine{

template<typename T>
void InputCereal(T& v, const std::string& arg_fileName)
{
#ifdef _EDITORBUILD
	std::stringstream stream;
	std::ifstream inputFile(GlobalSettings::GetResourceDirectory() + arg_fileName);
	stream << inputFile.rdbuf();
	cereal::JSONInputArchive jsonInputArchive(stream);
	jsonInputArchive(v);
#else
	std::stringstream stream;
	std::ifstream inputFile(GlobalSettings::GetResourceDirectory() + arg_fileName);
	stream << inputFile.rdbuf();
	cereal::JSONInputArchive jsonInputArchive(stream);
	jsonInputArchive(v);
#endif // EDITORBUILD	
}

template<typename T>
void OutputCereal(const T& v, const std::string& arg_fileName)
{
#ifdef _EDITORBUILD
	std::stringstream stream;
	{
		cereal::JSONOutputArchive jsonOutArchive(stream);
		jsonOutArchive(v);
	}
	std::ofstream outputFile(GlobalSettings::GetResourceDirectory() + arg_fileName);
	outputFile << stream.str();
	outputFile.close();
	stream.clear();
#else
	std::stringstream stream;
	{
		cereal::JSONOutputArchive jsonOutArchive(stream);
		jsonOutArchive(v);
	}
	std::ofstream outputFile(GlobalSettings::GetResourceDirectory() + arg_fileName);
	outputFile << stream.str();
	outputFile.close();
	stream.clear();
#endif
}
template<typename T>
static inline Value_ptr<T> CreateFromCereal(const std::string& arg_filePath) {
	Value_ptr<T> output = Value_ptr<T>();
	if (Util::ExistFile(GlobalSettings::GetResourceDirectory()+arg_filePath))
		InputCereal(output, arg_filePath);
	else {
		output = make_value<T>();
	}
	if constexpr (std::is_base_of_v<IObject, T>) {
		output->PreInitialize();
		output->Initialize();
	}
	return output;
};
}

#endif // !CEREALUTIL_H
