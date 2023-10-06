#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>  // Include GLM after GLEW
#include "shader_util.h"

// Vertex data for the cube
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  // front bottom left
     0.5f, -0.5f, -0.5f,  // front bottom right
     0.5f,  0.5f, -0.5f,  // front top right
     0.5f,  0.5f, -0.5f,  // front top right
    -0.5f,  0.5f, -0.5f,  // front top left
    -0.5f, -0.5f, -0.5f,  // front bottom left

    -0.5f, -0.5f,  0.5f,  // back bottom left
     0.5f, -0.5f,  0.5f,  // back bottom right
     0.5f,  0.5f,  0.5f,  // back top right
     0.5f,  0.5f,  0.5f,  // back top right
    -0.5f,  0.5f,  0.5f,  // back top left
    -0.5f, -0.5f,  0.5f,  // back bottom left

    -0.5f,  0.5f,  0.5f,  // top back left
    -0.5f,  0.5f, -0.5f,  // top front left
    -0.5f, -0.5f, -0.5f,  // bottom front left
    -0.5f, -0.5f, -0.5f,  // bottom front left
    -0.5f, -0.5f,  0.5f,  // bottom back left
    -0.5f,  0.5f,  0.5f,  // top back left

     0.5f,  0.5f,  0.5f,  // top back right
     0.5f,  0.5f, -0.5f,  // top front right
     0.5f, -0.5f, -0.5f,  // bottom front right
     0.5f, -0.5f, -0.5f,  // bottom front right
     0.5f, -0.5f,  0.5f,  // bottom back right
     0.5f,  0.5f,  0.5f,  // top back right

    -0.5f, -0.5f, -0.5f,  // bottom front left
     0.5f, -0.5f, -0.5f,  // bottom front right
     0.5f, -0.5f,  0.5f,  // bottom back right
     0.5f, -0.5f,  0.5f,  // bottom back right
    -0.5f, -0.5f,  0.5f,  // bottom back left
    -0.5f, -0.5f, -0.5f,  // bottom front left

    -0.5f,  0.5f, -0.5f,  // top front left
     0.5f,  0.5f, -0.5f,  // top front right
     0.5f,  0.5f,  0.5f,  // top back right
     0.5f,  0.5f,  0.5f,  // top back right
    -0.5f,  0.5f,  0.5f,  // top back left
    -0.5f,  0.5f, -0.5f   // top front left
};

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Minecraft Clone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Here setup VAO, VBO, and shaders
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Load and compile shaders
    GLuint shaderProgram = loadShaders("../shaders/vertexShader.glsl", "../shaders/fragmentShader.glsl");
    glUseProgram(shaderProgram);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Also clear the depth buffer

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);  // Drawing the cube using the VAO

        SDL_GL_SwapWindow(window);  // Swap the window buffers
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
