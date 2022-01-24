#pragma once

#include <chrono>
#include <iostream>
#include <thread>
#include <map>
#include <functional>


#define UNDEFINED_TIME -1.0 //used in permanent time events


enum time_event
{
    logic = 0 ,
    graphics , 
    handle_event
};

/*
dtTimeEvent should be used when dt is undefined, such as animation class movements.
*/

struct dtTimeEvent
{
    public:
    dtTimeEvent(std::function<void(double)> foo)
    {
        function  =  foo;
        t = std::chrono::high_resolution_clock::now();
    }
    void update()
    {
        auto dt = (std::chrono::high_resolution_clock::now() - t).count() / 1000000.0;

        function(dt);

        t = std::chrono::high_resolution_clock::now();
    }


    private:
        std::chrono::high_resolution_clock::time_point t;
        std::function<void(double)> function;

};

/*

timeEvent 

*/

struct timeEvent
{
            timeEvent(double _duration , std::function<void()> _function)
            {
                function = _function;
                duration = _duration;
                time_left = _duration;
                t1 = std::chrono::high_resolution_clock::now();

            }
            double duration;
            double time_left;
            void update()
            {
                
                double dt = (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0;
                t1 = std::chrono::high_resolution_clock::now();
                time_left -= dt;
                if(time_left < 0.0){
                    
                    int lost_calls = int(abs(time_left) / duration) + 1;
                    for(int i=0;i<lost_calls;i++) function();
                    time_left += duration * lost_calls;
                }
                
            }

            std::function<void()> function;

            private:
                std::chrono::high_resolution_clock::time_point t1;
};


class timer
{
    public:
                ~timer();
                timer(double fps , double cps);
                /*
                    warning: duration should be greater than 1000.0 / cps (ms), it may impact performance
                */
                void newTimeEvent(int id , double duration ,  std::function<void()> function); //create a time event, which executes a given function everytime time elapsed reaches duration in milliseconds
                void removeTimeEvent(int id);
                void process_time_events();

                void new_dt_function(int foo_id , std::function<void(double)> foo);
                void remove_dt_function(int foo_id);
                void update_dt_functions();


                void start_frame();
                void end_frame();
                void wait();

                void fpsTick();
                bool canTickFps();
                bool canTickCps();
                void cpsTick();

                


    private:
                std::map<int , timeEvent*> time_events;
                std::map<int , dtTimeEvent*> dtTime_events;
                double minium_time_event;
                
                std::chrono::high_resolution_clock::time_point start_f;
                std::chrono::high_resolution_clock::time_point end_f;

                int64_t standard_delay = 166666667;

                double fps = 30 , cps = 60;
                double fps_cps_ratio = fps / cps;
                int fps_tick = 1 , cps_tick = 1;
                

        



};