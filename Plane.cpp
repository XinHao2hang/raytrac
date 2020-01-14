#include "Plane.h"



Plane::Plane()
{
}


Ray Plane::intersect(Ray ray)
{
	Ray result(ray.direction, ray.position, ray.intensity,ray.color, nullptr);
	//判断光源位置,防止面自身发出的光线由于精度问题直接被误认为打到自己身上
	if (abs(dot(normalize(ray.position - (normal * normal_distance)), normal)) <= 0.0001)
		return result;
	//Ray result(ray.direction, ray.position, ray.intensity, ray.color, nullptr);
	result.distance = FLT_MAX;
	float light_d = dot(((normal * normal_distance) - ray.position),normal) / dot(ray.direction , normal);
	if (light_d <= 0)
		return result;
	result.normal = normal;
	result.distance = light_d;
	result.end = result.getEndPoint(light_d);
	result.polygon = this;
	return result;
}

Plane::~Plane()
{
}
