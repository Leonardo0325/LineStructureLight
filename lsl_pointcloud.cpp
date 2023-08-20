#include "pch.h"
#include "lsl_pointcloud.h"
//打开点云文件
void CPointCloud::PC_OpenPointCloud(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	//打开文件*.pcd *.ply *.obj
	CString sDefaultDir = _T("请选择路径"); //设置默认打开文件夹
	CString sFileFilter = _T("文件(*.pcd;*.ply;*.obj)|*.pcd;*.ply;*.obj|All File (*.*)|*.*||"); //设置文件过滤
	CFileDialog FileDlg(true, sDefaultDir, _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sFileFilter, NULL);
	//弹出选择文件对话框
	if (FileDlg.DoModal() == IDOK)
	{
		sFilePath = FileDlg.GetPathName();//得到完整的文件名和目录名拓展名  
		CString sFilename = FileDlg.GetFileName();
	}
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	//std::string sFilename = "huba_part.pcd";
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile(sFile, *cloud);          //载入点云

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, 255, 255, 255);	//设置点云颜色
	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud, single_color, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
void CPointCloud::PC_LslToPcl()
{
}
void VisualizeCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr& ptrCloud, pcl::PointCloud<pcl::PointXYZ>::Ptr& ptrFilterCloud) {
	//-----------------------显示点云-----------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("显示点云"));
	viewer->setBackgroundColor(0.1, 0.1, 0.1);
	viewer->addText("filtered point clouds", 10, 10, "v2_text");
	// 按照z字段进行渲染,将z改为x或y即为按照x或y字段渲染
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> fildColor(ptrCloud, "z");
	viewer->addPointCloud<pcl::PointXYZ>(ptrFilterCloud, "cloud_filtered");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 0, 1, 0, "cloud_filtered");
	//viewer->addCoordinateSystem(1.0);
	//viewer->initCameraParameters();
	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
}
//直通滤波
void CPointCloud::PC_PassThrough(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2(new pcl::PointCloud<pcl::PointXYZ>); //PointXYZ 数据结构
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_medium(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PCDReader reader;
	reader.read(sFile, *cloud2);

	pcl::PassThrough<pcl::PointXYZ> pass;
	pass.setInputCloud(cloud2);
	pass.setFilterFieldName("z");
	//pass.setFilterLimitsNegative(false);  不用写了，版本升级
	pass.setFilterLimits(0.0,1.0);
	pass.filter(*cloud_medium);

	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_medium, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
	
}
//统计滤波
void CPointCloud::PC_StatisticalFilter(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
	//读入点云数据
	pcl::PCDReader reader;
	reader.read<pcl::PointXYZ>(sFile, *cloud);
	cout << "Cloud before filtering:\n " << *cloud << endl;
	// -----------------统计滤波-------------------
	// 创建滤波器，对每个点分析的临近点的个数设置为50 ，并将标准差的倍数设置为1  这意味着如果一
	// 个点的距离超出了平均距离一个标准差以上，则该点被标记为离群点，并将它移除，存储起来
	pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
	sor.setInputCloud(cloud);   //设置待滤波的点云
	sor.setMeanK(50);           //设置在进行统计时考虑查询点邻近点数
	sor.setStddevMulThresh(1);  //设置判断是否为离群点的阈值，里边的数字表示标准差的倍数，1个标准差以上就是离群点。
	//即：当判断点的k近邻平均距离(mean distance)大于全局的1倍标准差+平均距离(global distances mean and standard)，则为离群点。


	sor.filter(*cloud_filtered); //存储内点
	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_filtered, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//x轴渲染
void CPointCloud::PC_XRender(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	pcl::io::loadPCDFile(sFile, *cloud);
	PointT min;
	PointT max;
	pcl::getMinMax3D(*cloud, min, max);
	float L;
	float L_2;
	L = max.x - min.x;
	L_2 = L / 2.0;
	for (size_t i = 0; i < cloud->size(); ++i)
	{
		if ((cloud->points[i].x - min.x) < L_2)
		{
			cloud->points[i].r = 0;
			cloud->points[i].g = (255 * ((cloud->points[i].x - min.x) / L_2));
			cloud->points[i].b = (255 * (1 - ((cloud->points[i].x - min.x) / L_2)));
		}
		else
		{
			cloud->points[i].r = (255 * (cloud->points[i].x - min.x - L_2) / L_2);
			cloud->points[i].g = (255 * (1 - (cloud->points[i].x - min.x - L_2) / L_2));
			cloud->points[i].b = 0;
		}
	}

	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<PointT>(cloud, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
	
	
}
//y轴渲染
void CPointCloud::PC_YRender(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	pcl::io::loadPCDFile(sFile, *cloud);
	PointT min;
	PointT max;
	pcl::getMinMax3D(*cloud, min, max);
	float L;
	float L_2;
	L = max.y - min.y;
	L_2 = L / 2.0;
	for (size_t i = 0; i < cloud->size(); ++i)
	{
		if ((cloud->points[i].y - min.y) < L_2)
		{
			cloud->points[i].r = 0;
			cloud->points[i].g = (255 * ((cloud->points[i].y - min.y) / L_2));
			cloud->points[i].b = (255 * (1 - ((cloud->points[i].y - min.y) / L_2)));
		}
		else
		{
			cloud->points[i].r = (255 * (cloud->points[i].y - min.y - L_2) / L_2);
			cloud->points[i].g = (255 * (1 - (cloud->points[i].y - min.y - L_2) / L_2));
			cloud->points[i].b = 0;
		}
	}
	/*
	pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("点云渲染"));
	viewer->addPointCloud<PointT>(cloud);
	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	*/

	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<PointT>(cloud, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//z轴渲染
void CPointCloud::PC_ZRender(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	pcl::io::loadPCDFile(sFile, *cloud);
	PointT min;
	PointT max;
	pcl::getMinMax3D(*cloud, min, max);
	float L;
	float L_2;
	L = max.z - min.z;
	L_2 = L / 2.0;
	for (size_t i = 0; i < cloud->size(); ++i)
	{
		if ((cloud->points[i].z - min.z) < L_2)
		{
			cloud->points[i].r = 0;
			cloud->points[i].g = (255 * ((cloud->points[i].z - min.z) / L_2));
			cloud->points[i].b = (255 * (1 - ((cloud->points[i].z - min.z) / L_2)));
		}
		else
		{
			cloud->points[i].r = (255 * (cloud->points[i].z - min.z - L_2) / L_2);
			cloud->points[i].g = (255 * (1 - (cloud->points[i].z - min.z - L_2) / L_2));
			cloud->points[i].b = 0;
		}
	}


	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<PointT>(cloud, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();

}
//高斯滤波
void CPointCloud::PC_GaussianFilter(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{

	//------------------加载数据------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile(sFile, *cloud) == -1)
	{
		PCL_ERROR("Couldn't read file pcd\n");
		
	}

	//-----------基于高斯核函数的卷积滤波实现------------------------
	pcl::filters::GaussianKernel<pcl::PointXYZ, pcl::PointXYZ> kernel;
	kernel.setSigma(4);//高斯函数的标准方差，决定函数的宽度
	kernel.setThresholdRelativeToSigma(4);//设置相对Sigma参数的距离阈值
	kernel.setThreshold(0.05);//设置距离阈值，若点间距离大于阈值则不予考虑
	cout << "Kernel made" << endl;

	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud);
	cout << "KdTree made" << endl;

	//---------设置Convolution 相关参数---------------------------
	pcl::filters::Convolution3D<pcl::PointXYZ, pcl::PointXYZ, pcl::filters::GaussianKernel<pcl::PointXYZ, pcl::PointXYZ>> convolution;
	convolution.setKernel(kernel);//设置卷积核
	convolution.setInputCloud(cloud);
	convolution.setNumberOfThreads(8);
	convolution.setSearchMethod(tree);
	convolution.setRadiusSearch(0.01);
	cout << "Convolution Start" << endl;

	convolution.convolve(*cloud_filtered);
	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_filtered, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
	
}
//半径滤波
void CPointCloud::PC_RadiusFilter(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	// ------------------------------读取点云数据-------------------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in(new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile(sFile, *cloud_in) < 0)
	{
		PCL_ERROR("Could not read file\n");
		
	}

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_radius(new pcl::PointCloud<pcl::PointXYZ>);
	// -------------------------------半径滤波----------------------------------------
	pcl::StopWatch time;
	pcl::RadiusOutlierRemoval<pcl::PointXYZ> ror;
	ror.setInputCloud(cloud_in);     // 输入点云
	ror.setRadiusSearch(0.1);        // 设置半径为0.1m范围内找临近点
	ror.setMinNeighborsInRadius(10); // 设置查询点的邻域点集数小于10删除
	ror.filter(*cloud_radius);       // 执行滤波
	//pcl::io::savePCDFileASCII("cloud_radius.pcd", *cloud_radius);
	// -----------------------------结果可视化----------------------------------------

	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_radius, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//条件滤波
void CPointCloud::PC_ConditionFilter(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{	
	// ------------------------------读取点云数据-------------------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_conditional(new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud_in) != 0)
	{
		
	}


	//--------------创建滤波器并用条件定义对象初始化---------------
	// 1、定义条件滤波器所要使用的条件
	// (1.1)字段条件
	pcl::ConditionAnd<pcl::PointXYZ>::Ptr range_cond(new pcl::ConditionAnd<pcl::PointXYZ>);//实例化条件指针
	// 添加在Z字段上大于（pcl::ComparisonOps::GT　great Then）13的比较算子
	range_cond->addComparison(pcl::FieldComparison<pcl::PointXYZ>::ConstPtr(new
		pcl::FieldComparison<pcl::PointXYZ>("z", pcl::ComparisonOps::GT, 13.0)));
	// 添加在Z字段上小于（pcl::ComparisonOps::LT　Lower Then）15的比较算子
	range_cond->addComparison(pcl::FieldComparison<pcl::PointXYZ>::ConstPtr(new
		pcl::FieldComparison<pcl::PointXYZ>("z", pcl::ComparisonOps::LT, 15.0)));
	/* (1.2)曲率条件
	  // 创建条件定义对象  曲率
	pcl::ConditionOr<PointNormal>::Ptr range_cond (new pcl::ConditionOr<PointNormal> () );

	range_cond->addComparison (pcl::FieldComparison<PointNormal>::ConstPtr (// 曲率 大于
	 new pcl::FieldComparison<PointNormal>("curvature", pcl::ComparisonOps::GT, threshold))
	 */
	 // 2、使用条件滤波器
	pcl::ConditionalRemoval<pcl::PointXYZ> condrem; // 创建条件滤波器
	condrem.setCondition(range_cond);               // 并用条件定义对象初始化     
	condrem.setInputCloud(cloud_in);                // 输入点云
	condrem.setKeepOrganized(true);                 // 设置true则保持点云的结构，保存原有点云结结构就是点的数目没有减少，采用nan代替了。
													// 设置为false则不需要 4、去除nan点的操作
	 // 3、执行滤波
	condrem.filter(*cloud_conditional);             // 不在条件范围内的点　被替换为　nan
	// 4、去除nan点
	std::vector<int> mapping;
	pcl::removeNaNFromPointCloud(*cloud_conditional, *cloud_conditional, mapping);
	//pcl::io::savePCDFileASCII("cloud_conditional.pcd", *cloud_conditional);
	VisualizeCloud(cloud_in, cloud_conditional);
}
//均匀采样

void CPointCloud::PC_UniformSampling(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	// ------------------------------读取点云数据-------------------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud) != 0)
	{
	
	}

	//cout << "原始点云个数：" << cloud->points.size() << endl;
	// ----------------创建均匀采样对象-------------------------
	pcl::UniformSampling<pcl::PointXYZ> US;
	US.setInputCloud(cloud);
	US.setRadiusSearch(0.005f);// 设置滤波时创建球体的半径
	US.filter(*cloud_filtered);
	//cout << "均匀采样之后点云的个数：" << cloud_filtered->points.size() << endl;
	//---------------------显示点云-----------------------
	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_filtered, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//随机采样
void Visualize_Clouds(pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr& filter_cloud) {
	//---------显示点云-----------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("显示点云"));
	viewer->setBackgroundColor(0.1, 0.1, 0.1);
	viewer->addText("filtered point clouds", 10, 10, "v2_text");
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> fildColor(cloud, "z"); // 按照z字段进行渲染,将z改为x或y即为按照x或y字段渲染
	viewer->addPointCloud<pcl::PointXYZ>(filter_cloud, "cloud_filtered");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 255, 255, 255, "cloud_filtered");
	//viewer->addCoordinateSystem(1.0);
	//viewer->initCameraParameters();
	
}
void CPointCloud::PC_RandomSampling(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	// ----------------------------加载点云-----------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud) == -1)
	{
		PCL_ERROR("读取源标点云失败 \n");
	}
	cout << "从点云中读取 " << cloud->size() << " 个点" << endl;
	//-----------------------采样固定的点云数量-------------------------
	pcl::RandomSample<pcl::PointXYZ> rs_src;
	rs_src.setInputCloud(cloud);
	rs_src.setSample(3000);// 设置要采样的点云个数
	//rs_src.setSeed(8);   // 设置随机函数的种子点
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_rsf(new pcl::PointCloud<pcl::PointXYZ>);
	rs_src.filter(*cloud_rsf);
	//pcl::io::savePCDFileASCII ("1111.pcd", *cloud_rsf);
	cout << "随机采样后的点云个数为：" << cloud_rsf->points.size() << endl;

	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_rsf, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//法线空间采样
void estimate_normals(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointCloud<pcl::Normal>::Ptr normals)
{
	pcl::NormalEstimationOMP<pcl::PointXYZ, pcl::Normal> n;
	n.setInputCloud(cloud_in);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
	n.setSearchMethod(tree);
	n.setNumberOfThreads(8);
	n.setKSearch(30);
	n.compute(*normals);
}
void VisualizeClouds(pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr& filter_cloud) {
	//---------显示点云-----------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("显示点云"));
	viewer->setBackgroundColor(0.1, 0.1, 0.1);
	viewer->addText("filtered point clouds", 10, 10, "v2_text");
	// 按照z字段进行渲染,将z改为x或y即为按照x或y字段渲染
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> fildColor(cloud, "z");
	viewer->addPointCloud<pcl::PointXYZ>(filter_cloud, "cloud_filtered");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 255, 255, 255, "cloud_filtered");
	//viewer->addCoordinateSystem(1.0);
	//viewer->initCameraParameters();
	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
}
void CPointCloud::PC_NormalSampling(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	// -----------------------加载点云--------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud) == -1)
	{
		PCL_ERROR("读取源标点云失败 \n");
	}
	cout << "从点云中读取 " << cloud->size() << " 个点" << endl;
	//------------------------计算法向量----------------------
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	estimate_normals(cloud, normals);
	//-----------------------法线空间采样---------------------
	pcl::NormalSpaceSampling<pcl::PointXYZ, pcl::Normal> nss;
	nss.setInputCloud(cloud);// 设置输入点云
	nss.setNormals(normals);// 设置在输入点云上计算的法线
	nss.setBins(2, 2, 2);// 设置x,y,z方向bins的个数
	nss.setSeed(0); // 设置种子点
	nss.setSample(1000); // 设置要采样的索引数。
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_nss(new pcl::PointCloud<pcl::PointXYZ>);
	nss.filter(*cloud_nss);
	pcl::io::savePCDFileASCII("nss.pcd", *cloud_nss);
	cout << "法线空间采样后的点云个数为：" << cloud_nss->points.size() << endl;

	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_nss, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//体素滤波
void CPointCloud::PC_VoxelFilter(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	// --------------------------------加载点云----------------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud);
	//cout << "从点云中读取 " << cloud->size() << " 个点" << endl;
	// ---------------------------ApproximateVoxelGrid---------------------------
	pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::ApproximateVoxelGrid<pcl::PointXYZ> avf;
	avf.setInputCloud(cloud);         // 输入点云
	avf.setLeafSize(0.01, 0.01, 0.01);// 最小体素的边长
	avf.filter(*filtered_cloud);      // 进行滤波
	//pcl::io::savePCDFileASCII ("filtered.pcd", *filtered_cloud); // 保存滤波结果
	cout << "体素中心点滤波完毕！！！" << endl;
	cout << "滤波后点的个数为：" << filtered_cloud->size() << endl;
	// ---------------------------------结果可视化-------------------------------
//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(filtered_cloud, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//重置点云
void CPointCloud::PC_ReturnPcl(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString格式转String格式
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud);
	//初始化点云数据
	m_spViewer->removeAllPointClouds();
	//添加点云数据
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
	m_spViewer->resetCamera();//使点云显示在屏幕中间，并绕中心操作
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}