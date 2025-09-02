#include "level.h"

Level::Level(const char *_name)
{
}

Level::~Level()
{
}

Entity &Level::create_entity(const char *name)
{
    m_entities.push_back(std::make_unique<Entity>(name));
    return *m_entities.back();
}

void Level::update(float dt)
{
    for (auto& e : m_entities)
    {
        e->update(dt);
    }
    
}

void Level::render(float dt)
{
}
