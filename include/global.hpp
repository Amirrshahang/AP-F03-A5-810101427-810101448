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
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

const int OFFSET = 95;
const int WIDTH = 1245;
const int HEIGHT = 695;
const int SPACING = 60;
const int LINECOUNT = 4;
const int LINEHEIGHT = 85;
const int FRAME_RATE = 144;
const int TOTAL_SHEEP_IN_QUEUE = 100;

const string PICS_PATH = "/Users/amir/Desktop/project5/Files/pics/", AUDIO_PATH = "./files/audio/",
             FONTS_PATH = "./files/fonts/";

#define debug(x) cout << x << endl, exit(0);
