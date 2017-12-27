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
	// 增加姓名列表
	bool SaveNameList(CStringArray & strNamelist);
	// subworkinfo用"工序/工分"字符串来表示
	bool GetSubworkInfo(CString strProject, CStringArray & strSubworkinfo);
	// 保存工序信息，保存有款号，工序，工分
	bool SaveSubworkInfo(CString strType, CStringArray & strSubworkInfo);
	// //将字符串按切割符解析
	bool StringTranslation(CString strInput, char chSplit, CStringArray & strOutput);
	// 保存款号
	bool SaveProjectList(CStringArray & strProjectlist);
	bool GetDayFromMonth(CString strMonth, CString & strDay_Begin, CString & strDay_End);
private:
	bool GetEndDay(int iYear, int iMonth, int & iDay);
public:
	// //获取个人工作量列表,以"款号-工序-工作量"形式输出到strPersonWkldList中
	bool GetPersonWorkLoadList(CTime tDate, CString strName, CStringArray & strPersonWkldList);
	// 删除由于误操作的工作量
	bool DeleteWorkLoadData(CString strDate, CString strName,CString strWorkload);
	// 从名字得到工号
	bool GetIDFromName(CString strName, int & iID);
	// 从款号和工序得到typenumber
	bool GetTypeNumFromWorkInfo(CString strType, CString strSubwork, CString & strTypeNumber);
	// //获取部门名称列表
	bool GetDepartmentInfo(CStringArray & strDepart);
	// 保存部门列表
	bool SaveDepartmentList(CStringArray & strDepartmentList);
	bool ModifyDepartName(CString & strOld, CString & strNew);

	// 由部门名称得到部门编号
	bool GetDepartIDFromName(CString strDepartName, int & ID);
	// 删除一个员工
	bool DeleteEmplyee(CString strName);
	// 更改员工信息包括:姓名,部门
	bool ModifyEmployeeInfo(CString strOldName , CString strNewName , CString strNewDepart);
	bool ModifySubworkInfo(CString strType, CString strOldSubwork, CString strSubwork, CString strPrice);
	bool GetNameAndDepartList(CStringArray & strList);
	// 修改款号信息
	bool ModifyTypeInfo(CString strOld, CString strNew);
};
