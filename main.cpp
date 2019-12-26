#include <iostream>
#include <opencv2/opencv.hpp>
#include <glm.hpp>
#include <vector>
#include "Polygon.h"
#include "Ray.h"
#include "Sphere.h"
#include "Camera.h"
using namespace std;
using namespace cv;
using namespace glm;
Ray rayTrac(Ray ray,vector<Polygon*> s,int times)
{
	Ray r;
	for (auto obj : s)
	{
		r = obj->intersect(ray);
	}
	return r;
}
Ray render(int i, int j, int rows, int cols, vector<Polygon*> s, Camera cam)
{
	float sy = 1.0 - (i * 1.0) / rows;
	float sx = (j * 1.0) / cols;
	Ray r = rayTrac(cam.generateRay(sx, sy), s, 0);
	/*float depth = 0;
	if(r.polygon != nullptr)
	depth = 255 - std::min(int((r.distance / 35)*255), 255);
	return Ray(r.direction, r.position, 0, vec3(depth, depth, depth), nullptr);*/
	//float normal = r.normal;
	return Ray(r.direction, r.position, 0, vec3((r.normal.x+1)*128, (r.normal.y + 1) * 128, (r.normal.z + 1) * 128), nullptr);
	
}
int main()
{
	Camera camera(vec3(0, 10, 10), vec3(0, 0, -1), vec3(0, 1, 0), 90);
	Mat img = Mat::zeros(Size(512, 512), CV_8UC3);
	Sphere s(vec3(12, 10, -20), 10);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			vec3 color = render(i, j, img.rows, img.cols, {&s},camera).color;
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