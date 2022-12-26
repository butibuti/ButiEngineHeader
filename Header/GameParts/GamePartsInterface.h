#ifndef GamePartInterface
#define GamePartInterface

#include"ButiUtil/ButiUtil/ObjectFactory.h"
#include"ButiMemorySystem/ButiMemorySystem/ButiPtr.h"
#include"ButiEngineHeader/Header/Common/GlobalSettings.h"
#include"GameAssetData.h"
namespace ButiBullet {
class RigidBody;
class PhysicsWorld;
class PhysicsManager;
}
namespace ButiSound {
class ISoundManager;
}
namespace ButiEngine 
{
	namespace Collision {
		class CollisionPrimitive;
	}

	namespace ButiRendering {
	class IDrawObject;
	template<typename T>
	class CBuffer;
	}
	class IScene;
	class IApplication;
	class SceneInformation;
	class GameObject;
	class GameObjectManager;
	class MaterialEditor;
	class ShaderEditor;
	class TextureEditor;
	class ScriptCompiler;
	namespace ImageFileIO {
	struct TextureResourceData;
	}


	class IResourceContainer;

	/// <summary>
	/// �E�B���h�E����C���^�[�t�F�[�X
	/// </summary>
	class IWindow
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="arg_windowName"�E�B���h�E�̖��O></param>
		/// <param name="arg_popType">�o���^�C�v</param>
		/// <param name="isFullScreen">�t���X�N���[���\��</param>
		/// <param name="width">��</param>
		/// <param name="height">����</param>
		virtual void Initialize(const std::string arg_windowName, const WindowPopType arg_popType,const bool isFullScreen, HINSTANCE& arg_hinstance ,const std::uint32_t width = 0,const std::uint32_t height = 0)=0;
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		virtual ~IWindow() {}
		/// <summary>
		/// �E�B���h�E�n���h���̎擾
		/// </summary>
		/// <returns>�E�B���h�E�n���h��</returns>
		virtual const HWND& GetHandle()=0;
		/// <summary>
		/// �T�C�Y�̎擾
		/// </summary>
		/// <returns></returns>
		virtual UInt2 GetSize()=0;
		/// <summary>
		/// �E�B���h�E�̒��S�ʒu�̎擾
		/// </summary>
		/// <returns>�E�B���h�E�̒��S�ʒu</returns>
		virtual Vector2 GetWindowCenterPosition()=0;
		/// <summary>
		/// �T�C�Y�̐ݒ�
		/// </summary>
		/// <param name="width">��</param>
		/// <param name="height">����</param>
		virtual void SetSize(const std::int32_t width,const std::int32_t height)=0;
		virtual bool Update()=0;
		/// <summary>
		/// �E�B���h�E�̍���[�̎擾
		/// </summary>
		/// <returns>�E�B���h�E�̍���[�̍��W</returns>
		virtual Vector2 GetWindowPosition()=0;
		/// <summary>
		/// �������
		/// </summary>
		virtual void Release()=0;
		/// <summary>
		/// �I����Ԃ�
		/// </summary>
		/// <returns>true->�I�𒆁@false->�I����ԂłȂ�</returns>
		virtual bool IsSelected() = 0;
		/// <summary>
		/// �I����Ԃɐ؂�ւ�����t���[����
		/// </summary>
		/// <returns>true->�I����Ԃɐ؂�ւ�����t���[���ł���@false->�I����Ԃɐ؂�ւ�����t���[���łȂ�</returns>
		virtual bool TriggerSelected() = 0;
#ifdef _EDITORBUILD
		/// <summary>
		/// �G�f�B�^�̃E�B���h�E�̑I����Ԃ��Z�b�g����(EditorBuild�̂�)
		/// </summary>
		/// <param name="arg_isActive">�G�f�B�^�̑I�����</param>
		/// <returns>���݂̑I�����</returns>
		virtual bool SetCurrentSelect(const bool arg_isSelect) = 0;
#endif // _EDITORBUILD

	private:

	};
	/// <summary>
	/// �V�[���Ǘ��C���^�[�t�F�[�X
	/// </summary>
	class ISceneManager :public IObject {

	public:

		virtual ~ISceneManager() {}
		virtual inline void Update() = 0;
		/// <summary>
		/// �V�[���̐ݒ�
		/// </summary>
		/// <param name="arg_sceneName">�V�[����</param>
		/// <param name="arg_vlp_scene">�V�[���̃C���X�^���X</param>
		virtual void SetScene(const std::string& arg_sceneName, Value_ptr<IScene> arg_vlp_scene) = 0;
		/// <summary>
		/// �Q�[���J�n���̃W�[���ݒ�
		/// </summary>
		/// <param name="arg_sceneName">�V�[����</param>
		/// <param name="arg_vlp_scene">�V�[���̃C���X�^���X</param>
		virtual void SetScene_Init(const std::string& arg_sceneName, Value_ptr<IScene> arg_vlp_scene) = 0;
		/// <summary>
		/// �V�[���̃��[�h
		/// </summary>
		/// <param name="arg_sceneName">�V�[����</param>
		/// <param name="arg_vlp_scene">�V�[���̃C���X�^���X(null�Ȃ疼�O���琶��)</param>
		virtual void LoadScene(const std::string& arg_sceneName, Value_ptr<SceneInformation> arg_vlp_scene = nullptr) = 0;
		/// <summary>
		/// �V�[���̃��[�h(�񓯊�)
		/// </summary>
		/// <param name="arg_sceneName">�V�[����</param>
		virtual void LoadScene_async(const std::string& arg_sceneName) = 0;
		/// <summary>
		/// �Q�[���J�n���̃V�[���̃��[�h
		/// </summary>
		/// <param name="arg_sceneName">�V�[����</param>
		/// <param name="arg_vlp_scene">�V�[���̃C���X�^���X(null�Ȃ疼�O���琶��)</param>
		virtual void LoadScene_Init(const std::string& arg_sceneName, Value_ptr<SceneInformation> arg_vlp_scene = nullptr) = 0;
		/// <summary>
		/// �V�[���̍폜
		/// </summary>
		/// <param name="arg_sceneName">�V�[����</param>
		virtual void RemoveScene(const std::string& arg_sceneName) = 0;
		/// <summary>
		/// �V�[���̐؂�ւ�
		/// </summary>
		/// <param name="arg_sceneName">�V�[����</param>
		virtual void ChangeScene(const std::string& arg_sceneName) = 0;
		/// <summary>
		/// �V�[���̃����[�h
		/// </summary>
		virtual void ReloadScene() = 0;
		/// <summary>
		/// �V�[���̃����[�h
		/// </summary>
		/// <param name="arg_sceneName">�����[�h����V�[����</param>
		virtual void ReloadScene(const std::string& arg_sceneName)=0;
		/// <summary>
		/// ���݂̃V�[���̎擾
		/// </summary>
		/// <returns>���݂̃V�[��</returns>
		virtual inline Value_ptr<IScene> GetCurrentScene()const = 0;
		/// <summary>
		/// 
		/// </summary>
		/// <returns>�ŐV�̃T�u�V�[��</returns>
		virtual inline Value_ptr<IScene> GetCurrentSubScene()const = 0;
		/// <summary>
		/// 
		/// </summary>
		/// <returns>�T�u�V�[���S��</returns>
		virtual inline const List<Value_ptr<IScene>>& GetCurrentSubScenes()const = 0;
		/// <summary>
		/// �A�v���P�[�V�����̎擾
		/// </summary>
		/// <returns>�A�v���P�[�V����</returns>
		virtual Value_ptr<IApplication> GetApplication() const= 0;
		/// <summary>
		/// �������
		/// </summary>
		virtual void Release() = 0;
		/// <summary>
		/// �V�[���̃��[�h����
		/// </summary>
		/// <returns>true=���[�h��/false=���[�h���Ă��Ȃ�</returns>
		virtual bool IsLoading() = 0;
		/// <summary>
		/// �T�u�V�[���̒ǉ�
		/// �V�[���̓T�u�V�[������܂Ŏ��Ă�
		/// </summary>
		virtual void PushSubScene(const std::string& arg_sceneName) = 0;
		/// <summary>
		/// �T�u�V�[���̍폜
		/// </summary>
		virtual void PopSubScene() = 0;
#ifdef _EDITORBUILD
		/// <summary>
		/// �V�[���̋N���A��~
		/// </summary>
		/// <param name="arg_isActive">true=�N��/false=��~</param>
		/// <returns>���݂̏��</returns>
		virtual bool SetActive(const bool arg_isActive) = 0;
		virtual void ReloadButtonPerform() = 0;
		virtual void SaveButtonPerform() = 0;
		/// <summary>
		/// �V�[���̕`��ɂ����������Ԃ̎擾
		/// </summary>
		/// <returns>�V�[���̕`��ɂ�����������(�~���b)</returns>
		virtual std::int32_t GetDrawMilliSecond()const = 0;
		/// <summary>
		/// �V�[���̍X�V�ɂ����������Ԃ̎擾
		/// </summary>
		/// <returns>�V�[���̍X�V�ɂ�����������(�~���b)</returns>
		virtual std::int32_t GetUpdateMilliSecond()const = 0;
		/// <summary>
		/// �V�[���̕`��ɂ����������Ԃ̎擾(60�t���[���̕���)
		/// </summary>
		/// <returns>����60�t���[���ɂ�����V�[���̕`��ɂ����������Ԃ̕���</returns>
		virtual float GetDrawMilliSecondAverage()const = 0;
		/// <summary>
		/// �V�[���̍X�V�ɂ����������Ԃ̎擾(60�t���[���̕���)
		/// </summary>
		/// <returns>����60�t���[���ɂ�����V�[���̍X�V�ɂ����������Ԃ̕���(�~���b)</returns>
		virtual float GetUpdateMilliSecondAverage()const = 0;
		virtual void SceneChangeButtonPerform(const std::string& arg_sceneName) = 0;
		virtual void Replay(const std::string& arg_logDir) = 0;
#endif

	};
	/// <summary>
	/// ���\�[�X�Ǘ��C���^�[�t�F�[�X
	/// </summary>
	class IResourceContainer :public IObject
	{
	public:

		/// <summary>
		/// �`��f�o�C�X�̐ݒ�
		/// </summary>
		/// <param name="arg_vlp_graphicDevice">�`��f�o�C�X</param>
		virtual void SetGraphicDevice(Value_weak_ptr<ButiRendering::GraphicDevice> arg_vlp_graphicDevice)=0;

		/// <summary>
		/// GUI�̌Ăяo��
		/// </summary>
		virtual void ShowGUI()=0;


		/// <summary>
		/// �N�����̃��\�[�X�̓ǂݍ���
		/// </summary>
		virtual void PreLoadResource() = 0;
		/// <summary>
		/// ���\�[�X�����ǂݍ��ݎ��̃��b�V���ǂݍ���
		/// </summary>
		virtual void InitMeshLoad() = 0;
		/// <summary>
		/// ���b�V���ǂݍ���
		/// </summary>
		virtual MeshTag LoadMesh(Value_ptr< ButiRendering::IResource_Mesh> arg_vlp_mesh) = 0;

		/// <summary>
		/// �l�𒼐ڎw�肵�ă}�e���A������
		/// </summary>
		/// <param name="arg_resourceMaterial">�}�e���A�����</param>
		/// <returns>�ǂݍ��񂾃}�e���A���̃^�O</returns>
		virtual MaterialTag LoadMaterial(const GameAssetData::MaterialAssetData& arg_resourceMaterial) =0;
		/// <summary>
		/// �}�e���A�����t�@�C������ǂݍ���
		/// </summary>
		/// <param name="arg_fileName">�t�@�C���̃p�X/param>
		/// <returns>�ǂݍ��񂾃}�e���A���̃^�O</returns>
		virtual MaterialTag LoadMaterial(const std::string& arg_fileName)=0;
		/// <summary>
		/// �}�e���A���̈ꊇ�ǂݍ���
		/// </summary>
		/// <param name="arg_list_filePathAndDirectory">�ǂݍ��ݏ���vector</param>
		/// <returns>�ǂݍ��񂾃}�e���A���̃^�O��vector</returns>
		virtual List < MaterialTag> LoadMaterial(const List<GameAssetData::MaterialAssetData>& arg_list_loadInfo) = 0;
		/// <summary>
		/// �}�e���A���̈ꊇ�ǂݍ���
		/// </summary>
		/// <param name="arg_list_filePathAndDirectory">�ǂݍ��݃t�@�C���p�X��vector</param>
		/// <returns>�ǂݍ��񂾃}�e���A���̃^�O��vector</returns>
		virtual List < MaterialTag> LoadMaterial(const List<std::string>& arg_list_filePathAndDirectory) = 0;
		/// <summary>
		/// �e�N�X�`���ǂݍ���
		/// </summary>
		/// <param name="arg_filePath">�e�N�X�`���̃p�X</param>
		/// <returns></returns>
		virtual TextureTag LoadTexture(const std::string& arg_filePath) = 0;
		/// <summary>
		/// �e�N�X�`���ǂݍ���
		/// </summary>
		/// <param name="arg_filePath">�e�N�X�`���̃p�X</param>
		/// <param name="arg_assetData">�����_�[�^�[�Q�b�g�e�N�X�`���̏��</param>
		/// <returns></returns>
		virtual TextureTag LoadTexture(const std::string& arg_filePath,const GameAssetData::RenderTargetAssetData& arg_assetData) = 0;
		/// <summary>
		/// �e�N�X�`���ǂݍ���
		/// </summary>
		/// <param name="arg_filePath">�e�N�X�`���̃p�X</param>
		/// <param name="arg_assetData">�[�x�e�N�X�`���̏��</param>
		/// <returns></returns>
		virtual TextureTag LoadTexture(const std::string& arg_filePath,const GameAssetData::DepthStencilAssetData& arg_assetData) = 0;
		/// <summary>
		/// �e�N�X�`���쐬
		/// </summary>
		/// <param name="arg_texName">�e�N�X�`���̌����Ɏg�p���閼�O</param>
		/// <param name="arg_p_pixelSrc">�摜�f�[�^</param>
		/// <param name="arg_width">���T�C�Y</param>
		/// <param name="arg_height">�c�T�C�Y</param>
		/// <param name="arg_pixelSize">��s�N�Z���ӂ�̑傫��</param>
		/// <param name="arg_format">�t�H�[�}�b�g</param>
		/// <returns></returns>
		virtual TextureTag LoadTexture(const std::string& arg_texName, void* arg_p_pixelSrc, const std::int32_t arg_width, const std::int32_t arg_height, const std::int32_t arg_pixelSize, const std::int32_t arg_format) = 0;
		/// <summary>
		/// �e�N�X�`���쐬
		/// </summary>
		/// <param name="arg_texName">�e�N�X�`���̌����Ɏg�p���閼�O</param>
		/// <param name="arg_texResourceData">�e�N�X�`���̏��</param>
		/// <returns></returns>
		virtual TextureTag LoadTexture(const std::string& arg_texName,Value_ptr<ImageFileIO::TextureResourceData> arg_texResourceData) = 0;
		/// <summary>
		/// �e�N�X�`���̈ꊇ�ǂݍ���
		/// </summary>
		/// <param name="arg_list_filePathAndDirectory">�e�N�X�`���p�X��vector</param>
		/// <returns>�ǂݍ��񂾃e�N�X�`���̃^�O��vector</returns>
		virtual List < TextureTag> LoadTexture(const List<std::string>& arg_list_filePathAndDirectory)=0;
		/// <summary>
		/// �s�N�Z���V�F�[�_�̓ǂݍ���
		/// </summary>
		/// <param name="arg_shader">�V�F�[�_</param>
		/// <returns>�ǂݍ��񂾃V�F�[�_�̃^�O</returns>
		virtual PixelShaderTag LoadPixelShader(Value_ptr<ButiRendering::IResource_PixelShader> arg_shader) = 0;
		/// <summary>
		/// �s�N�Z���V�F�[�_�̓ǂݍ���
		/// </summary>
		/// <param name="arg_filePath">�t�@�C����</param>
		/// <returns>�ǂݍ��񂾃V�F�[�_�̃^�O</returns>
		virtual PixelShaderTag LoadPixelShader(const std::string& arg_filePath) = 0;
		/// <summary>
		/// �s�N�Z���V�F�[�_�̈ꊇ�ǂݍ���
		/// </summary>
		/// <param name="arg_list_filePathAndDirectory">�t�@�C���p�X��vector</param>
		/// <returns>�ǂݍ��񂾃V�F�[�_�̃^�O��vector</returns>
		virtual List < PixelShaderTag> LoadPixelShader(const List<std::string>& arg_list_filePathAndDirectory)=0;

		/// <summary>
		/// ���_�V�F�[�_�̓ǂݍ���
		/// </summary>
		/// <param name="arg_shader">�V�F�[�_</param>
		/// <returns>�ǂݍ��񂾃V�F�[�_�̃^�O</returns>
		virtual VertexShaderTag LoadVertexShader(Value_ptr<ButiRendering::IResource_VertexShader> arg_shader) = 0;
		/// <summary>
		/// ���_�V�F�[�_�̓ǂݍ���
		/// </summary>
		/// <param name="arg_filePath">�t�@�C����</param>
		/// <returns>�ǂݍ��񂾃V�F�[�_�̃^�O</returns>
		virtual VertexShaderTag LoadVertexShader(const std::string& arg_filePath) = 0;
		/// <summary>
		/// ���_�V�F�[�_�̈ꊇ�ǂݍ���
		/// </summary>
		/// <param name="arg_list_filePathAndDirectory">�t�@�C���p�X��vector</param>
		/// <returns>�ǂݍ��񂾃V�F�[�_�̃^�O��vector</returns>
		virtual List < VertexShaderTag> LoadVertexShader(const List<std::string>& arg_list_filePathAndDirectory)=0;

		/// <summary>
		/// �W�I���g���V�F�[�_�̓ǂݍ���
		/// </summary>
		/// <param name="arg_shader">�V�F�[�_</param>
		/// <returns>�ǂݍ��񂾃V�F�[�_�̃^�O</returns>
		virtual GeometryShaderTag LoadGeometryShader(Value_ptr<ButiRendering::IResource_GeometryShader> arg_shader) = 0;
		/// <summary>
		/// �W�I���g���V�F�[�_�̓ǂݍ���
		/// </summary>
		/// <param name="arg_filePath">�t�@�C����</param>
		/// <returns>�ǂݍ��񂾃V�F�[�_�̃^�O</returns>
		virtual GeometryShaderTag LoadGeometryShader(const std::string& arg_filePath) = 0;
		/// <summary>
		/// �W�I���g���V�F�[�_�̈ꊇ�ǂݍ���
		/// </summary>
		/// <param name="arg_list_filePathAndDirectory">�t�@�C���p�X��vector</param>
		/// <returns>�ǂݍ��񂾃V�F�[�_�̃^�O��vector</returns>
		virtual List < GeometryShaderTag> LoadGeometryShader(const List<std::string>& arg_list_filePathAndDirectory)=0;

		/// <summary>
		/// �V�F�[�_�̐���
		/// </summary>
		/// <param name="arg_shaderInfos">�V�F�[�_�̏��</param>
		/// <returns>���������V�F�[�_�̃^�O</returns>
		virtual ShaderTag LoadShader(const  GameAssetData::ShaderAssetData& arg_shaderInfos) = 0;
		/// <summary>
		/// �V�F�[�_�̐���
		/// </summary>
		/// <param name="arg_shaderInfos">�V�F�[�_�̃t�@�C���p�X</param>
		/// <returns>���������V�F�[�_�̃^�O</returns>
		virtual ShaderTag LoadShader(const  std::string& arg_shaderFilePath) = 0;
		/// <summary>
		/// �V�F�[�_�̈ꊇ����
		/// </summary>
		/// <param name="arg_list_shaderPath">�t�@�C���p�X��vector</param>
		/// <returns>���������V�F�[�_��vector</returns>
		virtual List < ShaderTag> LoadShader(const List<std::string>& arg_list_shaderPath)=0;
		/// <summary>
		/// �V�F�[�_�̈ꊇ����
		/// </summary>
		/// <param name="arg_list_shaderInfos">�V�F�[�_����vector</param>
		/// <returns>���������V�F�[�_��vector</returns>
		virtual List < ShaderTag> LoadShader(const List<GameAssetData::ShaderAssetData>& arg_list_shaderInfos) = 0;
		/// <summary>
		/// �����̓ǂݍ���
		/// </summary>
		/// <param name="arg_filePath">�t�@�C����</param>
		/// <returns>�ǂݍ��񂾉����̃^�O</returns>
		virtual SoundTag LoadSound(const std::string& arg_filePath)=0;
		/// <summary>
		/// �����̈ꊇ�ǂݍ���
		/// </summary>
		/// <param name="arg_list_filePathAndDirectory">�t�@�C���p�X��vector</param>
		/// <returns>�ǂݍ��񂾉�����vector</returns>
		virtual List < SoundTag> LoadSound(const List<std::string>& arg_list_filePathAndDirectory)=0;

		/// <summary>
		/// ���f���f�[�^�̓ǂݍ���
		/// </summary>
		/// <param name="arg_filePath">�t�@�C����</param>
		/// <returns>�ǂݍ��񂾃��f���̃^�O</returns>
		virtual ModelTag LoadModel(const std::string& arg_filePath) = 0;
		/// <summary>
		/// ���f���f�[�^�̈ꊇ�ǂݍ���
		/// </summary>
		/// <param name="arg_list_filePathAndDirectory">�t�@�C���p�X��vector</param>
		/// <returns>�ǂݍ��񂾃��f���̃^�O��vector</returns>
		virtual List<ModelTag> LoadModel(const List<std::string>& arg_list_filePathAndDirectory)=0;

		/// <summary>
		/// ���[�V�����f�[�^�̓ǂݍ���
		/// </summary>
		/// <param name="arg_filePath">�t�@�C����</param>
		/// <returns>�ǂݍ��񂾃��[�V�����̃^�O</returns>
		virtual MotionTag LoadMotion(const std::string& arg_filePath) = 0;
		/// <summary>
		/// ���[�V�����f�[�^�̈ꊇ�ǂݍ���
		/// </summary>
		/// <param name="arg_list_filePathAndDirectory">�t�@�C���p�X��vector</param>
		/// <returns>�ǂݍ��񂾃��[�V�����̃^�O��vector</returns>
		virtual List<MotionTag> LoadMotion(const List<std::string>& arg_list_filePathAndDirectory)=0;
		/// <summary>
		/// �R���p�C���ς݃X�N���v�g�̓ǂݍ���
		/// </summary>
		/// <param name="arg_filePath">�t�@�C����</param>
		/// <returns>�ǂݍ��񂾃X�N���v�g�̃^�O</returns>
		virtual ScriptTag LoadScript(const std::string& arg_filePath) = 0;
		/// <summary>
		/// �X�N���v�g�̈ꊇ�ǂݍ���
		/// </summary>
		/// <param name="arg_list_filePathAndDirectory">�t�@�C���p�X��vector</param>
		/// <returns>�ǂݍ��񂾃X�N���v�g�̃^�O��vector</returns>
		virtual List<ScriptTag> LoadScript(const List<std::string>& arg_list_filePathAndDirectory) = 0;


		/// <summary>
		/// TrueTypeFont�̓ǂݍ���
		/// </summary>
		/// <param name="arg_filePath">�t�@�C����</param>
		/// <returns>�ǂݍ��񂾃t�H���g�̃^�O</returns>
		virtual FontTag LoadFont(const std::string& arg_filePath) = 0;
		/// <summary>
		/// �t�H���g�̈ꊇ�ǂݍ���
		/// </summary>
		/// <param name="arg_list_filePathAndDirectory">�t�@�C���p�X��vector</param>
		/// <returns>�ǂݍ��񂾃t�H���g�̃^�O��vector</returns>
		virtual List < FontTag> LoadFont(const List<std::string>& arg_list_filePathAndDirectory) = 0;
		/// <summary>
		/// �e�L�X�g�`��p���b�V���̐���
		/// </summary>
		/// <param name="arg_glyphMesh">�X�V�p�̖��O</param>
		/// <param name="glyphCount">������</param>
		/// <returns></returns>
		virtual MeshTag CreateTextMesh(const std::string& arg_glyphMesh, const std::int32_t glyphCount) = 0;
		/// <summary>
		/// �X�N���v�g�̃\�[�X�t�@�C�����X�V����Ă��Ȃ����`�F�b�N
		/// </summary>
		virtual void ScriptEditCheck() = 0;

		virtual List<TextureTag> GetTextureTags()const = 0;
		virtual List<ModelTag> GetModelTags()const = 0;
		virtual List<MeshTag> GetMeshTags()const = 0;
		virtual List<ScriptTag> GetScriptTags()const = 0;
		virtual List<SoundTag> GetSoundTags()const = 0;
		virtual List<MotionTag> GetMotionTags()const = 0;
		virtual List<FontTag> GetFontTags()const = 0;
		virtual List<VertexShaderTag> GetVertexShaderTags()const = 0;
		virtual List<GeometryShaderTag> GetGeometryShaderTags()const = 0;
		virtual List<PixelShaderTag> GetPixelShaderTags()const = 0;
		virtual List<ShaderTag> GetShaderTags()const = 0;
		virtual List<MaterialTag> GetMaterialTags()const = 0;

		virtual List<std::string> GetLoadedTextureNames()const = 0;
		virtual List<std::string> GetLoadedModelNames()const = 0;
		virtual List<std::string> GetLoadedMeshNames()const = 0;
		virtual List<std::string> GetLoadedScriptNames()const = 0;
		virtual List<std::string> GetLoadedSoundNames()const = 0;
		virtual List<std::string> GetLoadedMotionNames()const = 0;
		virtual List<std::string> GetLoadedFontNames()const = 0;
		virtual List<std::string> GetLoadedVertexShaderNames()const = 0;
		virtual List<std::string> GetLoadedGeometryShaderNames()const = 0;
		virtual List<std::string> GetLoadedPixelShaderNames()const = 0;
		virtual List<std::string> GetLoadedShaderNames()const = 0;
		virtual List<std::string> GetLoadedMaterialNames()const = 0;

		/// <summary>
		/// ���b�V���̍폜
		/// </summary>
		/// <param name="arg_meshTag">�폜����^�O</param>
		virtual void UnLoad(MeshTag arg_meshTag)=0;
		/// <summary>
		/// �e�N�X�`���̍폜
		/// </summary>
		/// <param name="arg_textureTag">�폜����^�O</param>
		virtual void UnLoad(TextureTag arg_textureTag)=0;
		/// <summary>
		/// �V�F�[�_�̍폜
		/// </summary>
		/// <param name="arg_shaderTag">�폜����^�O</param>
		virtual void UnLoad(ShaderTag arg_shaderTag)=0;
		/// <summary>
		/// �s�N�Z���V�F�[�_�̍폜
		/// </summary>
		/// <param name="arg_shaderTag">�폜����^�O</param>
		virtual void UnLoad(PixelShaderTag arg_shaderTag)=0;
		/// <summary>
		/// ���_�V�F�[�_�̍폜
		/// </summary>
		/// <param name="arg_shaderTag">�폜����^�O</param>
		virtual void UnLoad(VertexShaderTag arg_shaderTag)=0;
		/// <summary>
		/// �W�I���g���V�F�[�_�̍폜
		/// </summary>
		/// <param name="arg_shaderTag">�폜����^�O</param>
		virtual void UnLoad(GeometryShaderTag arg_shaderTag)=0;
		/// <summary>
		/// �����̍폜
		/// </summary>
		/// <param name="arg_soundTag">�폜����^�O</param>
		virtual void UnLoad(SoundTag arg_soundTag)=0;
		/// <summary>
		/// ���f���̍폜
		/// </summary>
		/// <param name="arg_modelTag">�폜����^�O</param>
		virtual void UnLoad(ModelTag arg_modelTag)=0;
		/// <summary>
		/// �}�e���A���̍폜
		/// </summary>
		/// <param name="arg_materialTag">�폜����^�O</param>
		virtual void UnLoad(MaterialTag arg_materialTag)=0;
		/// <summary>
		/// ���[�V�����̍폜
		/// </summary>
		/// <param name="arg_motionTag">�폜����^�O</param>
		virtual void UnLoad(MotionTag arg_motionTag) = 0;
		/// <summary>
		/// �X�N���v�g�̍폜
		/// </summary>
		/// <param name="arg_motionTag">�폜����^�O</param>
		virtual void UnLoad(ScriptTag arg_scriptTag) = 0;
		/// <summary>
		/// �t�H���g�̍폜
		/// </summary>
		/// <param name="arg_motionTag">�폜����^�O</param>
		virtual void UnLoad(FontTag arg_fontTag) = 0;

		/// <summary>
		/// �������
		/// </summary>
		virtual void Release()=0;

		/// <summary>
		/// ���b�V���̎擾
		/// </summary>
		/// <param name="arg_key">�����^�O</param>
		/// <returns>���b�V���̃��\�[�X</returns>
		virtual Value_weak_ptr<ButiRendering::IResource_Mesh> GetMesh(const  MeshTag& arg_key)=0;
		/// <summary>
		/// �e�N�X�`���̎擾
		/// </summary>
		/// <param name="arg_key">�����^�O</param>
		/// <returns>�e�N�X�`���̃��\�[�X</returns>
		virtual Value_weak_ptr<ButiRendering::IResource_Texture> GetTexture(const TextureTag& arg_key)=0;
		/// <summary>
		/// �V�F�[�_�̎擾
		/// </summary>
		/// <param name="arg_key">�����^�O</param>
		/// <returns>�V�F�[�_�̃��\�[�X</returns>
		virtual Value_weak_ptr<ButiRendering::IResource_Shader> GetShader(const ShaderTag& arg_key)=0;
		/// <summary>
		/// �����̎擾
		/// </summary>
		/// <param name="arg_key">�����^�O</param>
		/// <returns>�����̃��\�[�X</returns>
		virtual Value_weak_ptr<ButiSound::IResource_Sound> GetSound(const SoundTag& arg_key)=0;
		/// <summary>
		/// �}�e���A���̎擾
		/// </summary>
		/// <param name="arg_key">�����^�O</param>
		/// <returns>�}�e���A���̃��\�[�X</returns>
		virtual Value_weak_ptr<ButiRendering::IResource_Material>GetMaterial(const MaterialTag& arg_key)=0;
		/// <summary>
		/// �x���V�F�[�f�B���O�p�̃}�e���A�����X�g�̎擾
		/// </summary>
		/// <returns></returns>
		virtual void CreateDeferredMaterialList(ButiRendering::MaterialValue_Deferred& arg_ref_output) = 0;
		/// <summary>
		/// ���f���̎擾
		/// </summary>
		/// <param name="arg_key">�����^�O</param>
		/// <returns>���f���̃��\�[�X</returns>
		virtual Value_weak_ptr<ButiRendering::IResource_Model>GetModel(const ModelTag& arg_key)=0;
		/// <summary>
		/// ���[�V�����̎擾
		/// </summary>
		/// <param name="arg_key">�����^�O</param>
		/// <returns>���[�V�����̃��\�[�X</returns>
		virtual Value_weak_ptr<ButiRendering::IResource_Motion>GetMotion(const MotionTag& arg_key)=0;
		/// <summary>
		/// �R���p�C���ς݃X�N���v�g�̎擾
		/// </summary>
		/// <param name="arg_key">�����^�O</param>
		/// <returns>�X�N���v�g�̃��\�[�X</returns>
		virtual Value_weak_ptr<IResource_Script>GetScript(const ScriptTag& arg_key) = 0;
		/// <summary>
		/// �t�H���g�̎擾
		/// </summary>
		/// <param name="arg_key">�����^�O</param>
		/// <returns>�t�H���g�̃��\�[�X</returns>
		virtual Value_weak_ptr<ButiRendering::IResource_Font>GetFont(const FontTag& arg_key) = 0;

		virtual bool Exist(const TextureTag& arg_tag)const = 0;
		virtual bool Exist(const MeshTag& arg_tag)const = 0;
		virtual bool Exist(const ModelTag& arg_tag)const = 0;
		virtual bool Exist(const MaterialTag& arg_tag)const = 0;
		virtual bool Exist(const ScriptTag& arg_tag)const = 0;
		virtual bool Exist(const SoundTag& arg_tag)const = 0;
		virtual bool Exist(const ShaderTag& arg_tag)const = 0;
		virtual bool Exist(const VertexShaderTag& arg_tag)const = 0;
		virtual bool Exist(const PixelShaderTag& arg_tag)const = 0;
		virtual bool Exist(const GeometryShaderTag& arg_tag)const = 0;
		virtual bool Exist(const MotionTag& arg_tag)const = 0;
		virtual bool Exist(const FontTag& arg_tag)const = 0;

		virtual List < Value_ptr <ButiRendering::IResource_Mesh >>GetMeshes()const = 0;
		virtual List < Value_ptr <ButiRendering::IResource_Model >>GetModels()const = 0;
		virtual List < Value_ptr <ButiRendering::IResource_Texture >>GetTextures()const = 0;
		virtual List < Value_ptr <ButiRendering::IResource_Material >>GetMaterials()const = 0;
		virtual List < Value_ptr <ButiRendering::IResource_Shader >>GetShaders()const = 0;
		virtual List < Value_ptr <ButiRendering::IResource_VertexShader >>GetVertexShaders()const = 0;
		virtual List < Value_ptr <ButiRendering::IResource_PixelShader >>GetPixelShaders()const = 0;
		virtual List < Value_ptr <ButiRendering::IResource_GeometryShader >>GetGeometryShaders()const = 0;
		virtual List < Value_ptr <ButiRendering::IResource_Motion >>GetMotions()const = 0;
		virtual List < Value_ptr <ButiRendering::IResource_Font >>GetFonts()const = 0;
		virtual List < Value_ptr <ButiSound::IResource_Sound>>GetSounds()const = 0;
		virtual List < Value_ptr <IResource_Script>>GetScripts()const = 0;

		/// <summary>
		/// �ēǂݍ���
		/// </summary>
		virtual void LoadResource() = 0;
		/// <summary>
		/// �ēǂݍ���(�񓯊�)
		/// </summary>
		virtual void LoadResource_async() = 0;

		virtual void WaitLoading() = 0;

		virtual void MaterialListUpdate()=0;
		virtual Value_ptr<MaterialEditor> GetMaterialEditor()const = 0;
		virtual Value_ptr<ShaderEditor> GetShaderEditor()const = 0;
		virtual Value_ptr<TextureEditor> GetTextureEditor()const = 0;
		virtual Value_ptr<ScriptCompiler> GetScriptCompiler()const = 0;

		virtual Value_weak_ptr<IApplication> GetApplication()const = 0;
	};

	/// <summary>
	/// �A�v���P�[�V�����̃C���^�[�t�F�[�X
	/// </summary>
	class IApplication :public IObject
	{
	public:
		struct FrameRateInformation {
			float averageFPS;
			float currentFPS;
			std::int32_t drawMillSec;
			std::int32_t updateMillSec;
		};
		/// <summary>
		/// �E�B���h�E�̎擾
		/// </summary>
		/// <returns></returns>
		virtual Value_ptr<IWindow> GetWindow()=0;
		/// <summary>
		/// �V�[���}�l�[�W���[�̎擾
		/// </summary>
		/// <returns></returns>
		virtual Value_ptr<ISceneManager> GetSceneManager()=0;
		/// <summary>
		/// �`��f�o�C�X�̎擾
		/// </summary>
		/// <returns></returns>
		virtual Value_ptr<ButiRendering::GraphicDevice> GetGraphicDevice()=0;
		/// <summary>
		/// ���\�[�X�Ǘ��C���^�[�t�F�[�X�̎擾
		/// </summary>
		/// <returns>���\�[�X�Ǘ��C���^�[�t�F�[�X</returns>
		virtual Value_ptr<IResourceContainer> GetResourceContainer()=0;
		/// <summary>
		/// �����Ǘ��C���X�^���X�̎擾
		/// </summary>
		/// <returns>�����Ǘ��C���X�^���X</returns>
		virtual Value_ptr<ButiSound::ISoundManager> GetSoundManager() = 0;
		/// <summary>
		/// �X�V����
		/// </summary>
		/// <returns></returns>
		virtual bool Update()=0;
		/// <summary>
		/// ���s
		/// </summary>
		/// <returns></returns>
		virtual std::int32_t Run()=0;
		/// <summary>
		/// �ŏ��ɓǂݍ��ރ��\�[�X�̃��[�h
		/// </summary>
		virtual void PreLoadResources() = 0;
		/// <summary>
		/// ���\�[�X�R���e�i�ɋL�^����Ă��郊�\�[�X�̓ǂݍ���
		/// </summary>
		virtual void InitLoadResources() = 0;
		/// <summary>
		/// ���\�[�X�R���e�i�ɋL�^����Ă��郊�\�[�X�̓ǂݍ���(�񓯊�)
		/// </summary>
		virtual void InitLoadResources_async() = 0;
		/// <summary>
		/// �I������
		/// </summary>
		virtual void Exit()=0;
		/// <summary>
		/// �O��̃t���[���̏��v����(�~���b)
		/// </summary>
		/// <returns>�O��̃t���[���̏��v����(�~���b)</returns>
		virtual std::int64_t GetBefFrame()const = 0;
		virtual const GameAssetData::ApplicationInitData* GetAppInitData()const=0;

#ifdef _EDITORBUILD
		virtual const FrameRateInformation& GetFrameInformation()const=0;
#endif
	};

	class SceneInformation;
	class SceneChangeInformation;
	class SceneRenderingInformation;
	/// <summary>
	/// �V�[���̃C���^�[�t�F�[�X
	/// </summary>
	class IScene :public IObject
	{
	public:
		/// <summary>
		/// �X�V����
		/// </summary>
		virtual void Update() = 0;
		/// <summary>
		/// UI�X�V
		/// </summary>
		virtual void UIUpdate() = 0;
		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̓o�^
		/// </summary>
		virtual void RegistGameObjects() = 0;
		/// <summary>
		/// �`��O
		/// </summary>
		virtual void BefDraw() = 0;
		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() = 0;
		/// <summary>
		/// �ҏW���[�h�ł̃J�����̑���
		/// </summary>
		virtual void EditCameraUpdate() = 0;
		/// <summary>
		/// �J�����̎擾
		/// </summary>
		/// <param name="arg_camName">�J������</param>
		/// <returns> �J�����̎擾</returns>
		virtual Value_ptr<ButiRendering::ICamera> GetCamera(const std::string& arg_camName) = 0;
		/// <summary>
		///  �J�����̎擾
		/// </summary>
		/// <param name="arg_camNum">�`��p�X�̃C���f�b�N�X</param>
		/// <returns>�J�����̎擾</returns>
		virtual Value_ptr<ButiRendering::ICamera> GetCamera(const std::uint32_t arg_camNum = 0) = 0;
		/// <summary>
		/// �`��p�X�̒ǉ�
		/// </summary>
		/// <param name="arg_path">�`��p�X</param>
		/// <returns>�ǉ����ꂽ�`��p�X</returns>
		virtual Value_ptr<ButiRendering::IRenderingPath> AddRenderingPath(Value_ptr<ButiRendering::IRenderingPath> arg_path) = 0;
		/// <summary>
		/// �`��p�X�̍폜
		/// </summary>
		/// <param name="arg_pathName">�g�p����L�[</param>
		virtual void RemoveRenderingPath(const std::string& arg_pathName) = 0;
		/// <summary>
		/// �`��p�X�̍폜
		/// </summary>
		/// <param name="arg_pathIndex">�`��p�X�̃C���f�b�N�X</param>
		virtual void RemoveRenderingPath(const std::uint32_t arg_pathIndex) = 0;
		/// <summary>
		/// �`��p�X�̎擾
		/// </summary>
		/// <param name="arg_pathName">�g�p����L�[</param>
		virtual Value_ptr<ButiRendering::IRenderingPath> GetRenderingPath(const std::string& arg_pathName)const = 0;
		/// <summary>
		/// �`��p�X�̎擾
		/// </summary>
		/// <param name="arg_pathIndex">�`��p�X�̃C���f�b�N�X</param>
		virtual Value_ptr<ButiRendering::IRenderingPath> GetRenderingPath(const std::uint32_t arg_pathIndex)const = 0;
		virtual std::int32_t GetRenderingPathCount()const = 0;
		/// <summary>
		/// �`��Ǘ��C���X�^���X�̎擾
		/// </summary>
		/// <returns>�`��Ǘ��C���X�^���X</returns>
		virtual Value_ptr<ButiRendering::IRenderer> GetRenderer() = 0;
		/// <summary>
		/// ���\�[�X�Ǘ��C���X�^���X�̎擾
		/// </summary>
		/// <returns>���\�[�X�Ǘ��C���X�^���X</returns>
		virtual Value_ptr<IResourceContainer> GetResourceContainer() = 0;
		/// <summary>
		/// �V�[���Ǘ��C���X�^���X�̎擾
		/// </summary>
		/// <returns>�V�[���Ǘ��C���X�^���X</returns>
		virtual Value_weak_ptr< ISceneManager> GetSceneManager() = 0;
		/// <summary>
		/// �E�B���h�E�Ǘ��C���X�^���X�̎擾
		/// </summary>
		/// <returns>�E�B���h�E�Ǘ��C���X�^���X</returns>
		virtual Value_ptr<IWindow> GetWindow() = 0;
		/// <summary>
		/// �������
		/// </summary>
		virtual void Release() = 0;
		/// <summary>
		/// �V�[�����̎擾
		/// </summary>
		/// <returns>�V�[�����</returns>
		virtual Value_ptr< SceneInformation> GetSceneInformation() = 0;
		/// <summary>
		/// �V�[���ύX���̎擾
		/// </summary>
		/// <returns>�V�[���ύX���</returns>
		virtual Value_ptr< SceneChangeInformation> GetSceneChangeInformation() = 0;
		/// <summary>
		/// �V�[���`����̎擾
		/// </summary>
		/// <returns>�V�[���`����</returns>
		virtual Value_ptr< SceneRenderingInformation> GetSceneRenderingInformation() = 0;
		/// <summary>
		/// �V�[�����̎擾
		/// </summary>
		virtual void Save() = 0;
		/// <summary>
		/// �V�[�����s���̃J�����̋N��
		/// </summary>
		virtual void CameraActivation() = 0;
		/// <summary>
		/// �V�[���ҏW���̃J�����̋N��
		/// </summary>
		virtual void CameraEditActivation() = 0;
		/// <summary>
		/// �J�n
		/// </summary>
		virtual void Start() = 0;
		/// <summary>
		/// �I��
		/// </summary>
		virtual void End() = 0;
		/// <summary>
		/// GUI�o�^
		/// </summary>
		virtual void GUIRegist() = 0;
		/// <summary>
		/// GUI�ւ̓o�^����
		/// </summary>
		virtual void GUIRelease() = 0;
		/// <summary>
		/// GameObjectManager�̎擾
		/// </summary>
		virtual Value_ptr<GameObjectManager> GetGameObjectManager() = 0;
		/// <summary>
		/// �����V���~���[�V�����Ǘ��N���X�ւ̃A�N�Z�X
		/// </summary>
		/// <returns></returns>
		virtual Value_ptr<ButiBullet::PhysicsManager> GetPhysicsManager()const = 0;
	};


}



#endif // !GamePartInterface