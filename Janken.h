#pragma once
#include <iostream>
#include <string>
#include <array>

using namespace std;


enum class Hand 
{
    Rock = 0,
    Scissors = 1,
    Paper = 2
};


enum class Result 
{
    Draw,
    Win,
    Lose
};


class Player 
{
private:
    string name;
public:
    Player();
    void inputName();
    Hand chooseHand() const;
    string getName() const { return name; }
};


class Cpu 
{
public:
    Hand chooseHand() const;
};


class JankenGame 
{
private:
    Player player;
    Cpu cpu;
    array<int, 3> score; 
    int round;

    static constexpr array<const char*, 3> HandNames = { "ぐー", "チョキ", "パー" };

    Result judge(Hand playerHand, Hand cpuHand) const;
    string getHandName(Hand hand) const;

public:
    JankenGame();
    void play(); 
};