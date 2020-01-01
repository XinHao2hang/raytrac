#include "Triangle.h"
#define R_ANGLE  57.2957795130823208767981


Triangle::Triangle()
{
}


void Triangle::setPosition(vec3 _pos)
{
	position = _pos;
	//wA = transforms * A + position;
	//wB = transforms * B + position;
	//wC = transforms * C + position;
	
}

void Triangle::setTransform(mat3 _mat)
{
	transforms = _mat;
	
}

void Triangle::move()
{
	wA = transforms * A + position;
	wB = transforms * B + position;
	wC = transforms * C + position;
	normal_distance = dot(normal, wA);
}

Ray Triangle::intersect(Ray ray)
{
	Ray result(ray.direction, ray.position, ray.intensity, ray.color, nullptr);
	
	if ((result = Plane::intersect(ray)).polygon == nullptr)
		return Ray(ray.direction, ray.position, ray.intensity, vec3(0, 0, 0), nullptr);

	//判断是否在三角形内
	vec3 a = wA - result.end;
	vec3 b = wB - result.end;
	vec3 c = wC - result.end;
	//在三角形内部
	//double angle = (acos(dot(a, b))+ acos(dot(b, c))+ acos(dot(c, a)))* R_ANGLE;
	//if (fabs(angle-360.0)<0.1)
	//{
	//	return result;
	//}
	vec3 sa = normalize(cross(a, b));
	vec3 sb = normalize(cross(b, c));
	vec3 sc = normalize(cross(c, a));
	if(dot(sa,sb)>0.999 && dot(sb,sc)>0.999 && dot(sc,sa)>0.999)
		return result;
	return Ray(ray.direction, ray.position, ray.intensity, vec3(0, 0, 0), nullptr);
}

Triangle::~Triangle()
{
}
