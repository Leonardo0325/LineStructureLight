#include "pch.h"
#include "lsl_lightstripe.h"

Mat CLightStripe::LS_OutLine(String&sPicPath,Mat&mImgRect)
{

	Mat mImg = imread(sPicPath);
	Mat mRect, mThre, mImgCanny;
	mImg.copyTo(mRect);
	//边缘检测二值化
	threshold(mImg, mThre, 80, 255, THRESH_BINARY);
	Canny(mThre, mImgCanny, 80, 160, 3, false);



	//轮廓发现与绘制
	vector<vector<Point>>vContours;
	vector<Vec4i>vHierarchy;
	findContours(mImgCanny, vContours, vHierarchy, 0, 2, Point());
	//寻找轮廓的外接矩形
	for (int n = 0; n < vContours.size(); n++)
	{

		//最大外接矩形
		Rect rect = boundingRect(vContours[n]);
		rectangle(mRect, rect, Scalar(255, 255, 255), 1, 8, 0);
	}
	//相减得到边框
	Mat mSubtract;
	absdiff(mImg, mRect, mSubtract);
	Mat mImgThre, mGray;
	cvtColor(mSubtract, mGray, COLOR_BGR2GRAY);
	threshold(mGray, mImgThre, 80, 255, THRESH_BINARY);
	vector<vector<Point>>vContours1;
	vector<Vec4i>vHierarchy1;
	vector<Point>  vHull;
	//计算边框点
	vector<int> vXFrame;
	vector<int>vYFrame;
	findContours(mImgThre, vContours1, vHierarchy1, 0, 2, Point());
	for (int n = 0; n < vContours1.size(); n++)
	{
		convexHull(vContours1[n], vHull);    //检测该轮廓的凸包
		//绘制凸包
		for (int i = 0; i < vHull.size(); ++i) {
			circle(mSubtract, vHull[i], 4, Scalar(255, 0, 0), 1, 8, 0);
			vXFrame.push_back(vHull[i].x);
			vYFrame.push_back(vHull[i].y);
		}
	}
	vector<int>::iterator xmaxpos = max_element(vXFrame.begin(), vXFrame.end());
	vector<int>::iterator xminpos = min_element(vXFrame.begin(), vXFrame.end());
	vector<int>::iterator ymaxpos = max_element(vYFrame.begin(), vYFrame.end());
	vector<int>::iterator yminpos = min_element(vYFrame.begin(), vYFrame.end());
	//cout << *xmaxpos << " " << *xminpos << endl;
	//cout << *ymaxpos << " " << *yminpos << endl;
	vector<vector<Point2i>> vContours3;
	vector<Point2i> vPoints;
	vPoints.push_back(Point2i(*xmaxpos, *yminpos - 20));
	vPoints.push_back(Point2i(*xmaxpos, *ymaxpos + 20));
	vPoints.push_back(Point2i(*xminpos, *ymaxpos + 20));
	vPoints.push_back(Point2i(*xminpos, *yminpos - 20));
	vContours3.push_back(vPoints);
	int nXSubtract = *xmaxpos - *xminpos;
	int nYSubtract = *ymaxpos - *yminpos;
	Mat mRoi = mImg(Rect(*xminpos, *yminpos - 20, *xmaxpos - *xminpos, *ymaxpos + 40 - *yminpos));
	Mat mDst;
	mImg.copyTo(mImgRect); //深拷贝用来绘制最大外接矩形
	for (int n = 0; n < vContours3.size(); n++)
	{

		//最大外接矩形
		Rect rect = boundingRect(vContours3[n]);
		rectangle(mImgRect, rect, Scalar(255, 255, 255), 1, 8, 0);
	}
	//imgs.push_back(mDst);
	return mDst;
}
Mat CLightStripe::LS_RoiCut(String& m_sPicPath)
{
	Mat mImgCopy;
	String sPath = m_sPicPath;
	Mat mSrcImg = imread(sPath);
	Mat mRect, mImgThre, mImgCanny;
	mSrcImg.copyTo(mRect);
	mSrcImg.copyTo(mImgCopy);
	//边缘检测二值化
	threshold(mSrcImg, mImgThre, 80, 255, THRESH_BINARY);
	Canny(mImgThre, mImgCanny, 80, 160, 3, false);



	//轮廓发现与绘制
	vector<vector<Point>>vContours;
	vector<Vec4i>vHierarchy;
	findContours(mImgCanny, vContours, vHierarchy, 0, 2, Point());
	//寻找轮廓的外接矩形
	for (int n = 0; n < vContours.size(); n++)
	{

		//最大外接矩形
		Rect rect = boundingRect(vContours[n]);
		rectangle(mRect, rect, Scalar(255, 255, 255), 1, 8, 0);
	}
	//相减得到边框
	Mat mSubtract;
	absdiff(mSrcImg, mRect, mSubtract);
	Mat mThre, mGray;
	cvtColor(mSubtract, mGray, COLOR_BGR2GRAY);
	threshold(mGray, mThre, 80, 255, THRESH_BINARY);
	vector<vector<Point>>vContours1;
	vector<Vec4i>vHierarchy1;
	vector<Point>  vHull;
	//计算边框点
	vector<int> vXFrame;
	vector<int>vYFrame;
	findContours(mThre, vContours1, vHierarchy1, 0, 2, Point());
	for (int n = 0; n < vContours1.size(); n++)
	{
		convexHull(vContours1[n], vHull);    //检测该轮廓的凸包
		//绘制凸包
		for (int i = 0; i < vHull.size(); ++i) {
			circle(mSubtract, vHull[i], 4, Scalar(255, 0, 0), 1, 8, 0);
			vXFrame.push_back(vHull[i].x);
			vYFrame.push_back(vHull[i].y);
		}
	}
	vector<int>::iterator xmaxpos = max_element(vXFrame.begin(), vXFrame.end());
	vector<int>::iterator xminpos = min_element(vXFrame.begin(), vXFrame.end());
	vector<int>::iterator ymaxpos = max_element(vYFrame.begin(), vYFrame.end());
	vector<int>::iterator yminpos = min_element(vYFrame.begin(), vYFrame.end());
	//cout << *xmaxpos << " " << *xminpos << endl;
	//cout << *ymaxpos << " " << *yminpos << endl;
	vector<vector<Point2i>> vContours3;
	vector<Point2i> points;
	points.push_back(Point2i(*xmaxpos, *yminpos ));
	points.push_back(Point2i(*xmaxpos, *ymaxpos ));
	points.push_back(Point2i(*xminpos, *ymaxpos ));
	points.push_back(Point2i(*xminpos, *yminpos));
	vContours3.push_back(points);
	int nXSubtract = *xmaxpos - *xminpos;
	int nYSubtract = *ymaxpos - *yminpos;
	Mat mRoi = mSrcImg(Rect(*xminpos, *yminpos , *xmaxpos - *xminpos, *ymaxpos  - *yminpos));
	Mat mImgRect,mDst;
	mSrcImg.copyTo(mImgRect); //深拷贝用来绘制最大外接矩形
	for (int n = 0; n < vContours3.size(); n++)
	{

		//最大外接矩形
		Rect rect = boundingRect(vContours3[n]);
		rectangle(mImgRect, rect, Scalar(255, 255, 255), 1, 8, 0);
	}
	int nX = *xminpos;
	int nY = *yminpos;
	Rect rect(nX, nY, nXSubtract , nYSubtract);
	Mat mSaveRoi = mImgCopy(rect);
	imwrite("D:\\pictureSave\\lightSave\\light5\\imgsssssss.png", mSaveRoi);
	return mSaveRoi;

}
//中值滤波
Mat CLightStripe::LS_MidBlur(Mat&mSrcImg)
{
	Mat mGray,medianPic;
	cvtColor(mSrcImg, mGray, COLOR_BGR2GRAY);
	medianBlur(mGray, medianPic, 3);
	return medianPic;
}
//Otsu寻找最佳阈值
int CLightStripe::LS_Otsu(Mat& mSrcImg, Mat& mDst) {
	int nThresh;
	const int Grayscale = 256;
	int mGraynum[Grayscale] = { 0 };
	int rows = mSrcImg.rows;
	int cols = mSrcImg.cols;
	for (int i = 0; i < rows; ++i) {
		const uchar* ptr = mSrcImg.ptr<uchar>(i);
		for (int j = 0; j < cols; ++j) {        //直方图统计
			mGraynum[ptr[j]]++;
		}
	}

	double P[Grayscale] = { 0 };
	double PK[Grayscale] = { 0 };
	double MK[Grayscale] = { 0 };
	double mSrcImgpixnum = rows * cols, nSumtmpPK = 0, nSumtmpMK = 0;
	for (int i = 0; i < Grayscale; ++i) {
		P[i] = mGraynum[i] / mSrcImgpixnum;   //每个灰度级出现的概率
		PK[i] = nSumtmpPK + P[i];         //概率累计和 
		nSumtmpPK = PK[i];
		MK[i] = nSumtmpMK + i * P[i];       //灰度级的累加均值                                                                                                                                                                                                                                                                                                                                                                                                        
		nSumtmpMK = MK[i];
	}

	//计算类间方差
	double dVar = 0;
	for (int k = 0; k < Grayscale; ++k) {
		if ((MK[Grayscale - 1] * PK[k] - MK[k]) * (MK[Grayscale - 1] * PK[k] - MK[k]) / (PK[k] * (1 - PK[k])) > dVar) {
			dVar = (MK[Grayscale - 1] * PK[k] - MK[k]) * (MK[Grayscale - 1] * PK[k] - MK[k]) / (PK[k] * (1 - PK[k]));
			nThresh = k;
		}
	}

	//阈值处理
	mSrcImg.copyTo(mDst);
	for (int i = 0; i < rows; ++i) {
		uchar* ptr = mDst.ptr<uchar>(i);
		for (int j = 0; j < cols; ++j) {
			if (ptr[j] > nThresh)
				ptr[j] = 255;
			else
				ptr[j] = 0;
		}
	}
	return nThresh;
}
//创建文件，用于读取光条图像
void CLightStripe::LS_ThreshTxt(int nThresh, CString& str)
{
	ofstream flFile;//创建文件
	flFile.open("D:\\pictureSave\\lightSave\\thresh.txt");
	flFile  <<nThresh<< endl;
	
	flFile.close();
	CFileDialog FileDlg(TRUE);
	CFile f;
	f.Open("D:\\pictureSave\\lightSave\\thresh.txt", CFile::modeReadWrite);
	f.Read(str.GetBuffer(f.GetLength()), f.GetLength());
	f.Close();
}
//形态学操作
Mat CLightStripe::LS_Morphology(Mat&mDst)
{

	Mat mCloseImg;
	Mat mStruct, mDilateImg;  //创建图像膨胀矩形结构元素、存放膨胀后的图像
	mStruct = getStructuringElement(0, Size(3, 3));
	morphologyEx(mDst, mCloseImg, MORPH_CLOSE, mStruct);
	dilate(mCloseImg, mDilateImg, mStruct);
	erode(mDilateImg, mDilateImg, mStruct);
	return mDilateImg;
}
//连通域筛除
void CLightStripe::Clear_MicroConnected_Areas(Mat src, Mat& dst, double min_area)
{
	//备份复制
	dst = src.clone();
	vector<vector<Point>> contours; //创建轮廓容器
	vector<Vec4i> hierachy;
	// 第四个参数CV_RETR_EXTERNAL，表示寻找最外围轮廓
   // 第五个参数CV_CHAIN_APPROX_NONE，表示保存物体边界上所有连续的轮廓点到contours向量内
	findContours(src, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());

	if (!contours.empty() && !hierachy.empty())
	{
		vector<vector<Point>>::const_iterator itc = contours.begin();
		//遍历所有轮廓
		while (itc != contours.end())
		{
			//定位当前轮廓所在位置
			Rect rect = boundingRect(Mat(*itc));
			//计算连通区面积
			double area = contourArea(*itc);
			//若面积小于设置阈值
			if (area < min_area)
			{
				//遍历轮廓所在位置所有像素点
				for (int i = rect.y; i < rect.y + rect.height; i++)
				{
					uchar* output_data = dst.ptr<uchar>(i);
					for (int j = rect.x; j < rect.x + rect.width; j++)
					{
						//将连通区域的值设为0
						if (output_data[j] >= 20)
						{
							output_data[j] = 0;
						}
					}

				}
			}
			itc++;
		}
	}
}
//高通滤波核函数
Mat CLightStripe::ideal_high_kernel1(cv::Mat& scr, float sigma)
{
	cv::Mat ideal_high_pass(scr.size(), CV_32FC1); //，CV_32FC1
	float d0 = sigma;//半径D0越小，模糊越大；半径D0越大，模糊越小
	for (int i = 0; i < scr.rows; i++) {
		for (int j = 0; j < scr.cols; j++) {
			float d = sqrt(pow(float(i - scr.rows / 2), 2) + pow(float(j - scr.cols / 2), 2));//分子,计算pow必须为float型
			if (d <= d0) {
				ideal_high_pass.at<float>(i, j) = 0;
			}
			else {
				ideal_high_pass.at<float>(i, j) = 1;
			}
		}
	}
	return ideal_high_pass;
}
//高通滤波器
Mat CLightStripe::ideal_high_pass_filter1(cv::Mat& src, float sigma)
{
	cv::Mat padded = image_make_border1(src);
	cv::Mat ideal_kernel = ideal_high_kernel1(padded, sigma);
	cv::Mat result = frequency_filter1(padded, ideal_kernel);
	return result;
}
// 频率域滤波
cv::Mat CLightStripe::frequency_filter1(cv::Mat& scr, cv::Mat& blur)
{
	cv::Mat mask = scr == scr;
	scr.setTo(0.0f, ~mask);

	//创建通道，存储dft后的实部与虚部（CV_32F，必须为单通道数）
	cv::Mat plane[] = { scr.clone(), cv::Mat::zeros(scr.size() , CV_32FC1) };

	cv::Mat complexIm;
	cv::merge(plane, 2, complexIm); // 合并通道 （把两个矩阵合并为一个2通道的Mat类容器）
	cv::dft(complexIm, complexIm); // 进行傅立叶变换，结果保存在自身

	// 分离通道（数组分离）
	cv::split(complexIm, plane);

	// 以下的操作是频域迁移
	fftshift1(plane[0], plane[1]);

	// *****************滤波器函数与DFT结果的乘积****************
	cv::Mat blur_r, blur_i, BLUR;
	cv::multiply(plane[0], blur, blur_r);  // 滤波（实部与滤波器模板对应元素相乘）
	cv::multiply(plane[1], blur, blur_i);  // 滤波（虚部与滤波器模板对应元素相乘）
	cv::Mat plane1[] = { blur_r, blur_i };

	// 再次搬移回来进行逆变换
	fftshift1(plane1[0], plane1[1]);
	cv::merge(plane1, 2, BLUR); // 实部与虚部合并

	cv::idft(BLUR, BLUR);       // idft结果也为复数
	BLUR = BLUR / BLUR.rows / BLUR.cols;

	cv::split(BLUR, plane);//分离通道，主要获取通道

	return plane[0];
}
// 图像边界处理
cv::Mat CLightStripe::image_make_border1(cv::Mat& src)
{
	int w = cv::getOptimalDFTSize(src.cols); // 获取DFT变换的最佳宽度
	int h = cv::getOptimalDFTSize(src.rows); // 获取DFT变换的最佳高度

	cv::Mat padded;
	// 常量法扩充图像边界，常量 = 0
	cv::copyMakeBorder(src, padded, 0, h - src.rows, 0, w - src.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	padded.convertTo(padded, CV_32FC1);

	return padded;
}
// fft变换后进行频谱搬移
void CLightStripe::fftshift1(cv::Mat& plane0, cv::Mat& plane1)
{
	// 以下的操作是移动图像  (零频移到中心)
	int cx = plane0.cols / 2;
	int cy = plane0.rows / 2;
	cv::Mat part1_r(plane0, cv::Rect(0, 0, cx, cy));  // 元素坐标表示为(cx, cy)
	cv::Mat part2_r(plane0, cv::Rect(cx, 0, cx, cy));
	cv::Mat part3_r(plane0, cv::Rect(0, cy, cx, cy));
	cv::Mat part4_r(plane0, cv::Rect(cx, cy, cx, cy));

	cv::Mat temp;
	part1_r.copyTo(temp);  //左上与右下交换位置(实部)
	part4_r.copyTo(part1_r);
	temp.copyTo(part4_r);

	part2_r.copyTo(temp);  //右上与左下交换位置(实部)
	part3_r.copyTo(part2_r);
	temp.copyTo(part3_r);

	cv::Mat part1_i(plane1, cv::Rect(0, 0, cx, cy));  //元素坐标(cx,cy)
	cv::Mat part2_i(plane1, cv::Rect(cx, 0, cx, cy));
	cv::Mat part3_i(plane1, cv::Rect(0, cy, cx, cy));
	cv::Mat part4_i(plane1, cv::Rect(cx, cy, cx, cy));

	part1_i.copyTo(temp);  //左上与右下交换位置(虚部)
	part4_i.copyTo(part1_i);
	temp.copyTo(part4_i);

	part2_i.copyTo(temp);  //右上与左下交换位置(虚部)
	part3_i.copyTo(part2_i);
	temp.copyTo(part3_i);
}

//计算灰度重心
Mat CLightStripe::LS_LightStr(Mat&mDilateImg, String& m_sPicPath, Mat mRoiPic,int nThresh)
{
	String sPath = m_sPicPath;
	Mat mSrcImg = imread(sPath,  IMREAD_GRAYSCALE);
	Mat srcimg;
	int a = 0;
	float D1 = 1.0f;
	srcimg = imread(sPath);
	mSrcImg = ideal_high_pass_filter1(mSrcImg, D1);
	imwrite("D:\\pictureSave\\lightSave\\high pass1.png", mSrcImg);
	mSrcImg = imread("D:\\pictureSave\\lightSave\\high pass1.png");
	cvtColor(mSrcImg, mSrcImg, COLOR_BGR2GRAY);
	//Mat image = cv::imread("D:\\pictureSave\\lightSave\\light1\\connection_rod_022.png", IMREAD_GRAYSCALE);
	threshold(mSrcImg, mSrcImg, nThresh, 255, THRESH_BINARY);
	Clear_MicroConnected_Areas(mSrcImg, mSrcImg, 5);
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
					cout << "边界点:" << a << endl;

					break;
				}
			}
		}
		if (num == 0)
			continue;
		float x = sum / num;
		circle(srcimg, Point(i, x), 0.5, Scalar(0, 0, 255), -1, 8);
		//circle(srcimg, Points, 1, Scalar(0, 255, 255));
		int b = a + 1;
		for (size_t j = b; j < mSrcImg.rows; j++)
		{
			if (mSrcImg.at<uchar>(j, i) == 255)
			{
				sum1 += j;
				num1++;
			}
		}
		if (num1 == 0)
			continue;
		float x1 = sum1 / num1;
		circle(srcimg, Point(i, x1), 0.5, Scalar(0, 0, 255), -1, 8);
	}
	//namedWindow("srcimg", WINDOW_GUI_NORMAL);
	return srcimg;
}
//光条细化
void CLightStripe::LS_ThinSubiteration(Mat& pSrc, Mat& pDst) {
	int rows = pSrc.rows;
	int cols = pSrc.cols;
	pSrc.copyTo(pDst);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (pSrc.at<float>(i, j) == 1.0f) {
				/// get 8 neighbors
				/// calculate C(p)
				int neighbor0 = (int)pSrc.at<float>(i - 1, j - 1);
				int neighbor1 = (int)pSrc.at<float>(i - 1, j);
				int neighbor2 = (int)pSrc.at<float>(i - 1, j + 1);
				int neighbor3 = (int)pSrc.at<float>(i, j + 1);
				int neighbor4 = (int)pSrc.at<float>(i + 1, j + 1);
				int neighbor5 = (int)pSrc.at<float>(i + 1, j);
				int neighbor6 = (int)pSrc.at<float>(i + 1, j - 1);
				int neighbor7 = (int)pSrc.at<float>(i, j - 1);
				int C = int(~neighbor1 & (neighbor2 | neighbor3)) +
					int(~neighbor3 & (neighbor4 | neighbor5)) +
					int(~neighbor5 & (neighbor6 | neighbor7)) +
					int(~neighbor7 & (neighbor0 | neighbor1));
				if (C == 1) {
					/// calculate N
					int N1 = int(neighbor0 | neighbor1) +
						int(neighbor2 | neighbor3) +
						int(neighbor4 | neighbor5) +
						int(neighbor6 | neighbor7);
					int N2 = int(neighbor1 | neighbor2) +
						int(neighbor3 | neighbor4) +
						int(neighbor5 | neighbor6) +
						int(neighbor7 | neighbor0);
					int N = min(N1, N2);
					if ((N == 2) || (N == 3)) {
						/// calculate criteria 3
						int c3 = (neighbor1 | neighbor2 | ~neighbor4) & neighbor3;
						if (c3 == 0) {
							pDst.at<float>(i, j) = 0.0f;
						}
					}
				}
			}
		}
	}
}
//打开文件
CString CLightStripe::LS_OpenFile()
{
	TCHAR            szFolderPath[255] = { 0 };
	CString          strFolderPath;
	BROWSEINFO       sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = "请选择缓存文件所在文件夹";
	sInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
	sInfo.lpfn = NULL;

	LPITEMIDLIST  lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		if (::SHGetPathFromIDListA(lpidlBrowse, szFolderPath))
		{
			strFolderPath = szFolderPath;
		}
	}
	if (lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}
	return strFolderPath;
}
// 光条恢复
void CLightStripe::LS_StripeToPoint(String& m_sPicPath)
{
	String sPath = m_sPicPath;
	Mat mSrcImg = imread(sPath, IMREAD_GRAYSCALE);
	threshold(mSrcImg, mSrcImg, 80, 255, THRESH_BINARY);
	for (size_t i = 0; i < mSrcImg.cols; i++)
	{
		int sum = 0; int num = 0;
		for (size_t j = 0; j < mSrcImg.rows; j++)
		{
			if (mSrcImg.at<uchar>(j, i) == 255)
			{
				sum += j;
				num++;
			}
		}
		if (num == 0)
			continue;
		Point2f Points = Point2f(i, sum / num);
	}

}
