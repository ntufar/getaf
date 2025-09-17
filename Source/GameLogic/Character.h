#pragma once

#include <string>

class Character
{
public:
    Character();
    void Move(float deltaTime);
    void Jump();
    std::string GetName() const { return "DefaultCharacter"; }
};