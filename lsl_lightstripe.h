#pragma once
#include"lsl_population.h"
//#include "lsl_application_dlg.h"


class CLightStripe
{
private:
	
	//CApplicationDlg * m_pcMFC;					// MFC封装了常用接口
	//CMvCamera*m_pcMvCamera;                        // CMvCamera封装了常用接口 
	//Calib* m_pcCalib;                              //Calib封装了常用接口
	
public:
	
	
public:
	Mat LS_OutLine(String& sPicPath, Mat& mImgRect);
	Mat LS_RoiCut(String& sPicPath);
	Mat LS_MidBlur(Mat& mSrcImg);
	int LS_Otsu(Mat& mSrcImg, Mat& mDst);
	void LS_ThreshTxt(int thresh, CString& str);
	Mat LS_Morphology(Mat& mDst);
	Mat LS_LightStr(Mat& mDilateImg, String& m_sPicPath, Mat mRoiPic,int nThresh);
	void LS_ThinSubiteration(Mat& pSrc, Mat& pDst);
	CString LS_OpenFile();
	void LS_StripeToPoint(String& m_sPicPath);
	Mat ideal_high_kernel1(cv::Mat& scr, float sigma);
	Mat ideal_high_pass_filter1(cv::Mat& src, float sigma);
	Mat frequency_filter1(cv::Mat& scr, cv::Mat& blur);
	Mat image_make_border1(cv::Mat& src);
	void fftshift1(cv::Mat& plane0, cv::Mat& plane1);
	void Clear_MicroConnected_Areas(Mat src, Mat& dst, double min_area);
};

