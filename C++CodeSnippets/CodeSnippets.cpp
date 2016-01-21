//windows header files
#include <Windows.h>

//c++ std header files
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

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
	void fcn()
	{
		std::vector<std::string> v;
		RecursiveTraverseDir("C:\\Users\\zou\\Documents\\Visual Studio 2013\\Projects\\MyRayTracing\\MyRayTracing", v);
	}
}

//*******************************************************************************
namespace CodeSnippet4
{
	//c++ ���ж�ȡ�ļ�����
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
	//c++ һ���Զ�ȡ�����ļ�������
	std::string readFile(const std::string& file)
	{
		std::ifstream ifs(file);
		std::stringstream ss;
		ss << ifs.rdbuf();
		ifs.close();

		std::string content = ss.str();
		return content;
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

//*******************************************************************************
namespace CodeSnippet6
{
	//���ݷָ������ָ��ַ���, ��Ϊ��python�е�splitһ��
	std::vector<std::string> split(const std::string& msg, const std::string& delimiter = " ")
	{
		std::vector<std::string> ret;
		size_t prev = 0, step = delimiter.size();
		auto curr = msg.find(delimiter);
		while (curr != std::string::npos)
		{
			ret.emplace_back(msg.substr(prev, curr - prev));
			prev = curr + step;
			curr = msg.find(delimiter, prev);
		}
		ret.emplace_back(msg.substr(prev, msg.size() - prev));
		return ret;
	}
	//usage:
	void fcn()
	{
		std::string ss = " 1  1 ";
		auto v = CodeSnippet6::split(ss);//['', '1', '', '1', '']
	}
}

//*******************************************************************************
#include <chrono>
namespace CodeSnippet7
{
	//���Գ�������ʱ��
	template<class Clock = std::chrono::steady_clock>
	class TimeProfiler
	{
	public:
		typedef typename Clock::time_point TimePoint;
		typedef std::chrono::duration<double, std::ratio<1, 1>> DurationTime;//��λ��
	private:
		TimePoint startTime;
		TimePoint finishTime;
		DurationTime durationTime;
	public:
		TimeProfiler(){}
		void start(){ startTime = Clock::now(); }
		void finish()
		{
			finishTime = Clock::now();
			durationTime = std::chrono::duration_cast<DurationTime>(finishTime - startTime);
		}

		double seconds(){ return durationTime.count(); }
	};
	//usage:
	void fcn()
	{
		int i = 1000;
		TimeProfiler<> p;
		p.start();
		while (i--){}
		p.finish();
		auto time = p.seconds();
	}
}

int main()
{
	auto s = CodeSnippet4::readFile("D:\\Projects\\C++CodeSnippets\\C++CodeSnippets\\CodeSnippets.cpp");
	std::cout << s;
	system("pause");
}