#pragma once

namespace Libero
{
	// Functions
	template<class Interface>
	inline void SafeRelease(Interface& pInterfaceToRelease)
	{
		if (pInterfaceToRelease != nullptr)
		{
			pInterfaceToRelease->Release();
			pInterfaceToRelease = nullptr;
		}
	}

	template<class T>
	inline void SafeDelete(T& pObjectToDelete)
	{
		if (pObjectToDelete != nullptr)
		{
			delete pObjectToDelete;
			pObjectToDelete = nullptr;
		}
	}

#pragma region Getting&Setting

#define DefSet(Type, As, Var)\
	public: \
		void Set##As(const Type& val){Var = val;};

#define DefGet(Type, As, Var)\
	public: \
		const Type& Get##As() const{return Var;};

#define DefGetRef(Type, As, Var)\
	public: \
		 Type& Get##AsRef() const {return Var;};

#define DefGetSet(Type, As, Var)\
	DefSet(Type, As, Var)\
	DefGet(Type, As, Var)

#pragma endregion

#pragma region String conversion

	inline std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		std::wstring r(len, L'\0');
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, &r[0], len);
		return r;
	}

	inline std::string ws2s(const std::wstring& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
		std::string r(len, '\0');
		WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, &r[0], len, 0, 0);
		return r;
	}
#pragma endregion
}