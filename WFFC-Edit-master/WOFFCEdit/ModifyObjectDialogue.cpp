#include "ModifyObjectDialogue.h"

#include "resource.h"
#include "stdafx.h"


IMPLEMENT_DYNAMIC(ModifyObjectDialogue, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(ModifyObjectDialogue, CDialogEx)
	ON_COMMAND(IDOK, &ModifyObjectDialogue::End)					//ok button
	ON_BN_CLICKED(IDOK, &ModifyObjectDialogue::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &ModifyObjectDialogue::OnChangeXPos)
	//ON_LBN_SELCHANGE(IDC_LIST1, &ModifyObjectDialogue::Select)	//listbox
END_MESSAGE_MAP()

ModifyObjectDialogue::ModifyObjectDialogue(CWnd* pParent, std::vector<SceneObject>* SceneGraph)
{
}

ModifyObjectDialogue::ModifyObjectDialogue(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG2, pParent)
{
}


ModifyObjectDialogue::~ModifyObjectDialogue()
{
}

//void ModifyObjectDialogue::SetToolsAndInfo(ToolMain* tool)
//{
//	m_ToolSystem = tool;
//
//	m_currentSelectionID = m_ToolSystem->m_selectedObject;
//	m_sceneGraph = &m_ToolSystem->m_sceneGraph;
//
//	//means that an object other than the ground is selected
//	if(m_currentSelectionID > -1)
//	{
//		pWnd = GetDlgItem(IDC_EDIT1);
//		pWnd->SetWindowText(std::to_wstring(m_sceneGraph->at(m_currentSelectionID).posX).c_str());
//	}
//	
//}

void ModifyObjectDialogue::SetFieldInfo(std::vector<DisplayObject>* disList, ToolMain* tool)
{
	m_ToolSystem = tool;
	m_currentSelectionID = m_ToolSystem->m_selectedObject;
	m_displayList = disList;

	m_ToolSystem->IsSelectionAvailable(false);
	if (m_currentSelectionID > -1)
	{
		pWnd = GetDlgItem(IDC_EDIT1);
		pWnd->SetWindowText(std::to_wstring(m_displayList->at(m_currentSelectionID).m_position.x).c_str());
	}
}

void ModifyObjectDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void ModifyObjectDialogue::End()
{
	DestroyWindow();
}

void ModifyObjectDialogue::OnChangeXPos()
{
}

BOOL ModifyObjectDialogue::OnInitDialog()
{
	return CDialogEx::OnInitDialog();
}

void ModifyObjectDialogue::PostNcDestroy()
{
	m_ToolSystem->IsSelectionAvailable(true);
	CDialogEx::PostNcDestroy();
}

void ModifyObjectDialogue::OnBnClickedOk()
{
	CString newPosX;
	float newPosXFloat;

	pWnd = GetDlgItem(IDC_EDIT1);
	pWnd->GetWindowText(newPosX);

	//change to float
	swscanf_s(newPosX, L"%f", &newPosXFloat);
	//Set the new position.
	m_displayList->at(m_currentSelectionID).m_position.x = newPosXFloat;

	m_ToolSystem->IsSelectionAvailable(true);
	CDialogEx::OnOK();
}

