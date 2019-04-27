#ifndef GAME_CONST_H_
#define GAME_CONST_H_

using namespace std;

#define MAX_COLS 12
#define MAX_ROWS 15
#define MAX_CUS 41

const float R = 20.0f;  //  泡泡的半径
const int HOURGLASSTIME = 45;

const float TOUCH_TOP = 0.90f;
const float TOUCH_DOWN = 0.33f;

const float MOVE_DISTANCE = 10.0f;

const int BUBBLE_COUNT = 7;

#define MAX_WAIT_PAOPAO 2

#define READY_PAOPAO_POS Point(270, 193)
#define WAIT_PAOPAO_POS Point(175,170)

#define PAOPAO_SPEED 30.0f

const int RMB[5] = { 1, 4, 6, 10, 15 };

const string BUBBLE_NAME = "bubble_%d.png";
const string BUBBLE_COLOR_NAME = "caihong1.png";
const string BUBBLE_BOMB_NAME = "zhadan1.png";

const int customs[MAX_CUS][MAX_ROWS][MAX_COLS] = {
    {
        { 2, 2, 2, 2, 2, 3, 3, 3, 1, 1 },
        { 2, 2, 2, 2, 3, 3, 3, 1, 1 },
        { 2, 2, 2, 2, 3, 3, 3, 1, 1, 1 },
        { 2, 2, 2, 3, 3, 3, 1, 1, 1 },
        { 2, 2, 3, 3, 3, 3, 1, 1, 1, 1 },
        { 0, 0, 3, 3, 3, 3, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 0, 2, 0, 0, 0, 0, 3, 0, 0 },
        { 0, 2, 2, 2, 0, 0, 3, 1, 1 },
        { 0, 2, 2, 2, 3, 3, 3, 1, 1, 1 },
        { 0, 2, 2, 3, 3, 3, 1, 1, 1 },
        { 0, 2, 3, 3, 3, 3, 1, 1, 1, 1 },
        { 0, 0, 3, 3, 3, 3, 1, 0, 0 },
        { 0, 0, 0, 3, 3, 3, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 3, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { -1,-1, -1, -1, -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        { 1, 1, 1, 2, 2, 2, 2, 3, 3, 3 },
        { 1, 1, 1, 2, 2, 2, 3, 3, 3 },
        { 1, 1, 1, 2, 2, 2, 2, 3, 3, 3 },
        { 3, 3, 3, 2, 2, 2, 1, 1, 1 },
        { 3, 3, 3, 1, 1, 1, 2, 3, 3, 3 },
        { 3, 3, 3, 1, 1, 1, 3, 3, 3 },
        { 1, 1, 1, 2, 2, 2, 2, 3, 3, 3 },
    },
    {
        { 3, 2, 2, 0, 0, 0, 2, 2, 3, 1 },
        { 1, 3, 2, 2, 0, 2, 2, 3, 1 },
        { 0, 1, 3, 2, 2, 2, 3, 1, 0, 0 },
        { 0, 0, 1, 3, 2, 3, 1, 0, 0 },
        { 0, 0, 0, 1, 3, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 3, 3, 2, 2, 4, 4, 4, 1, 1, 1 },
        { 1, 3, 2, 2, 0, 2, 2, 3, 1 },
        { 3, 3, 3, 2, 2, 4, 4, 1, 1, 1 },
        { 3, 3, 2, 2, 2, 4, 4, 1, 1 },
        { 3, 3, 0, 2, 2, 4, 4, 1, 1, 1 },
        { 3, 3, 3, 2, 2, 4, 4, 1, 1 },
        { 3, 3, 0, 2, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    // 5
    {
        {0,1,4,4,4,0,0,0,1,1,1,0},
        {0,0,4,4,0,0,0,0,1,1,0,0},
        {0,0,2,2,2,0,0,0,0,1,0,0},
        {0,2,4,4,2,0,0,0,1,1,0,0},
        {0,2,4,4,4,2,0,0,2,2,2,0},
        {2,4,4,4,4,2,0,2,4,4,2,0},
        {0,2,4,4,4,2,0,2,4,4,4,2},
        {0,2,4,4,2,0,2,4,4,4,4,2},
        {0,0,2,2,2,0,0,2,4,4,4,2},
        {0,0,0,1,0,4,4,2,4,4,2,0},
        {0,0,0,2,2,4,4,4,2,2,2,0},
        {0,0,2,4,2,4,4,2,4,2,0,0},
        {0,0,2,4,4,2,0,2,4,4,2,0},
        {0,0,2,4,2,0,0,2,4,2,0,0},
        {0,0,0,2,2,0,0,0,2,2,0,0},
    },
    // 6
    {
        { 2, 2, 2, 3, 3, 3, 3, 2, 2, 2 },
        { 2, 2, 3, 3, 3, 3, 3, 2, 2 },
        { 3, 3, 3, 2, 2, 4, 4, 1, 1, 1 },
        { 3, 3, 2, 2, 2, 4, 4, 1, 1 },
        { 3, 3, 0, 2, 2, 4, 4, 1, 1, 1 },
        { 3, 2, 2, 2, 2, 4, 4, 1, 1 },
        { 3, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    //7
    {
        { 1, 1, 2, 2, 3, 3, 4, 4, 4, 4 },
        { 0, 1, 1, 2, 2, 3, 3, 4, 4 },
        { 1, 1, 1, 2, 2, 2, 3, 3, 3, 3 },
        { 0, 1, 0, 0, 2, 2, 3, 3, 0 },
        { 1, 1, 1, 2, 2, 2, 3, 3, 3, 0 },
        { 0, 1, 1, 0, 2, 2, 0, 3, 3 },
        { 1, 1, 1, 2, 2, 2, 3, 3, 3, 3 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    },//8
    {
        { 1, 1, 1, 1, 2, 2, 3, 3, 4, 4 },
        { 0, 1, 1, 2, 2, 3, 3, 4, 4 },
        { 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 },
        { 0, 1, 0, 0, 2, 2, 3, 3, 0 },
        { 1, 1, 1, 2, 2, 2, 3, 3, 3, 0 },
        { 0, 1, 1, 0, 2, 2, 0, 3, 3 },
        { 1, 1, 1, 2, 2, 2, 3, 3, 3, 3 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    },//9
    
    												{
    													{ 2, 2, 2, 3, 3, 3, 3, 2, 2, 2 },
													    { 2, 2, 3, 3, 3, 3, 3, 2, 2 },
														{ 2, 2, 5, 3, 3, 3, 3, 2, 2, 2 },
														{ 2, 5, 2, 2, 4, 2, 2, 2, 2 },
														{ 2, 5, 2, 2, 4, 4, 2, 2, 2, 2 },
														{ 0, 0, 1, 1, 1, 1, 1, 0, 0 },
														{ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },
														{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
														{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
														{ 0, 0, 0, 0, 1, 0, 0, 0, 0 }
													},// 10
													{
														{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
														{ 0, 0, 0, 6, 1, 7, 0, 0, 0 },
														{ 0, 0, 0, 4, 6, 7, 5, 0, 0, 0 },
														{ 0, 0, 1, 4, 0, 5, 6, 0, 0 },
														{ 0, 0, 2, 1, 0, 0, 6, 3, 0, 0 },
														{ 7, 7, 2, 0, 0, 0, 3, 4, 4 }
													},// 11
													{
														{ 0, 0, 1, 1, 6, 6, 7, 7, 0, 0 },
														{ 0, 1, 1, 1, 6, 7, 7, 7, 0 },
														{ 0, 0, 1, 1, 6, 6, 7, 7, 0, 0 },
														{ 0, 0, 4, 4, 5, 7, 7, 0, 0 },
														{ 0, 0, 0, 4, 5, 5, 3, 0, 0, 0 },
														{ 0, 0, 0, 2, 2, 2, 0, 0, 0 },
														{ 0, 0, 0, 0, 6, 6, 0, 0, 0, 0 },
														{ 0, 0, 0, 0, 6, 0, 0, 0, 0 }
													}, //12
													{
														{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
														{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
														{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
														{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
														{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
														{ 0, 0, 0, 2, 6, 0, 0, 0, 0 },
														{ 0, 0, 3, 4, 2, 2, 4, 3, 0, 0 },
														{ 0, 7, 7, 5, 5, 5, 7, 7, 0 },
														{ 0, 0, 0, 0, 6, 6, 0, 0, 0, 0 },
														{ 0, 0, 0, 0, 6, 0, 0, 0, 0 }
													},//13
													{
														{ 0, 0, 1, 0, 0, 0, 0, 4, 0, 0 },
														{ 0, 1, 1, 0, 0, 0, 4, 4, 0 },
														{ 0, 6, 1, 2, 5, 5, 2, 4, 3, 0 },
														{ 6, 6, 0, 2, 5, 2, 0, 3, 3 },
														{ 0, 6, 0, 0, 1, 1, 0, 0, 3, 0 },
														{ 0, 4, 5, 5, 1, 5, 5, 7, 0 },
														{ 0, 0, 4, 5, 5, 5, 5, 7, 0, 0 },
														{ 0, 0, 4, 6, 6, 6, 7, 0, 0 },
														{ 0, 0, 0, 4, 2, 2, 7, 0, 0, 0 },
														{ 0, 0, 0, 2, 2, 2, 0, 0, 0 }
													},//14
													{
														{ 0, -1, 0, 0, 0, 0, 0, 4, 0, 0 },
														{ -1, 0, 0, 0, 0, 0, 0, 0, 0 },
														{ -1, -1, -1, -1, -1, -1, -1, -1, -1, 0 },
														{ 0, 0, 0, 0, 0, 0, 0, -1, 0 },
														{ 0, -1, -1, -1, -1, -1, -1, -1, 0, 0 },
														{ -1, 0, 0, 0, 0, 0, 0, 0, 0 },
														{ -1, -1, -1, -1, -1, -1, -1, -1, -1, 0 }
													},//15
													{
														{ -1, 0, 0, 0, -1, -1, 0, 0, 0, -1 },
														{ -1, 0, 0, 0, -1, 0, 0, 0, -1 },
														{ -1, -1, 0, 0, -1, -1, 0, 0, -1, -1 },
														{ -1, -1, 0, 0, -1, 0, 0, -1, -1 },
														{ -1, -1, -1, 0, -1, -1, 0, -1, -1, -1 },
														{ -1, -1, 0, 0, -1, 0, 0, -1, -1 },
														{ -1, -1, 0, 0, -1, -1, 0, 0, -1, -1 },
														{ -1, 0, 0, 0, -1, 0, 0, 0, -1 }
													},//16
													{
														{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
														{ -1, 0, -1, -1, -1, -1, -1, 0, -1 },
														{ 0, -1, -1, 0, -1, -1, 0, -1, -1, 0 },
														{ 0, -1, 0, -1, 0, -1, 0, -1, 0 },
														{ 0, -1, -1, -1, 0, 0, -1, -1, -1, 0 },
														{ -1, 0, -1, 0, 0, 0, -1, 0, -1 },
														{ -1, -1, -1, -1, 0, 0, -1, -1, -1, -1 }
													},//17
													{
														{ -1, 0, 0, 0, -1, -1, 0, 0, 0, -1 },
														{ -1, 0, 0, -1, 0, -1, 0, 0, -1 },
														{ 0, -1, 0, -1, 0, 0, -1, 0, -1, 0 },
														{ 0, -1, -1, 0, 0, 0, -1, -1, 0 },
														{ 0, -1, 0, -1, -1, -1, -1, 0, -1, 0 },
														{ 0, -1, 0, -1, 0, -1, 0, -1, 0 },
														{ 0, -1, 0, 0, -1, -1, 0, 0, -1, 0 },
														{ -1, 0, 0, 0, -1, 0, 0, 0, -1 }
													},//18
    {
        { -1, -1, -1,  1,  1, 2, 2, -1, -1, -1 },
        { -1, -1, -1,  1,  1, 2, 2, -1, -1 },
        {  0, -1, -1,  1,  1, 2, 2, -1, -1, 0 },
        {  0,  0, -1,  1,  1, 2, 2, -1, -1 },
        {  0,  0,  0, -1,  1, 2, 2, -1, -1, 0 },
        {  0,  0,  0,  0, -1, 2, 2, -1, -1 },
        {  0,  0,  0,  0,  0, -1, -1, -1, 0, 0 },
        {  0,  0,  0,  0,  0,  0, -1,  0, 0 }
    },//19 -- 第18关
    {
        { -1,  0,  0,  1,  1, 2, 2, -1, -1, -1 },
        { -1,  0,  0,  1,  1, 2, 2, -1, -1 },
        {  0, -1,  0,  1,  1, 2, 0, -1, -1, 0 },
        {  0, -1,  0,  1,  1, 2, 0, -1, -1 },
        {  0,  0, -1,  0, -1, 0, 0, -1, -1, 0 },
        {  0,  0, -1,  0, -1, 0, 0, -1, -1 },
        {  0,  0,  0, -1,  0, 0, 0,  0,  0, 0 },
        {  0,  0,  0, -1,  0, 0, 0,  0, 0 }
    },//20 -- 第19关
    {
        { 2,  1,  1,  1,  1, 2, 2,  4, 4, -1 },
        { 3,  1,  1,  1,  1, 2, 2,  4, 4 },
        { 3,  1,  1,  1,  1, 2, 2,  4, 4, -1 },
        { 4,  1,  3,  1,  1, 1, 1,  1, 1 },
        { 5,  1,  1,  1,  1, 2, 2,  4, 4, -1 },
        { 6,  1,  1,  1,  1, 2, 2,  4, 4 },
        { 7,  1,  1,  1,  1, 2, 2,  4, 4, -1 },
        { 2,  3,  4,  5,  6, 7, 2,  3, 7 }
    },//21 -- 第20关
    {
        { 2,  0,  0,  0,  0, 0, 0,  0, 4, 0 },
        { 3,  6,  0,  0,  0, 0, 6,  4, 0 },
        { 0,  2,  6,  0,  0, 0, 2,  7, 0, 0 },
        { 0,  5,  1,  1,  1, 1, 5,  0, 0 },
        { 0,  2,  6,  0,  0, 0, 2,  6, 0, 0 },
        { 3,  0,  0,  0,  0, 0, 0,  3, 0 },
        { 0,  0,  0,  0,  0, 0, 0,  0, 4, 0 },
        { 0,  0,  0,  0,  0, 0, 0,  0, 0 }
    },//22 -- 第21关
    {
        { 7,  6,  5,  4,  3, 3, 4,  5, 6, 7 },
        { 6,  5,  4,  3,  2, 3, 4,  5, 6 },
        { 6,  6,  5,  3,  2, 2, 3,  4, 5, 6 },
        { 5,  4,  3,  2,  1, 2, 3,  4, 5 },
        { 4,  4,  3,  2,  1, 1, 2,  3, 4, 5 },
        { 3,  3,  2,  1,  0, 1, 2,  3, 3 },
        { 2,  2,  2,  1,  0, 0, 1,  2, 2, 2 },
        { 1,  1,  1,  0,  0, 0, 1,  1, 1 }
    },//23 -- 第22关
    {
        { 7,  7,  7,  7,  6, 6, 6,  6, 6, 6 },
        { 7,  7,  7,  5,  6, 6, 6,  6, 6 },
        { 6,  7,  7,  5,  5, 6, 6,  6, 6, 0 },
        { 5,  7,  5,  5,  5, 5, 6,  6, 6 },
        { 4,  4,  5,  5,  5, 5, 2,  6, 6, 5 },
        { 3,  3,  5,  5,  5, 5, 5,  3, 6 },
        { 2,  5,  5,  5,  5, 5, 5,  2, 2, 2 },
        { 1,  5,  5,  5,  5, 5, 5,  5, 1 }
    },//24 -- 第23关
    {
        { 7,  6,  4,  1,  4, 2, 6,  6, 6, 6 },
        { 6,  7,  1,  4,  1, 5, 6,  6, 6 },
        { 7,  6,  4,  1,  4, 2, 6,  6, 6, 0 },
        { 3,  2,  1,  4,  1, 5, 6,  6, 6 },
        { 2,  3,  4,  1,  4, 2, 2,  6, 6, 5 },
        { 3,  2,  1,  4,  1, 5, 5,  3, 6 },
        { 2,  3,  4,  1,  4, 2, 5,  2, 2, 2 },
        { 3,  2,  1,  4,  1, 5, 5,  5, 1 }
    },//25 -- 第24关
    {
        { 0, 1, 1, 3, 2, 3, 2, 4, 0, 0 },
        { 7, 4, 5, 5, 5, 6, 6, 6, 7 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 2, 2, 3, 4, 5, 6, 6, 1, 0 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
        { 2, 2, 2, 2, 2, 2, 2, 2, 2 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 }
    },//26 -- 第25关
    {
        { 0, 1, 0, 3, 2, 3, 2, 4, 0, 0 },
        { 1, 4, 1, 2, 5, 2, 6, 6, 7 },
        { 1, 1, 1, 2, 2, 2, 1, 6, 1, 0 },
        { 2, 1, 1, 2, 5, 2, 6, 6, 0 },
        { 2, 0, 0, 1, 2, 6, 6, 6, 0, 0 },
        { 0, 0, 0, 0, 0, 2, 6, 6, 2 },
        { 0, 0, 0, 0, 0, 1, 1, 6, 1, 2 }
    },//27 -- 第26关
    {
        { 0, 1, 0, 3, 2, 0, 0, 4, 0, 0 },
        { 1, 0, 0, 2, 6, 0, 0, 6, 7 },
        { 1, 0, 0, 2, 5, 0, 0, 6, 1, 0 },
        { 2, 0, 0, 2, 4, 0, 0, 6, 0 },
        { 2, 0, 0, 1, 3, 0, 0, 6, 0, 0 },
        { 3, 0, 0, 1, 3, 0, 0, 6, 2 },
        { 3, 0, 0, 6, 1, 0, 0, 6, 1, 2 }
    },//28 -- 第27关
    {
        { 0, 1, 0, 3, 2, 0, 0, 4, 0, 0 },
        { 1, 0, 0, 2, 6, 2, 0, 6, 7 },
        { 1, 0, 2, 2, 5, 0, 2, 6, 1, 0 },
        { 2, 2, 0, 2, 4, 0, 0, 2, 0 },
        { 2, 0, 2, 1, 3, 0, 2, 6, 0, 0 },
        { 3, 0, 0, 2, 3, 2, 0, 6, 2 },
        { 3, 0, 0, 6, 2, 0, 0, 6, 1, 2 }
    },//29 -- 第28关
    {
        { 1, 2, 2, 2, 2, 1, 0, 1, 0, 0 },
        { 2, 1, 2, 2, 2, 2, 1, 6, 7 },
        { 2, 2, 1, 2, 2, 1, 2, 6, 1, 0 },
        { 2, 2, 2, 1, 2, 0, 0, 2, 0 },
        { 2, 2, 1, 1, 2, 0, 2, 6, 0, 0 },
        { 2, 1, 0, 2, 3, 2, 0, 6, 2 },
        { 1, 0, 0, 6, 2, 1, 2, 6, 1, 2 }
    },//30 -- 第29关
    {
        { 1, 2, 3, 4, 5, 6, 7, 1, 2, 3 },
        { 3, 1, 2, 3, 4, 5, 1, 7, 1 },
        { 2, 3, 1, 2, 3, 4, 2, 6, 3, 0 },
        { 2, 3, 1, 1, 2, 3, 3, 5, 4 },
        { 2, 3, 1, 1, 1, 2, 4, 4, 5, 0 },
        { 3, 1, 2, 2, 7, 1, 5, 3, 6 },
        { 1, 3, 0, 6, 6, 7, 6, 2, 1, 2 }
    },//31 -- 第30关
    {
        { 1, 2, 0, 4, 5, 6, 7, 1, 2, 0 },
        { 0, 1, 2, 0, 0, 0, 1, 7, 1 },
        { 2, 0, 1, 0, 0, 0, 2, 6, 0, 0 },
        { 2, 0, 1, 0, 0, 0, 0, 5, 4 },
        { 2, 0, 1, 1, 1, 2, 4, 4, 5, 0 },
        { 3, 1, 2, 2, 7, 1, 5, 0, 6 },
        { 1, 0, 0, 6, 6, 7, 6, 2, 1, 2 }
    },//32 -- 第31关
    {
        { 1, 2, 0, 4, 5, 6, 7, 1, 2, 0 },
        { 0, 1, 2, 0, 5, 0, 1, 7, 1 },
        { 2, 0, 1, 4, 0, 4, 2, 6, 0, 0 },
        { 2, 0, 1, 0, 0, 0, 3, 5, 4 },
        { 2, 0, 3, 1, 1, 2, 4, 2, 5, 0 },
        { 3, 2, 2, 2, 7, 1, 5, 0, 2 },
        { 1, 0, 0, 6, 6, 7, 6, 2, 0, 2 }
    },//33 -- 第32关
    {
        { 1, 2, 0, 4, 5, 6, 7, 0, 0, 0 },
        { 0, 1, 2, 0, 5, 0, 1, 7, 0 },
        { 0, 0, 1, 4, 0, 4, 2, 0, 0, 0 },
        { 0, 0, 1, 4, 0, 0, 3, 0, 0 },
        { 0, 0, 3, 1, 1, 2, 0, 0, 0, 0 },
        { 0, 2, 2, 2, 7, 1, 5, 0, 0 },
        { 1, 0, 0, 6, 6, 7, 6, 0, 0, 0 }
    },//34 -- 第33关
    {
        { 1, 0, 0, 4, 1, 6, 7, -1, 1, 1 },
        { 1, 1, 1, 1, 1, 0, 1, 7, -1 },
        { 1, 0, 1, 4, 1, 4, 2, -1, -1, -1 },
        { 1, 0, 1, 4, 1, 0, 3, 0, 0 },
        { 0, 0, 3, 1, 1, 2, 0, 0, 0, 0 },
        { 0, 2, 2, 2, 7, 1, 5, 0, 0 },
        { 1, 0, 0, 6, 6, 7, 6, 0, 0, 0 }
    },//35 -- 第34关
    {
        { 1, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
        { 2, 0, 0, 2, 0, 0, 2, 0, 0 },
        { 3, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
        { 4, 0, 0, 4, 0, 0, 4, 0, 0 },
        { 5, 0, 0, 5, 0, 0, 5, 0, 0, 0 },
        { 6, 0, 0, 6, 0, 0, 6, 0, 0 },
        { 7, 0, 0, 7, 0, 0, 7, 0, 0, 0 }
    },//36 -- 第35关
    {
        { 1, 0, 1, 1, 0, 0, 1, 0, 0, 0 },
        { 2, 0, 2, 2, 0, 0, 2, 0, 0 },
        { 3, 0, 3, 3, 0, 0, 3, 0, 0, 0 },
        { 4, 0, 4, 4, 0, 0, 4, 0, 0 },
        { 5, 0, 5, 5, 0, 0, 5, 0, 0, 0 },
        { 6, 0, 6, 6, 0, 0, 6, 0, 0 },
        { 7, 0, 7, 7, 0, 0, 7, 0, 0, 0 }
    },//37 -- 第36关
    {
        { 1, 0, 1, 1, 1, 0, 1, 0, 0, 0 },
        { 2, 0, 2, 2, 2, 0, 2, 0, 0 },
        { 3, 0, 3, 3, 3, 0, 3, 0, 0, 0 },
        { 4, 0, 4, 4, 4, 0, 4, 0, 0 },
        { 5, 0, 5, 5, 5, 0, 5, 0, 0, 0 },
        { 6, 0, 6, 6, 6, 0, 6, 0, 0 },
        { 7, 0, 7, 7, 7, 0, 7, 0, 0, 0 }
    },//38 -- 第37关
    {
        { 1, 0, 1, 1, 1, 0, 1, 0, 0, 0 },
        { 2, 0, 2, 2, 2, 0, 2, 0, 0 },
        { 3, 0, 3, 3, 3, 0, 3, 0, 0, 0 },
        { 4, 0, 4, 4, 4, 0, 4, 0, 0 },
        { 5, 0, 5, 5, 5, 0, 5, 0, 0, 0 },
        { 6, 0, 6, 6, 6, 0, 6, 0, 0 },
        { 7, 0, 7, 7, 7, 0, 7, 0, 0, 0 }
    },//39 -- 第38关
    {
        { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
        { 2, 0, 2, 0, 2, 0, 2, 0, 2},
        { 3, 0, 3, 0, 3, 0, 3, 0, 3, 0 },
        { 4, 0, 4, 0, 4, 0, 4, 0, 4 },
        { 5, 0, 5, 0, 5, 0, 5, 0, 5, 0 },
        { 6, 0, 6, 0, 6, 0, 6, 0, 6 },
        { 7, 0, 7, 0, 7, 0, 7, 0, 7, 0 }
    },//40 -- 第39关
    {
														{ 0, 0, 0, -1, -1, 0, -1, 0, 0, 0 },
														{ 0, 0, -1, -1, -1, 0, -1, 0, 0 },
                                                        { 0, 0, -1, -1, -1, 0, -1, -1, 0, 0 },
														{ 0, -1, -1, -1, 0, 0, 0, 0, 0 },
														{ 0, -1, -1, -1, -1, -1, -1, 0, 0, 0 },
														{ 0, -1, 0, -1, 0, -1, 0, -1, 0 },
														{ 0, 0, -1, -1, -1, -1, 0, 0, -1, -1 },
														{ 0, 0, -1, -1, -1, 0, 0, 0, -1 }
													}
};


#endif
