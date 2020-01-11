#include "Triangles.h"



Triangles::Triangles()
{
}

Ray Triangles::intersect(Ray ray)
{
	//一束光线只能在同一时间打在这个物体的一个位置上
	for (int i = 0; i < triangles.size(); i++)
	{
		//光线打在物体上，返回的是光线到物体的信息
		Ray r = triangles[i].intersect(ray);
		if (r.polygon != nullptr)
			return r;
	}
	return Ray(ray.direction, ray.position, ray.intensity, ray.color, nullptr);
}

Ray Triangles::sample(Ray out, Ray reflect, Ray refract)
{
	for (int i = 0; i < triangles.size(); i++)
	{
		//找到光是打在哪个面上
		if (out.polygon == &triangles[i])
			return triangles[i].sample(out,reflect,refract);
	}
	//正常运行时候这里是不会被执行的
	return Ray(out.direction, out.position, 0, vec3(0,0,0), nullptr);
}

void Triangles::setPosition(vec3 _pos)
{
	for (int i = 0; i < triangles.size(); i++)
		triangles[i].setPosition(_pos);
}

void Triangles::setTransform(mat3 _mat)
{
	for (int i=0;i<triangles.size(); i++)
		triangles[i].setTransform(_mat);
}


void Triangles::move()
{
	for (int i = 0; i < triangles.size(); i++)
	{
		triangles[i].move();
	}
}

Triangles::~Triangles()
{
}
