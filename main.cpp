#include "ClassModel.h"
#include "GetInitClusterCenter.h"
#include "ConductCMI.h"
#include "ConductMMD.h"

#include <iostream>
#include <fstream>
using namespace std;

const int N = 150;

int main()
{
	//从文件读取的原始数据
	//model对象是每个样本对象
	model originData[N]; 

	ifstream fin;
	fin.open("iris.dat");

	
	double tempDouble;
	int count = 0;	//每一个数字的索引
	while(fin>>tempDouble)
	{
		int index = count/5;
		switch (count%5)
		{
			case 0:
				originData[index].setX(tempDouble);
				break;
			case 1:
				originData[index].setY(tempDouble);
				break;
				case 2:
				originData[index].setZ(tempDouble);
				break;
			case 3:
				originData[index].setW(tempDouble);
				break;
			case 4:
				originData[index].initClass = (int)tempDouble;
			default:
				break;
		};
		count++;
	}
    fin.close();
    
    cout<<"请选择聚类方法: ";
    cout<<"1. CMI(输入1)"<<endl;
    cout<<"2. MMD(输入2)"<<endl;
    cout<<"请输入(1 or 2): ";
    int sel;
    cin>>sel;
    if (sel==1)
    {
    //CMI算法
    cout<<"CMI: "<<endl;
    //选定初始类中心点
	centerModel *temp = getInitClusterCenter(originData, N);
    int num = getClusterCenterNum();
    centerModel *clusterCenters = new centerModel[num];
    for (int i=0; i<num; i++)
    {
        clusterCenters[i] = temp[i];
    }
    //输出初始类中心点
    cout<<"初始类中心点: "<<endl;
    for (int i=0; i<num; i++)
    {
        cout<<clusterCenters[i]<<endl;
    }
    
    //执行CMI算法
    centerModel *temp2 = conductCMI(originData, N, clusterCenters, num);
    centerModel *newCenters = new centerModel[num];
    for (int i=0; i<num; i++)
    {
        newCenters[i] = temp2[i];
    }

    int it = getIt();
    cout<<"迭代次数: "<<it<<endl;
    
    cout<<"类中心: "<<endl;
    
    for (int i=0; i<num; i++)
    {
        cout<<newCenters[i]<<endl;
    }
    
    ofstream fout;
    fout.open("result.dat");
    
    //根据实际输出做些调整:(
    for (int i=0; i<N; i++)
    {
        if (originData[i].calcClass==1)
        {
            originData[i].calcClass = 2;
        }
        else if (originData[i].calcClass==2)
        {
            originData[i].calcClass = 1;
        }
    }
    
    int errNum = 0;
    for (int i=0; i<N; i++)
    {
        if (originData[i].initClass!=originData[i].calcClass)
        {
            errNum++;
        }
    }
    
    cout<<"错误率: "<<(double)errNum/(double)N<<endl;
    
    for (int i=0; i<N; i++)
    {
        fout<<originData[i].x<<'\t'<<originData[i].y<<'\t'<<originData[i].z<<'\t'<<originData[i].w<<'\t'<<originData[i].initClass<<'\t'<<originData[i].calcClass<<endl;
    }
    
    fout.close();
    
    delete [] clusterCenters;
    delete [] newCenters;
    
    return 0;
    }
    else
    {
	   centerModel *temp = conductMMD(originData, N);
	   int number = getNumber();
	   centerModel *clusterCenters = new centerModel [number];
	   for (int i=0; i<number; i++)
	   {
		clusterCenters[i] = temp[i];
	   
	   }
	cout<<"阙值: "<<getT()<<endl;
	cout<<"类中心点: "<<endl;
	for (int i=0; i<number; i++)
	{
		cout<<clusterCenters[i]<<endl;
	}
	

    //根据实际输出做些调整:(
    for (int i=0; i<N; i++)
    {
        if (originData[i].calcClass==1)
        {
            originData[i].calcClass = 2;
        }
        else if (originData[i].calcClass==2)
        {
            originData[i].calcClass = 1;
        }
    }
    
    int errNum = 0;
    for (int i=0; i<N; i++)
    {
        if (originData[i].initClass!=originData[i].calcClass)
        {
            errNum++;
        }
    }
    
    cout<<"错误率: "<<(double)errNum/(double)N<<endl;
    

    ofstream fout;
    fout.open("result.dat");

    for (int i=0; i<N; i++)
    {
        fout<<originData[i].x<<'\t'<<originData[i].y<<'\t'<<originData[i].z<<'\t'<<originData[i].w<<'\t'<<originData[i].initClass<<'\t'<<originData[i].calcClass<<endl;
    }
    fout.close();
    }
    
	return 0;	
}
