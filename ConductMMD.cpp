#include "ConductMMD.h"
#include <limits>
#include <cmath>

double t;
int number = 0;

double getThresholdd(const model *data, int n);

double getDIST(const model &source, const model &dest);

centerModel *conductMMD(model *originData, int n)
{
    //原始数据计算出阙值t
	t = getThresholdd(originData, n);
    
    //所有的聚类中心
	centerModel yy[n];
    
	//step 1
	//第一个中心为第一个样本
	originData[0].centerFlag = 1;
    originData[0].calcClass = number;
	yy[0] = originData[0];
	yy[0].idxOfOrigin = 0;
    yy[0].calcClass = number;
	number++;//number=1
    
	//寻找第二个样本
	double maxValue = 0;
	int maxIdx = 1;
	for (int i=1; i<n; i++)
	{
		double temp = getDIST(yy[0], originData[i]);
        
		if (temp>maxValue)
		{
			maxValue = temp;
			maxIdx = i;
		}
	}
	originData[maxIdx].centerFlag = 1;
    originData[maxIdx].calcClass = number;
	yy[1] = originData[maxIdx];
	yy[1].idxOfOrigin = maxIdx;
    yy[1].calcClass = number;
	number++;	//number=2
    
    do
    {
        //	double a = getThreshold(yy, number);
        
        //step 2
        maxValue = std::numeric_limits<double>::min();
        for (int i=0; i<n; i++)
        {
            //如果样本originData[i]是cluster center，则跳过
            if (originData[i].centerFlag)
                continue;
            double minValue = std::numeric_limits<double>::max();
            for (int j=0; j<number; j++)
            {
                double temp = getDIST(originData[i], yy[j]);
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
        originData[maxIdx].calcClass = number;
        yy[number] = originData[maxIdx];
        yy[number].idxOfOrigin = maxIdx;
        yy[number].calcClass = number;
        number++;
    } while (number<n);
    
    for (int i=0; i<n; i++)
    {
        double minValue = std::numeric_limits<double>::max();
        int minIdx = 0;
        for (int j=0; j<number; j++)
        {
            double temp = getDIST(originData[i], yy[j]);
            if (temp<minValue)
            {
                minValue = temp;
                minIdx = j;
            }
        }
        originData[i].calcClass = yy[minIdx].calcClass;
    }//for i
    return yy;
}

//根据欧几里德范式计算阙值
double getThresholdd(const model *data, int n)
{
    int temp = 0;
	double t = 0;
	for (int i=0; i<n; i++)
	{
		for (int j=i+1; j<n; j++)
		{
			t += getDIST(data[i], data[j]);
            temp++;
		}
	}
	t /= temp;
    
	return t;
}
double getDIST(const model &source, const model &dest)
{
	double temp;
	temp = (dest.x-source.x)*(dest.x-source.x)+
    (dest.y-source.y)*(dest.y-source.y)+
    (dest.z-source.z)*(dest.z-source.z)+
    (dest.w-source.w)*(dest.w-source.w);
	temp = sqrt(temp);
    
	return temp;
}
double getT()
{
    return t;
}
int getNumber()
{
	return number;
}
