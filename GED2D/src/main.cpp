#define SDL_MAIN_HANDLED

#include <iostream>

#include "SDL.h"
#include "glad/glad.h"
#include "Windowing/Window.h"

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

    std::cout << "Vendor   : " << glGetString(GL_VENDOR) << '\n';
    std::cout << "Renderer : " << glGetString(GL_RENDERER) << '\n';
    std::cout << "Version  : " << glGetString(GL_VERSION) << '\n';

    // -------------------------
    // Triangle vertices
    // -------------------------

    float vertices[] =
    {
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    // -------------------------
    // Vertex Shader
    // -------------------------

    const char* vertexSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos,1.0);\n"
        "}";

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
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0,0.0,1.0,1.0);\n"
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
        3 * sizeof(float),
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
