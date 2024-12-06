#ifndef CONFIGS_HPP_INCLUDE
#define CONFIGS_HPP_INCLUDE

#include <vector>
#include <string>

struct SheepConfigs {
    std::string name;
    int damage;
    int strength;
    float displayProb;
};

const std::vector<SheepConfigs> SHEEP_CONFIGS = {
    {"Timmy", 50, 50, 0.5f},
    {"Shaun", 30, 150, 0.3f},
    {"Meow", 10, 250, 0.2f}
};

// سایر مقادیر کانفیگ
constexpr int COOLDOWN_MS = 2000;       
constexpr int INITIAL_HEALTH = 400;    
constexpr int CONSTANT_SPEED = 300;    

#endif 
