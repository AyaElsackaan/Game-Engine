#include "CameraControllerComponent.h"
#include <iostream>

CameraController::CameraController( int ord)  : Component( ord){}

void CameraController:: setDeltaTime(double del)
{
    delta_time = del;
}

void CameraController::initialize(GAME::Application* application, CameraComponent* camera)
{
    this->app = application;
    this->camera = camera;
    yaw_sensitivity = pitch_sensitivity = 0.01f;
    position_sensitivity = {3.0f, 3.0f, 3.0f};
    fov_sensitivity = glm::pi<float>()/10;

    position = camera->getEyePosition();
    auto direction = camera->getDirection();
    yaw = glm::atan(-direction.z, direction.x);
    float base_length = glm::sqrt(direction.x * direction.x + direction.z * direction.z);
    pitch = glm::atan(direction.y, base_length);
}

void CameraController::release(){
    if(mouse_locked) {
        mouse_locked = false;
        app->getMouse().unlockMouse(app->getWindow());
    }
}

void CameraController::update(double delta_time){

    if(app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && !mouse_locked){
        app->getMouse().lockMouse(app->getWindow());
        mouse_locked = true;
    } else if(!app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && mouse_locked) {
        app->getMouse().unlockMouse(app->getWindow());
        mouse_locked = false;
    }

    if(app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1)){
        glm::vec2 delta = app->getMouse().getMouseDelta();
        pitch -= delta.y * pitch_sensitivity;
        yaw -= delta.x * yaw_sensitivity;
    }

    if(pitch < -glm::half_pi<float>() * 0.99f) pitch = -glm::half_pi<float>() * 0.99f;
    if(pitch >  glm::half_pi<float>() * 0.99f) pitch  = glm::half_pi<float>() * 0.99f;
    yaw = glm::wrapAngle(yaw);

    float fov = camera->getVerticalFieldOfView() + app->getMouse().getScrollOffset().y * fov_sensitivity;
    fov = glm::clamp(fov, glm::pi<float>() * 0.01f, glm::pi<float>() * 0.99f);
    camera->setVerticalFieldOfView(fov);

    glm::vec3 front = camera->Forward(), up = camera->Up(), right = camera->Right();

    glm::vec3 current_sensitivity = this->position_sensitivity;
    if(app->getKeyboard().isPressed(GLFW_KEY_LEFT_SHIFT)) current_sensitivity *= speedup_factor;

    if(app->getKeyboard().isPressed(GLFW_KEY_W)) position += front * ((float)delta_time * current_sensitivity.z);
    if(app->getKeyboard().isPressed(GLFW_KEY_S)) position -= front * ((float)delta_time * current_sensitivity.z);
    if(app->getKeyboard().isPressed(GLFW_KEY_Q)) position += up * ((float)delta_time * current_sensitivity.y);
    if(app->getKeyboard().isPressed(GLFW_KEY_E)) position -= up * ((float)delta_time * current_sensitivity.y);
    if(app->getKeyboard().isPressed(GLFW_KEY_D)) position += right * ((float)delta_time * current_sensitivity.x);
    if(app->getKeyboard().isPressed(GLFW_KEY_A)) position -= right * ((float)delta_time * current_sensitivity.x);

    camera->setDirection(glm::vec3(glm::cos(yaw), 0, -glm::sin(yaw)) * glm::cos(pitch) + glm::vec3(0, glm::sin(pitch), 0));
    camera->setEyePosition(position);
}

        [[nodiscard]] float CameraController::getYaw() const {return yaw;}
        [[nodiscard]] float CameraController::getPitch() const {return pitch;}
        [[nodiscard]] glm::vec3 CameraController::getPosition() const {return position;}

        [[nodiscard]] float CameraController::getYawSensitivity() const {return yaw_sensitivity;}
        [[nodiscard]] float CameraController::getPitchSensitivity() const {return pitch_sensitivity;}
        [[nodiscard]] float CameraController::getFieldOfViewSensitivity() const {return fov_sensitivity;}
        [[nodiscard]] glm::vec3 CameraController::getPositionSensitivity() const {return position_sensitivity;}
        [[nodiscard]] float CameraController::getSpeedUpFactor() const {return speedup_factor;}

        void CameraController::setYaw(float _yaw){
            this->yaw = glm::wrapAngle(_yaw);
        }
        void CameraController::setPitch(float _pitch){
            const float v = 0.99f*glm::pi<float>()/2;
            if(_pitch > v) _pitch = v;
            else if(_pitch < -v) _pitch = -v;
            this->pitch = _pitch;
        }
        void CameraController::setPosition(glm::vec3 _pos){
            this->position = _pos;
        }

        void CameraController::setYawSensitivity(float sensitivity){this->yaw_sensitivity = sensitivity;}
        void CameraController::setPitchSensitivity(float sensitivity){this->pitch_sensitivity = sensitivity;}
        void CameraController::setFieldOfViewSensitivity(float sensitivity){this->fov_sensitivity = sensitivity;}
        void CameraController::setPositionSensitivity(glm::vec3 sensitivity){this->position_sensitivity = sensitivity;}
void CameraController::onStartApp()
{

}

void CameraController::onStartState()
{
}
void CameraController::onDeleteState()
{
}


void CameraController::onUpdate()
{
    this->update(delta_time);
}
void CameraController::onDeleteApp() {

}