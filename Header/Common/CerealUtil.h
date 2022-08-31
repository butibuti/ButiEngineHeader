#ifndef CEREALUTIL_H
#define CEREALUTIL_H
//cerial
#include "../../ButiCereal/include/cereal/cereal.hpp"
#include "../../ButiCereal/include/cereal/archives/binary.hpp"
#include "../../ButiCereal/include/cereal/archives/portable_binary.hpp"
#include "../../ButiCereal/include/cereal/archives/json.hpp"
#include "../../ButiCereal/include/cereal/types/polymorphic.hpp"
#include "../../ButiCereal/include/cereal/types/utility.hpp"
#include "../../ButiCereal/include/cereal/types/string.hpp"
#include "../../ButiCereal/include/cereal/types/unordered_map.hpp"
#include "../../ButiCereal/include/cereal/types/map.hpp"
#include "../../ButiCereal/include/cereal/types/tuple.hpp"
#include "../../ButiCereal/include/cereal/types/vector.hpp"
#include "../../ButiCereal/include/cereal/types/array.hpp"
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
	CEREAL_REGISTER_POLYMORPHIC_RELATION(ButiEngine::IValuePtrRestoreObject, ButiEngine::ValuePtrRestoreObject< T >);

#define BUTI_REGIST_BUTISCRIPTTYPE_HASMEMBER(T)\
	CEREAL_REGISTER_TYPE(ButiEngine::ValuePtrRestoreObject <ButiScript::Type_hasMember< T> >);\
	CEREAL_REGISTER_POLYMORPHIC_RELATION(ButiEngine::IValuePtrRestoreObject,ButiEngine::ValuePtrRestoreObject <ButiScript::Type_hasMember< T> >);

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
	stream.clear();
#else

#ifdef RESOURCE_SYSTEM_H
	std::stringstream stream;
	stream << std::string(ResourceSystem::GetResourcePtr(arg_fileName), ResourceSystem::GetResourceSize(arg_fileName));
	cereal::PortableBinaryInputArchive binInputArchive(stream);
	binInputArchive(v);
#else
	std::stringstream stream;
	std::ifstream inputFile(GlobalSettings::GetResourceDirectory() + arg_fileName);
	stream << inputFile.rdbuf();
	cereal::PortableBinaryInputArchive binInputArchive(stream);
	binInputArchive(v);
	stream.clear();

#endif
#endif // EDITORBUILD	
}

template<typename T>
void OutputCereal(const T& v, const std::string& arg_fileName)
{
#ifdef _EDITORBUILD
	_mkdir((GlobalSettings::GetResourceDirectory() + StringHelper::GetDirectory(arg_fileName)).c_str());
	std::stringstream stream;
	{
		cereal::JSONOutputArchive jsonOutArchive(stream);
		jsonOutArchive(v);
	}
	std::ofstream outputFile(GlobalSettings::GetResourceDirectory() + arg_fileName);
	outputFile << stream.str();
	outputFile.close();
	stream.clear();
	std::ofstream outputBinCerealFile(GlobalSettings::GetResourceDirectory() + arg_fileName + ".cerealBin", std::ios::out | std::ios::binary);
	{
		cereal::PortableBinaryOutputArchive binOutArchive(outputBinCerealFile);
		binOutArchive(v);
	}
	outputBinCerealFile.close();
#else
#ifdef RESOURCE_SYSTEM_H
#else

	_mkdir((GlobalSettings::GetResourceDirectory() + StringHelper::GetDirectory(arg_fileName)).c_str());
	std::stringstream stream;
	{
		cereal::PortableBinaryOutputArchive binOutArchive(stream);
		binOutArchive(v);
	}
	std::ofstream outputCerealFile(GlobalSettings::GetResourceDirectory() + arg_fileName);
	outputCerealFile << stream.str();
	outputCerealFile.close();
	stream.clear();

#endif // RESOURCE_SYSTEM_H
#endif
}
template<typename T>
static inline Value_ptr<T> CreateFromCereal(const std::string& arg_filePath) {
	Value_ptr<T> output = Value_ptr<T>();
	if (
#ifdef RESOURCE_SYSTEM_H
		ResourceSystem::ExistResource(arg_filePath)
#else
		Util::ExistFile(arg_filePath)
#endif
		)
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
