
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "ChatMessage.h"
#include <vector>

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
	CStatic* m_MessagesTexts;
	CImage* m_MessagesAvatars;
	
private:
	void OnBnSendClick();
	void UpdateMessageInputPosition(CRect editRect);
	void UpdateMessageSendButtonPosition(CRect editRect);
	void UpdateScrollBarSize(CRect editRect);
	void UpdateMessagesWindow();
	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	std::vector<ChatMessage> messages;
};


