#include "pch.h"
#include "lsl_lightstripe.h"

Mat CLightStripe::LS_OutLine(String&sPicPath,Mat&mImgRect)
{

	Mat mImg = imread(sPicPath);
	Mat mRect, mThre, mImgCanny;
	mImg.copyTo(mRect);
	//��Ե����ֵ��
	threshold(mImg, mThre, 80, 255, THRESH_BINARY);
	Canny(mThre, mImgCanny, 80, 160, 3, false);



	//�������������
	vector<vector<Point>>vContours;
	vector<Vec4i>vHierarchy;
	findContours(mImgCanny, vContours, vHierarchy, 0, 2, Point());
	//Ѱ����������Ӿ���
	for (int n = 0; n < vContours.size(); n++)
	{

		//�����Ӿ���
		Rect rect = boundingRect(vContours[n]);
		rectangle(mRect, rect, Scalar(255, 255, 255), 1, 8, 0);
	}
	//����õ��߿�
	Mat mSubtract;
	absdiff(mImg, mRect, mSubtract);
	Mat mImgThre, mGray;
	cvtColor(mSubtract, mGray, COLOR_BGR2GRAY);
	threshold(mGray, mImgThre, 80, 255, THRESH_BINARY);
	vector<vector<Point>>vContours1;
	vector<Vec4i>vHierarchy1;
	vector<Point>  vHull;
	//����߿��
	vector<int> vXFrame;
	vector<int>vYFrame;
	findContours(mImgThre, vContours1, vHierarchy1, 0, 2, Point());
	for (int n = 0; n < vContours1.size(); n++)
	{
		convexHull(vContours1[n], vHull);    //����������͹��
		//����͹��
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
	mImg.copyTo(mImgRect); //����������������Ӿ���
	for (int n = 0; n < vContours3.size(); n++)
	{

		//�����Ӿ���
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
	//��Ե����ֵ��
	threshold(mSrcImg, mImgThre, 80, 255, THRESH_BINARY);
	Canny(mImgThre, mImgCanny, 80, 160, 3, false);



	//�������������
	vector<vector<Point>>vContours;
	vector<Vec4i>vHierarchy;
	findContours(mImgCanny, vContours, vHierarchy, 0, 2, Point());
	//Ѱ����������Ӿ���
	for (int n = 0; n < vContours.size(); n++)
	{

		//�����Ӿ���
		Rect rect = boundingRect(vContours[n]);
		rectangle(mRect, rect, Scalar(255, 255, 255), 1, 8, 0);
	}
	//����õ��߿�
	Mat mSubtract;
	absdiff(mSrcImg, mRect, mSubtract);
	Mat mThre, mGray;
	cvtColor(mSubtract, mGray, COLOR_BGR2GRAY);
	threshold(mGray, mThre, 80, 255, THRESH_BINARY);
	vector<vector<Point>>vContours1;
	vector<Vec4i>vHierarchy1;
	vector<Point>  vHull;
	//����߿��
	vector<int> vXFrame;
	vector<int>vYFrame;
	findContours(mThre, vContours1, vHierarchy1, 0, 2, Point());
	for (int n = 0; n < vContours1.size(); n++)
	{
		convexHull(vContours1[n], vHull);    //����������͹��
		//����͹��
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
	mSrcImg.copyTo(mImgRect); //����������������Ӿ���
	for (int n = 0; n < vContours3.size(); n++)
	{

		//�����Ӿ���
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
//��ֵ�˲�
Mat CLightStripe::LS_MidBlur(Mat&mSrcImg)
{
	Mat mGray,medianPic;
	cvtColor(mSrcImg, mGray, COLOR_BGR2GRAY);
	medianBlur(mGray, medianPic, 3);
	return medianPic;
}
//OtsuѰ�������ֵ
int CLightStripe::LS_Otsu(Mat& mSrcImg, Mat& mDst) {
	int nThresh;
	const int Grayscale = 256;
	int mGraynum[Grayscale] = { 0 };
	int rows = mSrcImg.rows;
	int cols = mSrcImg.cols;
	for (int i = 0; i < rows; ++i) {
		const uchar* ptr = mSrcImg.ptr<uchar>(i);
		for (int j = 0; j < cols; ++j) {        //ֱ��ͼͳ��
			mGraynum[ptr[j]]++;
		}
	}

	double P[Grayscale] = { 0 };
	double PK[Grayscale] = { 0 };
	double MK[Grayscale] = { 0 };
	double mSrcImgpixnum = rows * cols, nSumtmpPK = 0, nSumtmpMK = 0;
	for (int i = 0; i < Grayscale; ++i) {
		P[i] = mGraynum[i] / mSrcImgpixnum;   //ÿ���Ҷȼ����ֵĸ���
		PK[i] = nSumtmpPK + P[i];         //�����ۼƺ� 
		nSumtmpPK = PK[i];
		MK[i] = nSumtmpMK + i * P[i];       //�Ҷȼ����ۼӾ�ֵ                                                                                                                                                                                                                                                                                                                                                                                                        
		nSumtmpMK = MK[i];
	}

	//������䷽��
	double dVar = 0;
	for (int k = 0; k < Grayscale; ++k) {
		if ((MK[Grayscale - 1] * PK[k] - MK[k]) * (MK[Grayscale - 1] * PK[k] - MK[k]) / (PK[k] * (1 - PK[k])) > dVar) {
			dVar = (MK[Grayscale - 1] * PK[k] - MK[k]) * (MK[Grayscale - 1] * PK[k] - MK[k]) / (PK[k] * (1 - PK[k]));
			nThresh = k;
		}
	}

	//��ֵ����
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
//�����ļ������ڶ�ȡ����ͼ��
void CLightStripe::LS_ThreshTxt(int nThresh, CString& str)
{
	ofstream flFile;//�����ļ�
	flFile.open("D:\\pictureSave\\lightSave\\thresh.txt");
	flFile  <<nThresh<< endl;
	
	flFile.close();
	CFileDialog FileDlg(TRUE);
	CFile f;
	f.Open("D:\\pictureSave\\lightSave\\thresh.txt", CFile::modeReadWrite);
	f.Read(str.GetBuffer(f.GetLength()), f.GetLength());
	f.Close();
}
//��̬ѧ����
Mat CLightStripe::LS_Morphology(Mat&mDst)
{

	Mat mCloseImg;
	Mat mStruct, mDilateImg;  //����ͼ�����;��νṹԪ�ء�������ͺ��ͼ��
	mStruct = getStructuringElement(0, Size(3, 3));
	morphologyEx(mDst, mCloseImg, MORPH_CLOSE, mStruct);
	dilate(mCloseImg, mDilateImg, mStruct);
	erode(mDilateImg, mDilateImg, mStruct);
	return mDilateImg;
}
//��ͨ��ɸ��
void CLightStripe::Clear_MicroConnected_Areas(Mat src, Mat& dst, double min_area)
{
	//���ݸ���
	dst = src.clone();
	vector<vector<Point>> contours; //������������
	vector<Vec4i> hierachy;
	// ���ĸ�����CV_RETR_EXTERNAL����ʾѰ������Χ����
   // ���������CV_CHAIN_APPROX_NONE����ʾ��������߽������������������㵽contours������
	findContours(src, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());

	if (!contours.empty() && !hierachy.empty())
	{
		vector<vector<Point>>::const_iterator itc = contours.begin();
		//������������
		while (itc != contours.end())
		{
			//��λ��ǰ��������λ��
			Rect rect = boundingRect(Mat(*itc));
			//������ͨ�����
			double area = contourArea(*itc);
			//�����С��������ֵ
			if (area < min_area)
			{
				//������������λ���������ص�
				for (int i = rect.y; i < rect.y + rect.height; i++)
				{
					uchar* output_data = dst.ptr<uchar>(i);
					for (int j = rect.x; j < rect.x + rect.width; j++)
					{
						//����ͨ�����ֵ��Ϊ0
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
//��ͨ�˲��˺���
Mat CLightStripe::ideal_high_kernel1(cv::Mat& scr, float sigma)
{
	cv::Mat ideal_high_pass(scr.size(), CV_32FC1); //��CV_32FC1
	float d0 = sigma;//�뾶D0ԽС��ģ��Խ�󣻰뾶D0Խ��ģ��ԽС
	for (int i = 0; i < scr.rows; i++) {
		for (int j = 0; j < scr.cols; j++) {
			float d = sqrt(pow(float(i - scr.rows / 2), 2) + pow(float(j - scr.cols / 2), 2));//����,����pow����Ϊfloat��
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
//��ͨ�˲���
Mat CLightStripe::ideal_high_pass_filter1(cv::Mat& src, float sigma)
{
	cv::Mat padded = image_make_border1(src);
	cv::Mat ideal_kernel = ideal_high_kernel1(padded, sigma);
	cv::Mat result = frequency_filter1(padded, ideal_kernel);
	return result;
}
// Ƶ�����˲�
cv::Mat CLightStripe::frequency_filter1(cv::Mat& scr, cv::Mat& blur)
{
	cv::Mat mask = scr == scr;
	scr.setTo(0.0f, ~mask);

	//����ͨ�����洢dft���ʵ�����鲿��CV_32F������Ϊ��ͨ������
	cv::Mat plane[] = { scr.clone(), cv::Mat::zeros(scr.size() , CV_32FC1) };

	cv::Mat complexIm;
	cv::merge(plane, 2, complexIm); // �ϲ�ͨ�� ������������ϲ�Ϊһ��2ͨ����Mat��������
	cv::dft(complexIm, complexIm); // ���и���Ҷ�任���������������

	// ����ͨ����������룩
	cv::split(complexIm, plane);

	// ���µĲ�����Ƶ��Ǩ��
	fftshift1(plane[0], plane[1]);

	// *****************�˲���������DFT����ĳ˻�****************
	cv::Mat blur_r, blur_i, BLUR;
	cv::multiply(plane[0], blur, blur_r);  // �˲���ʵ�����˲���ģ���ӦԪ����ˣ�
	cv::multiply(plane[1], blur, blur_i);  // �˲����鲿���˲���ģ���ӦԪ����ˣ�
	cv::Mat plane1[] = { blur_r, blur_i };

	// �ٴΰ��ƻ���������任
	fftshift1(plane1[0], plane1[1]);
	cv::merge(plane1, 2, BLUR); // ʵ�����鲿�ϲ�

	cv::idft(BLUR, BLUR);       // idft���ҲΪ����
	BLUR = BLUR / BLUR.rows / BLUR.cols;

	cv::split(BLUR, plane);//����ͨ������Ҫ��ȡͨ��

	return plane[0];
}
// ͼ��߽紦��
cv::Mat CLightStripe::image_make_border1(cv::Mat& src)
{
	int w = cv::getOptimalDFTSize(src.cols); // ��ȡDFT�任����ѿ��
	int h = cv::getOptimalDFTSize(src.rows); // ��ȡDFT�任����Ѹ߶�

	cv::Mat padded;
	// ����������ͼ��߽磬���� = 0
	cv::copyMakeBorder(src, padded, 0, h - src.rows, 0, w - src.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	padded.convertTo(padded, CV_32FC1);

	return padded;
}
// fft�任�����Ƶ�װ���
void CLightStripe::fftshift1(cv::Mat& plane0, cv::Mat& plane1)
{
	// ���µĲ������ƶ�ͼ��  (��Ƶ�Ƶ�����)
	int cx = plane0.cols / 2;
	int cy = plane0.rows / 2;
	cv::Mat part1_r(plane0, cv::Rect(0, 0, cx, cy));  // Ԫ�������ʾΪ(cx, cy)
	cv::Mat part2_r(plane0, cv::Rect(cx, 0, cx, cy));
	cv::Mat part3_r(plane0, cv::Rect(0, cy, cx, cy));
	cv::Mat part4_r(plane0, cv::Rect(cx, cy, cx, cy));

	cv::Mat temp;
	part1_r.copyTo(temp);  //���������½���λ��(ʵ��)
	part4_r.copyTo(part1_r);
	temp.copyTo(part4_r);

	part2_r.copyTo(temp);  //���������½���λ��(ʵ��)
	part3_r.copyTo(part2_r);
	temp.copyTo(part3_r);

	cv::Mat part1_i(plane1, cv::Rect(0, 0, cx, cy));  //Ԫ������(cx,cy)
	cv::Mat part2_i(plane1, cv::Rect(cx, 0, cx, cy));
	cv::Mat part3_i(plane1, cv::Rect(0, cy, cx, cy));
	cv::Mat part4_i(plane1, cv::Rect(cx, cy, cx, cy));

	part1_i.copyTo(temp);  //���������½���λ��(�鲿)
	part4_i.copyTo(part1_i);
	temp.copyTo(part4_i);

	part2_i.copyTo(temp);  //���������½���λ��(�鲿)
	part3_i.copyTo(part2_i);
	temp.copyTo(part3_i);
}

//����Ҷ�����
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
					cout << "�߽��:" << a << endl;

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
//����ϸ��
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
//���ļ�
CString CLightStripe::LS_OpenFile()
{
	TCHAR            szFolderPath[255] = { 0 };
	CString          strFolderPath;
	BROWSEINFO       sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = "��ѡ�񻺴��ļ������ļ���";
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
// �����ָ�
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
