#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H
namespace ButiEngine {

class GlobalSettings {
public:

	static std::string GetResourceDirectory() {
		return resourceDirectory;
	}
	static void SetResourceDirectory(const std::string& arg_dir) {
		resourceDirectory = arg_dir;

	}
#ifdef _EDITORBUILD
	static std::int64_t GetEditorWindowHandle() {
		return editorWindowHandle;
	}
	static void SetEditorWindowHandle(std::int64_t arg_handle) {
		editorWindowHandle = arg_handle;
	}
#endif // _EDITORBUILD

private:
	static std::string resourceDirectory;
#ifdef _EDITORBUILD
	static std::int64_t editorWindowHandle;
#endif

};
}
#endif // !GLOBAL_SETTINGS_H
