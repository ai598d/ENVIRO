#ifndef __DIFF_DRIVE_AGENT__H
#define __DIFF_DRIVE_AGENT__H 

#include "enviro.h"

using namespace enviro;

class MovingForward : public State, public AgentInterface
{
public:
    int time;
    void entry(const Event &e) {}
    void during()
    {
        track_velocity(-4, 0);
        //move_toward(100,0);
       

        if (sensor_value(1) < 40){
        
            emit(Event(tick_name));
        }
        
    }
    void exit(const Event &e) {}
    void set_tick_name(std::string b) { tick_name = b; }
    std::string tick_name;
};

class Reverse : public State, public AgentInterface
{
public:
    void entry(const Event &e) { rate = rand() % 2 == 0 ? 2 : -2; }
    void during()
    {
        //move_toward(0,0);
        track_velocity(10,0);

        if (sensor_value(0) < 40){
        
            emit(Event(tick_name));
        }
        
    }
    void exit(const Event &e) {}
    double rate;
    void set_tick_name(std::string b) { tick_name = b; }
    std::string tick_name;
};



class BlockController : public StateMachine, public AgentInterface {

    public:
    //BlockController();

    //void init() {}
    //void start() {}
    //void update();
    //void stop() {}

    BlockController(): StateMachine()
    {

        set_initial(moving_forward);
        tick_name = "tick_" + std::to_string(rand() % 1000); // use an agent specific generated
                                                                 // event name in case there are
                                                                 // multiple instances of this class
        add_transition(tick_name, moving_forward, reverse);
        add_transition(tick_name, reverse, moving_forward);
        moving_forward.set_tick_name(tick_name);
        reverse.set_tick_name(tick_name);
    }

    MovingForward moving_forward;
    Reverse reverse;
    std::string tick_name;

};

class Block : public Agent {
    public:
    Block(json spec, World& world) : Agent(spec, world) {
        add_process(bc);
    }
    private:
    BlockController bc;

};

DECLARE_INTERFACE(Block)

#endif