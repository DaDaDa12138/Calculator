
//

#pragma once

// CCalculatorDlg 
class CCalculatorDlg : public CDialog
{
	// Stucture
public:
	CCalculatorDlg(CWnd* pParent = NULL);	

	// Dlg Data
	enum { IDD = IDD_WINCECALCULATOR_DIALOG };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	
protected:
	HICON m_hIcon;
public:
	CString m_csCalculateRes;			//Save calculate result
	CString m_csOperateSign;			//Save calculate operator
	CString m_csArithRes;
	CString m_csArithExpression;
	int		m_bCalType;					//Calculator type 

	int		m_bIsAngle;					//angle
	double	m_dFirstNum;				
	double	m_dSecondNum;				

	double	m_dCoff;					
	double	m_PI;
	BOOL m_bIsLogical;					
public:
	void OnBtnClickNumber(int i_Num);
	void GetCalculateResult();
	void JudgeAngleOrRadian();							
	int	 FactorialCalcluate(int i_nNum);				
	void UpdateResultDisplay(double i_dValue);	//update calculate result
	void UpdateSceneDisplay();						//interface switch
	void UpdateSceneDisplay(BOOL i_bNormal,BOOL i_bScienc,BOOL i_bArith);	
	BOOL ArithInputJudgment();				
	void LogicalCalculate();					

	afx_msg void OnClickBtn0();
	afx_msg void OnClickBtn1();
	afx_msg void OnClickBtn2();
	afx_msg void OnClickBtn3();
	afx_msg void OnClickBtn4();
	afx_msg void OnClickBtn5();
	afx_msg void OnClickBtn6();
	afx_msg void OnClickBtn7();
	afx_msg void OnClickBtn8();
	afx_msg void OnClickBtn9();
	afx_msg void OnClickBtnB();
	afx_msg void OnClickBtnO();
	afx_msg void OnClickBtnD();
	afx_msg void OnClickBtnH();

	afx_msg void OnClickBtnAdd();
	afx_msg void OnClickBtnSub();
	afx_msg void OnClickBtnMul();
	afx_msg void OnClickBtnDiv();

	afx_msg void OnClickBtnResver();
	afx_msg void OnClickBtnPoint();
	afx_msg void OnClickBtnEnter();
	afx_msg void OnClickBtnNormalCal();
	afx_msg void OnClickBtnScienceCal();
	afx_msg void OnClickBtnArithCal();

	afx_msg void OnClickBtnSqrt();
	afx_msg void OnClickBtnBack();
	afx_msg void OnClickBtnExp();
	afx_msg void OnClickBtnPower();
	afx_msg void OnClickBtnCos();
	afx_msg void OnClickBtnSin();
	afx_msg void OnClickBtnLn();
	afx_msg void OnClickBtnLog();
	afx_msg void OnClickBtnTan();
	afx_msg void OnClickBtnFactor();
	afx_msg void OnClickBtnArith();


	afx_msg void OnClickBtnAnd();
	afx_msg void OnClickBtnOr();
	afx_msg void OnClickBtnInverse();
	afx_msg void OnClickBtnXor();
	afx_msg void OnClickBtnClear();

	afx_msg void OnBtnOK();
	
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};
