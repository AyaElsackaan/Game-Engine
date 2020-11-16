#version 330 core

uniform vec2 key;

uniform vec2 mousePos;
// The output that goes to the frame buffer
out vec4 frag_color;

// Just a constant
#define PI 3.1415926535897932384626433832795
void DrawFace()
{
    vec2 face_FragCoord ;
    vec2 eye1_Center ;
    vec2 eye2_Center ;
    vec2 smile_Center ;
    float smile=0;
    face_FragCoord.x =  gl_FragCoord.x;
    face_FragCoord.y = 720 - gl_FragCoord.y; 

    eye1_Center.x =  mousePos.x + 60;
    eye1_Center.y =  mousePos.y - 60;
    eye2_Center.x =  mousePos.x - 60;
    eye2_Center.y =  mousePos.y - 60;

    smile_Center.x =  mousePos.x;
    smile_Center.y =  mousePos.y + 50;

    float eye1 = length(face_FragCoord.xy - eye1_Center.xy);
    float eye2 = length(face_FragCoord.xy - eye2_Center.xy);

    float face = length(face_FragCoord.xy - mousePos.xy);
    if ( ( ((720-gl_FragCoord.y) - smile_Center.y > 0) &&  (720-gl_FragCoord.y) > 0) || ( ((720-gl_FragCoord.y) - smile_Center.y  < 0) &&  (720-gl_FragCoord.y)< 0))
    {
        smile = length(face_FragCoord.xy - smile_Center.xy);
    }



    if ( (face <= 200 && face >= 190) ||  eye1 <= 20 ||  eye2 <= 20 || ( (smile <= 100 && smile >= 85) ))
    {
        frag_color = vec4(1.0,1.0,1.0,1.0);
    }
    else
    {
        frag_color = vec4(1.0,0.0,0.0,1.0);

    }


}



void main() {

// face
   // if (key.x == 1)
   // {
   //    DrawFace(); 
   // }
    /// HEART
   //// else if (key.x == 2)
   // {
   //     DrawHeart();
   // }

   // else if (key.x == 3)
    ///{
    //    DrawG();
  //  }
  //  else if (key.x == 4)
   // {
    //    DrawHeart();
   // }
    vec2 face_FragCoord ;
    vec2 eye1_Center ;
    vec2 eye2_Center ;
    vec2 smile_Center ;
    float smile=0;
    face_FragCoord.x =  gl_FragCoord.x;
    face_FragCoord.y = 720 - gl_FragCoord.y; 

    eye1_Center.x =  mousePos.x + 60;
    eye1_Center.y =  mousePos.y - 60;
    eye2_Center.x =  mousePos.x - 60;
    eye2_Center.y =  mousePos.y - 60;

    smile_Center.x =  mousePos.x;
    smile_Center.y =  mousePos.y + 50;

    float eye1 = length(face_FragCoord.xy - eye1_Center.xy);
    float eye2 = length(face_FragCoord.xy - eye2_Center.xy);

    float face = length(face_FragCoord.xy - mousePos.xy);
    if ( ( ((720-gl_FragCoord.y) - smile_Center.y > 0) &&  (720-gl_FragCoord.y) > 0) || ( ((720-gl_FragCoord.y) - smile_Center.y  < 0) &&  (720-gl_FragCoord.y)< 0))
    {
        smile = length(face_FragCoord.xy - smile_Center.xy);
    }

    if ( (face <= 200 && face >= 190) ||  eye1 <= 20 ||  eye2 <= 20 || ( (smile <= 100 && smile >= 85) ))
    {
        frag_color = vec4(1.0,1.0,1.0,1.0);
    }
    else
    {
        frag_color = vec4(1.0,0.0,0.0,1.0);

    }

 

}
