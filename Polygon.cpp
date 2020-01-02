#include "Polygon.h"

Ray Polygon::sample(Ray out, Ray reflect, Ray refract)
{
	Ray res(out.direction, out.position, 0, vec3(0, 0, 0), out.polygon);
	//out光线带的是对应物体的法向量值
	float cosa = abs(dot(out.normal,-out.direction));//光线入射角和面法向量的cos值
	//发光计算
	res.color = m->getColor(out.end.textureUV) * m->light * std::fmaxf(cosa,0);
	//反射颜色计算
	if(reflect.polygon)
		res.color += reflect.color * m->specular;
	return res;
}

Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}