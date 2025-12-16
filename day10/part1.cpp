#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;
using Goal = vector<bool>;
using Button = vector<size_t>;

struct Machine {
    Goal goal;
    vector<Button> buttons;
};

bool lightsMatchGoal(Goal &goal, Goal &lights){
    for(size_t i{}; i < lights.size(); i++){
        if (goal.at(i) != lights.at(i))
            return false;
    }
    return true;
}

int main() {
    fstream file("./input.txt");
    vector<Machine> machines;

    for(string line; getline(file, line);){
        char c{};
        stringstream sline(line);
        Machine machine;
        sline >> c;
        sline >> c;
        while (c == '.' || c== '#'){
            machine.goal.push_back(c == '#' ? true : false);
            sline >> c;
        };
        sline >> c;
        do{
            Button button{};
            while(c != ')'){
                size_t lightIdx{};
                sline >> lightIdx;
                sline >> c;
                button.push_back(lightIdx);
            };
            machine.buttons.push_back(button);
            sline >> c; // remove space
        } while (c == '(');
        machines.push_back(machine);
    }

    size_t totalPresses{};
    for (auto machine: machines){
        size_t numOfButtons{machine.buttons.size()};
        size_t leastPresses{numOfButtons};
        for (size_t combination{1}; combination < pow(2, numOfButtons); combination++){
            size_t presses{static_cast<size_t>(__builtin_popcount(combination))};
            if (presses >= leastPresses) continue;
            Goal lights(machine.goal.size(), false);
            for(size_t buttonIdx{0}; buttonIdx < numOfButtons; buttonIdx++){
                if (!(combination & (0x1 << buttonIdx))) continue;
                for(auto lightIdx: machine.buttons.at(buttonIdx)){
                    if (lights.at(lightIdx) == true)
                        lights.at(lightIdx) = false;
                    else lights.at(lightIdx) = true;
                }
            }
            if (lightsMatchGoal(machine.goal, lights)){
                leastPresses = presses;
            }
        }
        totalPresses += leastPresses;
    }

    cout << "Total presses needed:" << totalPresses << endl;
}
