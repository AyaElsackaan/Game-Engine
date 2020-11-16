#version 330 core

uniform vec2 key;

uniform vec2 mousePos;
// The output that goes to the frame buffer
out vec4 frag_color;

// Just a constant
#define PI 3.1415926535897932384626433832795
void main()
{
    
    vec2 circle1_FragCoord;
    vec2 circle2_FragCoord;
    vec2 now_FragCoord ;
    now_FragCoord.x =  gl_FragCoord.x;
    now_FragCoord.y = 720 - gl_FragCoord.y; 

    circle1_FragCoord.x =  mousePos.x + 60;
    circle1_FragCoord.y  =  mousePos.y - 80;

    circle2_FragCoord.x =  mousePos.x - 60;
    circle2_FragCoord.y  =  mousePos.y - 80;

    float y =  1.42 *(gl_FragCoord.x - mousePos.x) + mousePos.y + 125;
    float y1 = - 1.42* (gl_FragCoord.x - mousePos.x) + mousePos.y + 125;
    float circle1 = length(now_FragCoord.xy - circle1_FragCoord.xy);
    float circle2 = length(now_FragCoord.xy - circle2_FragCoord.xy);


    if (  (circle1 <= 69 ||  circle2 <= 69) || ( (now_FragCoord.y < y) && (now_FragCoord.y < y1) && (now_FragCoord.y > (circle1_FragCoord.y + 35 ))  ) )
    {
        frag_color = vec4(1.0,1.0,1.0,1.0);
    }
    else
    {
        frag_color = vec4(1.0,0.0,0.0,1.0);

    }
    
}