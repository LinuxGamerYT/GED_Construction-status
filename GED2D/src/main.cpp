#define SDL_MAIN_HANDLED

#include <iostream>

#include "SDL.h"
#include "glad/glad.h"
#include "Windowing/Window.h"

bool LoadTexture(const std::string& filepath, int& width, int& height, bool blended)
{
    int channels = 0;
    GLint format = GL_RGBA;

    switch (channels){
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (!blended)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   
    }


    return true;
}


int main()
{
    // -------------------------
    // Initialize SDL
    // -------------------------
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL Init failed: " << SDL_GetError() << '\n';
        return -1;
    }

    SDL_GL_LoadLibrary(nullptr);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    // -------------------------
    // Create Window
    // -------------------------

    GED_WINDOWING::Window window(
        "GED Engine",
        800,
        600,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        true
    );

    // -------------------------
    // Create OpenGL Context
    // -------------------------

    SDL_GLContext context = SDL_GL_CreateContext(window.GetWindow());

    if (!context)
    {
        std::cout << "Failed to create OpenGL context\n";
        return -1;
    }

    window.SetGLContext(context);

    // -------------------------
    // Load GLAD
    // -------------------------

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    // temporary texture ID for testing
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    // create width and height for the texture to be loaded into
    int width{0}, height{0};

    // Now we can load the texture
    if (!LoadTexture("assets/textures/texture.png", width, height, true))
    {
        std::cout << "Failed to load texture\n";
        return -1;
    }

    // creates vertices for a square to be drawn
    float vertices[] = {
        -0.5f, 0.5f, 0.0f, 0.f, 1.f,
        0.5f, 0.5f, 0.0f, 1.f, 1.f,
        0.5f, -0.5f, 0.0f, 1.f, 0.f,
        -0.5f, -0.5f, 0.0f, 0.f, 0.f
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };


    std::cout << "Vendor   : " << glGetString(GL_VENDOR) << '\n';
    std::cout << "Renderer : " << glGetString(GL_RENDERER) << '\n';
    std::cout << "Version  : " << glGetString(GL_VERSION) << '\n';

    // -------------------------
    // Vertex Shader
    // -------------------------

    const char* vertexSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPosition;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "out vec2 fragUVs;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPosition, 1.0);\n"
        "    fragUVs = aTexCoord;\n"
        "}\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader,1,&vertexSource,nullptr);
    glCompileShader(vertexShader);

    GLint success;

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);

    if(!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(vertexShader,512,nullptr,infoLog);

        std::cout << "Vertex Shader Error:\n"
                  << infoLog << '\n';

        return -1;
    }

    // -------------------------
    // Fragment Shader
    // -------------------------

    const char* fragmentSource =
        "#version 330 core\n"
        "in vec2 fragUVs;\n"
        "out vec4 color;\n"
        "uniform sampler2D uTexture;\n"
        "void main()\n"
        "{\n"
        "    color = texture(uTexture, fragUVs);\n"
        "}";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader,1,&fragmentSource,nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);

    if(!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(fragmentShader,512,nullptr,infoLog);

        std::cout << "Fragment Shader Error:\n"
                  << infoLog << '\n';

        return -1;
    }

    // -------------------------
    // Shader Program
    // -------------------------

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);

    if(!success)
    {
        char infoLog[512];

        glGetProgramInfoLog(shaderProgram,512,nullptr,infoLog);

        std::cout << "Program Link Error:\n"
                  << infoLog << '\n';

        return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // -------------------------
    // VAO & VBO
    // -------------------------

    GLuint VAO;
    GLuint VBO;

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    SDL_GL_SetSwapInterval(1);

    // -------------------------
    // Main Loop
    // -------------------------

    bool running = true;

    SDL_Event event;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = false;

            if(event.type == SDL_KEYDOWN &&
               event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        glViewport(0,0,
                   window.GetWidth(),
                   window.GetHeight());

        glClearColor(0.1f,0.1f,0.15f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texID);

        glDrawArrays(GL_TRIANGLES,0,3);

        glBindVertexArray(0);

        SDL_GL_SwapWindow(window.GetWindow());
    }

    // -------------------------
    // Cleanup
    // -------------------------

    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
    glDeleteProgram(shaderProgram);

    SDL_GL_DeleteContext(context);

    SDL_Quit();

    return 0;
}
