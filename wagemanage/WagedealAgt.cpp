#include "StdAfx.h"
#include ".\wagedealagt.h"

#include <afxtempl.h>

CWagedealAgt::CWagedealAgt(void)
{
	Initialize();
}

CWagedealAgt::~CWagedealAgt(void)
{
	m_pDb.Close();

}

bool CWagedealAgt::GetNameList(CStringArray * pNamelist,CString strDepartment)
{
	CADORecordset pNames = CADORecordset(&m_pDb);
	CString szSQL;
	if(strDepartment.IsEmpty())
	{
		szSQL.Format("select name from employeeTB where state = true");//where state = %d",1
	}
	else
	{
		//(employeeTB.state = %d)
		szSQL.Format("select employeeTB.name from employeeTB, departmentTB where  \
			          (employeeTB.departnum =departmentTB.departnum) and \
					  (employeeTB.state = true) and \
					  (departmentTB.departname ='%s')",strDepartment);
	}
	pNames.Open(szSQL,CADORecordset::openQuery);

	if(!pNames.IsBOF())
	{
		pNames.MoveFirst();
	}
	else
	{
		return false;
	}
	
	DWORD dwCount = pNames.GetRecordCount();
	CString strTemp;
	for(DWORD dwIdx=0; dwIdx<dwCount; dwIdx++)
	{
		try
		{
			pNames.GetFieldValue(0,strTemp);
			pNamelist->Add(strTemp);

		}
		catch(CADOException * e)
		{
			CString szErr = e->GetErrorMessage();
			return false;
		}

		if(!pNames.IsEOF())
		{
			pNames.MoveNext();
		}
	}
	pNames.Close();
	return true;
}

bool CWagedealAgt::GetProjectlist(CStringArray * pList,bool bDescript)
{
	/*char* chProjectList[]={"816500","34212"};
	for (int i=0;i<2;i++)
	{
		pList->Add(chProjectList[i]);
	}*/

	CADORecordset pTypes = CADORecordset(&m_pDb);
	if( FALSE == pTypes.Open("divisionTB", CADORecordset::openTable))
	{	
		AfxMessageBox(pTypes.GetLastErrorString());
		DWORD dwError = pTypes.GetLastError();
		return false;
	}
	CString szSQL="select * from divisionTB";
	CADOCommand cmd(&m_pDb, szSQL, adCmdText);
	pTypes.Execute(&cmd);

	if(!pTypes.IsBOF())
	{
		pTypes.MoveFirst();
	}
	else
	{
		return false;
	}
	
	DWORD dwCount = pTypes.GetRecordCount();
	CString strTemp1,strTemp2;
	for(DWORD dwIdx=0; dwIdx<dwCount; dwIdx++)
	{
		try
		{
			pTypes.GetFieldValue("type",strTemp1);
			if (bDescript)
			{
				pTypes.GetFieldValue("description",strTemp2);
				pList->Add(strTemp1+"-"+strTemp2);
			}
			else
			{
				pList->Add(strTemp1);
			}

		}
		catch(CADOException * e)
		{
			CString szErr = e->GetErrorMessage();
			return false;
		}

		if(!pTypes.IsEOF())
		{
			pTypes.MoveNext();
		}
	}
	pTypes.Close();



	return true;
}

bool CWagedealAgt::GetsubworkList(CString in_strProject, CStringArray * out_pSubwklist)
{
	CADORecordset pTypes = CADORecordset(&m_pDb);
	if( FALSE == pTypes.Open("typeconfigTB", CADORecordset::openTable))
	{	
		AfxMessageBox(pTypes.GetLastErrorString());
		DWORD dwError = pTypes.GetLastError();
		return false;
	}
	CString szSQL;
	szSQL.Format("select subwork from typeconfigTB where type = '%s'",in_strProject);
		
	CADOCommand cmd(&m_pDb, szSQL, adCmdText);
	pTypes.Execute(&cmd);

	if(!pTypes.IsBOF())
	{
		pTypes.MoveFirst();
	}
	else
	{
		return false;
	}
	
	DWORD dwCount = pTypes.GetRecordCount();
	CString strTemp;
	for(DWORD dwIdx=0; dwIdx<dwCount; dwIdx++)
	{
		try
		{
			pTypes.GetFieldValue("subwork",strTemp);
			out_pSubwklist->Add(strTemp);

		}
		catch(CADOException * e)
		{
			CString szErr = e->GetErrorMessage();
			return false;
		}

		if(!pTypes.IsEOF())
		{
			pTypes.MoveNext();
		}
	}
	pTypes.Close();

	return true;
}

bool CWagedealAgt::SaveWorkLoadData(CString strDate, CString strName, CStringArray& strayWorkload)
{
	CADORecordset pWorkloads = CADORecordset(&m_pDb);
	CADORecordset pTb = CADORecordset(&m_pDb);
	int iCvNum;
	CString szSQL="select cvnumber from employeeTB where name = '"+strName+"'";
	CADOCommand cmd(&m_pDb, szSQL, adCmdText);
	pWorkloads.Execute(&cmd);

	if(!pWorkloads.IsBOF())
	{
		pWorkloads.MoveFirst();
	}
	else
	{
		AfxMessageBox("员工数据库出现故障,请检查");
		return false;
	}
	try
	{
		pWorkloads.GetFieldValue("cvnumber",iCvNum);
		
	}
	catch(CADOException * e)
	{
		CString szErr = e->GetErrorMessage();
		return false;
	}

	try
	{
		pWorkloads.Open("workloadTB", CADORecordset::openTable);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}

	// if the item to add has existed, prevent the new is added



	////////////////////////////////////////////////////////////

	if(!pWorkloads.IsEOF())
	{
		pWorkloads.MoveLast();
	}

	for (int i=0;i<strayWorkload.GetCount();i++)
	{
		CString strType,strSubwork,strWorkload;
		CString strTemp;
		int index1,index2;
		strTemp = strayWorkload.GetAt(i);
		index1=strTemp.Find('-');
		strType = strTemp.Left(index1);
		
		strTemp.Delete(0,index1+1);
		index2=strTemp.Find('-');
		strSubwork = strTemp.Left(index2);

		CString szSQL;
		szSQL.Format("select typenumber from typeconfigTB where type='%s' and subwork='%s'",strType,strSubwork);

		pTb.Open(szSQL,CADORecordset::openQuery);
		if(!pTb.IsBOF())
		{
			pTb.MoveFirst();
		}
		
		DWORD dwCount = pTb.GetRecordCount();
		if (dwCount!=1)
			return false;
		CString strTypenumber;
		try
		{
			pTb.GetFieldValue("typenumber",strTypenumber);
		}
		catch(CADOException* e)
		{
			CString szMsg = e->GetErrorMessage();
			AfxMessageBox(szMsg);
			return false;
		}
		


		strWorkload =strTemp;
		strWorkload.Delete(0,index2+1);

		pWorkloads.AddNew();
		try
		{
			pWorkloads.SetFieldValue("cvnumber", iCvNum);
			pWorkloads.SetFieldValue("typenumber", strTypenumber);
			pWorkloads.SetFieldValue("workload", strWorkload);
			pWorkloads.SetFieldValue("date", strDate);
		}
		catch(CADOException* e)
		{
			CString szMsg = e->GetErrorMessage();
			AfxMessageBox(szMsg);
			return false;
		}


		pWorkloads.Update();
	}
	pWorkloads.Close();
	return true;
}

bool CWagedealAgt::Initialize(void)
{
	// open media database
	char cPath[MAX_PATH];
	CString szPath("");
	CString strConnection("");

	::GetModuleFileName(NULL, cPath, MAX_PATH);
	szPath = cPath;
	int pos = szPath.ReverseFind('\\');
	szPath = szPath.Left(pos+1);
	strConnection.Format(_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%swage_manage.mdb"), szPath);

	try
	{
		m_pDb.Open(strConnection);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}
	return true;
}

bool CWagedealAgt::GetWorkload(CString strMonth, CString strName, CString strType, CString strSubwork, CString * strWorkload, CString * strPrice)
{
	CString strCVnum;
	CString strMonth_Begin;
	CString strMonth_End;

	CADORecordset pTb = CADORecordset(&m_pDb);
	CString szSQL="select cvnumber from employeeTB where name = '"+strName+"'";
	pTb.Open(szSQL,CADORecordset::openQuery);

	if (pTb.IsBOF())
		return false;
	
	try
	{
		pTb.GetFieldValue("cvnumber",strCVnum);

	}
	catch(CADOException * e)
	{
		CString szErr = e->GetErrorMessage();
		return false;
	}
	CString strSQL;
	//typeconfigTB.price
	/*strMonth_Begin = strMonth+"-1";
	CStringArray strTemp;
	StringTranslation(strMonth,'-',strTemp);
	atoi(strTemp.GetAt(1))*/
	GetDayFromMonth(strMonth,strMonth_Begin,strMonth_End);
	/*strMonth_End= strTemp.GetAt(0)+"-"+strTemp.GetAt(1)+"-1";*/
	strSQL.Format("select workloadTB.workload,typeconfigTB.price from workloadTB,typeconfigTB  \
				   where (workloadTB.cvnumber= %s) and (typeconfigTB.type = '%s') \
				   and (typeconfigTB.subwork = '%s') \
				   and (typeconfigTB.typenumber = workloadTB.typenumber) \
				   and (workloadTB.date between #%s# and #%s#) ",
				//Group by workloadTB.typenumber",
			strCVnum,strType,strSubwork,strMonth_Begin,strMonth_End);
	pTb.Open(strSQL,CADORecordset::openQuery);

	if(pTb.IsBOF())
	{
		*strWorkload="0";
		*strPrice="0";
		return false;
	}
	pTb.MoveFirst();
	int iTotalWork=0;
	DWORD dwCount = pTb.GetRecordCount();
	for (int i=0;i<dwCount;i++)
	{
		CString strTemp;
		
		try
		{
			pTb.GetFieldValue(0,*strWorkload);
			pTb.GetFieldValue(1,*strPrice);

			iTotalWork += atoi(*strWorkload);

		}
		catch(CADOException * e)
		{
			CString szErr = e->GetErrorMessage();
			return false;
		}
		if(!pTb.IsEOF())
		{
			pTb.MoveNext();
		}
	}
	strWorkload->Format("%d",iTotalWork);
	pTb.Close();
	return true;
}

bool CWagedealAgt::GetMonthSalary(CString strMonth, CString strName, CString strType, CString * strSalary)
{
	CString strCVnum;
	CString strMonth_Begin;
	CString strMonth_End;

	CADORecordset pTb = CADORecordset(&m_pDb);
	CString szSQL="select cvnumber from employeeTB where name = '"+strName+"'";
	pTb.Open(szSQL,CADORecordset::openQuery);
	
	try
	{
		pTb.GetFieldValue("cvnumber",strCVnum);

	}
	catch(CADOException * e)
	{
		CString szErr = e->GetErrorMessage();
		return false;
	}
	
	CString strSQL;
	//typeconfigTB.price
	GetDayFromMonth(strMonth,strMonth_Begin,strMonth_End);
	strSQL.Format("select workloadTB.workload,typeconfigTB.price from workloadTB,typeconfigTB  \
				   where (workloadTB.cvnumber= %s) and (typeconfigTB.type = '%s') \
				   and (typeconfigTB.typenumber = workloadTB.typenumber) \
				   and (workloadTB.date between #%s# and #%s#) ",
				//Group by workloadTB.typenumber",
			strCVnum,strType,strMonth_Begin,strMonth_End);
	pTb.Open(strSQL,CADORecordset::openQuery);

	if(pTb.IsBOF())
	{
		*strSalary="0";
		return false;
	}
	pTb.MoveFirst();
	float fTotalWage=0;
	CString strWorkload,strPrice;
	DWORD dwCount = pTb.GetRecordCount();
	for (int i=0;i<dwCount;i++)
	{
		
		try
		{
			pTb.GetFieldValue(0,strWorkload);
			pTb.GetFieldValue(1,strPrice);

			fTotalWage += atoi(strWorkload)*atof(strPrice);

		}
		catch(CADOException * e)
		{
			CString szErr = e->GetErrorMessage();
			return false;
		}
		if(!pTb.IsEOF())
		{
			pTb.MoveNext();
		}
	}
	strSalary->Format("%f",fTotalWage);
	pTb.Close();
	return true;
}

// 增加姓名列表
bool CWagedealAgt::SaveNameList(CStringArray & strNamelist)
{
	CStringArray strNameArray,strArrayTemp;
	CArray<int,int> iDepartIDArray;
	for (int i=0; i<strNamelist.GetCount();i++)
	{
		StringTranslation(strNamelist.GetAt(i),'-',strArrayTemp);
		strNameArray.Add(strArrayTemp.GetAt(0));
		int ID;
		GetDepartIDFromName(strArrayTemp.GetAt(1),ID);
		iDepartIDArray.Add(ID);
	}
	CADORecordset pTb = CADORecordset(&m_pDb);
	try
	{
		pTb.Open("employeeTB", CADORecordset::openTable);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}

	// if the item to add has existed, prevent the new is added

	////////////////////////////////////////////////////////////

	if(!pTb.IsEOF())
	{
		pTb.MoveLast();
	}

	for (int i=0;i<strNamelist.GetCount();i++)
	{

		pTb.AddNew();
		try
		{
			pTb.SetFieldValue("name", strNameArray.GetAt(i));
			pTb.SetFieldValue("departnum", iDepartIDArray.GetAt(i));
			pTb.SetFieldValue("state", true);

		}
		catch(CADOException* e)
		{
			CString szMsg = e->GetErrorMessage();
			AfxMessageBox(szMsg);
			return false;
		}


		pTb.Update();
	}
	pTb.Close();
	return true;
}

// subworkinfo用"工序/工分"字符串来表示
bool CWagedealAgt::GetSubworkInfo(CString strProject, CStringArray & strSubworkinfo)
{
	CString strSubwork,strPrice;
	double fPrice;
	CADORecordset pTb = CADORecordset(&m_pDb);
	CString szSQL="select subwork,price from typeconfigTB where type = '"+strProject+"'";
	pTb.Open(szSQL,CADORecordset::openQuery);
	
	if(pTb.IsBOF())
	{
		return false;
	}
	pTb.MoveFirst();
	DWORD dwCount = pTb.GetRecordCount();
	for (int i=0;i<dwCount;i++)
	{
		CString strTemp;
		
		try
		{
			pTb.GetFieldValue(0,strSubwork);
			pTb.GetFieldValue(1,fPrice);
			strPrice.Format("%f",fPrice);

			strSubworkinfo.Add(strSubwork+"/"+strPrice);

		}
		catch(CADOException * e)
		{
			CString szErr = e->GetErrorMessage();
			return false;
		}
		if(!pTb.IsEOF())
		{
			pTb.MoveNext();
		}
	}
	pTb.Close();

	return true;
}

// 保存工序信息，保存有款号，工序，工分
bool CWagedealAgt::SaveSubworkInfo(CString strType, CStringArray & strSubworkInfo)
{
	CADORecordset pTb = CADORecordset(&m_pDb);
	try
	{
		pTb.Open("typeconfigTB", CADORecordset::openTable);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}

	// if the item to add has existed, prevent the new is added

	////////////////////////////////////////////////////////////

	if(!pTb.IsEOF())
	{
		pTb.MoveLast();
	}

	for (int i=0;i<strSubworkInfo.GetCount();i++)
	{
		CStringArray strTemp;
		StringTranslation(strSubworkInfo.GetAt(i),'/',strTemp);

		pTb.AddNew();
		try
		{
			pTb.SetFieldValue("type", strType);
			pTb.SetFieldValue("subwork", strTemp.GetAt(0));
			pTb.SetFieldValue("price", strTemp.GetAt(1));
		}
		catch(CADOException* e)
		{
			CString szMsg = e->GetErrorMessage();
			AfxMessageBox(szMsg);
			return false;
		}


		pTb.Update();
	}
	pTb.Close();
	return true;
}

// //将字符串按切割符解析
bool CWagedealAgt::StringTranslation(CString strInput, char chSplit, CStringArray & strOutput)
{
	CString strTemp;
	int index;
	strOutput.RemoveAll();
	while(-1!=strInput.Find(chSplit))
	{
		index=strInput.Find(chSplit);
		strTemp = strInput.Left(index);

		strOutput.Add(strTemp);
			
		strInput.Delete(0,index+1);
	}
	strOutput.Add(strInput);

	
	return true;
}

// 保存款号
bool CWagedealAgt::SaveProjectList(CStringArray & strProjectlist)
{
	CADORecordset pTb = CADORecordset(&m_pDb);
	try
	{
		pTb.Open("divisionTB", CADORecordset::openTable);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}

	// if the item to add has existed, prevent the new is added

	////////////////////////////////////////////////////////////

	if(!pTb.IsEOF())
	{
		pTb.MoveLast();
	}

	for (int i=0;i<strProjectlist.GetCount();i++)
	{
		CString strTemp;
		CStringArray strTempArray;

		strTemp = strProjectlist.GetAt(i);
		StringTranslation(strTemp,'-',strTempArray);
		pTb.AddNew();
		try
		{
			pTb.SetFieldValue("type", strTempArray.GetAt(0));
			pTb.SetFieldValue("description",strTempArray.GetAt(1));
		}
		catch(CADOException* e)
		{
			CString szMsg = e->GetErrorMessage();
			AfxMessageBox(szMsg);
			return false;
		}


		pTb.Update();
	}
	pTb.Close();
	return true;
}
//strMonth is in the format of 2006-05
bool CWagedealAgt::GetDayFromMonth(CString strMonth, CString & strDay_Begin, CString & strDay_End)
{
	strDay_Begin = strMonth+"-1";
	CStringArray strTemp;
	StringTranslation(strMonth,'-',strTemp);
	int iTmp;
	GetEndDay(atoi(strTemp.GetAt(0)),atoi(strTemp.GetAt(1)),iTmp);
	strDay_End.Format("%s-%d",strMonth,iTmp);
	return true;
}

bool CWagedealAgt::GetEndDay(int iYear, int iMonth, int & iDay)
{
	switch (iMonth)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			iDay = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			iDay =30;
			break;
		case 2:
		{
			if (0==iYear%4)
				iDay =29;
			else
				iDay =28;
			break;
		}
		default:
			return false;
	}
	return true;
}

// //获取个人工作量列表,以"款号-工序-工作量"形式输出到strPersonWkldList中
bool CWagedealAgt::GetPersonWorkLoadList(CTime tDate, CString strName, CStringArray & strPersonWkldList)
{
	
	CString strCVnum;

	CADORecordset pTb = CADORecordset(&m_pDb);
	CString szSQL="select cvnumber from employeeTB where name = '"+strName+"'";
	pTb.Open(szSQL,CADORecordset::openQuery);
	
	try
	{
		pTb.GetFieldValue("cvnumber",strCVnum);

	}
	catch(CADOException * e)
	{
		CString szErr = e->GetErrorMessage();
		return false;
	}

	CString strDate;
	strDate=tDate.Format("%Y-%m-%d");

	CString strSQL;
	
	strSQL.Format("select typeconfigTB.type,typeconfigTB.subwork,workloadTB.workload from workloadTB,typeconfigTB  \
				   where (workloadTB.cvnumber= %s) and (typeconfigTB.typenumber = workloadTB.typenumber ) \
				   and (workloadTB.date = #%s# ) ",
				//Group by workloadTB.typenumber",
			strCVnum,strDate);
	pTb.Open(strSQL,CADORecordset::openQuery);

	if(pTb.IsBOF())
	{
		return false;
	}
	pTb.MoveFirst();
	DWORD dwCount = pTb.GetRecordCount();
	CString strType,strSubwork,strWorkload;
	for (int i=0;i<dwCount;i++)
	{
		CString strTemp;
		
		try
		{
			pTb.GetFieldValue(0,strType);
			pTb.GetFieldValue(1,strSubwork);
			pTb.GetFieldValue(2,strWorkload);

		}
		catch(CADOException * e)
		{
			CString szErr = e->GetErrorMessage();
			return false;
		}
		if(!pTb.IsEOF())
		{
			pTb.MoveNext();
		}
		strTemp.Format("%s-%s-%s",strType,strSubwork,strWorkload);
		strPersonWkldList.Add(strTemp);

	}
	
	pTb.Close();
	return true;
}

// 删除由于误操作的工作量
bool CWagedealAgt::DeleteWorkLoadData(CString strDate,CString strName, CString strWorkload)
{
	CADORecordset pWorkloads = CADORecordset(&m_pDb);
	int iCVNum;
	CString strTypeNum;
	GetIDFromName(strName,iCVNum);

	CStringArray strTemp;
	CString strType,strSubwork,strLoad;
	StringTranslation(strWorkload,'-',strTemp);
	strType = strTemp.GetAt(0);
	strSubwork = strTemp.GetAt(1);
	strLoad = strTemp.GetAt(2);

	GetTypeNumFromWorkInfo(strType,strSubwork,strTypeNum);
	
	pWorkloads.Open(_T("workloadTB"), CADORecordset::openTable);
	CString szFilter;
	szFilter.Format( _T("(cvnumber = %d) \
				 and (typenumber = %s) \
				 and (workload =%s) \
				 and (date = #%s#)"),iCVNum,strTypeNum,strLoad,strDate);
	pWorkloads.SetFilter( szFilter );


	if (pWorkloads.GetRecordCount()>0)
	{
		pWorkloads.Delete();
	}
	pWorkloads.Close();




	return true;
}

// 从名字得到工号
bool CWagedealAgt::GetIDFromName(CString strName, int & iID)
{

	CADORecordset pTb = CADORecordset(&m_pDb);
	CString szSQL="select cvnumber from employeeTB where name = '"+strName+"'";
	CADOCommand cmd(&m_pDb, szSQL, adCmdText);
	pTb.Execute(&cmd);

	if(!pTb.IsBOF())
	{
		pTb.MoveFirst();
	}
	else
	{
		AfxMessageBox("员工数据库出现故障,请检查");
		return false;
	}
	try
	{
		pTb.GetFieldValue("cvnumber",iID);
		
	}
	catch(CADOException * e)
	{
		CString szErr = e->GetErrorMessage();
		return false;
	}
	pTb.Close();
	return true;
}

// 从款号和工序得到typenumber
bool CWagedealAgt::GetTypeNumFromWorkInfo(CString strType, CString strSubwork, CString & strTypeNumber)
{
	CADORecordset pTb = CADORecordset(&m_pDb);
	CString szSQL;
	szSQL.Format("select typenumber from typeconfigTB where type='%s' and subwork='%s'",strType,strSubwork);

	pTb.Open(szSQL,CADORecordset::openQuery);
	if(!pTb.IsBOF())
	{
		pTb.MoveFirst();
	}
	
	DWORD dwCount = pTb.GetRecordCount();
	if (dwCount!=1)
		return false;
	try
	{
		pTb.GetFieldValue("typenumber",strTypeNumber);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}
	pTb.Close();

	return true;
}

// //获取部门名称列表
bool CWagedealAgt::GetDepartmentInfo(CStringArray & strDepart)
{
	CADORecordset pNames = CADORecordset(&m_pDb);
	if( FALSE == pNames.Open("departmentTB", CADORecordset::openTable))
	{	
		AfxMessageBox(pNames.GetLastErrorString());
		DWORD dwError = pNames.GetLastError();
		return false;
	}
	CString szSQL="select departname from departmentTB";
	CADOCommand cmd(&m_pDb, szSQL, adCmdText);
	pNames.Execute(&cmd);
	strDepart.RemoveAll();
	if(!pNames.IsBOF())
	{
		pNames.MoveFirst();
	}
	else
	{
		return false;
	}
	
	DWORD dwCount = pNames.GetRecordCount();
	CString strTemp;
	for(DWORD dwIdx=0; dwIdx<dwCount; dwIdx++)
	{
		try
		{
			pNames.GetFieldValue("departname",strTemp);
			strDepart.Add(strTemp);

		}
		catch(CADOException * e)
		{
			CString szErr = e->GetErrorMessage();
			return false;
		}

		if(!pNames.IsEOF())
		{
			pNames.MoveNext();
		}
	}
	pNames.Close();
	return true;
}

// 保存部门列表
bool CWagedealAgt::SaveDepartmentList(CStringArray & strDepartmentList)
{
	CADORecordset pTb = CADORecordset(&m_pDb);
	try
	{
		pTb.Open("departmentTB", CADORecordset::openTable);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}

	// if the item to add has existed, prevent the new is added

	////////////////////////////////////////////////////////////

	if(!pTb.IsEOF())
	{
		pTb.MoveLast();
	}

	for (int i=0;i<strDepartmentList.GetCount();i++)
	{
		CString strTemp;
		strTemp = strDepartmentList.GetAt(i);
		pTb.AddNew();
		try
		{
			pTb.SetFieldValue("departname", strTemp);
		}
		catch(CADOException* e)
		{
			CString szMsg = e->GetErrorMessage();
			AfxMessageBox(szMsg);
			return false;
		}


		pTb.Update();
	}
	pTb.Close();
	return true;
}

bool CWagedealAgt::ModifyDepartName(CString & strOld, CString & strNew)
{
	CADORecordset pTb = CADORecordset(&m_pDb);
	CString strSQL;
	strSQL.Format(_T("Select * from departmentTB where departname='%s'"),strOld);
	try
	{
		pTb.Open(strSQL, CADORecordset::openQuery);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}
	if (pTb.GetRecordCount() == 0 )
		return false;
	pTb.Edit();

	try
	{
		pTb.SetFieldValue( _T("departname"), strNew );
	}
	catch(CADOException * e)
	{
		return false;
	}

	pTb.Update();
	pTb.Close();

	return true;
}


// 由部门名称得到部门编号
bool CWagedealAgt::GetDepartIDFromName(CString strDepartName, int & ID)
{
	CADORecordset pTb = CADORecordset(&m_pDb);
	CString szSQL="select departnum from departmentTB where departname = '"+strDepartName+"'";
	pTb.Open(szSQL,CADORecordset::openQuery);

	if(!pTb.IsBOF())
	{
		pTb.MoveFirst();
	}
	else
	{
		AfxMessageBox("员工数据库出现故障,请检查");
		return false;
	}
	try
	{
		pTb.GetFieldValue("departnum",ID);
		
	}
	catch(CADOException * e)
	{
		CString szErr = e->GetErrorMessage();
		return false;
	}
	pTb.Close();
	return true;
}

// 删除一个员工
bool CWagedealAgt::DeleteEmplyee(CString strName)
{
	CADORecordset pTb = CADORecordset(&m_pDb);
	CString strSQL;
	CStringArray strArray;
	StringTranslation(strName,'-',strArray);
	strSQL.Format(_T("Select * from employeeTB where name='%s'"),strArray.GetAt(0));
	try
	{
		pTb.Open(strSQL, CADORecordset::openQuery);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}
	if (pTb.GetRecordCount() == 0 )
		return false;
	pTb.Edit();

	try
	{
		pTb.SetFieldValue( _T("state"), false );
	}
	catch(CADOException * e)
	{
		return false;
	}

	pTb.Update();
	pTb.Close();

	return true;
}

// 更改员工信息包括:姓名,部门
bool CWagedealAgt::ModifyEmployeeInfo(CString strOldName , CString strNewName , CString strNewDepart)
{
	CADORecordset pTb = CADORecordset(&m_pDb);
	CString strSQL;
	int iDepartID;
	GetDepartIDFromName(strNewDepart,iDepartID);
	strSQL.Format(_T("Select * from employeeTB where name='%s'"),strOldName);
	try
	{
		pTb.Open(strSQL, CADORecordset::openQuery);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}
	if (pTb.GetRecordCount() == 0 )
		return false;
	pTb.Edit();

	try
	{
		pTb.SetFieldValue( _T("name"), strNewName );
		pTb.SetFieldValue( _T("departnum"), iDepartID );

	}
	catch(CADOException * e)
	{
		return false;
	}

	pTb.Update();
	pTb.Close();

	return true;
}

bool CWagedealAgt::ModifySubworkInfo(CString strType, CString strOldSubwork, CString strSubwork, CString strPrice)
{
	CADORecordset pTb = CADORecordset(&m_pDb);
	CString strSQL;
	strSQL.Format(_T("Select * from typeconfigTB where type='%s' and subwork='%s'"),strType,strOldSubwork);
	try
	{
		pTb.Open(strSQL, CADORecordset::openQuery);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}
	if (pTb.GetRecordCount() == 0 )
		return false;
	pTb.Edit();

	try
	{
		pTb.SetFieldValue( _T("subwork"), strSubwork );
		pTb.SetFieldValue( _T("price"), strPrice );

	}
	catch(CADOException * e)
	{
		return false;
	}

	pTb.Update();
	pTb.Close();

	return true;
}

bool CWagedealAgt::GetNameAndDepartList(CStringArray & strList)
{

	CADORecordset pNames = CADORecordset(&m_pDb);
	CString szSQL;
	strList.RemoveAll();
	/*(employeeTB.state = %d) */
	szSQL.Format("select employeeTB.name,departmentTB.departname from employeeTB, departmentTB where \
			          (employeeTB.departnum =departmentTB.departnum) and \
					  (employeeTB.state = true ) ");

	pNames.Open(szSQL,CADORecordset::openQuery);

	if(!pNames.IsBOF())
	{
		pNames.MoveFirst();
	}
	else
	{
		return false;
	}
	
	DWORD dwCount = pNames.GetRecordCount();
	CString strTemp1,strTemp2;
	for(DWORD dwIdx=0; dwIdx<dwCount; dwIdx++)
	{
		try
		{
			pNames.GetFieldValue(0,strTemp1);
			pNames.GetFieldValue(1,strTemp2);
			strList.Add(strTemp1+"-"+strTemp2);

		}
		catch(CADOException * e)
		{
			CString szErr = e->GetErrorMessage();
			return false;
		}

		if(!pNames.IsEOF())
		{
			pNames.MoveNext();
		}
	}
	pNames.Close();
	return true;
}

// 修改款号信息
bool CWagedealAgt::ModifyTypeInfo(CString strOld, CString strNew)
{

	CADORecordset pTb = CADORecordset(&m_pDb);
	CString strSQL;
	CString strOldType;
	CString strNewType,strNewDes;
	CStringArray strTempArray;

	StringTranslation(strOld,'-',strTempArray);
	strOldType = strTempArray.GetAt(0);

	StringTranslation(strNew,'-',strTempArray);
	strNewType = strTempArray.GetAt(0);
	strNewDes = strTempArray.GetAt(1);

	strSQL.Format(_T("Select * from divisionTB where type='%s'"),strOldType);
	try
	{
		pTb.Open(strSQL, CADORecordset::openQuery);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}
	if (pTb.GetRecordCount() == 0 )
		return false;
	pTb.Edit();

	try
	{
		pTb.SetFieldValue( _T("type"), strNewType );
		pTb.SetFieldValue( _T("description"), strNewDes );

	}
	catch(CADOException * e)
	{
		return false;
	}

	pTb.Update();
	pTb.Close();



	strSQL.Format(_T("Select * from typeconfigTB where type='%s'"),strOldType);
	try
	{
		pTb.Open(strSQL, CADORecordset::openQuery);
	}
	catch(CADOException* e)
	{
		CString szMsg = e->GetErrorMessage();
		AfxMessageBox(szMsg);
		return false;
	}
	int iCount = pTb.GetRecordCount();
	if (iCount == 0 )
		return false;
	
	for(DWORD i=0; i<iCount; i++)
	{
		pTb.Edit();
		try
		{
			pTb.SetFieldValue( _T("type"), strNewType );

		}
		catch(CADOException * e)
		{
			return false;
		}
		pTb.Update();
		
		if(!pTb.IsEOF())
		{
			pTb.MoveNext();
		}
		
	}
	
	pTb.Close();
	return true;
}
