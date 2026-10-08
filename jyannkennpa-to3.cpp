#include "Janken.h"
#include <cstdlib>
#include <ctime>


using namespace std;


Player::Player() : name("nanashi") {}

void Player::inputName()
{
    cout << "Enter your name: ";
    cin >> name;
}

Hand Player::chooseHand() const 
{
    int inputHand = 0;
    while (true) 
    {
        cout << "Choose your hand (0: Rock, 1: Scissors, 2: Paper): ";
        cin >> inputHand;
        if (inputHand >= 0 && inputHand <= 2) 
        {
            break;
        }
        cout << "Invalid choice. Please choose 0, 1, or 2.\n";
    }
    return static_cast<Hand>(inputHand);
}


Hand Cpu::chooseHand() const 
{
    return static_cast<Hand>(rand() % 3);
}


JankenGame::JankenGame() : score({ 0, 0, 0 }), round(1) 
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

Result JankenGame::judge(Hand playerHand, Hand cpuHand) const 
{
    if (playerHand == cpuHand) return Result::Draw;

    if ((playerHand == Hand::Rock && cpuHand == Hand::Scissors) ||
        (playerHand == Hand::Scissors && cpuHand == Hand::Paper) ||
        (playerHand == Hand::Paper && cpuHand == Hand::Rock)) 
    {
        return Result::Win;
    }
    return Result::Lose;
}

string JankenGame::getHandName(Hand hand) const 
{
    size_t index = static_cast<size_t>(hand);
    if (index < HandNames.size())
    {
        return HandNames[index];
    }
    return "Unknown";
}

void JankenGame::play()
{
    player.inputName();
    cout << "Welcome, " << player.getName() << "! Let's start Janken!\n";
    cout << "First to 3 wins is the victor.\n";
    cout << "-----------------------------------------\n";

    while (score[static_cast<int>(Result::Win)] < 3 && score[static_cast<int>(Result::Lose)] < 3) 
    {
        cout << "\n[Round " << round << "]\n";

        Hand playerHand = player.chooseHand();
        Hand cpuHand = cpu.chooseHand();

        cout << player.getName() << ": " << getHandName(playerHand) << "\n";
        cout << "CPU: " << getHandName(cpuHand) << "\n";

        Result gameResult = judge(playerHand, cpuHand);

        if (gameResult == Result::Win) {
            cout << "Result: You WIN this round!\n";
            score[static_cast<int>(Result::Win)]++;
            round++;
        }
        else if (gameResult == Result::Lose) {
            cout << "Result: You LOSE this round!\n";
            score[static_cast<int>(Result::Lose)]++;
            round++;
        }
        else {
            cout << "Result: DRAW!\n";
            score[static_cast<int>(Result::Draw)]++;
        }

        cout << "Current Score -> Wins: " << score[static_cast<int>(Result::Win)]
            << ", Losses: " << score[static_cast<int>(Result::Lose)]
            << ", Draws: " << score[static_cast<int>(Result::Draw)] << "\n";
        cout << "-----------------------------------------\n";
    }

    cout << "\n=========================================\n";
    cout << "GAME OVER\n";
    cout << "=========================================\n";

    if (score[static_cast<int>(Result::Win)] == 3) {
        cout << "Congratulations, " << player.getName() << "! You won the game!\n";
    }
    else {
        cout << "Too bad, " << player.getName() << "! CPU won the game!\n";
    }

    cout << "Final Record: " << score[static_cast<int>(Result::Win)] << " Win(s), "
        << score[static_cast<int>(Result::Lose)] << " Loss(es), "
        << score[static_cast<int>(Result::Draw)] << " Draw(s)\n";
    cout << "=========================================\n";
}