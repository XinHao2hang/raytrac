#pragma once
#include "Plane.h"
class Triangle : public Plane
{
public:
	Triangle();
	Triangle(vec5 _A, vec5 _B, vec5 _C, Material * _m) :A(_A), B(_B), C(_C) 
	{
		m = _m; 
		normal = normalize(cross(A.position-B.position, B.position-C.position));
		lA = length(B.position-C.position);
		lB = length(A.position-C.position);
		lC = length(A.position-B.position);
		float P = (lA + lB + lC) / 2;
		area = sqrt(P*(P-lA)*(P-lB)*(P-lC));
	}
	//三角形三个点
	vec5 A, B, C;
	vec5 wA, wB, wC;
	//面积
	float area,lA,lB,lC;
	//
	void setPosition(vec3 _pos);
	void setTransform(mat3 _mat);
	//move在显示之前调用，不然不会更新
	void move();
	virtual Ray intersect(Ray ray);
	vec2 getUVCoord(vec5 A,vec5 B,vec5 C,vec5 T);
	//获取法向量
	virtual vec3 getNormal(vec3 _vector);
	bool onTriangle0(vec3 A,vec3 B,vec3 C,vec3 O);
	bool onTriangle1(vec3 A, vec3 B, vec3 C, vec3 O);
	~Triangle();
};

