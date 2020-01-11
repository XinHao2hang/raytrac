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
	wA = transforms * A.position + position;
	wB = transforms * B.position + position;
	wC = transforms * C.position + position;
	//更新平面参数
	normal_distance = dot(normal, wA.position);
	//更新法向量
	normal = normalize(cross(wA.position - wB.position, wB.position - wC.position));
}
Ray Triangle::intersect(Ray ray)
{
	Ray result(ray.direction, ray.position, ray.intensity, ray.color, nullptr);
	if ((result = Plane::intersect(ray)).polygon == nullptr)
		return Ray(ray.direction, ray.position, ray.intensity, vec3(0, 0, 0), nullptr);
	//这里说明点在三角面是上
	if (onTriangle0(wA.position, wB.position, wC.position, result.end.position))
	{
		//计算点所在的纹理坐标
		vec5 p_end;
		result.end.textureUV = getUVCoord(A, B, C, result.end);
		return result;
	}
	return Ray(ray.direction, ray.position, ray.intensity, vec3(0, 0, 0), nullptr);
}

vec2 Triangle::getUVCoord(vec5 A, vec5 B, vec5 C, vec5 T)
{
	//计算每个三角形需要的边长
	float la, lb, lc;
	la = length(T.position - wA.position);
	lb = length(T.position - wB.position);
	lc = length(T.position - wC.position);
	float pa = (lA + lb + lc) / 2;
	float pb = (lB + la + lc) / 2;
	//计算三个三角形的面积
	float area_a = sqrt(pa * (pa - lA) * (pa - lb) * (pa - lc));
	float area_b = sqrt(pb * (pb - lB) * (pb - la) * (pb - lc));
	float area_c = area - area_a - area_b;
	return (area_a * A.textureUV + area_b * B.textureUV + area_c * C.textureUV) / area;
}

vec3 Triangle::getNormal(vec3 _vector)
{

	return normal;
}

bool Triangle::onTriangle0(vec3 A, vec3 B, vec3 C, vec3 O)
{
	vec3 v0 = C - A;
	vec3 v1 = B - A;
	vec3 v2 = O - A;

	float dot00 = dot(v0, v0);
	float dot01 = dot(v0, v1);
	float dot02 = dot(v0, v2);
	float dot11 = dot(v1, v1);
	float dot12 = dot(v1, v2);

	float inverDeno = 1 / (dot00 * dot11 - dot01 * dot01);

	float u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
	if (u < 0 || u > 1)
		return false;

	float v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
	if (v < 0 || v > 1)
		return false;
	return u + v <= 1;
}

bool Triangle::onTriangle1(vec3 A, vec3 B, vec3 C, vec3 O)
{
	vec3 a = A - O;
	vec3 b = B - O;
	vec3 c = C - O;
	//在三角形内部
	//double angle = (acos(dot(a, b))+ acos(dot(b, c))+ acos(dot(c, a)))* R_ANGLE;
	//if (fabs(angle-360.0)<0.1)
	//{
	//	return result;
	//}
	vec3 sa = normalize(cross(a, b));
	vec3 sb = normalize(cross(b, c));
	vec3 sc = normalize(cross(c, a));
	return dot(sa, sb) > 0.9999&& dot(sb, sc) > 0.9999&& dot(sc, sa) > 0.9999;
}

Triangle::~Triangle()
{
}
