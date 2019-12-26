#include "Camera.h"



Camera::Camera()
{
}

Camera::Camera(vec3 _position, vec3 _front, vec3 _up, float fov)
{
	position = _position;
	//保存相机前方向
	front = glm::normalize(_front);
	//计算相机右方向
	right = glm::normalize(glm::cross(front,_up));
	//计算相机上方向
	up = glm::cross(right, front);
	//这里是计算相机投影范围的，暂时考虑的是正方形区域
	scale = tan(fov * 0.5 * 3.141592654 / 180) * 2;
}


Ray Camera::generateRay(float x, float y)
{
	vec3 u = right * vec1(x-0.5) * vec1(scale);
	vec3 v = up * vec1(y - 0.5) * vec1(scale);
	return Ray(glm::normalize(front+u+v),position,0,vec3(0,0,0),nullptr);
}

Camera::~Camera()
{
}
