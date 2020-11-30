//
// Created by AG on 26-Nov-20.
#ifndef GFX_LAB_CAMERACONTROLLERCOMPONENT_H
#define GFX_LAB_CAMERACONTROLLERCOMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <application.hpp>
#include "Components/Component.h"
#include "CameraComponent.h"


class CameraController : public Component {
    private:
        GAME::Application* app;
        CameraComponent* camera;

        float yaw, pitch;
        glm::vec3 position;

        float yaw_sensitivity, pitch_sensitivity, fov_sensitivity;
        glm::vec3 position_sensitivity;
        float speedup_factor = 5.0f; // A speed multiplier if "Left Shift" is held.

        bool mouse_locked = false;

     public:
        CameraController( int ord);
        void initialize(GAME::Application* application, CameraComponent* camera);
        void release();

        void update(double delta_time);

        [[nodiscard]] float getYaw() const;
        [[nodiscard]] float getPitch() const;
        [[nodiscard]] glm::vec3 getPosition() const;

        [[nodiscard]] float getYawSensitivity() const;
        [[nodiscard]] float getPitchSensitivity() const;
        [[nodiscard]] float getFieldOfViewSensitivity() const;
        [[nodiscard]] glm::vec3 getPositionSensitivity() const;
        [[nodiscard]] float getSpeedUpFactor() const;

        void setYaw(float _yaw);
        void setPitch(float _pitch);
        void setPosition(glm::vec3 _pos);

        void setYawSensitivity(float sensitivity);
        void setPitchSensitivity(float sensitivity);
        void setFieldOfViewSensitivity(float sensitivity);
        void setPositionSensitivity(glm::vec3 sensitivity);

        
        void onStartApp() override ; //virtual/pure virtual>> to be modified
        void onStartState() override;
        void onUpdate() override;
        void onDeleteApp() override;
        void onDeleteState() override;

    };
#endif //GFX_LAB_CAMERACOMPONENT_H


