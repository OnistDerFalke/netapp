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
	DDX_Control(pDX, IDC_AVATARIMG, m_AvatarControl);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
	ON_BN_CLICKED(IDLOGIN, &LoginDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDQUIT, &LoginDlg::OnBnClickedQuit)
	ON_EN_CHANGE(IDC_USERNAME, &LoginDlg::OnUsernameEdit)
	ON_STN_CLICKED(IDC_ERRORMSG, &LoginDlg::OnStnClickedErrormsg)
	ON_BN_CLICKED(IDC_AVATAR, &LoginDlg::OnBnClickedAvatar)
	ON_STN_CLICKED(IDC_AVATARIMG, &LoginDlg::OnStnClickedAvatarimg)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

void LoginDlg::OnClose()
{
	CDialogEx::OnClose();
}


void LoginDlg::OnBnClickedLogin()
{
	m_UsernameControl.GetWindowText(d_username);

	if(CheckUsernameMeetsCriteria() && CheckAvatarMeetsCriteria())
		CDialogEx::OnOK();
}


void LoginDlg::OnBnClickedQuit()
{
	CDialogEx::OnCancel();
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


void LoginDlg::OnBnClickedAvatar()
{
	CFileDialog fileDialog(TRUE, nullptr, nullptr, OFN_FILEMUSTEXIST, _T("Images (*.png;*.jpg)|*.png;*.jpg||"), this);

	if (fileDialog.DoModal() == IDOK)
	{
		//sciezka do obrazku awatara
		CString filePath = fileDialog.GetPathName();

		CImage image;
		CRect rect;
		CDC* pDC = m_AvatarControl.GetDC();

		m_AvatarControl.GetClientRect(rect);

		//czyszczenie przed wstawieniem obrazka
		pDC->FillSolidRect(rect, GetSysColor(COLOR_BTNFACE)); 

		//wstawienie obrazka do kontrolki (teoretycznie dziala ale z sama zawartoscia obrazka dzieja sie dziwne rzeczy)
		/*nie jestem dumny z tego kodu, wiem ze jest chaotycznie, ale niestety mialem w ostatnim tygodniu troche malo czasu zeby usiasc nad nim na dluzej i tez duzo dziwnych
		i niepotrzebnych rzeczy sie stworzylo przy generowaniu projektu, niektore usunalem, innych sie balem, ze cos popsuje, przez co mogl sie zrobic lekki chaos*/
		if (image.Load(filePath) == S_OK)
		{
			d_avatar = image;
			d_avatar.Draw(pDC->GetSafeHdc(), rect.left, rect.top, rect.Width(), rect.Height(),
				0, 0, d_avatar.GetWidth(), d_avatar.GetHeight());
			m_AvatarControl.InvalidateRect(rect);
			m_AvatarControl.ReleaseDC(pDC);
		}
	}
}


void LoginDlg::OnStnClickedAvatarimg()
{
	
}


//Sprawdzanie czy obrazek i nazwa uzytkownika sa w porzadku

bool LoginDlg::CheckUsernameMeetsCriteria()
{
	if (d_username.IsEmpty())
	{
		AfxMessageBox(_T("Username cannot be empty!"));
		return false;
	}

	if (d_username.GetLength() > 30)
	{
		AfxMessageBox(_T("Username cannot have more than 30 characters."));
		return false;
	}

	return true;
}

bool LoginDlg::CheckAvatarMeetsCriteria()
{
	if (d_avatar == nullptr)
	{
		AfxMessageBox(_T("Avatar image was not set."));
		return false;
	}
	return true;
}