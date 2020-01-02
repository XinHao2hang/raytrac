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
	void setPosition(vec3 _pos);
	void setTransform(mat3 _mat);
	void move();
	virtual Ray intersect(Ray ray);
	vec2 getUVCoord(vec5 A,vec5 B,vec5 C,vec5 T);
	~Triangle();
};

