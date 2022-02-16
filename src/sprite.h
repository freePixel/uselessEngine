#pragma once

#include "stdexcept"
#include "entity.h"
#include <vector>
#include "timer.h"
#include "textureManager.h"

namespace sprite_texture
{
    namespace player
    {
        static std::vector<int> sp1 = {TEXTURES::T1,TEXTURES::T2, TEXTURES::T3};
    };
}

enum sprite_speed
{
    normal = 750,
    medium = 500,
    fast = 250,
};



/*
sprite is should not be used in objects with multiple textures (textureSet size > 1)
*/

class sprite
{
    public:
        /*
        _texture_ids -> vector containing a list of texture ids of a given sprite
        sprite_speed -> time needed in ms to update sprite animation
        clock        -> current scene timer object
        */
        sprite(entity* e , std::vector<textureInfo>& _texture_ids, sprite_speed speed , timer* clock); 
         
        ~sprite();
        

        

    protected:

    private:
        entity* _entity = nullptr;
        int speed = sprite_speed::normal; //default value
        int size;
        int vec_pos_counter;
        timer* clock = nullptr;
        std::vector<textureInfo>& texture_ids;

        void update(); //next-texture (updated with timer)
        

};