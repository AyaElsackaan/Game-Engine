//
// Created by AG on 26-Nov-20.
//

#ifndef GFX_LAB_CAMERACOMPONENT_H
#define GFX_LAB_CAMERACOMPONENT_H
#include "Component.h"
#include <glm/gtx/euler_angles.hpp>
#include "TransformComponent.h"


    enum struct CameraType {
        Orthographic,
        Perspective
    };
    // A class that represents a camera
    // Used to generate a view and a projection matrix
    class CameraComponent : public Component{
    private:
        // Dirty Flags are programming pattern where we only regenerate some output if:
        // 1- The inputs were changed.
        // 2- The output is needed.
        // Where we have flags for whether the View, Projection & ViewProjection matrices needed to be regenerated.
        static const uint8_t V_DIRTY = 1, P_DIRTY = 2, VP_DIRTY = 4;
        uint8_t dirtyFlags = 0;

        // The camera position, camera forward direction and camera up direction
        glm::vec3 eye = {0, 0, 0}, direction = {0, 0, -1}, up = {0, 1, 0}; //forward*rotation

        CameraType type = CameraType::Perspective;

        // The field_of_view_y is in radians and is only used for perspective cameras
        // The orthographic_height is only used for orthographic cameras
        float field_of_view_y = glm::radians(90.0f), orthographic_height = 2.0f, aspect_ratio = 1.0f, near = 0.01f, far = 100.0f;

        glm::mat4 V{}, P{}, VP{};

    public:

        CameraComponent( int ord);
        // Setup the camera as a perspective camera
        void setupPerspective(float field_of_view_y, float aspect_ratio, float near, float far);

        // Setup the camera as an orthographic camera
        void setupOrthographic(float orthographic_height, float aspect_ratio, float near, float far);
        void setFlags();
        void setType(CameraType _type);
        void setOrthographicSize(float orthographic_height);
        void setVerticalFieldOfView(float field_of_view_y);
        void setAspectRatio(float aspect_ratio);
        void setNearPlane(float near);
        void setFarPlane(float far);
        void setEyePosition(glm::vec3 eye);
        void setDirection(glm::vec3 direction);
        void setTarget(glm::vec3 target);
        void setUp(glm::vec3 up);
        glm::mat4 getProjectionMatrix();
        glm::mat4 getViewMatrix(TransformComponent* t);
        glm::mat4 getVPMatrix(TransformComponent* t);
        CameraType getType();
        [[nodiscard]] float getVerticalFieldOfView() const;
        [[nodiscard]] float getHorizontalFieldOfView() const ;
        [[nodiscard]] float getOrthographicHeight() const;
        [[nodiscard]] float getOrthographicWidth() const;
        [[nodiscard]] float getAspectRatio() const;
        [[nodiscard]] float getNearPlane() const;
        [[nodiscard]] float getFarPlane() const;
        [[nodiscard]] glm::vec3 getEyePosition() const;
        [[nodiscard]] glm::vec3 getDirection() const;
        [[nodiscard]] glm::vec3 getOriginalUp() const;

        // Get the directions of the camera coordinates in the world space
        glm::vec3 Right(TransformComponent*t);
        glm::vec3 Left(TransformComponent*t);
        glm::vec3 Up(TransformComponent*t);
        glm::vec3 Down(TransformComponent*t);
        glm::vec3 Forward(TransformComponent*t);
        glm::vec3 Backward(TransformComponent*t);

        // Transform point from world space to normalized device coordinates
        glm::vec3 fromWorldToDeviceSpace(glm::vec3 world,TransformComponent*t);

        // Transform point from normalized device coordinates to world space
        glm::vec3 fromDeviceToWorldSpace(glm::vec3 device,TransformComponent*t);

        void onStartApp() override ; //virtual/pure virtual>> to be modified
        void onStartState() override;
        void onUpdate() override;
        void onDeleteApp() override;
        void onDeleteState() override;
    };
#endif //GFX_LAB_CAMERACOMPONENT_H
