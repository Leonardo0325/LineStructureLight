
#include "pch.h"
#include "framework.h"
#include "lsl_application.h"
#include "lsl_applicationdlg.h"
#include "afxdialogex.h"

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
// CApplicationDlg 对话框
CApplicationDlg::CApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO1, m_ctrlDeviceCombo);
	//DDX_Control(pDX, IDC_EDIT2, EDIT);
	//DDX_Control(pDX, IDC_EDIT3, m_edtEdit);
	//显示参数信息
	DDX_Text(pDX, IDC_EXPOSURE_EDIT, m_dExposureEdit);
	DDX_Text(pDX, IDC_GAIN_EDIT, m_dGainEdit);
	DDX_Text(pDX, IDC_FRAME_RATE_EDIT, m_dFrameRateEdit);
	//DDX_Text(pDX, IDC_EDIT5, m_mEdit1);
	DDX_Control(pDX, IDC_EDIT5, m_edtEdit2);
	DDX_Control(pDX, IDC_LIGHTPICTURE_STATIC, m_psPicture);
}
BEGIN_MESSAGE_MAP(CApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CApplicationDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CApplicationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_OPEN_BUTTON,&CApplicationDlg::OnBnClickedOpenButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CApplicationDlg::OnBnClickedButton2)
	ON_STN_CLICKED(IDC_DISPLAY_STATIC, &CApplicationDlg::OnStnClickedDisplayStatic)
	ON_BN_CLICKED(IDC_STOP_GRABBING_BUTTON, &CApplicationDlg::OnBnClickedStopGrabbingButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CApplicationDlg::OnBnClickedCloseButton)
	ON_BN_CLICKED(IDC_SAVE_MULTIPLE_STATIC, &CApplicationDlg::OnBnClickedSaveMultipleStatic)
	ON_BN_CLICKED(IDC_SAVE_SINGLE_BUTTON, &CApplicationDlg::OnBnClickedSaveSingleButton)
	ON_BN_CLICKED(IDC_CALIB_START, &CApplicationDlg::OnBnClickedCalibStart)
	//ON_EN_CHANGE(IDC_EDIT2, &CApplicationDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT5, &CApplicationDlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTON5, &CApplicationDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_GET_PARAMETER_BUTTON, &CApplicationDlg::OnBnClickedGetParameterButton)
	ON_BN_CLICKED(IDC_SET_PARAMETER_BUTTON, &CApplicationDlg::OnBnClickedSetParameterButton)
	ON_BN_CLICKED(IDC_CALIB_LIGHT, &CApplicationDlg::OnBnClickedCalibLight)
	ON_BN_CLICKED(IDC_LIGHT_SAVESINGLE, &CApplicationDlg::OnBnClickedLightSavesingle)
	ON_BN_CLICKED(IDC_SAVESINGLE_RADIO, &CApplicationDlg::OnBnClickedSavesingleRadio)
	ON_BN_CLICKED(IDC_LIGHT_SAVESTART, &CApplicationDlg::OnBnClickedLightSavestart)
	ON_BN_CLICKED(IDC_SAVEMULTIPLE_RADIO, &CApplicationDlg::OnBnClickedSavemultipleRadio)
	ON_BN_CLICKED(IDC_PICTURE_OPEN, &CApplicationDlg::OnBnClickedPictureOpen)
	ON_STN_CLICKED(IDC_LIGHTPICTURE_STATIC, &CApplicationDlg::OnStnClickedLightpictureStatic)
	ON_BN_CLICKED(IDC_OPENFILE, &CApplicationDlg::OnBnClickedOpenfile)
	ON_STN_CLICKED(IDC_PDCVIEW_STATIC, &CApplicationDlg::OnStnClickedPdcviewStatic)
	ON_BN_CLICKED(IDC_OUTLINE_BUTTON, &CApplicationDlg::OnBnClickedOutlineButton)
	ON_BN_CLICKED(IDC_ROI_BUTTON, &CApplicationDlg::OnBnClickedRoiButton)
	ON_BN_CLICKED(IDC_GETROI, &CApplicationDlg::OnBnClickedGetroi)
	ON_BN_CLICKED(IDC_MEANFILTER, &CApplicationDlg::OnBnClickedMeanfilter)
	ON_BN_CLICKED(IDC_OTSUCUT, &CApplicationDlg::OnBnClickedOtsucut)
	ON_BN_CLICKED(IDC_Binarization, &CApplicationDlg::OnBnClickedBinarization)
	ON_BN_CLICKED(IDC_morphology, &CApplicationDlg::OnBnClickedmorphology)
	ON_BN_CLICKED(IDC_LIGHTCUT, &CApplicationDlg::OnBnClickedLightcut)
	ON_BN_CLICKED(IDC_IMAGESHOW, &CApplicationDlg::OnBnClickedImageshow)
	ON_BN_CLICKED(IDC_CHOOSEFILE, &CApplicationDlg::OnBnClickedChoosefile)
	ON_EN_CHANGE(IDC_FILENAME_EDIT, &CApplicationDlg::OnEnChangeFilenameEdit)
	ON_BN_CLICKED(IDC_DOUBLEFILTER, &CApplicationDlg::OnBnClickedDoublefilter)
	//ON_BN_CLICKED(IDC_PASSTHROUGHFILTER, &CApplicationDlg::OnBnClickedPassthroughfilter)
	ON_BN_CLICKED(IDC_STATISTICAL, &CApplicationDlg::OnBnClickedStatistical)
	ON_BN_CLICKED(IDC_RETURNPOINT, &CApplicationDlg::OnBnClickedReturnpoint)
	ON_BN_CLICKED(IDC_XRENDER, &CApplicationDlg::OnBnClickedXrender)
	ON_BN_CLICKED(IDC_YRENDER, &CApplicationDlg::OnBnClickedYrender)
	ON_BN_CLICKED(IDC_ZRENDER, &CApplicationDlg::OnBnClickedZrender)
	ON_BN_CLICKED(IDC_BUTTON16, &CApplicationDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_RADIUSFILTER, &CApplicationDlg::OnBnClickedRadiusfilter)
	ON_BN_CLICKED(IDC_BUTTON15, &CApplicationDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_UNIFORMSAMPLING, &CApplicationDlg::OnBnClickedUniformsampling)
	ON_BN_CLICKED(IDC_RANDOMSAMPLING, &CApplicationDlg::OnBnClickedRandomsampling)
	ON_BN_CLICKED(IDC_NORMALSAMPLING, &CApplicationDlg::OnBnClickedNormalsampling)
	ON_BN_CLICKED(IDC_VOXELFILTER, &CApplicationDlg::OnBnClickedVoxelfilter)
	//ON_BN_CLICKED(IDC_SAVEFILE, &CApplicationDlg::OnBnClickedSavefile)
	ON_BN_CLICKED(IDC_SAVEFILE, &CApplicationDlg::OnBnClickedSavefile)
	ON_STN_CLICKED(IDC_BESTOTSU_STATIC, &CApplicationDlg::OnStnClickedBestotsuStatic)
	ON_BN_CLICKED(IDC_STOPSHOW, &CApplicationDlg::OnBnClickedStopshow)
	ON_BN_CLICKED(IDC_RETURNPCL, &CApplicationDlg::OnBnClickedReturnpcl)
	ON_BN_CLICKED(IDC_LIGHT_SAVESTOP, &CApplicationDlg::OnBnClickedLightSavestop)
	ON_BN_CLICKED(IDC_SAVEFILE2, &CApplicationDlg::OnBnClickedSavefile2)
	ON_BN_CLICKED(IDC_BUTTON6, &CApplicationDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON12, &CApplicationDlg::OnBnClickedButton12)
END_MESSAGE_MAP()


BOOL CApplicationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString sAboutMenu;
		bNameValid = sAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!sAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, sAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_spViewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
	//m_cloud=new pcl::PointCloud<pcl::PointXYZ>;
	m_spCloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
	m_spViewer->setBackgroundColor(0, 0, 0);  //背景颜色
	m_spViewer->addCoordinateSystem(1.0f);

	// TODO: afFiledraw code for native data here

	CStatic* pclStatic = new CStatic();
	LPRECT rect = new CRect;
	pclStatic = (CStatic*)GetDlgItem(IDC_PDCVIEW_STATIC);
	m_rwndRenWin = m_spViewer->getRenderWindow();
	m_rwndRenWin->SetParentId(pclStatic->m_hWnd);
	m_rwndinIren->GlobalWarningDisplayOff();
	m_rwndinIren = vtkRenderWindowInteractor::New();


	pclStatic->GetWindowRect(rect);
	m_rwndRenWin->SetSize(rect->right - rect->left, rect->bottom - rect->top);
	m_rwndRenWin->SetPosition(0, 0);
	m_rwndinIren->SetRenderWindow(m_rwndRenWin);
	m_spViewer->createInteractor();
	m_rwndinIren->Render();
	m_rwndRenWin->Render();

	DisplayWindowInitial();             // ch:显示框初始化 | en:Display Window Initialization

	InitializeCriticalSection(&m_hSaveImageMux);



	return TRUE;  // return TRUE  unless you set the focus to a control
}
// CApplicationDlg 消息处理程序
// // ch:最开始时的窗口初始化 | en:Initial window initialization
void CApplicationDlg::DisplayWindowInitial()
{
	CWnd* pWnd = GetDlgItem(IDC_DISPLAY_STATIC);
	if (pWnd)
	{
		m_hwndDisplay = pWnd->GetSafeHwnd();
		if (m_hwndDisplay)
		{
			EnableControls(FALSE);
		}
		
	}

}
//  按钮使能
void CApplicationDlg::EnableControls(BOOL bIsCameraReady)
{
	GetDlgItem(IDC_OPEN_BUTTON)->EnableWindow(m_bOpenDevice ? FALSE : (bIsCameraReady ? TRUE : FALSE));
	//GetDlgItem(IDC_CLOSE_BUTTON)->EnableWindow((m_bOpenDevice && bIsCameraReady) ? TRUE : FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow((m_bStartGrabbing && bIsCameraReady) ? FALSE : (m_bOpenDevice ? TRUE : FALSE));
	GetDlgItem(IDC_EXPOSURE_EDIT)->EnableWindow(m_bOpenDevice ? TRUE : FALSE);
	GetDlgItem(IDC_GAIN_EDIT)->EnableWindow(m_bOpenDevice ? TRUE : FALSE);
	GetDlgItem(IDC_FRAME_RATE_EDIT)->EnableWindow(m_bOpenDevice ? TRUE : FALSE);
	GetDlgItem(IDC_GET_PARAMETER_BUTTON)->EnableWindow(m_bOpenDevice ? TRUE : FALSE);
	GetDlgItem(IDC_SET_PARAMETER_BUTTON)->EnableWindow(m_bOpenDevice ? TRUE : FALSE);
	GetDlgItem(IDC_LIGHT_SAVESINGLE)->EnableWindow(m_bLightSaveSingle ? TRUE : FALSE);
	GetDlgItem(IDC_LIGHT_SAVESTART)->EnableWindow(m_bLightSaveMultiple ? TRUE : FALSE);
	GetDlgItem(IDC_LIGHT_SAVESTOP)->EnableWindow(m_bLightSaveMultiple ? TRUE : FALSE);

}
// ch:取流线程 | en:Grabbing thread
unsigned int __stdcall GrabThread(void* pUser)
{
	if (pUser)
	{
		CApplicationDlg* pCam = (CApplicationDlg*)pUser;

		pCam->GrabThreadProcess();

		return 0;
	}

	return -1;
}
//按帧保存图片
unsigned int __stdcall GrabThreadSave1(void* pUser)
{
	if (pUser)
	{
		CApplicationDlg* pCam = (CApplicationDlg*)pUser;

		pCam->GrabThreadSave();

		return 0;
	}

	return -1;
}
void CApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int ncxIcon = GetSystemMetrics(SM_CXICON);
		int ncyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int nx = (rect.Width() - ncxIcon + 1) / 2;
		int ny = (rect.Height() - ncyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(nx, ny, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//显示错误信息
void CApplicationDlg::ShowErrorMsg(CString csMessage, int nErrorNum)
{
	CString pstrErrorMsg;
	if (nErrorNum == 0)
	{
		pstrErrorMsg.Format(_T("%s"), csMessage);
	}
	else
	{
		pstrErrorMsg.Format(_T("%s: Error = %x: "), csMessage, nErrorNum);
	}

	switch (nErrorNum)
	{
	case MV_E_HANDLE:           pstrErrorMsg += "Error or invalid handle ";                                         break;
	case MV_E_SUPPORT:          pstrErrorMsg += "Not supported function ";                                          break;
	case MV_E_BUFOVER:          pstrErrorMsg += "Cache is full ";                                                   break;
	case MV_E_CALLORDER:        pstrErrorMsg += "Function calling order error ";                                    break;
	case MV_E_PARAMETER:        pstrErrorMsg += "Incorrect parameter ";                                             break;
	case MV_E_RESOURCE:         pstrErrorMsg += "Applying resource failed ";                                        break;
	case MV_E_NODATA:           pstrErrorMsg += "No data ";                                                         break;
	case MV_E_PRECONDITION:     pstrErrorMsg += "Precondition error, or running environment changed ";              break;
	case MV_E_VERSION:          pstrErrorMsg += "Version mismatches ";                                              break;
	case MV_E_NOENOUGH_BUF:     pstrErrorMsg += "Insufficient memory ";                                             break;
	case MV_E_ABNORMAL_IMAGE:   pstrErrorMsg += "Abnormal image, maybe incomplete image because of lost packet ";   break;
	case MV_E_UNKNOW:           pstrErrorMsg += "Unknown error ";                                                   break;
	case MV_E_GC_GENERIC:       pstrErrorMsg += "General error ";                                                   break;
	case MV_E_GC_ACCESS:        pstrErrorMsg += "Node accessing condition error ";                                  break;
	case MV_E_ACCESS_DENIED:	pstrErrorMsg += "No permission ";                                                   break;
	case MV_E_BUSY:             pstrErrorMsg += "Device is busy, or network disconnected ";                         break;
	case MV_E_NETER:            pstrErrorMsg += "Network error ";                                                   break;
	}

	MessageBox(pstrErrorMsg, TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
}
void CApplicationDlg::OnCbnSelchangeCombo1()
{

	// TODO: 在此添加控件通知处理程序代码
}
//查找设备
void CApplicationDlg::OnBnClickedButton1()
{
	CString pstrMsg;  //Cstring 为MFC中处理字符串的类
	m_ctrlDeviceCombo.ResetContent();
	memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));  //将设备列表的地址都设置为0

	//枚举子网内所有设备
	int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);
	if (MV_OK != nRet)
	{
		return;
	}
	// ch:将值加入到信息列表框中并显示出来 | en:AfFile value to the information list box and display
	for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++)
	{
		MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
		if (NULL == pDeviceInfo)
		{
			continue;
		}

		wchar_t* pUserName = NULL;
		if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
		{
			int nIp1 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
			int nIp2 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
			int nIp3 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
			int nIp4 = (m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

			if (strcmp("", (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName)) != 0)
			{
				DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName), -1, NULL, 0);
				pUserName = new wchar_t[dwLenUserName];
				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName), -1, pUserName, dwLenUserName);
			}
			else
			{
				char achUserName[256] = { 0 };
				sprintf_s(achUserName, 256, "%s %s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chManufacturerName,
					pDeviceInfo->SpecialInfo.stGigEInfo.chModelName,
					pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
				DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(achUserName), -1, NULL, 0);
				pUserName = new wchar_t[dwLenUserName];
				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(achUserName), -1, pUserName, dwLenUserName);
			}
			pstrMsg.Format(_T("[%d]GigE:    %s  (%d.%d.%d.%d)"), i, pUserName, nIp1, nIp2, nIp3, nIp4);
		}
		else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE)
		{
			if (strcmp("", (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName) != 0)
			{
				DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName), -1, NULL, 0);
				pUserName = new wchar_t[dwLenUserName];
				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName), -1, pUserName, dwLenUserName);
			}
			else
			{
				char achUserName[256] = { 0 };
				sprintf_s(achUserName, 256, "%s %s (%s)", pDeviceInfo->SpecialInfo.stUsb3VInfo.chManufacturerName,
					pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName,
					pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
				DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(achUserName), -1, NULL, 0);
				pUserName = new wchar_t[dwLenUserName];
				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(achUserName), -1, pUserName, dwLenUserName);
			}
			pstrMsg.Format(_T("[%d]UsbV3:  %s"), i, pUserName);
		}
		else
		{
			ShowErrorMsg(TEXT("Unknown device enumerated"), 0);
		}
		m_ctrlDeviceCombo.AddString(pstrMsg);

		if (pUserName)
		{
			delete[] pUserName;
			pUserName = NULL;
		}
	}

	if (0 == m_stDevList.nDeviceNum)
	{
		ShowErrorMsg(TEXT("No device"), 0);
		return;
	}
	m_ctrlDeviceCombo.SetCurSel(0);
	EnableControls(TRUE);
}
//打开设备
void CApplicationDlg::OnBnClickedOpenButton()
{
	if (TRUE == m_bOpenDevice || NULL !=m_pcMvCamera)
	{
		return;
	}
	UpdateData(TRUE);

	int nIndex = m_nDeviceCombo;
	if ((nIndex < 0) | (nIndex >= MV_MAX_DEVICE_NUM))
	{
		ShowErrorMsg(TEXT("Please select device"), 0);
		return;
	}

	// ch:由设备信息创建设备实例 | en:Device instance created by device information
	if (NULL == m_stDevList.pDeviceInfo[nIndex])
	{
		ShowErrorMsg(TEXT("Device does not exist"), 0);
		return;
	}

	m_pcMvCamera = new CMvCamera;
	if (NULL ==m_pcMvCamera)
	{
		return;
	}

	int nRet =m_pcMvCamera->MC_Open(m_stDevList.pDeviceInfo[nIndex]);
	if (MV_OK != nRet)
	{
		delete m_pcMvCamera;
		m_pcMvCamera = NULL;
		ShowErrorMsg(TEXT("Open Fail"), nRet);
		return;
	}

	// ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
	if (m_stDevList.pDeviceInfo[nIndex]->nTLayerType == MV_GIGE_DEVICE)
	{
		unsigned int nPacketSize = 0;
		nRet =m_pcMvCamera->MC_GetOptimalPacketSize(&nPacketSize);
		if (nRet == MV_OK)
		{
			nRet =m_pcMvCamera->MC_SetIntValue("GevSCPSPacketSize", nPacketSize);
			if (nRet != MV_OK)
			{
				ShowErrorMsg(TEXT("Warning: Set Packet Size fail!"), nRet);
			}
		}
		else
		{
			ShowErrorMsg(TEXT("Warning: Get Packet Size fail!"), nRet);
		}
	}

	m_bOpenDevice = TRUE;
	EnableControls(TRUE);
	OnBnClickedGetParameterButton(); // ch:获取参数 | en:Get Parameter
}
//开始采集
void CApplicationDlg::OnBnClickedButton2()
{
	//system("del D:\\pictureSave\\calibSave\\*.bmp");
	if (FALSE == m_bOpenDevice || TRUE == m_bStartGrabbing || NULL ==m_pcMvCamera)
	{
		return;
	}

	memset(&m_stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
	m_bThreadState = TRUE;
	unsigned int nThreadID = 0;
	m_phGrabThread = (void*)_beginthreadex(NULL, 0, GrabThread, this, 0, &nThreadID);
	if (NULL == m_phGrabThread)
	{
		m_bThreadState = FALSE;
		ShowErrorMsg(TEXT("Create thread fail"), 0);
		return;
	}

	int nRet =m_pcMvCamera->MC_StartGrabbing();
	if (MV_OK != nRet)
	{
		m_bThreadState = FALSE;
		ShowErrorMsg(TEXT("Start grabbing fail"), nRet);
		return;
	}
	m_bStartGrabbing = TRUE;
	EnableControls(TRUE);
}
// ch:获取触发模式 | en:Get Trigger Mode
int  CApplicationDlg::GetTriggerMode()
{
	MVCC_ENUMVALUE stEnumValue = { 0 };

	int nRet =m_pcMvCamera->MC_GetEnumValue("TriggerMode", &stEnumValue);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	m_nTriggerMode = stEnumValue.nCurValue;

	return MV_OK;
}// ch:获取触发源 | en:Get Trigger Source
int CApplicationDlg::GetTriggerSource()
{
	MVCC_ENUMVALUE stEnumValue = { 0 };

	int nRet =m_pcMvCamera->MC_GetEnumValue("TriggerSource", &stEnumValue);
	if (MV_OK != nRet)
	{
		return nRet;
	}



	return MV_OK;
}
// ch:获取曝光时间 | en:Get Exposure Time
int CApplicationDlg::GetExposureTime()
{
	MVCC_FLOATVALUE stFloatValue = { 0 };

	int nRet =m_pcMvCamera->MC_GetFloatValue("ExposureTime", &stFloatValue);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	m_dExposureEdit = stFloatValue.fCurValue;

	return MV_OK;
}
// ch:设置曝光时间 | en:Set Exposure Time
int CApplicationDlg::SetExposureTime()
{
	// ch:调节这两个曝光模式，才能让曝光时间生效
	// en:Adjust these two exposure mode to allow exposure time effective
	int nRet =m_pcMvCamera->MC_SetEnumValue("ExposureMode", MV_EXPOSURE_MODE_TIMED);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	m_pcMvCamera->MC_SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);

	return m_pcMvCamera->MC_SetFloatValue("ExposureTime", (float)m_dExposureEdit);
}
// ch:获取增益 | en:Get Gain
int CApplicationDlg::GetGain()
{
	MVCC_FLOATVALUE stFloatValue = { 0 };

	int nRet =m_pcMvCamera->MC_GetFloatValue("Gain", &stFloatValue);
	if (MV_OK != nRet)
	{
		return nRet;
	}
	m_dGainEdit = stFloatValue.fCurValue;

	return MV_OK;
}
// ch:设置增益 | en:Set Gain
int CApplicationDlg::SetGain()
{
	// ch:设置增益前先把自动增益关闭，失败无需返回
	//en:Set Gain after Auto Gain is turned off, this failure does not need to return
	m_pcMvCamera->MC_SetEnumValue("GainAuto", 0);

	return m_pcMvCamera->MC_SetFloatValue("Gain", (float)m_dGainEdit);
}
// ch:获取帧率 | en:Get Frame Rate
int CApplicationDlg::GetFrameRate()
{
	MVCC_FLOATVALUE stFloatValue = { 0 };

	int nRet =m_pcMvCamera->MC_GetFloatValue("ResultingFrameRate", &stFloatValue);
	if (MV_OK != nRet)
	{
		return nRet;
	}
	m_dFrameRateEdit = stFloatValue.fCurValue;

	return MV_OK;
}
// ch:设置帧率 | en:Set Frame Rate
int CApplicationDlg::SetFrameRate()
{
	int nRet =m_pcMvCamera->MC_SetBoolValue("AcquisitionFrameRateEnable", true);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	return m_pcMvCamera->MC_SetFloatValue("AcquisitionFrameRate", (float)m_dFrameRateEdit);
}
//   获取参数
void CApplicationDlg::OnBnClickedGetParameterButton()
{
	int nRet = GetTriggerMode();
	if (nRet != MV_OK)
	{
		ShowErrorMsg(TEXT("Get Trigger Mode Fail"), nRet);
	}

	nRet = GetExposureTime();
	if (nRet != MV_OK)
	{
		ShowErrorMsg(TEXT("曝光时间获取失败"), nRet);
	}

	nRet = GetGain();
	if (nRet != MV_OK)
	{
		ShowErrorMsg(TEXT("增益获取失败"), nRet);
	}

	nRet = GetFrameRate();
	if (nRet != MV_OK)
	{
		ShowErrorMsg(TEXT("帧率获取失败"), nRet);
	}

	nRet = GetTriggerSource();
	if (nRet != MV_OK)
	{
		ShowErrorMsg(TEXT("触发源获取失败"), nRet);
	}

	UpdateData(FALSE);
}
//参数设置
void CApplicationDlg::OnBnClickedSetParameterButton()
{
	UpdateData(TRUE);

	bool bIsSetSucceed = true;
	int nRet = SetExposureTime();
	if (nRet != MV_OK)
	{
		bIsSetSucceed = false;
		ShowErrorMsg(TEXT("曝光时间设置失败"), nRet);
	}
	nRet = SetGain();
	if (nRet != MV_OK)
	{
		bIsSetSucceed = false;
		ShowErrorMsg(TEXT("增益设置失败"), nRet);
	}
	nRet = SetFrameRate();
	if (nRet != MV_OK)
	{
		bIsSetSucceed = false;
		ShowErrorMsg(TEXT("帧率设置失败"), nRet);
	}

	if (true == bIsSetSucceed)
	{
		ShowErrorMsg(TEXT("参数设置成功！"), nRet);
	}
}
//取流线程
int CApplicationDlg::GrabThreadProcess()
{
	int nIndex = 1;
	MV_FRAME_OUT stImageInfo = { 0 };
	MV_DISPLAY_FRAME_INFO stDisplayInfo = { 0 };
	int nRet = MV_OK;

	while (m_bThreadState)
	{
		nRet =m_pcMvCamera->MC_GetImageBuffer(&stImageInfo, 1000);
		if (nRet == MV_OK)
		{
			//用于保存图片
			EnterCriticalSection(&m_hSaveImageMux);
			if (NULL == m_pchSaveImageBuf || stImageInfo.stFrameInfo.nFrameLen > m_chSaveImageBufSize)
			{
				if (m_pchSaveImageBuf)
				{
					free(m_pchSaveImageBuf);
					m_pchSaveImageBuf = NULL;
				}

				m_pchSaveImageBuf = (unsigned char*)malloc(sizeof(unsigned char) * stImageInfo.stFrameInfo.nFrameLen);

				if (m_pchSaveImageBuf == NULL)
				{
					LeaveCriticalSection(&m_hSaveImageMux);
					return 0;
				}
				m_chSaveImageBufSize = stImageInfo.stFrameInfo.nFrameLen;
			}
			memcpy(m_pchSaveImageBuf, stImageInfo.pBufAddr, stImageInfo.stFrameInfo.nFrameLen);
			memcpy(&m_stImageInfo, &(stImageInfo.stFrameInfo), sizeof(MV_FRAME_OUT_INFO_EX));



			LeaveCriticalSection(&m_hSaveImageMux);
			//index++;
			//自定义格式不支持显示
			if (RemoveCustomPixelFormats(stImageInfo.stFrameInfo.enPixelType))
			{
				m_pcMvCamera->MC_FreeImageBuffer(&stImageInfo);
				continue;
			}
			stDisplayInfo.hWnd = m_hwndDisplay;
			stDisplayInfo.pData = stImageInfo.pBufAddr;
			stDisplayInfo.nDataLen = stImageInfo.stFrameInfo.nFrameLen;
			stDisplayInfo.nWidth = stImageInfo.stFrameInfo.nWidth;
			stDisplayInfo.nHeight = stImageInfo.stFrameInfo.nHeight;
			stDisplayInfo.enPixelType = stImageInfo.stFrameInfo.enPixelType;
			m_pcMvCamera->MC_DisplayOneFrame(&stDisplayInfo);
			m_pcMvCamera->MC_FreeImageBuffer(&stImageInfo);
		}
		else
		{
			if (MV_TRIGGER_MODE_ON == m_nTriggerMode)
			{
				Sleep(5);
			}
		}
	}
	

	return MV_OK;
}
int CApplicationDlg::GrabThreadSave() {
		int nIndex = 1;
		MV_FRAME_OUT stImageInfo = { 0 };
		MV_DISPLAY_FRAME_INFO stDisplayInfo = { 0 };
		int nRet = MV_OK;

		while (m_bThreadState)
		{
			nRet = m_pcMvCamera->MC_GetImageBuffer(&stImageInfo, 1000);
			if (nRet == MV_OK)
			{
				//用于保存图片
				EnterCriticalSection(&m_hSaveImageMux);
				if (NULL == m_pchSaveImageBuf || stImageInfo.stFrameInfo.nFrameLen > m_chSaveImageBufSize)
				{
					if (m_pchSaveImageBuf)
					{
						free(m_pchSaveImageBuf);
						m_pchSaveImageBuf = NULL;
					}

					m_pchSaveImageBuf = (unsigned char*)malloc(sizeof(unsigned char) * stImageInfo.stFrameInfo.nFrameLen);

					if (m_pchSaveImageBuf == NULL)
					{
						LeaveCriticalSection(&m_hSaveImageMux);
						return 0;
					}
					m_chSaveImageBufSize = stImageInfo.stFrameInfo.nFrameLen;
				}
				memcpy(m_pchSaveImageBuf, stImageInfo.pBufAddr, stImageInfo.stFrameInfo.nFrameLen);
				memcpy(&m_stImageInfo, &(stImageInfo.stFrameInfo), sizeof(MV_FRAME_OUT_INFO_EX));



				LeaveCriticalSection(&m_hSaveImageMux);
				//index++;
				//自定义格式不支持显示
				if (RemoveCustomPixelFormats(stImageInfo.stFrameInfo.enPixelType))
				{
					m_pcMvCamera->MC_FreeImageBuffer(&stImageInfo);
					continue;
				}
				stDisplayInfo.hWnd = m_hwndDisplay;
				stDisplayInfo.pData = stImageInfo.pBufAddr;
				stDisplayInfo.nDataLen = stImageInfo.stFrameInfo.nFrameLen;
				stDisplayInfo.nWidth = stImageInfo.stFrameInfo.nWidth;
				stDisplayInfo.nHeight = stImageInfo.stFrameInfo.nHeight;
				stDisplayInfo.enPixelType = stImageInfo.stFrameInfo.enPixelType;
				m_pcMvCamera->MC_DisplayOneFrame(&stDisplayInfo);
				m_pcMvCamera->MC_FreeImageBuffer(&stImageInfo);
			}
			else
			{
				if (MV_TRIGGER_MODE_ON == m_nTriggerMode)
				{
					Sleep(5);
				}
			}
			int nRet = SaveLightImage(MV_Image_Bmp);
		}


		return MV_OK;
	}

bool CApplicationDlg::RemoveCustomPixelFormats(enum MvGvspPixelType enPixelFormat)
{
	int nResult = enPixelFormat & MV_GVSP_PIX_CUSTOM;
	if (MV_GVSP_PIX_CUSTOM == nResult)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void CApplicationDlg::OnStnClickedDisplayStatic()
{
	// TODO: 在此添加控件通知处理程序代码
}
//停止采集
void CApplicationDlg::OnBnClickedStopGrabbingButton()
{
	if (FALSE == m_bOpenDevice || FALSE == m_bStartGrabbing || NULL ==m_pcMvCamera)
	{
		return;
	}

	m_bThreadState = FALSE;
	if (m_phGrabThread)
	{
		WaitForSingleObject(m_phGrabThread, INFINITE);
		CloseHandle(m_phGrabThread);
		m_phGrabThread = NULL;
	}

	int nRet =m_pcMvCamera->MC_StopGrabbing();
	if (MV_OK != nRet)
	{
		ShowErrorMsg(TEXT("Stop grabbing fail"), nRet);
		return;
	}
	m_bStartGrabbing = FALSE;
	EnableControls(TRUE);
}
// ch:关闭设备 | en:Close Device
int CApplicationDlg::CloseDevice()
{
	m_bThreadState = FALSE;
	if (m_phGrabThread)
	{
		WaitForSingleObject(m_phGrabThread, INFINITE);
		CloseHandle(m_phGrabThread);
		m_phGrabThread = NULL;
	}

	if (m_pcMvCamera)
	{
		m_pcMvCamera->MC_Close();
		delete m_pcMvCamera;
		m_pcMvCamera = NULL;
	}

	m_bStartGrabbing = FALSE;
	m_bOpenDevice = FALSE;

	if (m_pchSaveImageBuf)
	{
		free(m_pchSaveImageBuf);
		m_pchSaveImageBuf = NULL;
	}
	m_chSaveImageBufSize = 0;

	return MV_OK;
}
void CApplicationDlg::OnBnClickedCloseButton()
{
	CloseDevice();
	EnableControls(TRUE);
}
void CApplicationDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
void CApplicationDlg::OnBnClickedSaveMultipleStatic()
{
	// TODO: 在此添加控件通知处理程序代码
}
// ch:标定保存图片 | en:Save Image
int CApplicationDlg::SaveCalibImage(MV_SAVE_IAMGE_TYPE enSaveImageType)
{

	
		MV_SAVE_IMG_TO_FILE_PARAM stSaveFileParam;
		memset(&stSaveFileParam, 0, sizeof(MV_SAVE_IMG_TO_FILE_PARAM));

		EnterCriticalSection(&m_hSaveImageMux);
		if (m_pchSaveImageBuf == NULL || m_stImageInfo.enPixelType == 0)
		{
			LeaveCriticalSection(&m_hSaveImageMux);
			return MV_E_NODATA;
		}

		if (RemoveCustomPixelFormats(m_stImageInfo.enPixelType))
		{
			LeaveCriticalSection(&m_hSaveImageMux);
			return MV_E_SUPPORT;
		}
		
		stSaveFileParam.enImageType = enSaveImageType; // ch:需要保存的图像类型 | en:Image format to save
		stSaveFileParam.enPixelType = m_stImageInfo.enPixelType;  // ch:相机对应的像素格式 | en:Camera pixel type
		stSaveFileParam.nWidth = m_stImageInfo.nWidth;         // ch:相机对应的宽 | en:Width
		stSaveFileParam.nHeight = m_stImageInfo.nHeight;          // ch:相机对应的高 | en:Height
		stSaveFileParam.nDataLen = m_stImageInfo.nFrameLen;
		stSaveFileParam.pData = m_pchSaveImageBuf;
		stSaveFileParam.iMethodValue = 0;

		// ch:jpg图像质量范围为(50-99], png图像质量范围为[0-9] | en:jpg image nQuality range is (50-99], png image nQuality range is [0-9]
		if (MV_Image_Bmp == stSaveFileParam.enImageType)
		{
		
			sprintf_s(stSaveFileParam.pImagePath, 256, "D:\\pictureSave\\calibSave1\\Image_w%d_h%d_fn%03d.bmp" , stSaveFileParam.nWidth, stSaveFileParam.nHeight, m_stImageInfo.nFrameNum);
			
			
		}
		int nRet =m_pcMvCamera->MC_SaveImageToFile(&stSaveFileParam);
		LeaveCriticalSection(&m_hSaveImageMux);

		return nRet;
	
}
void CApplicationDlg::OnBnClickedSaveSingleButton()
{

	int nRet = SaveCalibImage(MV_Image_Bmp);
	
	if (MV_OK != nRet)
	{
		ShowErrorMsg(TEXT("图片保存失败"), nRet);
		return;
	}
	ShowErrorMsg(TEXT("图片保存成功"), nRet);
}
//内外参标定
void CApplicationDlg::OnBnClickedCalibStart()
{
	vector<vector<Point3f>>vImgPoints3f;
	vector<vector<Point2f>>vImagePoints2f;
	Mat mSrcImg;
	m_pcCalib->CA_CalPict(vImgPoints3f, vImagePoints2f,mSrcImg);
	vector<Mat>vRMatrix;//旋转矩阵
	CString pstr;
	//相机标定函数，根据拍的标定图片，求相机内参与外参
	float rms = calibrateCamera(vImgPoints3f, vImagePoints2f, cv::Size(mSrcImg.cols, mSrcImg.rows), m_mCameraMatrix, m_mDistCoeff, m_vRvecsMat, m_vTvecsMat, CALIB_FIX_K3);
	vector<string>vResult;
	string sPath = "D:\\pictureSave\\calibSave1\\*.bmp";
	glob(sPath, vResult, false); //从文件夹中读取图片路径名
	for (int i = 0; i < vResult.size(); i++)
	{
		Mat mR;
		Rodrigues(m_vRvecsMat[i], mR);
		vRMatrix.push_back(mR);
	}
	//objRealPoint:世界坐标系的点（3维），imagePoint：对应的图像的点， cv::Size：图像的大小，m_mCameraMatrix：内参矩阵，m_mDistCoeff：畸变矩阵，m_vRvecsMat：旋转矩阵，m_vTvecsMat：平移矩阵。flags:标定所用的算法。（CALIB_FIX_K3）
	if (!(m_mCameraMatrix.empty())) {
		MessageBox(_T("内外参标定成功！"), NULL, MB_OK);

		m_pcCalib->CA_SaveTxt(m_vRvecsMat, m_vTvecsMat, vRMatrix, m_mCameraMatrix, m_mDistCoeff,pstr);
		GetDlgItem(IDC_EDIT5)->SetWindowText(pstr);
		destroyAllWindows();
		return ;
	}	
}
//光平面标定
void CApplicationDlg::OnBnClickedCalibLight()
{
	CString pstr;
	m_pcCalib->CA_Point3d_3d(m_vRvecsMat, m_vPoints3d_19, m_vvPoints3d20to19, m_vTvecsMat, m_mCameraMatrix);

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1(new pcl::PointCloud<pcl::PointXYZ>);

	for (int i = 0; i < m_vPoints3d_19.size(); ++i)
	{
		pcl::PointXYZ data;
		data.x = m_vPoints3d_19[i].x;//矩阵的值进行初始化X的坐标值
		data.y = m_vPoints3d_19[i].y;//  Y的坐标值
		data.z = m_vPoints3d_19[i].z;//  Z的坐标值</span>
		cloud1->points.push_back(data);
	}
	for (int i = 0; i < m_vvPoints3d20to19.size(); ++i)
	{
		pcl::PointXYZ data;
		data.x = m_vvPoints3d20to19[i].x;//矩阵的值进行初始化   X的坐标值
		data.y = m_vvPoints3d20to19[i].y;//  Y的坐标值
		data.z = m_vvPoints3d20to19[i].z;//  Z的坐标值</span>
		cloud1->points.push_back(data);
	}
	cloud1->width = cloud1->points.size();
	cloud1->height = 1;
	cloud1->is_dense = false;
	cloud1->points.resize(cloud1->width * cloud1->height);
	
	//cvFitPlane(points_mat, line_plane);//调用方程 line_plane[2]=-0.23太小
									   //line_plane[2] = -0.5;
	m_pcCalib->CA_FittingPlane(cloud1, line_plane);
	if (sizeof(line_plane)/sizeof(line_plane[0]))
	{
		MessageBox(_T("光平面标定成功！"), NULL, MB_OK);
		wchar_t unicode = 0xFEFF; //添加这个文件头，记事本打开才能识别里面的汉字，不会乱码。
		CString strEnter = _T("\r\n");//换行
		ofstream fFile;//创建文件
		fFile.open("D:\\CalibTxt\\fFile.txt");
		fFile << "光平面方程：AX+BY+CZ+D=0" << endl;
		fFile << "A=" << line_plane[0] << endl;
		fFile << "B=" << line_plane[1] << endl;
		fFile << "C=" << line_plane[2] << endl;
		fFile << "D=" << line_plane[3] << endl;
		//fFile.Write(strEnter, wcslen(strEnter) * sizeof(wchar_t));	//换行
		fFile.close();
		CFileDialog FileDlg(TRUE);
		CFile f;
		f.Open("D:\\CalibTxt\\fFile.txt", CFile::modeReadWrite);
		f.Read(pstr.GetBufferSetLength(f.GetLength()), f.GetLength());
		//使用GetBufferSetLength，这样可保证不用将分配的内存全部填充（会出现乱码）
		//使用GetBuffer在最后一行会出现乱码
		f.Close();
		GetDlgItem(IDC_EDIT5)->SetWindowText(pstr);
	}

	
}
void CApplicationDlg::OnEnChangeEdit5()
{
	}
void CApplicationDlg::OnBnClickedButton5()
{
	CString pstr;
	m_mMoveStep = m_pcCalib->CA_Platfrom(m_mCameraMatrix, m_mDistCoeff, m_vRvecsMat, m_vTvecsMat);
	ofstream fFile;//创建文件
	fFile.open("D:\\CalibTxt\\fPlatform.txt");
	fFile << "移动位姿：" << m_mMoveStep << endl;
	fFile.close();
	CFileDialog FileDlg(TRUE);
	CFile f;
	f.Open("D:\\CalibTxt\\fPlatform.txt", CFile::modeReadWrite);
	f.Read(pstr.GetBufferSetLength(f.GetLength()), f.GetLength());
	f.Close();
	GetDlgItem(IDC_EDIT5)->SetWindowText(pstr);
	MessageBox(_T("移动平台标定成功！"), NULL, MB_OK);
}
// ch:光条保存图片 | en:Save Image
int CApplicationDlg::SaveLightImage(MV_SAVE_IAMGE_TYPE enSaveImageType)
{
	MV_SAVE_IMG_TO_FILE_PARAM stSaveFileParam;
	memset(&stSaveFileParam, 0, sizeof(MV_SAVE_IMG_TO_FILE_PARAM));
	EnterCriticalSection(&m_hSaveImageMux);
	if (m_pchSaveImageBuf == NULL || m_stImageInfo.enPixelType == 0)
	{
		LeaveCriticalSection(&m_hSaveImageMux);
		return MV_E_NODATA;
	}

	if (RemoveCustomPixelFormats(m_stImageInfo.enPixelType))
	{
		LeaveCriticalSection(&m_hSaveImageMux);
		return MV_E_SUPPORT;
	}

	stSaveFileParam.enImageType = enSaveImageType; // ch:需要保存的图像类型 | en:Image format to save
	stSaveFileParam.enPixelType = m_stImageInfo.enPixelType;  // ch:相机对应的像素格式 | en:Camera pixel type
	stSaveFileParam.nWidth = m_stImageInfo.nWidth;         // ch:相机对应的宽 | en:Width
	stSaveFileParam.nHeight = m_stImageInfo.nHeight;          // ch:相机对应的高 | en:Height
	stSaveFileParam.nDataLen = m_stImageInfo.nFrameLen;
	stSaveFileParam.pData = m_pchSaveImageBuf;
	stSaveFileParam.iMethodValue = 0;

	// ch:jpg图像质量范围为(50-99], png图像质量范围为[0-9] | en:jpg image nQuality range is (50-99], png image nQuality range is [0-9]
	if (MV_Image_Bmp == stSaveFileParam.enImageType)
	{

		sprintf_s(stSaveFileParam.pImagePath, 256, "D:\\pictureSave\\LightSave3\\Image_w%d_h%d_fn%03d.bmp", stSaveFileParam.nWidth, stSaveFileParam.nHeight, m_stImageInfo.nFrameNum);


	}
	int nRet =m_pcMvCamera->MC_SaveImageToFile(&stSaveFileParam);
	LeaveCriticalSection(&m_hSaveImageMux);

	return nRet;

}
void CApplicationDlg::OnBnClickedLightSavesingle()
{
	int nRet = SaveLightImage(MV_Image_Bmp);
	if (MV_OK != nRet)
	{
		ShowErrorMsg(TEXT("图片保存失败"), nRet);
		return;
	}
	ShowErrorMsg(TEXT("图片保存成功"), nRet);
}
void CApplicationDlg::OnBnClickedSavesingleRadio()
{
	GetDlgItem(IDC_LIGHT_SAVESINGLE)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIGHT_SAVESTART)->EnableWindow( FALSE);
	GetDlgItem(IDC_LIGHT_SAVESTOP)->EnableWindow( FALSE);
}
void CApplicationDlg::OnBnClickedSavemultipleRadio()
{
	GetDlgItem(IDC_LIGHT_SAVESINGLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIGHT_SAVESTART)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIGHT_SAVESTOP)->EnableWindow(TRUE);
}

void CApplicationDlg::OnBnClickedLightSavestart()
{
	//system("del D:\\pictureSave\\calibSave\\*.bmp");
	if (FALSE == m_bOpenDevice || TRUE == m_bStartGrabbing || NULL == m_pcMvCamera)
	{
		return;
	}

	memset(&m_stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
	m_bThreadState = TRUE;
	unsigned int nThreadID = 0;
	m_phGrabThread = (void*)_beginthreadex(NULL, 0, GrabThreadSave1, this, 0, &nThreadID);
	if (NULL == m_phGrabThread)
	{
		m_bThreadState = FALSE;
		ShowErrorMsg(TEXT("Create thread fail"), 0);
		return;
	}

	int nRet = m_pcMvCamera->MC_StartGrabbing();
	if (MV_OK != nRet)
	{
		m_bThreadState = FALSE;
		ShowErrorMsg(TEXT("Start grabbing fail"), nRet);
		return;
	}
	m_bStartGrabbing = TRUE;
	EnableControls(TRUE);
	GetDlgItem(IDC_LIGHT_SAVESTOP)->EnableWindow(TRUE);

}

//光条打开图片
void CApplicationDlg::OpenPic(CImage&imgLightImg)
{
	float fImgWid, fImgHigh, fRecWid, fRecHigh, k, t;//跟控件的宽和高以及图片宽和高有关的参数
	//显示图片
	CRect rect;//控件矩形对象
	CRect rect1;
	//获取control控件大小
	fImgWid = imgLightImg.GetWidth();
	fImgHigh = imgLightImg.GetHeight();//获取图片的宽 高
	k = fImgHigh / fImgWid;//获得图片的宽高比

	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_LIGHTPICTURE_STATIC);//获取控件句柄
	pWnd->GetClientRect(&rect);//获取Picture Control控件的客户区
	fRecWid = rect.Width();
	fRecHigh = rect.Height();//获得控件的宽高比
	t = fRecHigh / fRecWid;//获得控件的宽高比
	if (k >= t)
	{

		rect.right = floor(rect.bottom / k);
		rect.left = (fRecWid - rect.right) / 2;
		rect.right = floor(rect.bottom / k) + (fRecWid - rect.right) / 2;
	}
	else
	{
		rect.bottom = floor(k * rect.right);
		rect.top = (fRecHigh - rect.bottom) / 2;
		rect.bottom = floor(k * rect.right) + (fRecHigh - rect.bottom) / 2;
	}
	//相关的计算为了让图片在绘图区居中按比例显示，如果图片很宽但是不高，就上下留有空白区；如果图片很高而不宽就左右留有空白区，并且保持两边空白区一样大

	CDC* pDc = NULL;
	pDc = pWnd->GetDC();//获取picture control的DC
	int nModeOld = SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式

	GetDlgItem(IDC_LIGHTPICTURE_STATIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_LIGHTPICTURE_STATIC)->ShowWindow(TRUE);
	imgLightImg.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//显示函数
	SetStretchBltMode(pDc->m_hDC, nModeOld);
	ReleaseDC(pDc);//释放指针空间
}
void CApplicationDlg::OnBnClickedPictureOpen()
{
//打开图片
	CImage cLightImg; //光条图片
	CFileDialog FileDlg(TRUE, _T("png"), NULL, 0, _T("image Files(*.bmp; *.jpg;*.png)|*.JPG;*.PNG;*.BMP|All Files (*.*) |*.*|"), this);
	FileDlg.DoModal();
	m_pstrFilePath = FileDlg.GetPathName();		//文件路径
	m_pstrFileName = FileDlg.GetFileName();	//文件名
	m_sPicPath = FileDlg.GetPathName();
	if (m_pstrFilePath == _T(""))
	{
		return;
	}
	
	cLightImg.Load(m_pstrFilePath);
	OpenPic(cLightImg);


}
void CApplicationDlg::OnStnClickedLightpictureStatic()
{
	// TODO: 在此添加控件通知处理程序代码
}
CString sFilePath;  //定义一个打开文件的全局变量
//打开点云文件
void CApplicationDlg::OnBnClickedOpenfile()
{
	m_pcPointCloud->PC_OpenPointCloud(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
void CApplicationDlg::OnStnClickedPdcviewStatic()
{
	// TODO: 在此添加控件通知处理程序代码
}
//Mat转换为CImage
void CApplicationDlg::MatToCImage(Mat& mMatImg, CImage& cImage)
{
	if (0 == mMatImg.total())
	{
		return;
	}


	int nChannels = mMatImg.channels();
	if ((1 != nChannels) && (3 != nChannels))
	{
		return;
	}
	int nWidth = mMatImg.cols;
	int nHeight = mMatImg.rows;


	//重建cimage
	cImage.Destroy();
	cImage.Create(nWidth, nHeight, 8 * nChannels);


	//拷贝数据


	uchar* pucRow;									//指向数据区的行指针
	uchar* pucImage = (uchar*)cImage.GetBits();		//指向数据区的指针
	int nStep = cImage.GetPitch();					//每行的字节数,注意这个返回值有正有负


	if (1 == nChannels)								//对于单通道的图像需要初始化调色板
	{
		RGBQUAD* rgbquadColorTable;
		int nMaxColors = 256;
		rgbquadColorTable = new RGBQUAD[nMaxColors];
		cImage.GetColorTable(0, nMaxColors, rgbquadColorTable);
		for (int nColor = 0; nColor < nMaxColors; nColor++)
		{
			rgbquadColorTable[nColor].rgbBlue = (uchar)nColor;
			rgbquadColorTable[nColor].rgbGreen = (uchar)nColor;
			rgbquadColorTable[nColor].rgbRed = (uchar)nColor;
		}
		cImage.SetColorTable(0, nMaxColors, rgbquadColorTable);
		delete[]rgbquadColorTable;
	}


	for (int nRow = 0; nRow < nHeight; nRow++)
	{
		pucRow = (mMatImg.ptr<uchar>(nRow));
		for (int nCol = 0; nCol < nWidth; nCol++)
		{
			if (1 == nChannels)
			{
				*(pucImage + nRow * nStep + nCol) = pucRow[nCol];
			}
			else if (3 == nChannels)
			{
				for (int nCha = 0; nCha < 3; nCha++)
				{
					*(pucImage + nRow * nStep + nCol * 3 + nCha) = pucRow[nCol * 3 + nCha];
				}
			}
		}
	}
}
void CApplicationDlg::OnBnClickedOutlineButton()
{
	if (m_sPicPath.empty())
	{
		MessageBox(_T("请选择图片！"), NULL, MB_ICONERROR);
		return;
	}
	Mat mImgRect;
	Mat mDst = m_pcLightStripe->LS_OutLine(m_sPicPath,mImgRect);
	
	CImage Img1,Img2;
	MatToCImage(mImgRect, Img1);
	//MatToCImage(img44, Img2);
	OpenPic(Img1);
	//OpenPic(Img2);
}
//ROI提取
void CApplicationDlg::OnBnClickedRoiButton()
{
	if (m_sPicPath.empty())
	{
		MessageBox(_T("请选择图片！"), NULL, MB_ICONERROR);
		return;
	}
	m_mRoiPic = m_pcLightStripe->LS_RoiCut(m_sPicPath);
	m_mRoiPic.copyTo(m_mCopyRoi);
	CImage Img1;
	MatToCImage(m_mRoiPic, Img1);
	OpenPic(Img1);
}

void CApplicationDlg::OnBnClickedGetroi()
{
	if (m_mRoiPic.empty())
	{
		MessageBox(_T("请选择图片！"), NULL, MB_ICONERROR);
		return;
	}
	CImage Img1;
	MatToCImage(m_mRoiPic, Img1);
	OpenPic(Img1);
}
//中值滤波
void CApplicationDlg::OnBnClickedMeanfilter()
{
	if (m_mRoiPic.empty())
	{
		MessageBox(_T("请选择图片！"), NULL, MB_ICONERROR);
		return;
	}
	m_mMidPic =m_pcLightStripe->LS_MidBlur(m_mRoiPic);
	CImage Img1;
	MatToCImage(m_mMidPic, Img1);
	OpenPic(Img1);
}
//Otsu阈值
void CApplicationDlg::OnBnClickedOtsucut()
{
	if (m_mMidPic.empty())
	{
		MessageBox(_T("请选择图片！"), NULL, MB_ICONERROR);
		return;
	}
	Mat mDst;
	CString pstr;
	G_nThresh = m_pcLightStripe->LS_Otsu(m_mMidPic,mDst);
	m_pcLightStripe->LS_ThreshTxt(G_nThresh, pstr);
	GetDlgItem(IDC_OTSU_EDIT)->SetWindowText(pstr);

}
//二值化
void CApplicationDlg::OnBnClickedBinarization()
{

	if (m_mRoiPic.empty())
	{
		MessageBox(_T("请选择图片！"), NULL, MB_ICONERROR);
		return;
	}
	threshold(m_mRoiPic, m_mBinDst, G_nThresh, 255, THRESH_BINARY);
	CImage Img1;
	MatToCImage(m_mBinDst, Img1);
	OpenPic(Img1);
}
//形态学处理
void CApplicationDlg::OnBnClickedmorphology()
{
	if (m_mBinDst.empty())
	{
		MessageBox(_T("请选择图片！"), NULL, MB_ICONERROR);
		return ;
	}
	m_mMorDst = m_pcLightStripe->LS_Morphology(m_mBinDst);
	CImage Img1;
	MatToCImage(m_mMorDst, Img1);
	OpenPic(Img1);
}
//光条提取
void CApplicationDlg::OnBnClickedLightcut()
{
	Mat mDst;
	int nThresh = m_pcLightStripe->LS_Otsu(m_mMidPic, mDst);
	Mat mLightSrc = m_pcLightStripe->LS_LightStr(m_mMorDst, m_sPicPath, m_mCopyRoi, nThresh-20);
	CImage Img1;
	MatToCImage(mLightSrc, Img1);
	OpenPic(Img1);
}
//单条恢复点云
void CApplicationDlg::OnBnClickedReturnpoint()
{
	vector<Point3f> Points3d_all;
	Mat mSrcImg = imread(m_sPicPath, IMREAD_GRAYSCALE);
	threshold(mSrcImg, mSrcImg, 80, 255, THRESH_BINARY);
	int a = 0;
	for (size_t i = 0; i < mSrcImg.cols; i++)
	{
		int sum = 0; int num = 0;
		int sum1 = 0; int num1 = 0;
		for (size_t j = 0; j < mSrcImg.rows; j++)
		{
			if (mSrcImg.at<uchar>(j, i) == 255)
			{
				sum += j;
				num++;
				if (mSrcImg.at<uchar>(j + 1, i) - mSrcImg.at<uchar>(j, i) < 0)
				{
					a = j;
					break;
				}
			}
		}
		int b = a + 1;
		for (size_t j = b; j < mSrcImg.rows; j++)
		{
			if (mSrcImg.at<uchar>(j, i) == 255)
			{
				sum1 += j;
				num1++;
			}
		}
		if (num == 0)
			continue;
		Point2f Points = Point2f(i, sum / num);
		Point3f Points3d = m_pcCalib->CA_GetWorldPoints(Points, m_vRvecsMat[18], m_vTvecsMat[18], m_mCameraMatrix);
		//Points3d.z = (line_plane[3] - line_plane[0] * Points3d.x - line_plane[1] * Points3d.y) / line_plane[2];
		Points3d_all.push_back(Points3d);
		if (num1 == 0)
			continue;
		Point3f Points3d1 = m_pcCalib->CA_GetWorldPoints(Point2f(i, 1.0 * sum1 / num1), m_vRvecsMat[18], m_vTvecsMat[18], m_mCameraMatrix);
		Points3d1.z = (line_plane[3] - line_plane[0] * Points3d1.x - line_plane[1] * Points3d1.y) / line_plane[2];
		Points3d_all.push_back(Points3d1);
	}

	//显示
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>); // 创建点云（指针）
	(*cloud).points.resize(Points3d_all.size());
	for (size_t i = 0; i < Points3d_all.size(); i++)
	{
		(*cloud).points[i].x = Points3d_all[i].x;
		(*cloud).points[i].y = Points3d_all[i].y;
		(*cloud).points[i].z = Points3d_all[i].z;
	}
	pcl::io::savePLYFileASCII("D:\\pictureSave\\testPoint3d.ply", *cloud);
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer("ShowCloud"));
	viewer->setBackgroundColor(0, 0, 0);
	//viewer->addCoordinateSystem(1.0);
	//viewer->initCameraParameters();
	viewer->addPointCloud<pcl::PointXYZ>(cloud, "cloud_filtered");
	while(!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}


}
//打开光条文件夹
void CApplicationDlg::OnBnClickedChoosefile()
{
	m_sPathName = m_pcLightStripe->LS_OpenFile();
	SetDlgItemText(IDC_FILENAME_EDIT, m_sPathName); //Edit控件IDC_EDIT1
	
}
//给予点云指针
pcl::PointCloud<pcl::PointXYZ>::Ptr CloudFull(new pcl::PointCloud<pcl::PointXYZ>); // 创建点云（指针）
//读入文件夹中的图像，恢复点云
void CApplicationDlg::OnBnClickedImageshow()
{
	vector<Point3f> Points3d_all;
	vector<string> vResult;
	m_sPathName += "\\*.jpg";
	string sFilePath = CT2A(m_sPathName.GetBuffer());
	glob(sFilePath, vResult, false); //从文件夹中读取图片路径名
	for (size_t k = 0; k < vResult.size(); k++)     //读取扫描物体的所有结构光图片
	{
		//string path = "D:\\pictureSave\\lightSave\\light1\\connection_rod_" + to_string(k / 100) + to_string(k / 10 - (k / 100 * 10)) + to_string(k % 10) + ".png";
		Mat mSrcImg = imread(vResult[k]);
		//Mat mSrcImg = imread(m_sPicPath, IMREAD_GRAYSCALE);
		Mat mDst;
		Mat m_mMidPic = m_pcLightStripe->LS_MidBlur(mSrcImg);
		int a = 0;
		float D1 = 1.0f;
		//mSrcImg = m_pcLightStripe->ideal_high_pass_filter1(mSrcImg, D1);
		//imwrite("D:\\pictureSave\\lightSave\\high pass1.png", mSrcImg);
		//mSrcImg = imread("D:\\pictureSave\\lightSave\\high pass1.png");
		cvtColor(mSrcImg, mSrcImg, COLOR_BGR2GRAY);
		int nThresh = m_pcLightStripe->LS_Otsu(m_mMidPic, mDst);
		threshold(m_mMidPic, m_mMidPic, nThresh, 255, THRESH_BINARY);
		m_pcLightStripe->Clear_MicroConnected_Areas(m_mMidPic, m_mMidPic, 10);
		for (size_t i = 0; i < m_mMidPic.cols; i++)
		{
			int sum = 0; int num = 0;
			int sum1 = 0; int num1 = 0;
			for (size_t j = 0; j < m_mMidPic.rows; j++)
			{
				if (m_mMidPic.at<uchar>(j, i) == 255)
				{
					sum += j;
					num++;
					if (m_mMidPic.at<uchar>(j, i) == 255)
					{
						sum += j;
						num++;
						if (m_mMidPic.at<uchar>(j + 1, i) - m_mMidPic.at<uchar>(j, i) < 0)
						{
							a = j;
							break;
						}
					}
				}
			}
			int b = a + 1;
			for (size_t j = b; j < m_mMidPic.rows; j++)
			{
				if (m_mMidPic.at<uchar>(j, i) == 255)
				{
					sum1 += j;
					num1++;
				}
			}
			if (num == 0)
				continue;
			Point2f Points = Point2f(i, sum / num);
			Point3f Points3d = m_pcCalib->CA_GetWorldPoints(Points, m_vRvecsMat[18], m_vTvecsMat[18], m_mCameraMatrix);
			Points3d.z = (line_plane[3] - line_plane[0] * Points3d.x - line_plane[1] * Points3d.y) / line_plane[2];
			Points3d += Point3f((k) * m_mMoveStep.at<double>(0, 0), (k) * m_mMoveStep.at<double>(1, 0), (k) * m_mMoveStep.at<double>(2, 0));
			Points3d_all.push_back(Points3d);
			if (num1 == 0)
				continue;
			Point3f Points3d1 = m_pcCalib->CA_GetWorldPoints(Point2f(i, 1.0 * sum1 / num1), m_vRvecsMat[18], m_vTvecsMat[18], m_mCameraMatrix);
			Points3d1.z = (line_plane[3] - line_plane[0] * Points3d1.x - line_plane[1] * Points3d1.y) / line_plane[2];
			Points3d1 += Point3f((k)*m_mMoveStep.at<double>(0, 0), (k)*m_mMoveStep.at<double>(1, 0), (k)*m_mMoveStep.at<double>(2, 0));
			Points3d_all.push_back(Points3d1);
		}
		CImage cImg;
		MatToCImage(m_mMidPic, cImg);
		OpenPic(cImg);
		//imshow("photos", imageInput);//显示图片
		waitKey(20);//暂停0.5S
	}

	/*
	CFileFind finder;
	CStringList filelist;//文件列表
	unsigned long filenum = 0;
	BOOL bResult = finder.FindFile(m_sPathName);
	if (!bResult) {
		AfxMessageBox(_T("未找到图像文件！"));
		return;
	}
	int k = 0;
	while (bResult)
	{
		
		k++;
		bResult = finder.FindNextFile();
		//判断是否是目录或者是隐藏文件，又或者是".."和"."，如果是，进入下一轮循环
		if (finder.IsDirectory() || finder.IsDots() || finder.IsHidden())
			continue;
		else//如果是文件
		{
			CString str;
			//得到文件名
			str = finder.GetFileName();
			//得到文件后缀名
			int nLen = str.GetLength() - finder.GetFileTitle().GetLength();
			str = str.Right(nLen);
			//判断文件格式，如果是图像文件，将其完整的路径保存在列表中
			if (str == ".jpg" || str == ".png" || str == ".bmp" || str == ".gif" || str == ".tif") {
				filelist.AddTail(finder.GetFilePath());
				//AfxMessageBox(finder.GetFilePath());
				CString filePath = finder.GetFilePath();
				
		}
		
	}
	*/
	
	(*CloudFull).points.resize(Points3d_all.size());
	for (size_t i = 0; i < Points3d_all.size(); i++)
	{
		(*CloudFull).points[i].x = Points3d_all[i].x;
		(*CloudFull).points[i].y = Points3d_all[i].y;
		(*CloudFull).points[i].z = Points3d_all[i].z;
	}

	// 保存为pcd文件时，需要给定height和width
	//对于无序点云hight默认是1
	CloudFull->height = 1;
	//cloud_extract点云文件中push_back的点数为Points3d_all.size()
	CloudFull->width = Points3d_all.size();
	pcl::io::savePCDFileASCII("D:\\pictureSave\\testPoint4d.pcd", *CloudFull);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile("D:\\pictureSave\\egg.pcd", *cloud);          //载入点云

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, 255, 255, 255);	//设置点云颜色
	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud, single_color, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
	while (!m_spViewer->wasStopped())
	{
		m_spViewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	
	/*pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(CloudFull, 255, 255, 255);	//设置点云颜色
		//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(CloudFull, single_color, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
	while (!m_spViewer->wasStopped())
	{
		m_spViewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	*/




	/*
	finder.Close();
	filenum = filelist.GetCount();
	//m_photoNum = filenum;
	UpdateData(FALSE);
	*/

}
/*
void CApplicationDlg::PostNcDestroy()
{
	delete this; //  对象的自销毁


}
*/
//直通滤波
void CApplicationDlg::OnBnClickedDoublefilter()
{
	m_pcPointCloud->PC_PassThrough(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
void CApplicationDlg::OnCbnSelchangeFileCombo()
{
	// TODO: 在此添加控件通知处理程序代码
}
void CApplicationDlg::OnEnChangeFilenameEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
//统计滤波
void CApplicationDlg::OnBnClickedStatistical()
{
	m_pcPointCloud->PC_StatisticalFilter(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
//X轴渲染
void CApplicationDlg::OnBnClickedXrender()
{
	m_pcPointCloud->PC_XRender(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
//Y轴渲染
void CApplicationDlg::OnBnClickedYrender()
{
	m_pcPointCloud->PC_YRender(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
//Z轴渲染
void CApplicationDlg::OnBnClickedZrender()
{
	m_pcPointCloud->PC_ZRender(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
//高斯滤波
void CApplicationDlg::OnBnClickedButton16()
{
	m_pcPointCloud->PC_GaussianFilter(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
//半径滤波
void CApplicationDlg::OnBnClickedRadiusfilter()
{
	m_pcPointCloud->PC_RadiusFilter(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
//条件滤波
void CApplicationDlg::OnBnClickedButton15()
{
	m_pcPointCloud->PC_ConditionFilter(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
//均匀采样
void CApplicationDlg::OnBnClickedUniformsampling()
{
	m_pcPointCloud->PC_UniformSampling(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
//随机采样
void CApplicationDlg::OnBnClickedRandomsampling()
{
	m_pcPointCloud->PC_RandomSampling(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
//法线空间采样
void CApplicationDlg::OnBnClickedNormalsampling()
{
	m_pcPointCloud->PC_NormalSampling(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
//体素滤波
void CApplicationDlg::OnBnClickedVoxelfilter()
{
	m_pcPointCloud->PC_VoxelFilter(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}
//保存点云文件
void CApplicationDlg::OnBnClickedSavefile()
{
	//保存文件*.pcd *.ply *.obj
	CString sDefaultDir = _T("请选择路径"); //设置默认打开文件夹
	CString sFileFilter = _T("文件(*.pcd;*.ply;*.obj)|*.pcd;*.ply;*.obj|All File (*.*)|*.*||"); //设置文件过滤
	CFileDialog FileDlg(false, sDefaultDir, _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sFileFilter, NULL);
	CString sFileName;
	if (FileDlg.DoModal() != IDOK)
		sFileName = FileDlg.GetPathName();
	int pos = sFileName.ReverseFind('.');

	CString ext = sFileName.Right(sFileName.GetLength() - pos);//用来判断文件是pcd还是ply，这里直接默认为pcd
	pcl::io::savePCDFileASCII(sFileName.GetString(), *CloudFull);

	/*
	pcl::io::savePCDFileASCII("PointCloudSave\\testPoint3d22.pcd", *CloudFull);
	string sPcdPath = "PointCloudSave\\testPoint3d22.pcd";
	if (file_is_empty(sPcdPath))
	{
		MessageBox(_T("保存失败！"), NULL, MB_ICONERROR);
		return;
	}
	else
		MessageBox(_T("保存成功！"), NULL, MB_OK);
		*/
}


void CApplicationDlg::OnStnClickedBestotsuStatic()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CApplicationDlg::OnBnClickedStopshow()
{
	//初始化点云数据
	m_spViewer->removeAllPointClouds();
}


void CApplicationDlg::OnBnClickedReturnpcl()
{
	m_pcPointCloud->PC_ReturnPcl(m_spViewer, m_rwndinIren, m_rwndRenWin, sFilePath);
}


void CApplicationDlg::OnBnClickedLightSavestop()
{
	if (FALSE == m_bOpenDevice || FALSE == m_bStartGrabbing || NULL == m_pcMvCamera)
	{
		return;
	}

	m_bThreadState = FALSE;
	if (m_phGrabThread)
	{
		WaitForSingleObject(m_phGrabThread, INFINITE);
		CloseHandle(m_phGrabThread);
		m_phGrabThread = NULL;
	}

	int nRet = m_pcMvCamera->MC_StopGrabbing();
	if (MV_OK != nRet)
	{
		ShowErrorMsg(TEXT("Stop grabbing fail"), nRet);
		return;
	}
	m_bStartGrabbing = FALSE;
	EnableControls(TRUE);
}


void CApplicationDlg::OnBnClickedSavefile2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CApplicationDlg::OnBnClickedButton6()
{
	MessageBox(_T("保存图片成功！"), NULL, MB_OK);
}


void CApplicationDlg::OnBnClickedButton12()
{
	MessageBox(_T("保存图片成功！"), NULL, MB_OK);
}
