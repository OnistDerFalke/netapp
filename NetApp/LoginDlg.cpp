// LoginDlg.cpp : implementation file
//

#include "pch.h"
#include "NetApp.h"
#include "afxdialogex.h"
#include "LoginDlg.h"


// LoginDlg dialog

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
{

}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERNAME, m_UsernameControl);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
	ON_BN_CLICKED(IDLOGIN, &LoginDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDQUIT, &LoginDlg::OnBnClickedQuit)
	ON_EN_CHANGE(IDC_USERNAME, &LoginDlg::OnUsernameEdit)
	ON_STN_CLICKED(IDC_ERRORMSG, &LoginDlg::OnStnClickedErrormsg)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


void LoginDlg::OnClose()
{
	AfxPostQuitMessage(0);
}


void LoginDlg::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void LoginDlg::OnBnClickedQuit()
{
	AfxPostQuitMessage(0);
}


void LoginDlg::OnUsernameEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void LoginDlg::OnStnClickedErrormsg()
{
	// TODO: Add your control notification handler code here
}
