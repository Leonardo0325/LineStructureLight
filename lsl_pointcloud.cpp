#include "pch.h"
#include "lsl_pointcloud.h"
//�򿪵����ļ�
void CPointCloud::PC_OpenPointCloud(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	//���ļ�*.pcd *.ply *.obj
	CString sDefaultDir = _T("��ѡ��·��"); //����Ĭ�ϴ��ļ���
	CString sFileFilter = _T("�ļ�(*.pcd;*.ply;*.obj)|*.pcd;*.ply;*.obj|All File (*.*)|*.*||"); //�����ļ�����
	CFileDialog FileDlg(true, sDefaultDir, _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sFileFilter, NULL);
	//����ѡ���ļ��Ի���
	if (FileDlg.DoModal() == IDOK)
	{
		sFilePath = FileDlg.GetPathName();//�õ��������ļ�����Ŀ¼����չ��  
		CString sFilename = FileDlg.GetFileName();
	}
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
	//std::string sFilename = "huba_part.pcd";
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile(sFile, *cloud);          //�������

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, 255, 255, 255);	//���õ�����ɫ
	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud, single_color, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
void CPointCloud::PC_LslToPcl()
{
}
void VisualizeCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr& ptrCloud, pcl::PointCloud<pcl::PointXYZ>::Ptr& ptrFilterCloud) {
	//-----------------------��ʾ����-----------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("��ʾ����"));
	viewer->setBackgroundColor(0.1, 0.1, 0.1);
	viewer->addText("filtered point clouds", 10, 10, "v2_text");
	// ����z�ֶν�����Ⱦ,��z��Ϊx��y��Ϊ����x��y�ֶ���Ⱦ
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
//ֱͨ�˲�
void CPointCloud::PC_PassThrough(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2(new pcl::PointCloud<pcl::PointXYZ>); //PointXYZ ���ݽṹ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_medium(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PCDReader reader;
	reader.read(sFile, *cloud2);

	pcl::PassThrough<pcl::PointXYZ> pass;
	pass.setInputCloud(cloud2);
	pass.setFilterFieldName("z");
	//pass.setFilterLimitsNegative(false);  ����д�ˣ��汾����
	pass.setFilterLimits(0.0,1.0);
	pass.filter(*cloud_medium);

	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_medium, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
	
}
//ͳ���˲�
void CPointCloud::PC_StatisticalFilter(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
	//�����������
	pcl::PCDReader reader;
	reader.read<pcl::PointXYZ>(sFile, *cloud);
	cout << "Cloud before filtering:\n " << *cloud << endl;
	// -----------------ͳ���˲�-------------------
	// �����˲�������ÿ����������ٽ���ĸ�������Ϊ50 ��������׼��ı�������Ϊ1  ����ζ�����һ
	// ����ľ��볬����ƽ������һ����׼�����ϣ���õ㱻���Ϊ��Ⱥ�㣬�������Ƴ����洢����
	pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
	sor.setInputCloud(cloud);   //���ô��˲��ĵ���
	sor.setMeanK(50);           //�����ڽ���ͳ��ʱ���ǲ�ѯ���ڽ�����
	sor.setStddevMulThresh(1);  //�����ж��Ƿ�Ϊ��Ⱥ�����ֵ����ߵ����ֱ�ʾ��׼��ı�����1����׼�����Ͼ�����Ⱥ�㡣
	//�������жϵ��k����ƽ������(mean distance)����ȫ�ֵ�1����׼��+ƽ������(global distances mean and standard)����Ϊ��Ⱥ�㡣


	sor.filter(*cloud_filtered); //�洢�ڵ�
	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_filtered, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//x����Ⱦ
void CPointCloud::PC_XRender(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
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

	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<PointT>(cloud, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
	
	
}
//y����Ⱦ
void CPointCloud::PC_YRender(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
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
	pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("������Ⱦ"));
	viewer->addPointCloud<PointT>(cloud);
	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	*/

	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<PointT>(cloud, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//z����Ⱦ
void CPointCloud::PC_ZRender(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
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


	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<PointT>(cloud, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();

}
//��˹�˲�
void CPointCloud::PC_GaussianFilter(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{

	//------------------��������------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile(sFile, *cloud) == -1)
	{
		PCL_ERROR("Couldn't read file pcd\n");
		
	}

	//-----------���ڸ�˹�˺����ľ���˲�ʵ��------------------------
	pcl::filters::GaussianKernel<pcl::PointXYZ, pcl::PointXYZ> kernel;
	kernel.setSigma(4);//��˹�����ı�׼������������Ŀ��
	kernel.setThresholdRelativeToSigma(4);//�������Sigma�����ľ�����ֵ
	kernel.setThreshold(0.05);//���þ�����ֵ���������������ֵ���迼��
	cout << "Kernel made" << endl;

	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud);
	cout << "KdTree made" << endl;

	//---------����Convolution ��ز���---------------------------
	pcl::filters::Convolution3D<pcl::PointXYZ, pcl::PointXYZ, pcl::filters::GaussianKernel<pcl::PointXYZ, pcl::PointXYZ>> convolution;
	convolution.setKernel(kernel);//���þ����
	convolution.setInputCloud(cloud);
	convolution.setNumberOfThreads(8);
	convolution.setSearchMethod(tree);
	convolution.setRadiusSearch(0.01);
	cout << "Convolution Start" << endl;

	convolution.convolve(*cloud_filtered);
	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_filtered, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
	
}
//�뾶�˲�
void CPointCloud::PC_RadiusFilter(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	// ------------------------------��ȡ��������-------------------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in(new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile(sFile, *cloud_in) < 0)
	{
		PCL_ERROR("Could not read file\n");
		
	}

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_radius(new pcl::PointCloud<pcl::PointXYZ>);
	// -------------------------------�뾶�˲�----------------------------------------
	pcl::StopWatch time;
	pcl::RadiusOutlierRemoval<pcl::PointXYZ> ror;
	ror.setInputCloud(cloud_in);     // �������
	ror.setRadiusSearch(0.1);        // ���ð뾶Ϊ0.1m��Χ�����ٽ���
	ror.setMinNeighborsInRadius(10); // ���ò�ѯ�������㼯��С��10ɾ��
	ror.filter(*cloud_radius);       // ִ���˲�
	//pcl::io::savePCDFileASCII("cloud_radius.pcd", *cloud_radius);
	// -----------------------------������ӻ�----------------------------------------

	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_radius, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//�����˲�
void CPointCloud::PC_ConditionFilter(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{	
	// ------------------------------��ȡ��������-------------------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_conditional(new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud_in) != 0)
	{
		
	}


	//--------------�����˲�������������������ʼ��---------------
	// 1�����������˲�����Ҫʹ�õ�����
	// (1.1)�ֶ�����
	pcl::ConditionAnd<pcl::PointXYZ>::Ptr range_cond(new pcl::ConditionAnd<pcl::PointXYZ>);//ʵ��������ָ��
	// �����Z�ֶ��ϴ��ڣ�pcl::ComparisonOps::GT��great Then��13�ıȽ�����
	range_cond->addComparison(pcl::FieldComparison<pcl::PointXYZ>::ConstPtr(new
		pcl::FieldComparison<pcl::PointXYZ>("z", pcl::ComparisonOps::GT, 13.0)));
	// �����Z�ֶ���С�ڣ�pcl::ComparisonOps::LT��Lower Then��15�ıȽ�����
	range_cond->addComparison(pcl::FieldComparison<pcl::PointXYZ>::ConstPtr(new
		pcl::FieldComparison<pcl::PointXYZ>("z", pcl::ComparisonOps::LT, 15.0)));
	/* (1.2)��������
	  // ���������������  ����
	pcl::ConditionOr<PointNormal>::Ptr range_cond (new pcl::ConditionOr<PointNormal> () );

	range_cond->addComparison (pcl::FieldComparison<PointNormal>::ConstPtr (// ���� ����
	 new pcl::FieldComparison<PointNormal>("curvature", pcl::ComparisonOps::GT, threshold))
	 */
	 // 2��ʹ�������˲���
	pcl::ConditionalRemoval<pcl::PointXYZ> condrem; // ���������˲���
	condrem.setCondition(range_cond);               // ����������������ʼ��     
	condrem.setInputCloud(cloud_in);                // �������
	condrem.setKeepOrganized(true);                 // ����true�򱣳ֵ��ƵĽṹ������ԭ�е��ƽ�ṹ���ǵ����Ŀû�м��٣�����nan�����ˡ�
													// ����Ϊfalse����Ҫ 4��ȥ��nan��Ĳ���
	 // 3��ִ���˲�
	condrem.filter(*cloud_conditional);             // ����������Χ�ڵĵ㡡���滻Ϊ��nan
	// 4��ȥ��nan��
	std::vector<int> mapping;
	pcl::removeNaNFromPointCloud(*cloud_conditional, *cloud_conditional, mapping);
	//pcl::io::savePCDFileASCII("cloud_conditional.pcd", *cloud_conditional);
	VisualizeCloud(cloud_in, cloud_conditional);
}
//���Ȳ���

void CPointCloud::PC_UniformSampling(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	// ------------------------------��ȡ��������-------------------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud) != 0)
	{
	
	}

	//cout << "ԭʼ���Ƹ�����" << cloud->points.size() << endl;
	// ----------------�������Ȳ�������-------------------------
	pcl::UniformSampling<pcl::PointXYZ> US;
	US.setInputCloud(cloud);
	US.setRadiusSearch(0.005f);// �����˲�ʱ��������İ뾶
	US.filter(*cloud_filtered);
	//cout << "���Ȳ���֮����Ƶĸ�����" << cloud_filtered->points.size() << endl;
	//---------------------��ʾ����-----------------------
	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_filtered, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//�������
void Visualize_Clouds(pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr& filter_cloud) {
	//---------��ʾ����-----------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("��ʾ����"));
	viewer->setBackgroundColor(0.1, 0.1, 0.1);
	viewer->addText("filtered point clouds", 10, 10, "v2_text");
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> fildColor(cloud, "z"); // ����z�ֶν�����Ⱦ,��z��Ϊx��y��Ϊ����x��y�ֶ���Ⱦ
	viewer->addPointCloud<pcl::PointXYZ>(filter_cloud, "cloud_filtered");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 255, 255, 255, "cloud_filtered");
	//viewer->addCoordinateSystem(1.0);
	//viewer->initCameraParameters();
	
}
void CPointCloud::PC_RandomSampling(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	// ----------------------------���ص���-----------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud) == -1)
	{
		PCL_ERROR("��ȡԴ�����ʧ�� \n");
	}
	cout << "�ӵ����ж�ȡ " << cloud->size() << " ����" << endl;
	//-----------------------�����̶��ĵ�������-------------------------
	pcl::RandomSample<pcl::PointXYZ> rs_src;
	rs_src.setInputCloud(cloud);
	rs_src.setSample(3000);// ����Ҫ�����ĵ��Ƹ���
	//rs_src.setSeed(8);   // ����������������ӵ�
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_rsf(new pcl::PointCloud<pcl::PointXYZ>);
	rs_src.filter(*cloud_rsf);
	//pcl::io::savePCDFileASCII ("1111.pcd", *cloud_rsf);
	cout << "���������ĵ��Ƹ���Ϊ��" << cloud_rsf->points.size() << endl;

	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_rsf, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//���߿ռ����
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
	//---------��ʾ����-----------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("��ʾ����"));
	viewer->setBackgroundColor(0.1, 0.1, 0.1);
	viewer->addText("filtered point clouds", 10, 10, "v2_text");
	// ����z�ֶν�����Ⱦ,��z��Ϊx��y��Ϊ����x��y�ֶ���Ⱦ
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
	// -----------------------���ص���--------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud) == -1)
	{
		PCL_ERROR("��ȡԴ�����ʧ�� \n");
	}
	cout << "�ӵ����ж�ȡ " << cloud->size() << " ����" << endl;
	//------------------------���㷨����----------------------
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	estimate_normals(cloud, normals);
	//-----------------------���߿ռ����---------------------
	pcl::NormalSpaceSampling<pcl::PointXYZ, pcl::Normal> nss;
	nss.setInputCloud(cloud);// �����������
	nss.setNormals(normals);// ��������������ϼ���ķ���
	nss.setBins(2, 2, 2);// ����x,y,z����bins�ĸ���
	nss.setSeed(0); // �������ӵ�
	nss.setSample(1000); // ����Ҫ��������������
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_nss(new pcl::PointCloud<pcl::PointXYZ>);
	nss.filter(*cloud_nss);
	pcl::io::savePCDFileASCII("nss.pcd", *cloud_nss);
	cout << "���߿ռ������ĵ��Ƹ���Ϊ��" << cloud_nss->points.size() << endl;

	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud_nss, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//�����˲�
void CPointCloud::PC_VoxelFilter(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	// --------------------------------���ص���----------------------------------
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud);
	//cout << "�ӵ����ж�ȡ " << cloud->size() << " ����" << endl;
	// ---------------------------ApproximateVoxelGrid---------------------------
	pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::ApproximateVoxelGrid<pcl::PointXYZ> avf;
	avf.setInputCloud(cloud);         // �������
	avf.setLeafSize(0.01, 0.01, 0.01);// ��С���صı߳�
	avf.filter(*filtered_cloud);      // �����˲�
	//pcl::io::savePCDFileASCII ("filtered.pcd", *filtered_cloud); // �����˲����
	cout << "�������ĵ��˲���ϣ�����" << endl;
	cout << "�˲����ĸ���Ϊ��" << filtered_cloud->size() << endl;
	// ---------------------------------������ӻ�-------------------------------
//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<pcl::PointXYZ>(filtered_cloud, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}
//���õ���
void CPointCloud::PC_ReturnPcl(boost::shared_ptr<pcl::visualization::PCLVisualizer>& m_spViewer,
	vtkRenderWindowInteractor* m_rwndinIren,
	vtkRenderWindow* m_rwndRenWin, CString& sFilePath)
{
	string sFile = CT2A(sFilePath.GetBuffer());   //CString��ʽתString��ʽ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile<pcl::PointXYZ>(sFile, *cloud);
	//��ʼ����������
	m_spViewer->removeAllPointClouds();
	//��ӵ�������
	m_spViewer->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
	m_spViewer->resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
	m_rwndinIren->Render();
	m_rwndRenWin->Render();
}