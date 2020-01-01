#pragma once
#include "Plane.h"
class Triangle : public Plane
{
public:
	Triangle();
	Triangle(vec3 _A, vec3 _B, vec3 _C, Material _m) :A(_A), B(_B), C(_C) 
	{
		m = _m; 
		normal = normalize(cross(A-B, B-C));
		
	}
	//三角形三个点
	vec3 A, B, C;
	vec3 wA, wB, wC;
	void setPosition(vec3 _pos);
	void setTransform(mat3 _mat);
	void move();
	virtual Ray intersect(Ray ray);
	~Triangle();
};

