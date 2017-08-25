#pragma once

#ifndef _CLIENT_PROTOCOL_H_
#define _CLIENT_PROTOCOL_H_

#include <set>
#include <string>

/*
	�淶Cef Protocolд��
*/

namespace CefProtocol
{
	typedef const char* FunType;

	static std::set<FunType> fun_name_set;

	static auto addFun = [](IN FunType funName, IN std::set<FunType>& set)->FunType
	{	
		ASSERT(set.find(funName) == set.end());//����ĺ������Ѵ��ڣ�����

		set.insert(funName); return funName;	
	};


	//���庯�������ú�������󶨵�v8�����У�
	//��ҳ����˵���൱������һ������c++�ĺ����ӿ�
	//
	//
#define AddFunName(name /*��������*/ , fun /*������*/ ) \
	static FunType name = addFun(fun, fun_name_set);



	/*			AddFunName  begin			*/

	AddFunName(kTestFun	, "testFun");

	/*			AddFunName  end				*/




};//namespace CefProtocol

#endif //_CLIENT_PROTOCOL_H_