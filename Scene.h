/**
* Author: Will Lee
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Utility.h"
#include "Entity.h"
#include "Map.h"
#include <vector>
#include <ctime>
#include "cmath"

/**
    Notice that the game's state is now part of the Scene class, not the main file.
*/

enum SceneType { BATTLE, NOT };

struct GameState
{
    Map* map;
    Entity* P1;
    Entity* P2;

    Mix_Music* bgm;
    Mix_Chunk* dead_sfx;

    int next_scene_id;
};

class Scene {
public:
    int m_number_of_enemies = 3;

    float current_death = 0.0f;
    float death_timer = 7.0f;

    SceneType m_scene;
    GameState m_state;
    virtual void initialise() = 0;
    virtual void update(float delta_time) = 0;
    virtual void render(ShaderProgram* program) = 0;

    GameState const get_state()             const { return m_state; }
    int       const get_number_of_enemies() const { return m_number_of_enemies; }
};