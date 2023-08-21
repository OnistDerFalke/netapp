
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "NetApp.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MESSAGES_BUFFER_SIZE 100

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SETTINGCHANGE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_MESSAGE_SEND, &CMainFrame::OnBnSendClick)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,          
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


CMainFrame::CMainFrame() noexcept
{

}

CMainFrame::~CMainFrame()
{
	delete m_MessageInputControl;
	delete m_SendButton;
	delete[] m_MessagesTexts;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_MessageInputControl.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_MESSAGE_INPUT))
	{
		TRACE0("Message input field could not be created.\n");
		return -1;
	}

	if (!m_SendButton.Create(_T("Send"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(0, 0, 0, 0), this, IDC_MESSAGE_SEND))
	{
		TRACE0("Button could not be created.\n");
		return -1;
	}

	m_Scrollbar.Create(SBS_VERT | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_SCROLLBAR);
	
	m_MessagesTexts = new CStatic[MESSAGES_BUFFER_SIZE];
	for (int i = 0; i < MESSAGES_BUFFER_SIZE; i++)
	{
		CRect rect(10, 10 + i * 30, 200 - GetSystemMetrics(SM_CXVSCROLL), 30 + i * 30);
		m_MessagesTexts[i].Create(_T(""), WS_CHILD | WS_VISIBLE, rect, this);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}


#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}
	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);

	if (IsWindow(m_MessageInputControl.m_hWnd))
	{
		CRect editRect;
		GetClientRect(&editRect);

		UpdateMessageInputPosition(editRect);
		UpdateMessageSendButtonPosition(editRect);
		UpdateScrollBarSize(editRect);
	}
}

void CMainFrame::OnBnSendClick()
{
	CString message;
	m_MessageInputControl.GetWindowText(message);
	m_MessageInputControl.SetWindowText(_T(""));
	//TODO: ogarnac to dodawanie wiadomosci
	messages.emplace_back(message, std::time(nullptr), m_UserAvatar, m_UserName, false);
	UpdateMessagesWindow();
}

void CMainFrame::UpdateMessageInputPosition(CRect editRect)
{
	int width = static_cast<int>(editRect.Width() * 0.8);
	int height = editRect.Height() * 0.1;
	int left = (editRect.Width() - static_cast<double>(width)) / 2 - 0.095 * editRect.Width();
	int top = editRect.bottom - height - 5;

	m_MessageInputControl.MoveWindow(left, top, width, height);
}

void CMainFrame::UpdateMessageSendButtonPosition(CRect editRect)
{
	int width = static_cast<int>(editRect.Width() * 0.19);
	int height = editRect.Height() * 0.1;
	int left = (editRect.Width() - width) - 0.0025 * editRect.Width();
	int top = editRect.bottom - height - 5;

	m_SendButton.MoveWindow(left, top, width, height);
}

void CMainFrame::UpdateScrollBarSize(CRect editRect)
{
	int width = static_cast<int>(editRect.Width() * 0.01);
	int height = editRect.Height() * 0.89;
	int left = editRect.Width() - width;
	int top = editRect.Height() * 0.005;
	m_Scrollbar.MoveWindow(left, top, width, height);
}

void CMainFrame::UpdateMessagesWindow()
{
	int size = messages.size();
	for (int i = 0; i < size; i++)
	{
		m_Scrollbar.SetScrollRange(0, size - 10);
		m_MessagesTexts[i].SetWindowText(messages[i].message);
	}
}

void CMainFrame::SetUser(CString username, CImage avatar)
{
	this->m_UserName = username;
	this->m_UserAvatar = avatar;
}

void CMainFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nScrollPos = m_Scrollbar.GetScrollPos();

	switch (nSBCode)
	{
	case SB_LINEUP:
		
		break;
	case SB_LINEDOWN:
		
		break;
		
	}

	CFrameWndEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

