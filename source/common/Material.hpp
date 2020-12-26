#ifndef GFX_LAB_MATERIAL_H
#define GFX_LAB_MATERIAL_H
 
//#include <shader.hpp>
#include "RenderState.hpp"

    class Material {

        private:    
            // shader ,uniforms , render state

            RenderState* state;
            GAME::ShaderProgram* Sprogram;
            
            std::map<std::string,std::any> uniforms;

            //std::pair<Texture2D*, Sampler*> // gwa el

        public:

            void setState(RenderState* st);
            RenderState* getState();
            void LinkUniform();
            void setShader(GAME::ShaderProgram* S);


            GAME::ShaderProgram* getShader() const;

            void AddUniforms(std::string uniformName,std::any val);

            std::any getUniforms(std::string s);


        };
#endif //MATERIAL_H
