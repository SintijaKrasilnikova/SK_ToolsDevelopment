#include "ModifyObjectDialogue.h"

#include "resource.h"
#include "stdafx.h"


IMPLEMENT_DYNAMIC(ModifyObjectDialogue, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(ModifyObjectDialogue, CDialogEx)
	ON_COMMAND(IDOK, &ModifyObjectDialogue::End)					//ok button
	ON_BN_CLICKED(IDOK, &ModifyObjectDialogue::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ModifyObjectDialogue::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &ModifyObjectDialogue::OnSelectTexture)
	ON_EN_CHANGE(IDC_EDIT1, &ModifyObjectDialogue::OnXPosChanged)
	ON_EN_CHANGE(IDC_EDIT2, &ModifyObjectDialogue::OnYPosChanged)
	ON_EN_CHANGE(IDC_EDIT3, &ModifyObjectDialogue::OnZPosChanged)

	ON_EN_CHANGE(IDC_EDIT4, &ModifyObjectDialogue::OnXRotChanged)
	ON_EN_CHANGE(IDC_EDIT5, &ModifyObjectDialogue::OnYRotChanged)
	ON_EN_CHANGE(IDC_EDIT6, &ModifyObjectDialogue::OnZRotChanged)

	ON_EN_CHANGE(IDC_EDIT7, &ModifyObjectDialogue::OnXScaleChanged)
	ON_EN_CHANGE(IDC_EDIT8, &ModifyObjectDialogue::OnYScaleChanged)
	ON_EN_CHANGE(IDC_EDIT9, &ModifyObjectDialogue::OnZScaleChanged)
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
	if (tool != nullptr)
	{
		m_currentSelectionID = m_ToolSystem->m_selectedObject;
		m_displayList = disList;

		m_ToolSystem->IsSelectionAvailable(false);
		if (m_currentSelectionID > -1)
		{
			//set x pos
			pWnd = GetDlgItem(IDC_EDIT1);
			pWnd->SetWindowText(std::to_wstring(m_displayList->at(m_currentSelectionID).m_position.x).c_str());
			//set y pos
			pWnd = GetDlgItem(IDC_EDIT2);
			pWnd->SetWindowText(std::to_wstring(m_displayList->at(m_currentSelectionID).m_position.y).c_str());
			//set z pos
			pWnd = GetDlgItem(IDC_EDIT3);
			pWnd->SetWindowText(std::to_wstring(m_displayList->at(m_currentSelectionID).m_position.z).c_str());

			//set x rot
			pWnd = GetDlgItem(IDC_EDIT4);
			pWnd->SetWindowText(std::to_wstring(m_displayList->at(m_currentSelectionID).m_orientation.x).c_str());
			//set y rot
			pWnd = GetDlgItem(IDC_EDIT5);
			pWnd->SetWindowText(std::to_wstring(m_displayList->at(m_currentSelectionID).m_orientation.y).c_str());
			//set z rot
			pWnd = GetDlgItem(IDC_EDIT6);
			pWnd->SetWindowText(std::to_wstring(m_displayList->at(m_currentSelectionID).m_orientation.z).c_str());

			//set x scale
			pWnd = GetDlgItem(IDC_EDIT7);
			pWnd->SetWindowText(std::to_wstring(m_displayList->at(m_currentSelectionID).m_scale.x).c_str());
			//set y scale
			pWnd = GetDlgItem(IDC_EDIT8);
			pWnd->SetWindowText(std::to_wstring(m_displayList->at(m_currentSelectionID).m_scale.y).c_str());
			//set z scale
			pWnd = GetDlgItem(IDC_EDIT9);
			pWnd->SetWindowText(std::to_wstring(m_displayList->at(m_currentSelectionID).m_scale.z).c_str());

			pWnd = GetDlgItem(IDC_EDIT11);
			std::string texPathString = m_displayList->at(m_currentSelectionID).m_texturePath;
			std::wstring wstringTexPath;
			StringToWString(wstringTexPath, texPathString);

			//https://stackoverflow.com/questions/1200188/how-to-convert-stdstring-to-lpcstr
			LPCWSTR pcwstr = wstringTexPath.c_str();
			pWnd->SetWindowText(pcwstr);

		}
	}
}
int ModifyObjectDialogue::StringToWString(std::wstring& ws, const std::string& s)
{
	//https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
	std::wstring wsTmp(s.begin(), s.end());
	ws = wsTmp;
	return 0;
}

void ModifyObjectDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, newPosXFloat);
	DDX_Text(pDX, IDC_EDIT2, newPosYFloat);
	DDX_Text(pDX, IDC_EDIT3, newPosZFloat);

	DDX_Text(pDX, IDC_EDIT4, newRotXFloat);
	DDX_Text(pDX, IDC_EDIT5, newRotYFloat);
	DDX_Text(pDX, IDC_EDIT6, newRotZFloat);

	DDX_Text(pDX, IDC_EDIT7, newScaleXFloat);
	DDX_Text(pDX, IDC_EDIT8, newScaleYFloat);
	DDX_Text(pDX, IDC_EDIT9, newScaleZFloat);
	//DDX_Text(pDX, IDC_EDIT11, texPathWindow);
}

void ModifyObjectDialogue::End()
{
	m_ToolSystem->IsSelectionAvailable(true);
	m_ToolSystem = nullptr;
	m_currentSelectionID -= 1;
	m_displayList = nullptr;

	DestroyWindow();
	return;
}

void ModifyObjectDialogue::OnSelectTexture()
{
	//https://www.programmerall.com/article/50391274688/

	CString strFile = _T("");
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Textures (*.dds)|*.dds|All Files (*.*)|*.*||"), NULL);
	
	if (dlgFile.DoModal())
	{
	    strFile = dlgFile.GetPathName();
	}

	//set the texture path for the new selected
	CT2A changedCString(strFile);
	std::string textureString(changedCString);


	//https://cplusplus.com/reference/string/string/find/
	int found = textureString.find("database");
	if (found != std::string::npos)
	{
		strcpy(changedCString, &textureString[found]);
		std::string textureString(changedCString);
		m_displayList->at(m_currentSelectionID).m_texturePath = textureString;
		m_ToolSystem->TellGameNewTextureChosen(textureString);
	}
		
}

//void ModifyObjectDialogue::OnChangeXPos()
//{
//	CString newPosX;
//	//float newPosXFloat;
//
//	pWnd = GetDlgItem(IDC_EDIT1);
//	pWnd->GetWindowText(newPosX);
//
//	//change to float
//	swscanf_s(newPosX, L"%f", &newPosXFloat);
//	//Set the new position.
//	m_displayList->at(m_currentSelectionID).m_position.x = newPosXFloat;
//
//	//m_ToolSystem->IsSelectionAvailable(true);
//}

BOOL ModifyObjectDialogue::OnInitDialog()
{
	return CDialogEx::OnInitDialog();
}

void ModifyObjectDialogue::PostNcDestroy()
{
	//m_ToolSystem->IsSelectionAvailable(true);
	CDialogEx::PostNcDestroy();
}

void ModifyObjectDialogue::OnBnClickedOk()
{
	//CString newPosX;
	//float newPosXFloat;

	//pWnd = GetDlgItem(IDC_EDIT1);
	//pWnd->GetWindowText(newPosX);

	////change to float
	//swscanf_s(newPosX, L"%f", &newPosXFloat);
	////Set the new position.
	//m_displayList->at(m_currentSelectionID).m_position.x = newPosXFloat;

	m_ToolSystem->IsSelectionAvailable(true);
	CDialogEx::OnOK();
}

void ModifyObjectDialogue::OnBnClickedCancel()
{
	m_ToolSystem->IsSelectionAvailable(true);
	CDialogEx::OnCancel();
}

void ModifyObjectDialogue::OnXPosChanged()
{
	CString newPosX;
	pWnd = GetDlgItem(IDC_EDIT1);
	pWnd->GetWindowText(newPosX);

	//change to float
	swscanf_s(newPosX, L"%f", &newPosXFloat);
	//Set the new position.
	m_displayList->at(m_currentSelectionID).m_position.x = newPosXFloat;
}

void ModifyObjectDialogue::OnYPosChanged()
{
	CString newPosY;
	pWnd = GetDlgItem(IDC_EDIT2);
	pWnd->GetWindowText(newPosY);

	//change to float
	swscanf_s(newPosY, L"%f", &newPosYFloat);
	//Set the new position.
	m_displayList->at(m_currentSelectionID).m_position.y = newPosYFloat;
}

void ModifyObjectDialogue::OnZPosChanged()
{
	CString newPosZ;
	pWnd = GetDlgItem(IDC_EDIT3);
	pWnd->GetWindowText(newPosZ);

	//change to float
	swscanf_s(newPosZ, L"%f", &newPosZFloat);
	//Set the new position.
	m_displayList->at(m_currentSelectionID).m_position.z = newPosZFloat;
}

void ModifyObjectDialogue::OnXRotChanged()
{
	CString newPosX;
	pWnd = GetDlgItem(IDC_EDIT4);
	pWnd->GetWindowText(newPosX);

	//change to float
	swscanf_s(newPosX, L"%f", &newRotXFloat);
	//Set the new position.
	m_displayList->at(m_currentSelectionID).m_orientation.x = newRotXFloat;
}

void ModifyObjectDialogue::OnYRotChanged()
{
	CString newPosY;
	pWnd = GetDlgItem(IDC_EDIT5);
	pWnd->GetWindowText(newPosY);

	//change to float
	swscanf_s(newPosY, L"%f", &newRotYFloat);
	//Set the new position.
	m_displayList->at(m_currentSelectionID).m_orientation.y = newRotYFloat;
}

void ModifyObjectDialogue::OnZRotChanged()
{
	CString newPosZ;
	pWnd = GetDlgItem(IDC_EDIT6);
	pWnd->GetWindowText(newPosZ);

	//change to float
	swscanf_s(newPosZ, L"%f", &newRotZFloat);
	//Set the new position.
	m_displayList->at(m_currentSelectionID).m_orientation.z = newRotZFloat;
}

void ModifyObjectDialogue::OnXScaleChanged()
{
	CString newPosX;
	pWnd = GetDlgItem(IDC_EDIT7);
	pWnd->GetWindowText(newPosX);

	//change to float
	swscanf_s(newPosX, L"%f", &newScaleXFloat);
	//Set the new position.
	m_displayList->at(m_currentSelectionID).m_scale.x = newScaleXFloat;
}

void ModifyObjectDialogue::OnYScaleChanged()
{
	CString newPosY;
	pWnd = GetDlgItem(IDC_EDIT8);
	pWnd->GetWindowText(newPosY);

	//change to float
	swscanf_s(newPosY, L"%f", &newScaleYFloat);
	//Set the new position.
	m_displayList->at(m_currentSelectionID).m_scale.y = newScaleYFloat;
}

void ModifyObjectDialogue::OnZScaleChanged()
{
	CString newPosZ;
	pWnd = GetDlgItem(IDC_EDIT9);
	pWnd->GetWindowText(newPosZ);

	//change to float
	swscanf_s(newPosZ, L"%f", &newScaleZFloat);
	//Set the new position.
	m_displayList->at(m_currentSelectionID).m_scale.z = newScaleZFloat;
}

