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
    circle_FragCoord.x =  gl_FragCoord.x;
    circle_FragCoord.y =  720 - gl_FragCoord.y; 

    float y = 1.5 * (gl_FragCoord.x - mousePos.x) + mousePos.y ;
    float y1 = -1.3 * (gl_FragCoord.x - mousePos.x) + mousePos.y;
    float x = mousePos.x + 81;
    float x1 = mousePos.x + 121;
    float yyy = mousePos.y + 180;
    float circle = length(circle_FragCoord.xy - mousePos.xy);


    if (( (circle >= 180 && circle <= 220) && !(circle_FragCoord.y > y1 && circle_FragCoord.y < y ) )|| ((circle_FragCoord.y > mousePos.y) &&(circle_FragCoord.y < yyy) && (circle_FragCoord.x >= x ) && (circle_FragCoord.x<= x1)) )
    {
        frag_color = vec4(1.0,1.0,1.0,1.0);
    }
    else
    {
        frag_color = vec4(1.0,0.0,0.0,1.0);

    }
}