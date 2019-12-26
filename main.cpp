#include <iostream>
#include <opencv2/opencv.hpp>
#include <glm.hpp>
#include <vector>
#include "Polygon.h"
#include "Ray.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
using namespace std;
using namespace cv;
using namespace glm;
Ray rayTrac(Ray ray,vector<Polygon*> s,int times)
{
	Ray r(vec3(0,0,0),vec3(0,0,0),0,vec3(0,0,0),nullptr);
	float minDistance= FLT_MAX;
	for (auto obj : s)
	{
		//找到最近的物体
		Ray rayTemp = obj->intersect(ray);
		if (rayTemp.distance < minDistance )
		{
			minDistance = rayTemp.distance;
			r = rayTemp;
		}
	}
	if (r.polygon == nullptr)
		return Ray(vec3(0, 0, 0), vec3(0, 0, 0), 0, vec3(0, 0, 0), nullptr);
	r = ((Polygon*)(r.polygon))->sample(r,r,r);
	return r;
}
Ray render(int i, int j, int rows, int cols, vector<Polygon*> s, Camera cam)
{
	float sy = 1.0 - (i * 1.0) / rows;
	float sx = (j * 1.0) / cols;
	Ray r = rayTrac(cam.generateRay(sx, sy), s, 0);
	if(r.polygon == nullptr)
		return Ray(r.direction, r.position, 0, vec3(0, 0,0), nullptr);
	return Ray(r.direction, r.position, 0, vec3(r.color.x, r.color.y, r.color.z), nullptr);
	
}
int main()
{
	Camera camera(vec3(0, 10, 10), vec3(0, 0, -1), vec3(0, 1, 0), 90);
	Mat img = Mat::zeros(Size(512, 512), CV_8UC3);
	Material m0(0.8,0.5,0.5,0,0,vec3(255,255,0));
	Material m1(0.8, 0.5, 0.5, 0, 0, vec3(0, 0, 255));
	Sphere s0(vec3(12, 10, -20), 10,m0);
	Sphere s1(vec3(-12, 10, -20), 10, m1);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			vec3 color = render(i, j, img.rows, img.cols, {&s0,&s1},camera).color;
			if (color.z > 255)
				color.z = 255;
			if (color.y > 255)
				color.y = 255;
			if (color.x > 255)
				color.x = 255;
			img.at<Vec3b>(i, j) = Vec3b(color.z, color.y, color.x);
		}
	}
	imshow("img",img);
	imwrite("1.jpg",img);
	waitKey(0);
	return 0;
}