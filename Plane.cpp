#include "Plane.h"



Plane::Plane()
{
}


Ray Plane::intersect(Ray ray)
{
	Ray result(ray.direction, ray.position, ray.intensity,vec3(0,0,0), nullptr);
	//≈–∂œπ‚‘¥Œª÷√
	if ((dot(normalize(ray.position - (normal * normal_distance)), normal)) <= 0.0001)
		return result;
	//Ray result(ray.direction, ray.position, ray.intensity, ray.color, nullptr);
	result.distance = FLT_MAX;
	float light_d = dot(((normal * normal_distance) - ray.position),normal) / dot(ray.direction , normal);
	if (light_d <= 0)
		return result;
	result.normal = normal;
	result.distance = light_d;
	result.end = ray.getEndPoint(light_d);
	result.polygon = this;
	return result;
}

Plane::~Plane()
{
}
