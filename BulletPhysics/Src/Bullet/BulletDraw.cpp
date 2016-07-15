#include "BulletDraw.h"
#include "../Graphic/Graphic.h"
#include "../Math/Converter.h"

DxDebugDraw::DxDebugDraw():
	m_debugMode(0)
{
}

void DxDebugDraw::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & fromColor, const btVector3 & toColor)
{
	Graphic::GetInstance().DrawLine(RConvertB(from), RConvertB(to), CAMERA_ID::NORMAL_CAMERA, RConvertB(fromColor));
}

void DxDebugDraw::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color)
{
	Graphic::GetInstance().DrawLine(RConvertB(from), RConvertB(to), CAMERA_ID::NORMAL_CAMERA, RConvertB(color));
}

void DxDebugDraw::drawSphere(const btVector3 & p, btScalar radius, const btVector3 & color)
{
	Graphic::GetInstance().DrawSphere(RConvertB(p), radius, CAMERA_ID::NORMAL_CAMERA, RConvertB(color));
}

void DxDebugDraw::drawBox(const btVector3 & boxMin, const btVector3 & boxMax, const btVector3 & color, btScalar alpha)
{
	Graphic::GetInstance().DrawCube(RConvertB(boxMin), RConvertB(boxMax), CAMERA_ID::NORMAL_CAMERA, RConvertB(color), alpha);
}

void DxDebugDraw::drawTriangle(const btVector3 & a, const btVector3 & b, const btVector3 & c, const btVector3 & color, btScalar alpha)
{
}

void DxDebugDraw::drawContactPoint(const btVector3 & PointOnB, const btVector3 & normalOnB, btScalar distance, int lifeTime, const btVector3 & color)
{
}

void DxDebugDraw::reportErrorWarning(const char * warningString)
{
}

void DxDebugDraw::draw3dText(const btVector3 & location, const char * textString)
{
}

void DxDebugDraw::setDebugMode(int debugMode)
{
	m_debugMode = debugMode;
}
