#version 330 core

uniform vec2 scale;

// Just a constant
#define PI 3.1415926535897932384626433832795

void main() {
    // This time we have 6 points since we are drawing a Quad (in NDC, it is a square).
    const vec3 positions[6] = vec3[6](
        vec3(-1.0, -1.0, 0.0),
        vec3( 1.0, -1.0, 0.0),
        vec3( 1.0,  1.0, 0.0),
        vec3( 1.0,  1.0, 0.0),
        vec3(-1.0,  1.0, 0.0),
        vec3(-1.0, -1.0, 0.0)
    );
    vec3 position = positions[gl_VertexID];
        gl_Position = vec4(position, 1.0);

}