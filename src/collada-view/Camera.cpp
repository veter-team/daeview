#include "Camera.h"
#include "comdefs.h"


Camera::Camera()
  : Xfov(0.0f),
    Yfov(0.0f),
    aspect(0.0f),
    ZNear(10.0f),
    ZFar(15000.0f)
{
}


InstanceCamera::InstanceCamera()
{
}
