/**
* Author: Will Lee
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Title.h"
#include "Utility.h"


Title::~Title()
{
    Mix_FreeMusic(m_state.bgm);
}

void Title::initialise()
{
    m_state.next_scene_id = 1;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    m_state.bgm = Mix_LoadMUS("assets/music/dolce.mp3");
    //Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME);
}

void Title::update(float delta_time)
{
}


void Title::render(ShaderProgram* program)
{
    GLuint text_texture_id = Utility::load_texture("assets/font1.png");
    Utility::draw_text(program, text_texture_id, std::string("EXTREME FIGHTER 900000"), 0.25f, 0.0f, glm::vec3(2.2f, -2.0f, 0.0f));
    Utility::draw_text(program, text_texture_id, std::string("Please press ENTER to begin."), 0.25f, 0.0f, glm::vec3(2.0f, -4.0f, 0.0f));
}