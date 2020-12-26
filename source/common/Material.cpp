

#include "Material.hpp"

       void Material::setState(RenderState* st)
        {
            state =st;
        }
        RenderState* Material::getState()
        {
            return state;
        }
        void Material::LinkUniform()
        {
            for ( auto m : uniforms )
            {
            // Sprogram->set(m.first,m.second);
            }
        }
        void Material::setShader(GAME::ShaderProgram * S)
        {
            Sprogram = S;
        }


        GAME::ShaderProgram* Material::getShader() const
        {
            return Sprogram;
        }

        void Material::AddUniforms(std::string uniformName,std::any val)
        {
        uniforms[uniformName] = val;
        // Sprogram->set(uniformName,val);
        }

        std::any Material::getUniforms(std::string s)
        {
            return uniforms[s];
        }
