#include "ConductCMI.h"
//#include "ClassModel.h"

#include <cmath>
#include <limits>
//迭代次数
int it = 0;

double getDist(const model &source, const model &dest);

//最短距离分类
void minDistanceClassify(model *originData, int n, centerModel *clusterCenters, int c);

centerModel *calcNewCenters(model *originData, int n, centerModel *clusterCenters, int c);

centerModel *conductCMI(model *originData, int n, centerModel *clusterCenters, int c)
{
    do {
        it++;
        //step 2
        //最短距离分类
        minDistanceClassify(originData, n, clusterCenters, c);
        
        //step 3
        //重新计算簇中心
        centerModel *newCenters = calcNewCenters(originData, n, clusterCenters, c);
        
        //step 4
        int i;
        for (i=0; i<c; i++)
        {
            if (!(newCenters[i]==clusterCenters[i]))
            {
                break;
            }
        }
        if (i >= c)
        {
            return newCenters;
            break;
        }
        for (i=0; i<c; i++)
        {
            clusterCenters[i] = newCenters[i];
        }
//        clusterCenters = newCenters;
    } while (1);
}

centerModel *calcNewCenters(model *originData, int n, centerModel *clusterCenters, int c)
{
    centerModel newCenters[c];
    
    model *collection = new model[c];
    int intCollection[c];
    for (int i=0; i<c; i++)
    {
        intCollection[i] = 0;
    }
    
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<c; j++)
        {
            if (originData[i].calcClass == clusterCenters[j].calcClass)
            {
                collection[j] += originData[i];
                collection[j].calcClass = clusterCenters[j].calcClass;
                intCollection[j]++;
            }
        }
    }//for i
    
    for (int i=0; i<c; i++)
    {
        newCenters[i] = collection[i]/intCollection[i];
        newCenters[i].centerFlag = 1;
        newCenters[i].calcClass = collection[i].calcClass;
    }
    delete [] collection;
    
    return newCenters;
}

void minDistanceClassify(model *originData, int n, centerModel *clusterCenters, int c)
{
    for (int i=0; i<n; i++)
    {
//        if (originData[i].centerFlag)
//        {
//            continue;
//        }
        double minValue = std::numeric_limits<double>::max();
        int minIdx = 0;
        for (int j=0; j<c; j++)
        {
            double temp = getDist(originData[i], clusterCenters[j]);
            if (temp<minValue)
            {
                minValue = temp;
                minIdx = j;
            }
        }
        originData[i].calcClass = clusterCenters[minIdx].calcClass;
    }//for i
}

double getDist(const model &source, const model &dest)
{
	double temp;
	temp = (dest.x-source.x)*(dest.x-source.x)+
    (dest.y-source.y)*(dest.y-source.y)+
    (dest.z-source.z)*(dest.z-source.z)+
    (dest.w-source.w)*(dest.w-source.w);
	temp = sqrt(temp);
    
	return temp;
}

int getIt()
{
    return it;
}
