#ifndef _GAME_H_
#define _GAME_H_

#include "Engine/Engine.h"

class Game : public Engine {
    public:
        
        Game();
        ~Game();

        bool init() override;
};

#endif