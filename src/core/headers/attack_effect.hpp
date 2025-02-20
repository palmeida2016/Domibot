#ifndef ATTACK_EFFECT_HPP
#define ATTACK_EFFECT_HPP

#include <functional>

enum class AttackType {
    DISCARD,
    DRAW,
    GAIN_CURSE,
    REVEAL_CARDS,
    NONE
    // Add more attack types as needed
};

class AttackEffect {
public:
    AttackEffect(AttackType type, int value = 0) 
        : type(type), value(value) {}

    AttackType type;
    int value;  // Number of cards to discard/draw/etc.
};

#endif 