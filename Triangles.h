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
	//���������ײ
	virtual Ray intersect(Ray ray);
	//������ɫ����
	virtual Ray sample(Ray out, Ray reflect, Ray refract);
	//����λ��
	void setPosition(vec3 _pos);
	//������̬����
	void setTransform(mat3 _mat);
	//
	void move();
	~Triangles();
};

