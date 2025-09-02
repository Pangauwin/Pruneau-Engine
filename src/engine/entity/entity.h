#pragma once

#include <engine/component/component.h>

#include <memory>
#include <unordered_map>
#include <typeindex>

class Entity
{
public:
    explicit Entity(std::string name) : m_name(std::move(name)) {}


    template<class T, class... Args>
    T& add_component(Args&&... args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component Class");        
        std::unique_ptr<T> comp = std::make_unique<T>(std::forward<Args>(args)...);
        Component& ref = *comp;
        ((Component*)comp)->on_attach(*this); // pass the owner to the component
    }

    template<class T>
    T* get_component()
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component Class");        
        auto it = m_components.find(std::type_index(typeid(T)));
        if(it == m_components.end()) return nullptr;
        return static_cast<T*>(it->second.get());
    }

    void update(float dt)
    {
        for(auto& [_, comp] : m_components) comp->on_update(dt);
    }

    const std::string& name() const {return m_name;}

private:
    std::string m_name;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
};