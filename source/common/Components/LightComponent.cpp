#include "LightComponent.h"


LightComponent::LightComponent(int ord,LightType t,bool enable,spot_angle ang,glm::vec3 col,attenuation s) : Component(ord) 
{
    enabled = enable;
    angle = ang;
    color = col;
    atten = s;

}

void LightComponent::setAngle(spot_angle ang)
{
    angle = ang;
}
void LightComponent::setAttenuation (attenuation att)
{
    atten = att;
}
void LightComponent::setColor(glm::vec3 col)
{
    color = col;
}
void LightComponent::setLightType(LightType t)
{
    type = t;
}
void LightComponent::setEnable(bool enable)
{
    enabled = enable;
}

LightType LightComponent::getLightType()
{
    return type;
}
glm::vec3 LightComponent::getColor()
{
    return color;
}
attenuation LightComponent::getAttenuation()
{
    return atten;
}
spot_angle LightComponent::getAngle()
{
    return angle;
}
bool LightComponent::getEnable()
{
    return enabled;
}