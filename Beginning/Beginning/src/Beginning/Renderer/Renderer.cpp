#include "Renderer.h"

#include "glad/glad.h"
#include <SDL.h>
#include "../../bgpch.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <direct.h>   // for _getcwd
#define GetCurrentDir _getcwd
#else
#include <unistd.h>   // for getcwd
#define GetCurrentDir getcwd
#endif

namespace Beginning{

	float spriteVertices[] = {
		// positions         // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};

	unsigned int spriteIndices[] = {
	0, 1, 3,   // first triangle
	1, 2, 3
	};


const char* vertexShaderSourceSprite = R"glsl(
		#version 330 core

		in vec3 position;
		in vec3 color;
		in vec2 texCoord;
		
		out vec3 Color;
		out vec2 TexCoord;

		void main()
		{
			Color = color;
			TexCoord = texCoord;
			gl_Position = vec4(position, 1.0);

		}
		)glsl";

const char* fragmentShaderSourceSprite = R"glsl(
		#version 330 core
		in vec3 Color;
		in vec2 TexCoord;

		out vec4 outColor;

		uniform sampler2D ourTexture;
		uniform sampler2D ourTexture2;

		void main()
		{
			vec4 colTex1 = texture(ourTexture, TexCoord);
			vec4 colTex2 = texture(ourTexture2, TexCoord);
			outColor = colTex1;
		}
)glsl";

Renderer::Renderer(Renderer::RendererType type) :
    m_window(nullptr), m_glContext(nullptr), 
    m_vbo(0), m_ebo(0), m_vao(0),
    m_shaderProgram(0) {


 	InitRenderer(800, 600);
	
	switch (type) {
	case Renderer::RendererType::Sprite:

		InitVertexData(spriteVertices, spriteIndices);
		ShaderProgram(vertexShaderSourceSprite, fragmentShaderSourceSprite);
		break;
	case Renderer::RendererType::Image:
	//	initVertexData(rectangleVertices, sizeof(rectangleVertices) / sizeof(float));
		break;
	case Renderer::RendererType::ThreeDimensions:
		//initVertexData(squareVertices, sizeof(squareVertices) / sizeof(float));
		break;
	default:
		std::cerr << "Invalid shape specified!" << std::endl;
		return;
	}
	


	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::cout << "Current working directory: " << std::string(buff) << std::endl;
	
    m_textureID = Renderer::LoadTexture("container.jpg"); //pedir ao stor para mudar o sitio onde vai buscar a imagem

	

	glUseProgram(m_shaderProgram);

	
	GLuint textureLocation;

	textureLocation = glGetUniformLocation(m_shaderProgram, "ourTexture");

    glUniform1i(textureLocation, 0);

	glClearColor(0.2f, 0.5f, 0.3f, 1.0f);


}

Renderer::~Renderer() {
    if (m_window != nullptr) {
        SDL_DestroyWindow(m_window);
    }

    if (m_glContext != nullptr) {
        SDL_GL_DeleteContext(m_glContext);
    }

    if (m_shaderProgram != 0) {
        glDeleteProgram(m_shaderProgram);
    }

    SDL_Quit();
}

void Renderer::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);



	// Draw a triangle

	SDL_GL_SwapWindow(m_window);
}

int Renderer::InitRenderer(int screenWidth, int screenHeight) {
  

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    m_window = SDL_CreateWindow("Minecraft World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
    if (m_window == nullptr)
    {
        std::cout << "Failed to create SDL Window" << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_GLContext m_glContext = SDL_GL_CreateContext(m_window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        SDL_Quit();
        return -2;
    }

    return 0;
}

int Renderer::InitVertexData(float vertices[], unsigned int indices[])
{   glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	glGenVertexArrays(1, &m_vao);


	
	float verticess[] = {
		// positions         // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};

	unsigned int indicess[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticess), (const void*)&verticess, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicess), (const void*)&indicess, GL_STATIC_DRAW);


	return 0;
}

int Renderer::ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint  success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	m_shaderProgram = glCreateProgram();

	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLint posAttrib = glGetAttribLocation(m_shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	GLint colorAttrib = glGetAttribLocation(m_shaderProgram, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	GLint texCoordAttrib = glGetAttribLocation(m_shaderProgram, "texCoord");
	glEnableVertexAttribArray(texCoordAttrib);
	glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	

	


	return 0;
}

unsigned int Renderer::LoadTexture(std::string fileName)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);


	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else
	{
		std::cout << "Failed to load texture " << stbi_failure_reason() << std::endl;
	}
	stbi_image_free(data);

	return texture;
}
}