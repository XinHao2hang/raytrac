#include "Sphere.h"
using namespace glm;


Sphere::Sphere()
{
}


vec3 Sphere::getNormal(vec3 _vector)
{
	return glm::normalize(_vector - center);
}

Ray Sphere::intersect(Ray ray)
{
	Ray result(ray.direction,ray.position,ray.intensity, vec3(0,0,0), nullptr);
	//计算球和光线的向量
	vec3 v = ray.position - center;
	//如果光源在球体表面或者内部，要专门注意这种情况
	if (abs(length(v) - radius) < 0.001 && dot(normalize(v) , ray.direction) <= 0)
	{
		result.polygon = this;	
		float cosa = glm::dot(normalize((center - ray.position)), normalize(ray.direction));//normalize(abs((center - ray.position))*normalize(ray.direction));
		result.distance = 2 * radius * abs(cosa);
		result.end = ray.getEndPoint(result.distance);
		result.normal = -normalize(result.end.position - center);
		return result;
	}
	float disSubR = dot(v , v) - (radius * radius);
	float ray_v_dot = dot(ray.direction , v);

	if (ray_v_dot <= 0)
	{
		float discr = ray_v_dot * ray_v_dot - disSubR;
		if (discr >= 0)
		{
			result.polygon = this;
			result.distance = -ray_v_dot - sqrt(discr);
			result.end = ray.getEndPoint(result.distance);
			result.normal = normalize(result.end.position - center);
			return result;
		}
	}
	return result;
}

Sphere::~Sphere()
{
}
