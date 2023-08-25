#pragma once
#include "ChatMessage.h"
#include "ConnectionManager.h"
#include "SerializableChatMessage.h"
#include <vector>
#include <thread>

class ConnectionManager;
class CMainFrame : public CFrameWndEx
{
public:
	virtual ~CMainFrame();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = nullptr, CCreateContext* pContext = nullptr);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	void SetUser(CString username, CImage avatar);
	void UpdateMessagesWindow(CRect editRect);
#endif
	CImage m_UserAvatar;
	CString m_UserName;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)
	DECLARE_MESSAGE_MAP()

	CEdit m_MessageInputControl;
	CButton m_SendButton;
	CScrollBar m_Scrollbar;
	std::vector<CStatic*> m_MessagesTexts;
	std::vector<CStatic*> m_MessagesAvatars;
	
private:
	void OnBnSendClick();
	void UpdateMessageInputPosition(CRect editRect);
	void UpdateMessageSendButtonPosition(CRect editRect);
	void UpdateScrollBarSize(CRect editRect);
	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	std::vector<ChatMessage> messages;
	ConnectionManager* connectionManager;
	std::thread listeningThread;
};