#include "Ray.h"



vec3 Ray::getEndPoint(float distance)
{
	return position + distance * direction;
}

Ray::Ray()
{
}


Ray::~Ray()
{
}
