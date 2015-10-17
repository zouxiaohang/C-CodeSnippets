//windows header files
#include <Windows.h>

//c++ std header files
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//*******************************************************************************
namespace CodeSnippet1
{
	//�ڱ����ڼ����ѡ��
	template<bool flag, class T, class U>
	struct Select
	{
		typedef T Result;
	};
	template<class T, class U>
	struct Select<false, T, U>
	{
		typedef U Result;
	};

	//usage:
	template<class T, bool isPolymorphic>
	struct Container
	{
		//���ݲ���isPolymorphic���ڱ���ʱ�ھ���container��Ԫ�ص�����
		typedef typename Select<isPolymorphic, T*, T>::Result ValueType;
		std::vector<ValueType> container;
	};
}

//*******************************************************************************
namespace CodeSnippet2
{
	//��������ӳ��Ϊ�����ͱ�
	template<int v>
	struct Int2Type
	{
		enum{ value = v };
	};

	//һ����ԣ��������������������ʹ��Int2Type
	//��1������ĳ�������ڼ䳣�����ò�ͬ�ĺ���
	//��2���б�Ҫ�ڱ�����ʵʩdispatch

	//usage:
	template<class T>
	void fcn(T *p, Int2Type<true>){}
	template<class T>
	void fcn(T *p, Int2Type<false>){}
}

//*******************************************************************************
namespace CodeSnippet3
{
	//windows �ݹ�����ļ���
	void RecursiveTraverseDir(const std::string& path, std::vector<std::string>& v)
	{
		const std::string szPath = (path + "\\");
		std::string szFile;
		std::string szFind;

		WIN32_FIND_DATA FindFileData;
		szFind += (szPath + "*.*");

		HANDLE hFind = ::FindFirstFile(szFind.c_str(), &FindFileData);

		if (INVALID_HANDLE_VALUE == hFind) 
			return;
		while (true)
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (FindFileData.cFileName[0] != '.')
				{
					szFile = (szPath + FindFileData.cFileName);
					RecursiveTraverseDir(szFile, v);
				}
			}
			else
			{
				v.emplace_back(szPath + FindFileData.cFileName);
			}
			if (!FindNextFile(hFind, &FindFileData)) 
				break;
		}
		FindClose(hFind);
	}
	//usage:
	int fcn()
	{
		std::vector<std::string> v;
		RecursiveTraverseDir("C:\\Users\\zou\\Documents\\Visual Studio 2013\\Projects\\MyRayTracing\\MyRayTracing", v);
	}
}

//*******************************************************************************
namespace CodeSnippet4
{
	//c++ ��ȡ���ж�ȡ�ļ�����
	void readFileByLine(const std::string& file)
	{
		std::ifstream ifs(file);
		std::string line;

		while (std::getline(ifs, line))
		{
			//std::cout << line << std::endl;
		}

		ifs.close();
	}
}

//*******************************************************************************
#include <codecvt>
#include <locale>
#include <string>
namespace CodeSnippet5
{
	//string �� wstring ֮���ת��
	// convert UTF-8 string to wstring
	std::wstring utf8_to_wstring(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.from_bytes(str);
	}
	// convert wstring to UTF-8 string
	std::string wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}
}