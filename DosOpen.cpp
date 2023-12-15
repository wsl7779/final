/**
* Author: Will Lee
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "DosOpen.h"
#include "Utility.h"


DosOpen::~DosOpen()
{
}

void DosOpen::initialise()
{
    m_state.next_scene_id = 4;
}

void DosOpen::update(float delta_time)
{
}


void DosOpen::render(ShaderProgram* program)
{
    GLuint text_texture_id = Utility::load_texture("assets/font1.png");
    Utility::draw_text(program, text_texture_id, std::string("The Slidester 3-17"), 0.25f, 0.0f, glm::vec3(2.7f, -2.0f, 0.0f));
    Utility::draw_text(program, text_texture_id, std::string("Watch out for his lightning fast slide!"), 0.25f, 0.0f, glm::vec3(0.3f, -3.5f, 0.0f));
    Utility::draw_text(program, text_texture_id, std::string("Either beat him to the punch,"), 0.25f, 0.0f, glm::vec3(1.5f, -4.0f, 0.0f));
    Utility::draw_text(program, text_texture_id, std::string("or get him while he backs off."), 0.25f, 0.0f, glm::vec3(1.3f, -4.5f, 0.0f));
    Utility::draw_text(program, text_texture_id, std::string("Press ENTER to continue"), 0.25f, 0.0f, glm::vec3(2.0f, -6.0f, 0.0f));
}