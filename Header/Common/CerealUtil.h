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
#include "../../ButiCereal/include/cereal/types/ButiContaier.hpp"
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



#define ARCHIVE_BUTI(v)\
	archive(CEREAL_NVP(v));

#define ARCHIVE2_BUTI(v,v2)\
	archive(CEREAL_NVP(v),CEREAL_NVP(v2));

#define ARCHIVE3_BUTI(v,v2,v3)\
	archive(CEREAL_NVP(v),CEREAL_NVP(v2),CEREAL_NVP(v3));

#define ARCHIVE4_BUTI(v,v2,v3,v4)\
	archive(CEREAL_NVP(v),CEREAL_NVP(v2),CEREAL_NVP(v3),CEREAL_NVP(v4));

namespace ButiEngine{

template<typename T>
void InputCereal(T& v, const std::string& arg_fileName)
{
#ifdef _EDITORBUILD
	if (!Util::ExistFile(GlobalSettings::GetResourceDirectory() + arg_fileName)) { return; }
	std::stringstream stream;
	std::ifstream inputFile(GlobalSettings::GetResourceDirectory() + arg_fileName);
	stream << inputFile.rdbuf();
	cereal::JSONInputArchive jsonInputARCHIVE_BUTI(stream);
	try
	{
		jsonInputARCHIVE_BUTI(v);
	}
	catch (const ButiException& ex)
	{
		std::cout << arg_fileName << "‚Ì“Ç‚Ýž‚Ý’†‚É—áŠO”­¶:" << ex.GetErrorMessage() << std::endl;
	}
	stream.clear();
#else

#ifdef RESOURCE_SYSTEM_H
	std::stringstream stream;
	stream << std::string(ResourceSystem::GetResourcePtr(arg_fileName), ResourceSystem::GetResourceSize(arg_fileName));
	cereal::PortableBinaryInputArchive binInputARCHIVE_BUTI(stream);
	binInputARCHIVE_BUTI(v);
#else
	std::stringstream stream;
	std::ifstream inputFile(GlobalSettings::GetResourceDirectory() + arg_fileName);
	stream << inputFile.rdbuf();
	cereal::PortableBinaryInputArchive binInputARCHIVE_BUTI(stream);
	binInputARCHIVE_BUTI(v);
	stream.clear();

#endif
#endif // EDITORBUILD	
}

template<typename T>
void OutputCereal(const T& v, const std::string& arg_fileName)
{
#ifdef _EDITORBUILD
	Util::MakeDirectory(GlobalSettings::GetResourceDirectory() + StringHelper::GetDirectory(arg_fileName));
	std::stringstream stream;
	{
		cereal::JSONOutputArchive jsonOutARCHIVE_BUTI(stream);
		jsonOutARCHIVE_BUTI(v);
	}
	std::ofstream outputFile(GlobalSettings::GetResourceDirectory() + arg_fileName);
	outputFile << stream.str();
	outputFile.close();
	stream.clear();
	std::ofstream outputBinCerealFile(GlobalSettings::GetResourceDirectory() + arg_fileName + ".cerealBin", std::ios::out | std::ios::binary);
	{
		cereal::PortableBinaryOutputArchive binOutARCHIVE_BUTI(outputBinCerealFile);
		binOutARCHIVE_BUTI(v);
	}
	outputBinCerealFile.close();
#else
#ifdef RESOURCE_SYSTEM_H
#else

	_mkdir((GlobalSettings::GetResourceDirectory() + StringHelper::GetDirectory(arg_fileName)).c_str());
	std::stringstream stream;
	{
		cereal::PortableBinaryOutputArchive binOutARCHIVE_BUTI(stream);
		binOutARCHIVE_BUTI(v);
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
