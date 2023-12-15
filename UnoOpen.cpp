/**
* Author: Will Lee
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "UnoOpen.h"
#include "Utility.h"


UnoOpen::~UnoOpen()
{
}

void UnoOpen::initialise()
{
    m_state.next_scene_id = 2;
}

void UnoOpen::update(float delta_time)
{
}


void UnoOpen::render(ShaderProgram* program)
{
    GLuint text_texture_id = Utility::load_texture("assets/font1.png");
    Utility::draw_text(program, text_texture_id, std::string("Rookie Rick 0-24"), 0.25f, 0.0f, glm::vec3(2.7f, -2.0f, 0.0f));
    Utility::draw_text(program, text_texture_id, std::string("Runs around and randomly punches"), 0.25f, 0.0f, glm::vec3(1.2f, -4.0f, 0.0f));
    Utility::draw_text(program, text_texture_id, std::string("Press ENTER to continue"), 0.25f, 0.0f, glm::vec3(2.0f, -6.0f, 0.0f));
}