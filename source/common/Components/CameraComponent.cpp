//
// Created by AG on 26-Nov-20.
//

#include "CameraComponent.h"

//CameraComponent::CameraComponent(Entity *e, int ord, glm::vec3 eye, glm::vec3 center, glm::vec3 up,
//                                 bool is_perspective, float near, float far, float aspect_ratio,
//                                 float vertical_field_of_view_angle, float orthographic_height) : Component(e, ord) {
//    this-> eye=eye;
//    this-> center=center;
//    this->up=up;
//    this-> is_perspective=is_perspective;
//    this-> near=near;
///    this-> far=far;
 //   this-> aspect_ratio=aspect_ratio;
 //   this-> vertical_field_of_view_angle=vertical_field_of_view_angle;
 //   this-> orthographic_height=orthographic_height;
//}
CameraComponent::CameraComponent(int ord)  : Component(ord){
            dirtyFlags = V_DIRTY | P_DIRTY | VP_DIRTY;
            up = {0, 1, 0};
        }

        void CameraComponent::setupPerspective(float field_of_view_y, float aspect_ratio, float near, float far){
            this->type = CameraType::Perspective;
            this->field_of_view_y = field_of_view_y;
            this->aspect_ratio = aspect_ratio;
            this->near = near;
            this->far = far;
            dirtyFlags |= P_DIRTY | VP_DIRTY; // Both P & VP need to be regenerated
        }
void CameraComponent::setupOrthographic(float orthographic_height, float aspect_ratio, float near, float far){
            this->type = CameraType::Orthographic;
            this->orthographic_height = orthographic_height;
            this->aspect_ratio = aspect_ratio;
            this->near = near;
            this->far = far;
            dirtyFlags |= P_DIRTY | VP_DIRTY; // Both P & VP need to be regenerated
        }
 void CameraComponent::setType(CameraType _type){
            if(this->type != _type){
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->type = _type;
            }
        }
        void CameraComponent::setOrthographicSize(float orthographic_height){
            if(this->orthographic_height != orthographic_height){
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->orthographic_height = orthographic_height;
            }
        }
        void CameraComponent::setVerticalFieldOfView(float field_of_view_y){
            if(this->field_of_view_y != field_of_view_y){
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->field_of_view_y = field_of_view_y;
            }
        }
        void CameraComponent::setAspectRatio(float aspect_ratio){
            if(this->aspect_ratio != aspect_ratio){
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->aspect_ratio = aspect_ratio;
            }
        }
        void CameraComponent::setNearPlane(float near){
            if(this->near != near){
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->near = near;
            }
        }
        void CameraComponent::setFarPlane(float far){
            if(this->far != far){
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->far = far;
            }
        }
        void CameraComponent::setEyePosition(glm::vec3 eye){
            if(this->eye != eye){
                dirtyFlags |= V_DIRTY | VP_DIRTY;
                this->eye = eye;
            }
        }
        void CameraComponent::setDirection(glm::vec3 direction){
            if(this->direction != direction){
                dirtyFlags |= V_DIRTY | VP_DIRTY;
                this->direction = direction;
            }
        }
        void CameraComponent::setTarget(glm::vec3 target){
            glm::vec3 direction = target - eye;
            if(this->direction != direction){
                dirtyFlags |= V_DIRTY | VP_DIRTY;
                this->direction = direction;
            }
        }
        void CameraComponent::setUp(glm::vec3 up){
            if(this->up != up){
                dirtyFlags |= V_DIRTY | VP_DIRTY;
                this->up = up;
            }
        }

        glm::mat4 CameraComponent::getProjectionMatrix(){
            if(dirtyFlags & P_DIRTY){ // Only regenerate the projection matrix if its flag is dirty
                if(type == CameraType::Orthographic){
                    float half_height = orthographic_height * 0.5f;
                    float half_width = aspect_ratio * half_height;
                    P = glm::ortho(-half_width, half_width, -half_height, half_height, near, far);
                } else {
                    P = glm::perspective(field_of_view_y, aspect_ratio, near, far);
                }
                dirtyFlags &= ~P_DIRTY; // P is no longer dirty
            }
            return P;
        }

        glm::mat4 CameraComponent::getViewMatrix(){
            if(dirtyFlags & V_DIRTY){ // Only regenerate the view matrix if its flag is dirty
                V = glm::lookAt(eye, eye + direction, up);
                dirtyFlags &= ~V_DIRTY; // V is no longer dirty
            }
            return V;
        }

        glm::mat4 CameraComponent::getVPMatrix(){
            if(dirtyFlags & VP_DIRTY){
                VP = getProjectionMatrix() * getViewMatrix();
                // Note that we called the functions getProjectionMatrix & getViewMatrix instead of directly using V & P
                // to make sure that they are not outdated
                dirtyFlags = 0; // Nothing is dirty anymore
            }
            return VP;
        }

        CameraType CameraComponent::getType(){return type;}
        [[nodiscard]] float CameraComponent::getVerticalFieldOfView() const {return field_of_view_y;}
        [[nodiscard]] float CameraComponent::getHorizontalFieldOfView() const {return field_of_view_y * aspect_ratio;}
        [[nodiscard]] float CameraComponent::getOrthographicHeight() const {return orthographic_height;}
        [[nodiscard]] float CameraComponent::getOrthographicWidth() const {return orthographic_height * aspect_ratio;}
        [[nodiscard]] float CameraComponent::getAspectRatio() const {return aspect_ratio;}
        [[nodiscard]] float CameraComponent::getNearPlane() const {return near;}
        [[nodiscard]] float CameraComponent::getFarPlane() const {return far;}
        [[nodiscard]] glm::vec3 CameraComponent::getEyePosition() const {return eye;}
        [[nodiscard]] glm::vec3 CameraComponent::getDirection() const {return direction;}
        [[nodiscard]] glm::vec3 CameraComponent::getOriginalUp() const {return up;}

        // Get the directions of the camera coordinates in the world space
        glm::vec3 CameraComponent::Right(){
            getViewMatrix();
            return {V[0][0],V[1][0],V[2][0]};
        }
        glm::vec3 CameraComponent::Left(){
            getViewMatrix();
            return {-V[0][0],-V[1][0],-V[2][0]};
        }
        glm::vec3 CameraComponent::Up(){
            getViewMatrix();
            return {V[0][1],V[1][1],V[2][1]};
        }
        glm::vec3 CameraComponent::Down(){
            getViewMatrix();
            return {-V[0][1],-V[1][1],-V[2][1]};
        }
        glm::vec3 CameraComponent::Forward(){
            getViewMatrix();
            return {-V[0][2],-V[1][2],-V[2][2]};
        }
        glm::vec3 CameraComponent::Backward(){
            getViewMatrix();
            return {V[0][2],V[1][2],V[2][2]};
        }

        // Transform point from world space to normalized device coordinates
        glm::vec3 CameraComponent::fromWorldToDeviceSpace(glm::vec3 world){
            glm::vec4 clip = getVPMatrix() * glm::vec4(world, 1.0f);
            return glm::vec3(clip)/clip.w;
            // Note that we must divide by w. This is because of the projection matrix.
        }

        // Transform point from normalized device coordinates to world space
        glm::vec3 CameraComponent::fromDeviceToWorldSpace(glm::vec3 device){
            glm::vec4 clip = glm::inverse(getVPMatrix()) * glm::vec4(device, 1.0f);
            return glm::vec3(clip)/clip.w;
            // Note that we must divide by w even though we not going to the NDC space. This is because of the projection matrix.
        }
void CameraComponent::onStartApp() {

}

void CameraComponent::onStartState() 
{
       // setEyePosition(eye);
       // setTarget({0, 0, 0});
       // setUp(up);
      //  setupPerspective(glm::pi<float>()/2, static_cast<float>(width)/height, 0.1f, 100.0f);
}

void CameraComponent::onUpdate() 
{

}

void CameraComponent::onDeleteApp() 
{

}

void CameraComponent::onDeleteState() 
{

}
