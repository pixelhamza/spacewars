#include "raylib.h"

class Block{ 
    public: 
        Block(Vector2 position);
        void Draw();
        bool active = true ;
        Rectangle GetRect() const;

    private: 
        Vector2 position;

};