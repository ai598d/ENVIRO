#ifndef __WANDERER_AGENT__H
#define __WANDERER_AGENT__H

#include <string>
#include <cstdlib>
#include <math.h>
#include "enviro.h"

namespace
{

    using namespace enviro;

    class Calibrate : public State, public AgentInterface{

        public:
        
        void entry(const Event &e) {printf("Calibration State \n");}
        void during()
        {
            
            track_velocity(4, 0);
    
            cpVect xy = position(); // get current position          



            if (xy.x > 0 )
            {
                emit(Event(tick_name));
            }


        }
        void exit(const Event &e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;


    };

    class MovingForward : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {printf("Moving Forward State \n");}
        void during()
        {
            
            
            err_angvel = 1.5 - abs(angle()); // 
            track_velocity(4,kp*err_angvel); // proprtional controller gain Kp corrects angle
            cpVect xy = position();
            printf("th_error:%f\n",err_angvel);


            if (sensor_value(0) < 40)
            {
                emit(Event(tick_name));
            }
        }
        void exit(const Event &e) {}
        float err_angvel;
        float kp=-2;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    class Brake : public State, public AgentInterface{

        public:
        void entry(const Event &e) { printf("Brake State \n"); }
        void during()
        {
            
                
            track_velocity(0, 0);

           if (sensor_value(0) > 40) //140
            {
                emit(Event(tick_name));
            }
        }
        void exit(const Event &e) {}
        double rate;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;

        


    };

    class Rotating : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) { printf("Rotating State \n"); rate = rand() % 2 == 0 ? 2 : -2; }
        void during()
        {
            
            track_velocity(0, rate);
            cpFloat theta = angle();
           if (theta < 1.2) //140
            {
                emit(Event(tick_name));
            }
        }
        void exit(const Event &e) {}
        double rate;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };


       

    class WandererController : public StateMachine, public AgentInterface
    {

    public:
        WandererController() : StateMachine()
        {

            set_initial(calibrate);
            tick_name = "tick_" + std::to_string(rand() % 1000); // use an agent specific generated
                                                                 // event name in case there are
                                                                 // multiple instances of this class
            
            add_transition(tick_name, calibrate,rotating);
            add_transition(tick_name, rotating, moving_forward);
            add_transition(tick_name, moving_forward, brake);
            add_transition(tick_name, brake, moving_forward);
            
            
            calibrate.set_tick_name(tick_name);
            moving_forward.set_tick_name(tick_name);
            rotating.set_tick_name(tick_name);
            brake.set_tick_name(tick_name);
        }

        // declare state objects
        Calibrate calibrate;
        Brake brake;
        MovingForward moving_forward;
        Rotating rotating;
        
        std::string tick_name;
    };

    class Wanderer : public Agent
    {

    public:
        Wanderer(json spec, World &world) : Agent(spec, world)
        {
            add_process(wc);
        }

        WandererController wc; // decalre wanderer control onject
    };

    DECLARE_INTERFACE(Wanderer);

}

#endif