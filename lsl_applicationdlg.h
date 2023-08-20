
#include "lsl_calib.h"
#include"resource.h"
#pragma once


// APPLICATION_DLm_C 对话框
class CApplicationDlg : public CDialogEx
{
// 构造
public:
	CApplicationDlg(CWnd* pParent = nullptr);	// 标准构造函数
	
// 对话框数据

	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	
//控件函数
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam); //afx_msg用作宏定义，用来告诉编译器这个函数是消息处理函数
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButton1();                //查找设备
	afx_msg void OnBnClickedOpenButton();					//打开设备
	//afx_msg void OnBnClickedCloseButton();					//关闭设备
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnStnClickedDisplayStatic();
	//afx_msg void OnBnClickedStopGrabbingButton();
	//afx_msg void OnBnClickedContinusModeRadio();
	afx_msg void OnBnClickedStopGrabbingButton();
	afx_msg void OnBnClickedCloseButton();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedSaveMultipleStatic();
	afx_msg void OnBnClickedSaveSingleButton();
	afx_msg void OnBnClickedCalibStart();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedGetParameterButton();
	afx_msg void OnBnClickedSetParameterButton();
	afx_msg void OnBnClickedCalibLight();
	afx_msg void OnBnClickedLightSavesingle();
	afx_msg void OnBnClickedSavesingleRadio();
	afx_msg void OnBnClickedLightSavestart();
	afx_msg void OnBnClickedSavemultipleRadio();
	afx_msg void OnBnClickedPictureOpen();
	afx_msg void OnStnClickedLightpictureStatic();
	afx_msg void OnBnClickedOpenfile();
	afx_msg void OnStnClickedPdcviewStatic();
	afx_msg void OnBnClickedOutlineButton();
	afx_msg void OnBnClickedRoiButton();
	afx_msg void OnBnClickedGetroi();
	afx_msg void OnBnClickedMeanfilter();
	afx_msg void OnBnClickedOtsucut();
	afx_msg void OnBnClickedBinarization();
	afx_msg void OnBnClickedmorphology();
	afx_msg void OnBnClickedLightcut();
// 控件对应变量
private:
	/*ch:最开始时的窗口初始化 | en:Window initialization*/
	void DisplayWindowInitial();
	CComboBox						m_ctrlDeviceCombo;//枚举到的设备
	CComboBox                       m_ctrlFileNameCombo;   //选择的文件名
	int								m_nDeviceCombo;//在线的设备数
	MV_FRAME_OUT_INFO_EX            m_stImageInfo;
	void* m_phGrabThread;              // ch:取流线程句柄 | en:Grab thread handle
	BOOL                    m_bThreadState;
private:
	MV_CC_DEVICE_INFO_LIST			m_stDevList;   //设备列表
	
	CRITICAL_SECTION        m_hSaveImageMux;
	unsigned char* m_pchSaveImageBuf;
	unsigned int            m_chSaveImageBufSize;
	void EnableControls(BOOL bIsCameraReady);
public:
	int GrabThreadProcess();                  //初始化
	int GrabThreadSave();					  //取流+保存图片
private:
// ch:去除自定义的像素格式 | en:Remove custom pixel formats
bool RemoveCustomPixelFormats(enum MvGvspPixelType enPixelFormat);
private:
	BOOL                    m_bOpenDevice;                        // ch:是否打开设备 | en:Whether to open device
	BOOL                    m_bStartGrabbing;                     // ch:是否开始抓图 | en:Whether to start grabbing
	BOOL                    m_bLightSaveSingle;                   //光条单张保存
	BOOL                    m_bLightSaveMultiple;                 //光条多张保存
	int                     m_nTriggerMode;                       // ch:触发模式 | en:Trigger Mode
	int                     m_nTriggerSource;                     // ch:触发源 | en:Trigger Source
	int                     GetTriggerMode();                     //  获取触发模式
	int CloseDevice();                   // ch:关闭设备 | en:Close Device
	int SaveCalibImage(MV_SAVE_IAMGE_TYPE enSaveImageType);						 //保存图片
	int SaveLightImage(MV_SAVE_IAMGE_TYPE enSaveImageType);
	int SaveLightImage1(MV_SAVE_IAMGE_TYPE enSaveImageType);
	CMvCamera* m_pcMvCamera;               // MvCamera封装了常用接口 | en:ClslMV_CAMERA_C packed commonly used interface
	CCalib* m_pcCalib;				   	   // Calib封装了常用接口
	CLightStripe* m_pcLightStripe;         // LightStripe封装了常用接口
	CPointCloud* m_pcPointCloud;           // PointCloud封装了常用接口
	HWND                    m_hwndDisplay;                        // ch:显示句柄 | en:Display Handle
private:
	//最开始时的窗口初始化 
	void ShowErrorMsg(CString csMessage, int nErrorNum);   //显示错误信息
	int GetExposureTime();               // ch:设置曝光时间 | en:Set Exposure Time
	int SetExposureTime();
	int GetGain();                       // ch:设置增益 | en:Set Gain
	int SetGain();
	int GetFrameRate();                  // ch:设置帧率 | en:Set Frame Rate
	int SetFrameRate();
	int GetTriggerSource();              // ch:设置触发源 | en:Set Trigger Source
	int SetTriggerSource();

	double                  m_dExposureEdit;
	double                  m_dGainEdit;
	double                  m_dFrameRateEdit;

	
private:
	CEdit m_edtEdit;

public:
	Mat m_mEdit1;
private:
	CEdit m_edtEdit2;
public:
	void OpenPic(CImage& imgLightImg);
	void MatToCImage(Mat& mat, CImage& cimage);
//标定所用参量
public:
	CString m_pstrFilePath, m_pstrFileName;
	string m_sPicPath;
	vector<Mat> m_vRvecsMat; //旋转向量
	vector<Mat> m_vTvecsMat; //平移向量
	Mat m_mMoveStep;         //移动位姿
	float line_plane[4] = { 0 };//定义用来储存平面参数的数组 
	//标定
	Mat m_mCameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0));//内参矩阵
	Mat m_mDistCoeff = Mat(1, 5, CV_32FC1, Scalar::all(0)); //畸变矩阵
	vector<Point3f> m_vvPoints3d20to19; 
	vector<Point3f> m_vPoints3d_19;
	CStatic m_psPicture;
	
	//VTK显示
private:
	boost::shared_ptr<pcl::visualization::PCLVisualizer> m_spViewer;    //申明VTK变量
	boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>> m_spCloud;
	vtkRenderWindow* m_rwndRenWin;
	vtkRenderWindowInteractor* m_rwndinIren;
	//光条
public:
	Mat m_mRoiPic;  //ROI图像
	Mat m_mCopyRoi;
	Mat m_mMidPic;  //中值滤波图像
	int G_nThresh;  //最佳阈值
	Mat m_mBinDst;     //二值化后图像
	Mat m_mMorDst;     //形态学操作后图像
	CString m_sPathName;  //光条文件夹路径
	
	afx_msg void OnBnClickedImageshow();
	afx_msg void OnBnClickedChoosefile();
	afx_msg void OnCbnSelchangeFileCombo();
	afx_msg void OnEnChangeFilenameEdit();
	afx_msg void OnBnClickedDoublefilter();

	void visualize_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr& filter_cloud);
	//inline double kernel(double x, double sigma);
	afx_msg void OnBnClickedPassthroughfilter();
	afx_msg void OnBnClickedStatistical();
	afx_msg void OnBnClickedReturnpoint();
	afx_msg void OnBnClickedXrender();
	afx_msg void OnBnClickedYrender();
	afx_msg void OnBnClickedZrender();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedRadiusfilter();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedUniformsampling();
	afx_msg void OnBnClickedRandomsampling();
	afx_msg void OnBnClickedNormalsampling();
	afx_msg void OnBnClickedVoxelfilter();
	afx_msg void OnBnClickedSavefile();
public:
	//显示
	
	afx_msg void OnStnClickedBestotsuStatic();
	afx_msg void OnBnClickedStopshow();
	afx_msg void OnBnClickedReturnpcl();
	afx_msg void OnBnClickedLightSavestop();
	afx_msg void OnBnClickedSavefile2();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton12();
};
