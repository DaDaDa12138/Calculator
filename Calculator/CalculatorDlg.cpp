
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <iostream>  
#include <cctype>  
#include <cstdlib>  
#include <stack>  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CCalculatorDlg 

CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalculatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_csCalculateRes = _T("0");
	m_bCalType = 0;
	m_bIsAngle = 0;
	m_dFirstNum = 0.0;
	m_dSecondNum = 0.0;
	m_csOperateSign = _T("+");
	m_dCoff = 1.0;
	m_PI = 3.14159265358979323846;
	m_bIsLogical = FALSE;
	m_csArithRes = _T("");
	m_csArithExpression = _T("");
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_csCalculateRes);
	DDX_Radio(pDX, IDC_RADIO_NORMAL, m_bCalType);
	DDX_Radio(pDX, IDC_RADIO_ANGLE, m_bIsAngle);
	DDX_Text(pDX, IDC_EDIT_ARITH_RESULT, m_csArithRes);
	DDX_Text(pDX, IDC_EDIT_ARITH_EXPRESSION, m_csArithExpression);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RADIO_NORMAL,&CCalculatorDlg::OnClickBtnNormalCal)
	ON_BN_CLICKED(IDC_RADIO_SCIENCE,&CCalculatorDlg::OnClickBtnScienceCal)
	ON_BN_CLICKED(IDC_RADIO_ARITH,&CCalculatorDlg::OnClickBtnArithCal)

	ON_BN_CLICKED(IDC_BUTTON0, &CCalculatorDlg::OnClickBtn0)
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorDlg::OnClickBtn1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCalculatorDlg::OnClickBtn2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCalculatorDlg::OnClickBtn3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCalculatorDlg::OnClickBtn4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCalculatorDlg::OnClickBtn5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCalculatorDlg::OnClickBtn6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCalculatorDlg::OnClickBtn7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCalculatorDlg::OnClickBtn8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCalculatorDlg::OnClickBtn9)
	ON_BN_CLICKED(IDC_BUTTON_B, &CCalculatorDlg::OnClickBtnB)
	ON_BN_CLICKED(IDC_BUTTON_O, &CCalculatorDlg::OnClickBtnO)
	ON_BN_CLICKED(IDC_BUTTON_D, &CCalculatorDlg::OnClickBtnD)
	ON_BN_CLICKED(IDC_BUTTON_H, &CCalculatorDlg::OnClickBtnH)

	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCalculatorDlg::OnClickBtnAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CCalculatorDlg::OnClickBtnSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CCalculatorDlg::OnClickBtnMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalculatorDlg::OnClickBtnDiv)

	ON_BN_CLICKED(IDC_BUTTON_RESVER, &CCalculatorDlg::OnClickBtnResver)
	ON_BN_CLICKED(IDC_BUTTON_POINT, &CCalculatorDlg::OnClickBtnPoint)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCalculatorDlg::OnClickBtnClear)
	ON_BN_CLICKED(IDC_BUTTON_ENTER, &CCalculatorDlg::OnClickBtnEnter)

	ON_BN_CLICKED(IDC_BUTTON_SQRT, &CCalculatorDlg::OnClickBtnSqrt)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CCalculatorDlg::OnClickBtnBack)
	ON_BN_CLICKED(IDC_BUTTON_EXP, &CCalculatorDlg::OnClickBtnExp)
	ON_BN_CLICKED(IDC_BUTTON_POWER, &CCalculatorDlg::OnClickBtnPower)
	ON_BN_CLICKED(IDC_BUTTON_COS, &CCalculatorDlg::OnClickBtnCos)
	ON_BN_CLICKED(IDC_BUTTON_SIN, &CCalculatorDlg::OnClickBtnSin)
	ON_BN_CLICKED(IDC_BUTTON_LN, &CCalculatorDlg::OnClickBtnLn)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &CCalculatorDlg::OnClickBtnLog)
	ON_BN_CLICKED(IDC_BUTTON_TAN, &CCalculatorDlg::OnClickBtnTan)
	ON_BN_CLICKED(IDC_BUTTON_FACTOR, &CCalculatorDlg::OnClickBtnFactor)
	ON_BN_CLICKED(IDC_BUTTON_ARITH, &CCalculatorDlg::OnClickBtnArith)

	ON_BN_CLICKED(IDC_BUTTON_AND, &CCalculatorDlg::OnClickBtnAnd)
	ON_BN_CLICKED(IDC_BUTTON_OR, &CCalculatorDlg::OnClickBtnOr)
	ON_BN_CLICKED(IDC_BUTTON_INVERSE, &CCalculatorDlg::OnClickBtnInverse)
	ON_BN_CLICKED(IDC_BUTTON_XOR, &CCalculatorDlg::OnClickBtnXor)

	ON_BN_CLICKED(IDOK,&CCalculatorDlg::OnBtnOK)
	ON_WM_PAINT()
END_MESSAGE_MAP()



BOOL CCalculatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		


	UpdateData(FALSE);
	UpdateSceneDisplay();
	return TRUE;  
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CCalculatorDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_WINCECALCULATOR_DIALOG_WIDE) : 
		MAKEINTRESOURCE(IDD_WINCECALCULATOR_DIALOG));
	}
}
#endif

void CCalculatorDlg::UpdateSceneDisplay()	
{
	UpdateData(TRUE);
	switch (m_bCalType)
	{
	case 0:
		{		
			MoveWindow(600,500,430,280);
			UpdateSceneDisplay(TRUE,FALSE,FALSE);
			break;
		}
	case 1:
		{
			MoveWindow(600,500,450,400);
			UpdateSceneDisplay(TRUE,TRUE,FALSE);
			break;
		}
	case 2:
		{
			MoveWindow(600,500,520,140);
			UpdateSceneDisplay(FALSE,FALSE,TRUE);

			break;
		}

	}

}

void CCalculatorDlg::UpdateSceneDisplay(BOOL i_bNormal,BOOL i_bScienc,BOOL i_bArith)
{
	//Basic
	GetDlgItem(IDC_BUTTON0)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON6)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON7)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON8)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON9)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_DIV)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_MUL)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_SUB)->ShowWindow(i_bNormal);

	GetDlgItem(IDC_BUTTON_RESVER)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_POINT)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_CLEAR)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_SQRT)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_BACK)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_ENTER)->ShowWindow(i_bNormal);

	//Scientific
	GetDlgItem(IDC_RADIO_ANGLE)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_RADIO_RADIAN)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_EXP)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_POWER)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_COS)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_SIN)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_LN)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_LOG)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_TAN)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_FACTOR)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_O)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_B)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_D)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_H)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_AND)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_OR)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_INVERSE)->ShowWindow(i_bScienc);
	GetDlgItem(IDC_BUTTON_XOR)->ShowWindow(i_bScienc);

	//Arithmetic
	GetDlgItem(IDC_EDIT_ARITH_EXPRESSION)->ShowWindow(i_bArith);
	GetDlgItem(IDC_EDIT_ARITH_RESULT)->ShowWindow(i_bArith);
	GetDlgItem(IDC_BUTTON_ARITH)->ShowWindow(i_bArith);
	GetDlgItem(IDC_BUTTON_MR)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_MC)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_MS)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_BUTTON_MADD)->ShowWindow(i_bNormal);
	GetDlgItem(IDC_EDIT_RESULT)->ShowWindow(!i_bArith);
}

void CCalculatorDlg::UpdateResultDisplay(double i_dValue)	//Output Function
{
	m_csCalculateRes.Format(_T("%f"),i_dValue);
	int iLength = m_csCalculateRes.GetLength();
	while(m_csCalculateRes.GetAt(iLength-1)=='0') 
	{  
		m_csCalculateRes.Delete(iLength-1,1);  
		iLength--; 
	}
	if (m_csCalculateRes.GetAt(iLength-1)=='.')
	{
		m_csCalculateRes.Delete(iLength-1,1);
	}
	UpdateData(FALSE);
}

void CCalculatorDlg::JudgeAngleOrRadian()	
{
	switch(m_bIsAngle)
	{
	case 0:
		m_dSecondNum=m_dSecondNum*m_PI/180;
		break;
	case 1:
		m_dSecondNum=m_dSecondNum;
		break;
	}
}

void CCalculatorDlg::GetCalculateResult()	
{

	if(!m_bIsLogical)
	{
		switch(m_csOperateSign.GetAt(0))
		{  
		case '+': 
			m_dFirstNum+=m_dSecondNum;
			break;
		case '-': 
			m_dFirstNum-=m_dSecondNum;
			break;
		case '*': 
			m_dFirstNum*=m_dSecondNum;
			break;
		case '/':
			if(fabs(m_dSecondNum)<=0.000001)
			{
				m_csCalculateRes=_T("Divisor can not be 0");
				UpdateData(FALSE);
				return;  
			}
			else
			{
				m_dFirstNum/=m_dSecondNum;
				break;
			}

		}
	}
	else
	{
		int nResult = 0;
		if(0 == m_csOperateSign.Compare(_T("&&")))
		{
			nResult = m_dFirstNum && m_dSecondNum;
		}
		else if(0 == m_csOperateSign.Compare(_T("||")))
		{
			nResult = m_dFirstNum || m_dSecondNum;
		}
		else if(0 == m_csOperateSign.Compare(_T("!")))
		{
			m_dFirstNum+=m_dSecondNum;
			nResult = !m_dFirstNum;
		}
		else if(0 == m_csOperateSign.Compare(_T("^")))
		{
			nResult = (int)m_dFirstNum ^ (int)m_dSecondNum;
		}
		m_dFirstNum = nResult;
		m_bIsLogical = FALSE;
	}


	m_dSecondNum=0.0;
	m_dCoff=1.0;
	m_csOperateSign=_T("+");
	UpdateResultDisplay(m_dFirstNum);//Update display Result
}

void CCalculatorDlg::OnBtnClickNumber(int i_Num)	
{
	UpdateData(TRUE);
	if( m_dCoff == 1.0)
	{
		m_dSecondNum = m_dSecondNum*10 + i_Num;
	}
	else  
	{ 
		m_dSecondNum = m_dSecondNum + i_Num*m_dCoff; 
		m_dCoff *= 0.1;
	}
	UpdateResultDisplay(m_dSecondNum);
}

void CCalculatorDlg::OnClickBtn0()
{
	
	OnBtnClickNumber(0);
}

void CCalculatorDlg::OnClickBtn1()
{
	OnBtnClickNumber(1);
}


void CCalculatorDlg::OnClickBtn2()
{
	
	OnBtnClickNumber(2);
}


void CCalculatorDlg::OnClickBtn3()
{
	
	OnBtnClickNumber(3);
}

void CCalculatorDlg::OnClickBtn4()
{
	
	OnBtnClickNumber(4);
}

void CCalculatorDlg::OnClickBtn5()
{
	
	OnBtnClickNumber(5);
}


void CCalculatorDlg::OnClickBtn6()
{
	
	OnBtnClickNumber(6);
}


void CCalculatorDlg::OnClickBtn7()
{
	
	OnBtnClickNumber(7);
}


void CCalculatorDlg::OnClickBtn8()
{
	
	OnBtnClickNumber(8);
}


void CCalculatorDlg::OnClickBtn9()
{
	
	OnBtnClickNumber(9);
}


void CCalculatorDlg::OnClickBtnResver()	
{
	
	UpdateData(TRUE);
	CString csSign = _T("-");
	int nPos = m_csCalculateRes.Find('-');
	if (-1 == nPos)
	{
		csSign.Append(m_csCalculateRes);
		m_csCalculateRes = csSign;
	}
	else
	{
		m_csCalculateRes = m_csCalculateRes.Right(m_csCalculateRes.GetLength()-1);
	}

	UpdateData(FALSE);
}


void CCalculatorDlg::OnClickBtnPoint()	
{
	
	m_dCoff= 0.1 ;
}

void CCalculatorDlg::OnClickBtnClear()	//Clear
{
	
	m_dFirstNum=0.0;
	m_dSecondNum=0.0;
	m_csOperateSign = _T("+");
	m_dCoff = 1.0;
	UpdateResultDisplay(0.0);
}

void CCalculatorDlg::OnClickBtnEnter()	
{

	GetCalculateResult(); 
}


void CCalculatorDlg::OnClickBtnNormalCal()	
{
	UpdateSceneDisplay();
}

void CCalculatorDlg::OnClickBtnScienceCal()
{
	UpdateSceneDisplay();
}

void CCalculatorDlg::OnClickBtnArithCal()	
{
	UpdateSceneDisplay();
}

void CCalculatorDlg::OnClickBtnAdd()	//+
{

	GetCalculateResult();
	m_csOperateSign="+";
}


void CCalculatorDlg::OnClickBtnSub()	//-
{

	GetCalculateResult();
	m_csOperateSign="-";
}


void CCalculatorDlg::OnClickBtnMul()	//*
{

	GetCalculateResult();
	m_csOperateSign="*";
}


void CCalculatorDlg::OnClickBtnDiv()	///
{

	GetCalculateResult();
	m_csOperateSign.Format(_T("%s"),"/");
}


void CCalculatorDlg::OnClickBtnSqrt()	//sqrt
{

	if( m_dSecondNum==0)
	{    
		m_dFirstNum=sqrt(m_dFirstNum);      
		UpdateResultDisplay(m_dFirstNum);   
	}
	else
	{ 
		m_dSecondNum=sqrt(m_dSecondNum);    
		UpdateResultDisplay(m_dSecondNum);
	}
}


void CCalculatorDlg::OnClickBtnBack()	
{

	if(fabs(m_dSecondNum)<0.000001 && fabs(m_dFirstNum)<0.000001)
	{
		m_csCalculateRes = _T("Divisor can not be 0");
		UpdateData(FALSE);
		return;
	}
	if( fabs(m_dSecondNum)<0.000001)
	{    
		m_dFirstNum=1.0/m_dFirstNum;
		UpdateResultDisplay(m_dFirstNum);
	}
	else
	{ 
		m_dSecondNum=1.0/m_dSecondNum;
		UpdateResultDisplay(m_dSecondNum);
	}

}



void CCalculatorDlg::OnClickBtnExp()	
{

	m_dSecondNum=exp(m_dSecondNum);
	UpdateResultDisplay(m_dSecondNum);
}


void CCalculatorDlg::OnClickBtnPower()	//10 N square
{

	m_dSecondNum=pow(10,m_dSecondNum);
	UpdateResultDisplay(m_dSecondNum);
}


void CCalculatorDlg::OnClickBtnCos()	//¼ÆËãCOS
{

	JudgeAngleOrRadian();
	m_dSecondNum=cos(m_dSecondNum);
	UpdateResultDisplay(m_dSecondNum);
}


void CCalculatorDlg::OnClickBtnSin()	//calculate SIN
{

	JudgeAngleOrRadian();
	m_dSecondNum=sin(m_dSecondNum);
	UpdateResultDisplay(m_dSecondNum);
}


void CCalculatorDlg::OnClickBtnLn()	//calculate LN
{

	m_dSecondNum=log(m_dSecondNum);
	UpdateResultDisplay(m_dSecondNum);
}


void CCalculatorDlg::OnClickBtnLog()	//calculate LOG
{

	m_dSecondNum=log10(m_dSecondNum);
	UpdateResultDisplay(m_dSecondNum);
}


void CCalculatorDlg::OnClickBtnTan()	//calculate TAN
{

	JudgeAngleOrRadian();
	m_dSecondNum=tan(m_dSecondNum);
	UpdateResultDisplay(m_dSecondNum);
}


void CCalculatorDlg::OnClickBtnFactor()	//factor
{

	if((m_dSecondNum-(int)m_dSecondNum)>0)
	{
		m_csCalculateRes =_T("Please enter integer number");
		UpdateData(false);
		return;
	}
	else 
	{
		m_dSecondNum=(double)FactorialCalcluate(m_dSecondNum);
		UpdateResultDisplay(m_dSecondNum);
	}
}

int CCalculatorDlg::FactorialCalcluate(int i_nNum)	//factor calculate function
{
	if(0 == i_nNum||1 == i_nNum)
	{
		return 1;
	}
	else if(1<i_nNum)
	{
		return i_nNum*FactorialCalcluate(i_nNum-1);
	}
}

BOOL CCalculatorDlg::ArithInputJudgment()	//Arithmetic input
{
	BOOL bContinue = TRUE;
	CString csExpression = m_csArithExpression;
	int nLength = csExpression.GetLength();
	for (int i=0;i<nLength;i++)
	{
		char ch = csExpression.GetAt(i);
		if (!((ch <= '9' && ch >= '0') || ch == '+' || ch == '-'||ch == '*'||ch == '/'||ch == '('||ch == ')' ))
		{
			bContinue = FALSE;
			MessageBox(_T("Error"),_T("tips"),MB_OKCANCEL|MB_ICONWARNING);
			break;
		}
	}
	char cLast = csExpression.GetAt(nLength-1);
	if (cLast == '+' || cLast == '-'||cLast == '*'||cLast == '/')
	{
		bContinue = FALSE;
		MessageBox(_T("    Error"),_T("tips"),MB_OKCANCEL|MB_ICONWARNING);
	}
	return bContinue;
}

void ArithExpressionTransform(string &i_strExpression)	
{  
	stringstream ss;  
	stack<char> stk;  
	for (size_t i = 0; i < i_strExpression.length(); i++) 
	{  
		if (isdigit(i_strExpression.at(i))) 
		{  
			ss << i_strExpression.at(i);   
			if ((i < i_strExpression.length() - 1 && !isdigit(i_strExpression.at(i + 1)))  
				|| i == i_strExpression.length() - 1) 
			{  
				ss << ' ';  
			}  
		}  
		else 
		{  
			if (stk.empty()) 
			{  
				stk.push(i_strExpression.at(i));  
			}  
			else 
			{  
				switch (i_strExpression.at(i)) 
				{  
				case '(':  
					stk.push(i_strExpression.at(i));  
					break;  
				case ')':  
					while (stk.top() != '(') 
					{  
						ss << stk.top();  
						stk.pop();  
					}  
					stk.pop();  
					break;  
				case '+':  
				case '-':  
					while (!stk.empty() && stk.top() != '(')
					{  
						ss << stk.top();  
						stk.pop();  
					}  
					stk.push(i_strExpression.at(i));  
					break;  
				case '*':  
				case '/':  
					while (!stk.empty() && (stk.top() == '*' || stk.top() == '/')) 
					{  
						ss << stk.top();  
						stk.pop();  
					}  
					stk.push(i_strExpression.at(i));  
					break;  
				}  
			}  
		}  
	}  
	while (!stk.empty()) 
	{  
		ss << stk.top();  
		stk.pop();  
	}  
	i_strExpression = ss.str();  
}  

float ArithExpressionCalculate(const string &i_sreExpression)	
{  
	stack<float> stk;  
	for (size_t i = 0; i < i_sreExpression.length(); i++) 
	{  

		if (isdigit(i_sreExpression.at(i))) 
		{  
			int e = atoi(&i_sreExpression.at(i));  
			int t = e / 10;  
			while (t > 0) 
			{  
				i++;  
				t /= 10;  
			}  
			i++;  
			stk.push(e);  
		}  
		else 
		{  
			float r = stk.top();  
			stk.pop();  
			float l = stk.top();  
			stk.pop();  
			float result;  
			switch (i_sreExpression.at(i))
			{  
			case '+':  
				result = l + r;  
				break;  
			case '-':  
				result = l - r;  
				break;  
			case '*':  
				result = l * r;  
				break;  
			case '/':  
				result = l / r;  
				break;  
			}  
			stk.push(result);  
		}  
	}  
	return stk.top();  
}  

void CCalculatorDlg::OnClickBtnArith()	
{

	UpdateData(TRUE);
	USES_CONVERSION;
	BOOL bContinue = ArithInputJudgment();
	if (bContinue)
	{
		string strExpression = T2A(m_csArithExpression);
		ArithExpressionTransform(strExpression);
		float fResult = ArithExpressionCalculate(strExpression);
		CString csResult;
		if (0 == fResult-(int)fResult)
		{
			csResult.Format(_T("%.0f"),fResult);
		}
		else
		{
			csResult.Format(_T("%.6f"),fResult);
		}

		m_csArithRes = csResult;
	}
	else
	{
		m_csArithExpression = _T("");
		m_csArithRes = _T("");
	}

	UpdateData(FALSE);
}

void CCalculatorDlg::OnBtnOK()
{
	
}

void CCalculatorDlg::OnClickBtnB()	//convert to Binary
{

	char s2[100]; 
	_itoa(m_dSecondNum,s2,2); 
	m_csCalculateRes = s2;
	UpdateData(FALSE);
}


void CCalculatorDlg::OnClickBtnO()	//convert to Octal
{
	
	char s8[100];
	_itoa(m_dSecondNum,s8,8);
	m_csCalculateRes = s8;
	UpdateData(FALSE);
}


void CCalculatorDlg::OnClickBtnD()	//convert to Decimal
{

	char s10[100];
	_itoa(m_dSecondNum,s10,10); 
	m_csCalculateRes = s10;
	UpdateData(FALSE);
}


void CCalculatorDlg::OnClickBtnH()	//convert to Heaxadecimal
{

	char s16[100];
	_itoa(m_dSecondNum,s16,16); 
	m_csCalculateRes = s16;
	UpdateData(FALSE);
}


void CCalculatorDlg::OnClickBtnAnd()	
{

	GetCalculateResult();
	m_csOperateSign = "&&";
	m_bIsLogical = TRUE;
}


void CCalculatorDlg::OnClickBtnOr()	
{

	GetCalculateResult();
	m_csOperateSign = "||";
	m_bIsLogical = TRUE;
}


void CCalculatorDlg::OnClickBtnInverse()	
{

	m_csOperateSign = "!";
	m_bIsLogical = TRUE;
	GetCalculateResult();


}


void CCalculatorDlg::OnClickBtnXor()	
{

	GetCalculateResult();
	m_csOperateSign = "^";
	m_bIsLogical = TRUE;
}


void CCalculatorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(100,128,235));
	//dc.FillPath();
	CDialog::OnPaint();
	// CDialog::OnPaint()
}
