#include "GetInitClusterCenter.h"
//#include "ClassModel.h"

#include <cmath>
#include <limits>

//聚集出的类数量，也就是clustercenter的数量
int num= 0;

double getDistance(const model &source, const model &dest);
double getThreshold(const model *data, int n);

int getClusterCenterNum()
{
    return num;
}

centerModel *getInitClusterCenter(model *originData, int n)
{
	//原始数据计算出阙值t
	double t = getThreshold(originData, n);

	//所有的聚类中心
	centerModel xy[n];

	//step 1
	//第一个中心为第一个样本
	originData[0].centerFlag = 1;
    originData[0].calcClass = num;
	xy[0] = originData[0];
	xy[0].idxOfOrigin = 0;
    xy[0].calcClass = num;
	num++;//num=1

	//寻找第二个样本
	double maxValue = 0;
	int maxIdx = 1;
	for (int i=1; i<n; i++)
	{
		double temp = getDistance(xy[0], originData[i]);

		if (temp>maxValue)
		{
			maxValue = temp;
			maxIdx = i;
		}
	}	
	originData[maxIdx].centerFlag = 1;
    originData[maxIdx].calcClass = num;
	xy[1] = originData[maxIdx];
	xy[1].idxOfOrigin = maxIdx;
    xy[1].calcClass = num;
	num++;	//num=2

    do
    {
//	double a = getThreshold(xy, num);

	//step 2
        maxValue = std::numeric_limits<double>::min();
	for (int i=0; i<n; i++)
	{
		//如果样本originData[i]是cluster center，则跳过
		if (originData[i].centerFlag)
			continue;
		double minValue = std::numeric_limits<double>::max();
		for (int j=0; j<num; j++)
		{
			double temp = getDistance(originData[i], xy[j]);
			if (temp<minValue)
			{
				minValue = temp;
			}
		}
		if (minValue>maxValue)
		{
			maxValue = minValue;
            maxIdx = i;
		}
	}
        if (maxValue<t)
        {
            break;
        }
        //产生新的cluster center
        originData[maxIdx].centerFlag = 1;
        originData[maxIdx].calcClass = num;
        xy[num] = originData[maxIdx];
        xy[num].idxOfOrigin = maxIdx;
        xy[num].calcClass = num;
        num++;
        
    } while (num<n);

	return xy;
}

double getDistance(const model &source, const model &dest)
{
	double temp;
	temp = (dest.x-source.x)*(dest.x-source.x)+
		(dest.y-source.y)*(dest.y-source.y)+
		(dest.z-source.z)*(dest.z-source.z)+
		(dest.w-source.w)*(dest.w-source.w);
	temp = sqrt(temp);

	return temp;
}

//根据欧几里德范式计算阙值
double getThreshold(const model *data, int n)
{
    int temp = 0;
	double t = 0;
	for (int i=0; i<n; i++)
	{
		for (int j=i+1; j<n; j++)
		{
			t += getDistance(data[i], data[j]);
            temp++;
		}
	}
	t /= temp;

	return t;
}

