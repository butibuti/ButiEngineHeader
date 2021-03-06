#include"ButiUtil/ButiUtil/ID.h"
#include"ButiRendering_Dx12/Header/ResourceInterface.h"
namespace ButiScript {
class CompiledData;
class Compiler;
}

namespace ButiFont {
class IFontInformation;
}
namespace ButiEngine {

namespace ButiRendering {
class IResource_Mesh;
class IResource_Motion;
class IResource_VertexShader;
class IResource_PixelShader;
class IResource_GeometryShader;
class IResource_Shader;
class IResource_Texture;
class IResource_Model;
class IResource_Material;
}

using MeshTag = ID<ButiRendering::IResource_Mesh>;
using MotionTag = ID<ButiRendering::IResource_Motion>;
using VertexShaderTag = ID < ButiRendering::IResource_VertexShader >;
using PixelShaderTag = ID<ButiRendering::IResource_PixelShader>;
using GeometryShaderTag = ID<ButiRendering::IResource_GeometryShader>;
using ShaderTag = ID<ButiRendering::IResource_Shader>;
using TextureTag = ID<ButiRendering::IResource_Texture>;
using ModelTag = ID<ButiRendering::IResource_Model>;
using MaterialTag = ID<ButiRendering::IResource_Material>;

class IResource_Script;
class IResource_Sound;

using ScriptTag = ID<IResource_Script>;
using SoundTag = ID<IResource_Sound>;

struct WaveDatas;
namespace ImageFileIO {
class IFontInformation;
}

class IResource_Sound :public IObject {
public:
	virtual Value_ptr<WaveDatas> GetWavDatas() = 0;
};


class IResource_Script :public IObject {
public:
	virtual void SetCompiler(ButiScript::Compiler* arg_compiler) = 0;
	virtual Value_ptr<ButiScript::CompiledData> GetCompiledData() = 0;
	/// <summary>
	/// 再コンパイル
	/// </summary>
	/// <returns>0＝成功/1＝失敗</returns>
	virtual std::int32_t Recompile() = 0;
	virtual void Reload() = 0;
	/// <summary>
	/// シーン上の全ての仮想マシンをホットリロード
	/// </summary>
	virtual void HotReload() = 0;
	virtual const std::string& GetScriptName()const=0;
	/// <summary>
	/// ソースファイルに変更があったかチェック、変更ありならそのまま再コンパイル
	/// </summary>
	/// <returns>0＝変更なし/1＝変更あり</returns>
	virtual std::int32_t SourceEditCheck() = 0;
};
class IResource_Font:public IObject {
public:
	virtual const std::string & GetFontName()const = 0;
	virtual TextureTag GetTextureTag()const = 0;
	virtual MaterialTag GetMaterialTag()const = 0;
	virtual ButiFont::IFontInformation* GetFontInformation() const= 0;
};
}