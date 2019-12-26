#include "Polygon.h"



Ray Polygon::sample(Ray out, Ray reflact, Ray refract)
{
	Ray res(out.direction, out.position, 0, vec3(0, 0, 0), out.polygon);
	//原始发光
	float cosa = dot(out.normal ,normalize(out.direction));//光线入射角和面法向量的cos值
	res.color = m.color * m.light * abs(cosa) ;

	return res;
}

Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}
