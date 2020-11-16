#version 330 core

uniform vec2 key;

uniform vec2 mousePos;
// The output that goes to the frame buffer
out vec4 frag_color;

// Just a constant
#define PI 3.1415926535897932384626433832795

void main()
{
    vec2 circle_FragCoord;
    vec2 eye_Center;
    circle_FragCoord.x =  gl_FragCoord.x;
    circle_FragCoord.y =  720 - gl_FragCoord.y; 

    eye_Center.x =  mousePos.x - 50;
    eye_Center.y =  mousePos.y - 70;

    float eye = length(circle_FragCoord.xy - eye_Center.xy);

    float y = 0.5 * (gl_FragCoord.x - mousePos.x) + mousePos.y ;
    float y1 = -0.5 * (gl_FragCoord.x - mousePos.x) + mousePos.y;
    float circle = length(circle_FragCoord.xy - mousePos.xy);


    if (( circle <= 190 && !(circle_FragCoord.y > y1 && circle_FragCoord.y < y ) ) )
    {
        if (eye <20)
        {
           frag_color = vec4(1.0,0.0,0.0,1.0);
        }
        else
        {
        frag_color = vec4(1.0,1.0,1.0,1.0);
        }
    }
    else
    {
        frag_color = vec4(1.0,0.0,0.0,1.0);

    }
}