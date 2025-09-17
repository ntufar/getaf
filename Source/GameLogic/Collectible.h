#pragma once

#include <string>

class Collectible
{
public:
    Collectible();
    void PickUp();
    std::string GetType() const { return "DefaultCollectible"; }
};