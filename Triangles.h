#pragma once
#include "Triangle.h"
#include "Polygon.h"
#include <vector>
using namespace std;
class Triangles : public Polygon
{
	
public:
	vector<Triangle> triangles;
	Triangles();
	Triangles(vector<Triangle> tr) 
	{
		for (int i = 0; i < tr.size(); i++)
		{
			triangles.push_back(Triangle(tr[i]));
		}
	}
	//计算光线碰撞
	virtual Ray intersect(Ray ray);
	//计算颜色采样
	virtual Ray sample(Ray out, Ray reflect, Ray refract);
	//设置位置
	void setPosition(vec3 _pos);
	//设置姿态矩阵
	void setTransform(mat3 _mat);
	//
	void move();
	~Triangles();
};

