#pragma once

#include "stdexcept"
#include "entity.h"
#include <vector>
#include "timer.h"

namespace sprite_texture
{
    namespace player
    {
        static std::vector<int> sp1 = {texture_id::t1,texture_id::t2, texture_id::t3};
    };
}

enum sprite_speed
{
    normal = 750,
    medium = 500,
    fast = 250,
};



class sprite : public entity
{
    public:
        sprite(std::vector<int>& _texture_ids , sprite_speed speed , timer* clock); 
        /*
        _texture_ids -> vector containing a list of texture ids of a given sprite
        sprite_speed -> time needed in ms to update sprite animation
        clock        -> current scene timer object
        */
         
        ~sprite();
        

        

    protected:

    private:
        int speed = sprite_speed::normal; //default value
        int size;
        int vec_pos_counter;
        timer* clock = nullptr;
        std::vector<int>* texture_ids;

        void update(); //next-texture (updated with timer)
        

};