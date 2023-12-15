/**
* Author: Will Lee
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Win.h"
#include "Utility.h"


Win::~Win()
{
}

void Win::initialise()
{
    m_state.next_scene_id = 0;
}

void Win::update(float delta_time)
{
}


void Win::render(ShaderProgram* program)
{
    GLuint text_texture_id = Utility::load_texture("assets/font1.png");
    Utility::draw_text(program, text_texture_id, std::string("You win. Press ENTER to return."), 0.25f, 0.0f, glm::vec3(1.0f, -4.0f, 0.0f));
}