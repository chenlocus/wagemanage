#pragma once
#include "afx.h"
#include "ado2.h"
class CWagedealAgt :
	public CObject
{
public:
	CWagedealAgt(void);
	~CWagedealAgt(void);
	bool GetNameList(CStringArray * pNamelist,CString strDepartment=0);
	bool GetProjectlist(CStringArray * pList,bool bDescript=false);
	bool GetsubworkList(CString in_strProject, CStringArray * out_pSubwklist);
	bool SaveWorkLoadData(CString strDate, CString strName, CStringArray &strayWorkload);
	bool Initialize(void);

private:
	CADODatabase	m_pDb;				// database
public:
	bool GetWorkload(CString strMonth, CString strName, CString strType, CString strSubwork, CString * strWorkload, CString * strPrice);
	bool GetMonthSalary(CString strMonth, CString strName, CString strType, CString * strSalary);
	// ���������б�
	bool SaveNameList(CStringArray & strNamelist);
	// subworkinfo��"����/����"�ַ�������ʾ
	bool GetSubworkInfo(CString strProject, CStringArray & strSubworkinfo);
	// ���湤����Ϣ�������п�ţ����򣬹���
	bool SaveSubworkInfo(CString strType, CStringArray & strSubworkInfo);
	// //���ַ������и������
	bool StringTranslation(CString strInput, char chSplit, CStringArray & strOutput);
	// ������
	bool SaveProjectList(CStringArray & strProjectlist);
	bool GetDayFromMonth(CString strMonth, CString & strDay_Begin, CString & strDay_End);
private:
	bool GetEndDay(int iYear, int iMonth, int & iDay);
public:
	// //��ȡ���˹������б�,��"���-����-������"��ʽ�����strPersonWkldList��
	bool GetPersonWorkLoadList(CTime tDate, CString strName, CStringArray & strPersonWkldList);
	// ɾ������������Ĺ�����
	bool DeleteWorkLoadData(CString strDate, CString strName,CString strWorkload);
	// �����ֵõ�����
	bool GetIDFromName(CString strName, int & iID);
	// �ӿ�ź͹���õ�typenumber
	bool GetTypeNumFromWorkInfo(CString strType, CString strSubwork, CString & strTypeNumber);
	// //��ȡ���������б�
	bool GetDepartmentInfo(CStringArray & strDepart);
	// ���沿���б�
	bool SaveDepartmentList(CStringArray & strDepartmentList);
	bool ModifyDepartName(CString & strOld, CString & strNew);

	// �ɲ������Ƶõ����ű��
	bool GetDepartIDFromName(CString strDepartName, int & ID);
	// ɾ��һ��Ա��
	bool DeleteEmplyee(CString strName);
	// ����Ա����Ϣ����:����,����
	bool ModifyEmployeeInfo(CString strOldName , CString strNewName , CString strNewDepart);
	bool ModifySubworkInfo(CString strType, CString strOldSubwork, CString strSubwork, CString strPrice);
	bool GetNameAndDepartList(CStringArray & strList);
	// �޸Ŀ����Ϣ
	bool ModifyTypeInfo(CString strOld, CString strNew);
};
