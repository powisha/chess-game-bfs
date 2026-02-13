#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include <nlohmann/json.hpp>
#include "ConfigReader.hpp"

struct Piece {
    std::string type;
    std::string color;
    Movement movement;
    SpecialAbilities special_abilities;
    int firstx;
    int firsty;


};

#endif
