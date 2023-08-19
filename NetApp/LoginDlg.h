#pragma once
#include "afxdialogex.h"

class LoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = nullptr); 
	virtual ~LoginDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedQuit();
	afx_msg void OnUsernameEdit();
	afx_msg void OnStnClickedErrormsg();
	afx_msg void OnClose();

	bool LoginDlg::CheckUsernameMeetsCriteria();
	bool LoginDlg::CheckAvatarMeetsCriteria();

	CEdit m_UsernameControl;
	CStatic m_AvatarControl;
	
	afx_msg void OnBnClickedAvatar();
	afx_msg void OnStnClickedAvatarimg();

	CString d_username;
	CImage d_avatar;
};
