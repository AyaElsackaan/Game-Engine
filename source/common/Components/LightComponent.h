
#ifndef GFX_LAB_LIGHTCOMPONENT_H
#define GFX_LAB_LIGHTCOMPONENT_H

#include <glm/glm.hpp>
#include "Component.h"

//using namespace GAME;

enum class LightType {
    DIRECTIONAL,
    POINT,
    SPOT
};

struct attenuation{
    float constant, linear, quadratic;
} ; // Used for Point and Spot Lights only
struct spot_angle{
    float inner, outer;
} ; // Used for Spot Lights only

class LightComponent: public Component {
private:
    LightType type;
    bool enabled = true;
    glm::vec3 color;
    spot_angle angle;
    attenuation atten;
 
    
public:
      LightComponent(int ord,LightType t,bool enable,spot_angle ang,glm::vec3 col,attenuation s);

      void setAngle(spot_angle ang);
      void setAttenuation (attenuation att);
      void setColor(glm::vec3 col);
      void setLightType(LightType t);
      void setEnable(bool enable);

      int getLightType();
      glm::vec3 getColor();
      attenuation getAttenuation();
      spot_angle getAngle();
      bool getEnable();

    void onStartApp() override ; //virtual/pure virtual>> to be modified
    void onStartState() override;
    void onUpdate() override;
    void onDeleteApp() override;
    void onDeleteState() override;



};
#endif //GFX_LAB_TRANSFORMCOMPONENT_H
