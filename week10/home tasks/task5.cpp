// Task 05 (CP): Salary Calculator with Bonus Rules

#include <iostream>
using namespace std;

float calculateSalary(float base, int score, int experience)
{
    float bonusPercent = 0;

    // Performance score bonus
    if (score >= 90)
    {
        bonusPercent = 20;
    }
    else if (score >= 75)
    {
        bonusPercent = 10;
    }
    else
    {
        bonusPercent = 5;
    }

    // Experience bonus
    if (experience >= 5)
    {
        bonusPercent += 5;
    }

    float totalBonus = base * (bonusPercent / 100.0f);
    return base + totalBonus;
}

int main()
{
    float base;
    int score, experience;

    cout << "Enter base, score and experience in years: " << endl;
    cin >> base >> score >> experience;

    float finalSalary = calculateSalary(base, score, experience);
    cout << "Final Salary: " << finalSalary << endl;

    return 0;
}