//数据模型（iris.dat文件中的每一行数据）

#ifndef CLASSMODEL_H
#define CLASSMODEL_H

#include <iostream>
using namespace std;

class model
{
public:
	model():centerFlag(0), x(0), y(0), z(0), w(0), initClass(0), calcClass(0) {};
	void setX(double fromX);
	double getX();

	void setY(double fromY);
	double getY();

	void setZ(double fromZ);
	double getZ();

	void setW(double fromW);
	double getW();

	void setInitClass(int fromInitClass);
	int getInitClass();

	void setCalcClass(int fromCalcClass);
	int getCalcClass();

	model operator=(const model &data);
    model operator+=(const model &data);
//    model operator+(const model &data);
    model operator/(int d);
//private:
	//表明该对象是否是一个cluster center
	bool centerFlag;

	double x, y, z, w;
	int initClass;
	int calcClass;
};

class centerModel : public model
{
	public:
    centerModel operator=(const model &data);
    centerModel operator=(const centerModel &data);
    centerModel operator+(const model &data);
    centerModel operator/(int d);
    bool operator==(const centerModel &data);
    
    friend ostream &operator<<(std::ostream &os, const centerModel &data);
//	private:
	double idxOfOrigin;	
};
#endif

