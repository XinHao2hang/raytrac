#include "Camera.h"



Camera::Camera()
{
}

Camera::Camera(vec3 _position, vec3 _front, vec3 _up, float fov)
{
	position = _position;
	//�������ǰ����
	front = glm::normalize(_front);
	//��������ҷ���
	right = glm::normalize(glm::cross(front,_up));
	//��������Ϸ���
	up = glm::cross(right, front);
	//�����Ǽ������ͶӰ��Χ�ģ���ʱ���ǵ�������������
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
