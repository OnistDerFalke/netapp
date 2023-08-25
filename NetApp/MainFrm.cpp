
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
	//Sprzatanie
	delete m_MessageInputControl;
	delete m_SendButton;
	for (CStatic* pStatic : m_MessagesTexts) delete pStatic;
	for (CStatic* pStatic : m_MessagesAvatars) delete pStatic;
	m_MessagesTexts.clear();
	m_MessagesAvatars.clear();
	delete connectionManager;
	listeningThread.join();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//Tworzenie dynamiczne tych wszystkich elementow UI w czacie

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

	if(!m_Scrollbar.Create(SBS_VERT | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_SCROLLBAR))
	{
		TRACE0("Scrollbar could not be created.\n");
		return -1;
	}

	//inicjalizacja tego polaczenia z serwerem i osobny watek nasluchujacy na wiadomosci i wyswietlajacy je
	//teoretycznie mialo dzialac ale cos nie do konca od serwera wraca ten broadcast (czasem tak czasem nie) i aplikacja lubi sie zawiesic
	connectionManager = new ConnectionManager();
	CRect editRect;
	GetClientRect(&editRect);
	listeningThread = std::thread([&]() {
		connectionManager->ListenForMessages(messages, editRect, this);
		});
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

		//Dopasowywanie elementow UI do rozmiaru okna
		UpdateMessageInputPosition(editRect);
		UpdateMessageSendButtonPosition(editRect);
		UpdateScrollBarSize(editRect);
	}
}

void CMainFrame::OnBnSendClick()
{
	CString message;
	CRect editRect;
	GetClientRect(&editRect);
	m_MessageInputControl.GetWindowText(message);
	m_MessageInputControl.SetWindowText(_T(""));

	/*wysylanie wiadomosci do serwera (CImage planowalem zeby zapisywany jakos moze jako ciag znakow, na razie wstawilem username zeby bylo cokolwiek do wyslania jako avatar)*/
	//SerializableChatMessage msg(static_cast<std::string>(CW2A(message)), static_cast<std::string>(CW2A(m_UserName)));
	//connectionManager->SendMsg(msg.ToString());

	/*dodawanie wiadomosci lokalnie bez udzialu serwera*/
	messages.emplace_back(message, m_UserAvatar);
	UpdateMessagesWindow(editRect);
}

//Responsywnosc okna do inputu
void CMainFrame::UpdateMessageInputPosition(CRect editRect)
{
	int width = static_cast<int>(editRect.Width() * 0.8);
	int height = editRect.Height() * 0.1;
	int left = (editRect.Width() - static_cast<double>(width)) / 2 - 0.095 * editRect.Width();
	int top = editRect.bottom - height - 5;

	m_MessageInputControl.MoveWindow(left, top, width, height);
}

//Responsywnosc przycisku wysylania
void CMainFrame::UpdateMessageSendButtonPosition(CRect editRect)
{
	int width = static_cast<int>(editRect.Width() * 0.19);
	int height = editRect.Height() * 0.1;
	int left = (editRect.Width() - width) - 0.0025 * editRect.Width();
	int top = editRect.bottom - height - 5;

	m_SendButton.MoveWindow(left, top, width, height);
}

//Responsywnosc suwaka (nie jest podlaczony do kontekstu czatu)
void CMainFrame::UpdateScrollBarSize(CRect editRect)
{
	int width = static_cast<int>(editRect.Width() * 0.01);
	int height = editRect.Height() * 0.89;
	int left = editRect.Width() - width;
	int top = editRect.Height() * 0.005;
	m_Scrollbar.MoveWindow(left, top, width, height);
}

void CMainFrame::UpdateMessagesWindow(CRect editRect)
{
	int messages_num = messages.size();
	int messages_elem = m_MessagesTexts.size();
	m_Scrollbar.SetScrollRange(0, messages_num - 10);

	for (int i = messages_elem; i < messages_num; i++)
	{
		/* Wyswietlanie wiadomosci na czacie, na razie bez podlaczania scrolla */
		CRect rect(50, 10 + i * 30, editRect.Width() - 60, 30 + i * 30);
		CStatic* pStatic = new CStatic();
		pStatic->Create(_T(""), WS_CHILD | WS_VISIBLE, rect, this);
		pStatic->SetWindowTextW(messages[i].message);
		m_MessagesTexts.push_back(pStatic);

		/*Tutaj wyswietlanie awatara (na razie po prostu czarny kwadrat), 
		totalnie w pionie offset sie nie zgadza chociaz ten sam wzor jest, 
		a jeszcze cos przeslania, zostawilem na pozniej*/

		/*CRect avrect(5, 10 + i * 30, 25, 30 + i * 30);
		CStatic* pPictureStatic = new CStatic();
		pPictureStatic->Create(_T(""), WS_CHILD | WS_VISIBLE | SS_BITMAP, avrect, this);
		CDC* pDC = pPictureStatic->GetDC();
		pDC->FillSolidRect(avrect, RGB(0, 0, 0));
		pPictureStatic->InvalidateRect(avrect);
		pPictureStatic->ReleaseDC(pDC);
		m_MessagesAvatars.push_back(pPictureStatic);*/
	}
}

void CMainFrame::SetUser(CString username, CImage avatar)
{
	this->m_UserName = username;
	this->m_UserAvatar = avatar;
}

//Tutaj bylby podlaczony scroll
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

