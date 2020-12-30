
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

   // glm::vec3 diffuse, specular, ambient;

    bool enabled;

    glm::vec3 color;

    spot_angle angle;
    attenuation atten;
   // glm::vec3 position; // Used for Point and Spot Lights only
   // glm::vec3 direction; // Used for Directional and Spot Lights only
 
    
public:
      LightComponent(int ord,LightType t,bool enable,spot_angle ang,glm::vec3 col,attenuation s);

      void setAngle(spot_angle ang);
      void setAttenuation (attenuation att);
      void setColor(glm::vec3 col);
      void setLightType(LightType t);
      void setEnable(bool enable);

      LightType getLightType();
      glm::vec3 getColor();
      attenuation getAttenuation();
      spot_angle getAngle();
      bool getEnable();


};
#endif //GFX_LAB_TRANSFORMCOMPONENT_H
