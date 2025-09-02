#include <engine/entity/entity.h>

#include <vector>
#include <memory>
#define MAX_ENTITY 1000

class Level
{
public:
    Level(const char* _name);
    ~Level();

    Entity& create_entity(const char* name);

    void update(float dt);
    void render(float dt);

    const char* name;
private:
    std::vector<std::unique_ptr<Entity>> m_entities; // std::unique_ptr : https://en.cppreference.com/w/cpp/memory/unique_ptr.html
};