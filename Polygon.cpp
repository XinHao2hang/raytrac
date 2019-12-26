#include "Polygon.h"



Ray Polygon::sample(Ray out, Ray reflect, Ray refract)
{
	Ray res(out.direction, out.position, 0, vec3(0, 0, 0), out.polygon);
	float cosa = dot(out.normal ,normalize(-out.direction));//光线入射角和面法向量的cos值
	//发光计算
	res.color += m.color * m.light * std::fmaxf(cosa,0);
	//反射颜色计算
	res.color += reflect.color * m.specular;

	return res;
}

Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}
