#include <string>

class Entity;

class Component
{
public:
    virtual ~Component() = default;
    virtual void on_attach(Entity& owner) {(void) owner;} // Ignore the warning that the variable owner isn't used
    virtual void on_update(float dt) {(void)dt;}
};