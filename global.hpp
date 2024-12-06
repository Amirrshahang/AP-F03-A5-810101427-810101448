#pragma once

#include <math.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace sf;
using namespace std;

const float PI = acos(-1);
const int WIDTH = 1265;
const int HEIGHT = 694;
const int FRAME_RATE = 144;
const int LEVEL_COUNT = 6;
const int LINEHEIGHT = 98;
const int SPACING = 33;
const int OFFSET = 58;
const string PICS_PATH = "/Users/amir/Desktop/project5/Files/pics/", AUDIO_PATH = "./files/audio/",
             FONTS_PATH = "./files/fonts/";
const Color BLUE = Color(50, 115, 220);
const Color PURPLE = Color(130, 50, 220);
const Color YELLOW = Color(255, 248, 220);
const int BUTTON_MARGIN = 5;

#define debug(x) cout << x << endl, exit(0);
