#version 330 core

// The attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

// A transformation matrix sent as a Uniform
uniform mat4 transform;
uniform mat4 view_projection;
uniform vec3 camera_position;

// The varying
//out vec4 vertex_color;

out Varyings {
    vec3 view;
} vsout;

void main() {
    vsout.view = position;
    vec4 clip_space = view_projection * vec4(position + camera_position, 1.0);
    gl_Position = clip_space.xyww;
}




