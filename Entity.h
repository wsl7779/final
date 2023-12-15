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
#include "Map.h"

enum EntityType { PLAYER, ENEMY, HITBOX };
enum HitboxType { PUNCH, KICK };
enum HitboxState { INACTIVE, ACTIVE };
enum AIType { DUMBO, KICKER, BOSS };
enum AIState { CHILL, PUNCHING, KICKING, OHO, BOSSFIGHT, OY };


class Entity
{
private:
    bool m_is_active = true;
    EntityType m_type;
    AIType m_aitype;
    AIState m_aistate;
    HitboxType hit_type;
    HitboxState hit_state;

    // ––––– ANIMATION ––––– //

    // ––––– PHYSICS (GRAVITY) ––––– //
    glm::vec3 m_position;
    glm::vec3 m_velocity;
    glm::vec3 m_acceleration;

    // ————— TRANSFORMATIONS ————— //
    float     m_speed;
    glm::vec3 m_movement;
    glm::vec3 m_scale = glm::vec3(1.0f);
    glm::mat4 m_model_matrix;

    float m_width = 1;
    float m_height = 1;
    float patrol_sec = 0.5f;
    float patrol_sec2 = 1.0f;
    float current_step = 0.0f;
    bool is_left = true;

    float jump_time = 2.0f;
    float jump_time2 = 1.5f;
    float current_jump = 0.0f;

    float current_time = 0.0f;
    float cooldown = 1.5f;
    bool cd = false;
    bool kicked = false;

    float startup_timep = 0.05f;
    float startup_timek = 0.2f;
    float current_start = 0.0f;

public:
    bool facing_right = true;
    bool m_is_jumping = false;
    float m_jumping_power = 7.0f;
    bool dead = false;

    bool crouching = false;

    bool hit = false;
    bool punch_input = false;
    bool punching = false;
    const float punch_cd = 0.25f;
    float punch_timer = 0.0f;

    bool kick_input = false;
    bool kicking = false;
    const float kick_cd = 0.5f;
    float kick_timer = 0.0f;

    float act_timer = 0.0f;
    bool is_act = false;

    bool const check_collision(Entity* other) const;
    void const check_collision_x(Entity* collidable_entities, int collidable_entity_count);
    void const check_collision_y(Entity* collidable_entities, int collidable_entity_count);

    void const check_collision_y(Map* map);
    void const check_collision_x(Map* map);

    // ————— STATIC VARIABLES ————— //
    static const int SECONDS_PER_FRAME = 4;

    // ————— ANIMATION ————— //

    int* m_idle = NULL;
    int* m_jumping = NULL;

    int m_animation_frames = 0,
        m_animation_index = 0,
        m_animation_cols = 0,
        m_animation_rows = 0;

    int* m_animation_indices = NULL;
    float m_animation_time = 0.0f;

    bool m_collided_top = false;
    bool m_collided_bottom = false;
    bool m_collided_left = false;
    bool m_collided_right = false;

    GLuint    m_texture_id;

    // ————— METHODS ————— //
    Entity();
    ~Entity();

    void draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index);
    void update(float delta_time, Entity* player, Entity* objects, int object_count, Map* map);
    void hit_update(float delta_time, Entity* player, Entity* objects, int object_count);
    void render(ShaderProgram* program);


    void activate() { m_is_active = true; };
    void deactivate() { m_is_active = false; };
    void toggle_active() { m_is_active = !m_is_active; };

    void ai_activate(Entity* player, Entity* objects, float delta_time);
    void ai_patrol(Entity* player, Entity* opp, float delta_time);
    void ai_jump(Entity* player, float delta_time);
    void ai_boss(Entity* player, Entity* opp, float delta_time);

    void hitbox_activate(Entity* player, Entity* objects, float delta_time);
    void hit_punch(float delta_time);
    void hit_kick(float delta_time);

    void move_left() { m_movement.x = -1.0f; };
    void move_right() { m_movement.x = 1.0f; };
    void punch(Entity* player) {
        if (!player[1].is_act && !player[2].is_act) { player[1].punch_input = true; }
    };
    void kick(Entity* player) {
        if (!player[1].is_act && !player[2].is_act) { player[2].kick_input = true; }
    };
    void crouch() {
        if (!crouching) {
            m_position = glm::vec3(m_position.x, m_position.y - 1.0f, 0.0f);
            m_width = 1.0f;
            m_height = 1.5f;
            m_scale = glm::vec3(1.0f, 1.5f, 1.0f);
            crouching = true;
        }
    }

    void stand() {
        if (crouching) {
            m_width = 1.0f;
            m_height = 3.0f;
            m_scale = glm::vec3(1.0f, 3.0f, 1.0f);
            crouching = false;
        }
    }



    // ————— GETTERS ————— //
    glm::vec3 const get_position()     const { return m_position; };
    glm::vec3 const get_velocity()     const { return m_velocity; };
    glm::vec3 const get_acceleration() const { return m_acceleration; };
    glm::vec3 const get_movement()     const { return m_movement; };
    float     const get_jumping_power()  const { return m_jumping_power; };
    EntityType const get_type()     const { return m_type; };
    AIType     const get_ai_type()        const { return m_aitype; };
    AIState    const get_ai_state()       const { return m_aistate; };
    float      const get_speed()          const { return m_speed; };
    bool       const get_active()         const { return m_is_active; };

    // ————— SETTERS ————— //
    void const set_position(glm::vec3 new_position) { m_position = new_position; };
    void const set_velocity(glm::vec3 new_velocity) { m_velocity = new_velocity; };
    void const set_acceleration(glm::vec3 new_position) { m_acceleration = new_position; };
    void const set_movement(glm::vec3 new_movement) { m_movement = new_movement; };
    void const set_type(EntityType new_type, bool active) { m_type = new_type; m_is_active = active; };
    void const set_wh(float new_w, float new_h) { m_width = new_w; m_height = new_h; };
    void const set_speed(float new_speed) { m_speed = new_speed; };
    void const set_jumping_power(float new_jumping_power) { m_jumping_power = new_jumping_power; };
    void const set_entity_type(EntityType new_entity_type) { m_type = new_entity_type; };
    void const set_ai_type(AIType new_ai_type) { m_aitype = new_ai_type; };
    void const set_ai_state(AIState new_state) { m_aistate = new_state; };
    void const set_hit_type(HitboxType new_hit_type) { hit_type = new_hit_type; };
    void const set_hit_state(HitboxState new_hit_state) { hit_state = new_hit_state; };
    void const set_scale(glm::vec3 new_scale) { m_scale = new_scale; };
    void const change_texture(GLuint new_id) { m_texture_id = new_id; };
};