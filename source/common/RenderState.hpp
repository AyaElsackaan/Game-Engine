    
#include <map>
#include <any>
#include <shader.hpp>
    
    
    struct RenderState {
        bool Enable_DepthTesting;
        GLenum depth_function;

        bool Enable_Blending;
        GLenum blend_equation;
        GLenum blend_source_function;
        GLenum blend_destination_function;
        glm::vec4 blend_constant_color;


        bool Enable_Culling;
        GLenum culled_face;

        bool enable_transparent_depth_write;
        GLenum front_face_winding;

        bool enable_alpha_test;
        float alpha_test_threshold;
        bool enable_alpha_to_coverage;
    };