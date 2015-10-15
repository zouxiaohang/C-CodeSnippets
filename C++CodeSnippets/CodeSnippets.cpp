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