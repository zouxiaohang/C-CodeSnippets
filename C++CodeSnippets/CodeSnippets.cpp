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