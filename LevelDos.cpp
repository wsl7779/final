/**
* Author: Will Lee
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "LevelDos.h"
#include "Utility.h"

#define LEVEL_WIDTH 11
#define LEVEL_HEIGHT 10

unsigned int LEVELDOS_DATA[] =
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    23, 24, 24, 25, 1, 1, 23, 24, 24, 24, 1,
};

LevelDos::~LevelDos()
{
    delete[]  m_state.P1;
    delete[]  m_state.P2;
    delete    m_state.map;
}

void LevelDos::initialise()
{
    current_death = 0;
    m_state.next_scene_id = -1;

    GLuint map_texture_id = Utility::load_texture("assets/tileset.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELDOS_DATA, map_texture_id, 1.0f, 22, 7);

    m_state.P1 = new Entity[3];
    m_state.P2 = new Entity[3];

    // Code from main.cpp's initialise()
     // Existing
    m_state.P1[0].set_entity_type(PLAYER);
    m_state.P1[0].set_position(glm::vec3(2.0f, -4.0f, 0.0f));
    m_state.P1[0].set_movement(glm::vec3(0.0f));
    m_state.P1[0].set_speed(2.5f);
    m_state.P1[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.P1[0].m_texture_id = Utility::load_texture("assets/yuuka trans.png");
    m_state.P1[0].set_wh(1.0f, 3.0f);
    m_state.P1[0].set_scale(glm::vec3(1.0f, 3.0f, 1.0f));


    // Idle

   /* m_state.player->m_idle = new int[4] {0, 1, 2, 3};

    m_state.player->m_animation_indices = m_state.player->m_idle;
    m_state.player->m_animation_frames = 4;
    m_state.player->m_animation_index = 0;
    m_state.player->m_animation_time = 0.0f;
    m_state.player->m_animation_cols = 4;
    m_state.player->m_animation_rows = 1;
    m_state.player->set_wh(0.9f, 0.9f);*/


    // Jumping
    m_state.P1[0].m_jumping_power = 5.0f;

    /**
     Enemies' stuff */

    m_state.P2[0].facing_right = false;
    m_state.P2[0].m_texture_id = Utility::load_texture("assets/yuuka trans.png");
    m_state.P2[0].set_entity_type(ENEMY);
    m_state.P2[0].set_ai_type(KICKER);
    m_state.P2[0].set_ai_state(KICKING);
    m_state.P2[0].set_position(glm::vec3(9.0f, -4.0f, 0.0f));
    m_state.P2[0].set_movement(glm::vec3(0.0f));
    m_state.P2[0].set_speed(2.5f);
    m_state.P2[0].set_wh(1.0f, 3.0f);
    m_state.P2[0].set_scale(glm::vec3(1.0f, 3.0f, 1.0f));
    m_state.P2[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));


    // HITBOXES

    m_state.P1[1].set_entity_type(HITBOX);
    m_state.P1[1].set_hit_type(PUNCH);
    m_state.P1[1].set_hit_state(INACTIVE);
    m_state.P1[1].m_texture_id = Utility::load_texture("assets/fist right.png");
    m_state.P1[1].deactivate();

    m_state.P1[2].set_entity_type(HITBOX);
    m_state.P1[2].set_hit_type(KICK);
    m_state.P1[2].set_hit_state(INACTIVE);
    m_state.P1[2].m_texture_id = Utility::load_texture("assets/fist right.png");
    m_state.P1[2].set_wh(2.0f, 0.5f);
    m_state.P1[2].set_scale(glm::vec3(2.0f, 0.5f, 1.0f));
    m_state.P1[2].deactivate();

    m_state.P2[1].set_entity_type(HITBOX);
    m_state.P2[1].set_hit_type(PUNCH);
    m_state.P2[1].set_hit_state(INACTIVE);
    m_state.P2[1].m_texture_id = Utility::load_texture("assets/fist left.png");
    m_state.P2[1].deactivate();

    m_state.P2[2].set_entity_type(HITBOX);
    m_state.P2[2].set_hit_type(KICK);
    m_state.P2[2].set_hit_state(INACTIVE);
    m_state.P2[2].m_texture_id = Utility::load_texture("assets/fist left.png");
    m_state.P2[2].set_wh(2.0f, 0.5f);
    m_state.P2[2].set_scale(glm::vec3(2.0f, 0.5f, 1.0f));
    m_state.P2[2].deactivate();

}

void LevelDos::update(float delta_time)
{
    m_state.P1[0].update(delta_time, m_state.P1, m_state.P2, ENEMY_COUNT, m_state.map);

    m_state.P2[0].update(delta_time, m_state.P2, m_state.P1, ENEMY_COUNT, m_state.map);

    m_state.P1[1].hit_update(delta_time, m_state.P1, m_state.P2, ENEMY_COUNT);

    m_state.P2[1].hit_update(delta_time, m_state.P2, m_state.P1, ENEMY_COUNT);

    m_state.P1[2].hit_update(delta_time, m_state.P1, m_state.P2, ENEMY_COUNT);

    m_state.P2[2].hit_update(delta_time, m_state.P2, m_state.P1, ENEMY_COUNT);

    for (int i = 0; i < 3; i++) {
        if (m_state.P2[i].dead) {

            if (current_death > death_timer) {
                m_state.next_scene_id = 5;
            }
            current_death += delta_time;
        }
    }
}


void LevelDos::render(ShaderProgram* program)
{
    m_state.map->render(program);
    for (int i = 0; i < 3; i++)
    {
        m_state.P1[i].render(program);
        m_state.P2[i].render(program);
    }

    if (current_death > death_timer - 2.0f) {
        GLuint text_texture_id = Utility::load_texture("assets/font1.png");
        Utility::draw_text(program, text_texture_id, std::string("You killed him."), 0.25f, 0.0f, glm::vec3(4.0f, -4.0f, 0.0f));
    }
}