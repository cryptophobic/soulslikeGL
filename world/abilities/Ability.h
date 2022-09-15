//
// Created by dmitr on 15.09.2022.
//

#ifndef SOULSLIKEGL_ABILITY_H
#define SOULSLIKEGL_ABILITY_H

#include "../Object.h"

namespace world::abilities {

    class Ability {
    public:
        explicit Ability(Object *);
        virtual void execute() = 0;
    protected:
        Object *boundObject = nullptr;
    };

} // abilities

#endif //SOULSLIKEGL_ABILITY_H
