#ifndef GLWRAPPER_TEST_CONTEXT_HPP
#define GLWRAPPER_TEST_CONTEXT_HPP

/*
Creates a GL context using SDL2 and glew 2
*/

#include "GL/glew.h"

#include "glwrapper/profile.hpp"

#include "SDL.h"


// Not a super clean RAII class.
// Doesn't destroy correctly if there is an error in the constructor
// It's okay, this is only used for testing.
class Context {
private:
    bool init = false;
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
public:
    Context() {

        if(SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error("SDLInit");
        }

        int sdlProfileRequest;
        int majorRequest;
        int minorRequest;

        switch(glwrapper::getProfile()) {

        case glwrapper::Profile::DESKTOP:
            sdlProfileRequest = SDL_GL_CONTEXT_PROFILE_CORE;
            majorRequest = 3;
            minorRequest = 2;
            break;

        default:
            throw std::runtime_error("unknown profile");
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, sdlProfileRequest);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorRequest);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorRequest);

        window = SDL_CreateWindow("glwrapper-test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
        if(!window) {
            throw std::runtime_error("SDL_CreateWindow");
        }

        glContext = SDL_GL_CreateContext(window);
        if(!glContext) {
            throw std::runtime_error("SDL_GL_CreateContext");
        }

        if(glewInit() != GLEW_OK) {
            throw std::runtime_error("glewInit");
        }
    }

    ~Context() {
        if(glContext) {
            SDL_GL_DeleteContext(glContext);
            glContext = nullptr;
        }

        if(window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }

        if(init) {
            SDL_Quit();
            init = false;
        }
    }
};


#endif //#ifndef GLWRAPPER_TEST_CONTEXT_HPP
