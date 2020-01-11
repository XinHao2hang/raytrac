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

	//判断是否在三角形内
	vec3 a = wA.position - result.end.position;
	vec3 b = wB.position - result.end.position;
	vec3 c = wC.position - result.end.position;
	//在三角形内部
	//double angle = (acos(dot(a, b))+ acos(dot(b, c))+ acos(dot(c, a)))* R_ANGLE;
	//if (fabs(angle-360.0)<0.1)
	//{
	//	return result;
	//}
	vec3 sa = normalize(cross(a, b));
	vec3 sb = normalize(cross(b, c));
	vec3 sc = normalize(cross(c, a));
	//这里说明点在三角面是上
	if (dot(sa, sb) > 0.9999 && dot(sb, sc) > 0.9999 && dot(sc, sa) > 0.9999)
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

Triangle::~Triangle()
{
}
