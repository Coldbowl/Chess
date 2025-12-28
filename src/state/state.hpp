#pragma once

#pragma once

// Forward declarations
namespace sf {class RenderWindow; }
class Engine;

class State {
public:
    explicit State(Engine* engine) : engine(engine) {}
    virtual ~State() = default;

    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handle_events() = 0;

protected:
    Engine* engine;
};
