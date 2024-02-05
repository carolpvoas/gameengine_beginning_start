#pragma once
#ifndef OPENGL_SDL_RENDERER_H
#define OPENGL_SDL_RENDERER_H

#include <SDL.h>
#include "../../bgpch.h"
#include "stb_image.h"

namespace Beginning{

class Renderer {
	
public:

    enum class RendererType {
        Sprite,
        Image,
        ThreeDimensions
        //.................
    };

	Renderer(RendererType type);
    ~Renderer();

    int InitRenderer(int screenWidth, int screenHeight);

    int InitVertexData(float vertices[], unsigned int indices[]);

    int ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

    unsigned int LoadTexture(std::string fileName);

    void Update();

private:

    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    
    unsigned int m_vbo; // Example vertex buffer
    unsigned int m_ebo; // Example index buffer
    unsigned int m_vao;

    unsigned int m_shaderProgram;

    unsigned int m_textureID;
};

extern const char* vertexShaderSourceSprite;
extern const char* fragmentShaderSourceSprite;


}

#endif OPENGL_SDL_RENDERER_H