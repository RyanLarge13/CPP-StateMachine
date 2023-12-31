#include <iostream>
#include <chrono>
#include <thread>
#include <map>
using namespace std;

// Below is an example of a procedural stoplight program. This example does not follow FSM conventions, rather it is here to help you understand the differences between a event driven finite state machine and a procedural program that achieves the same-ish result but with different implementation.
class StopLight {
	public:
	string lights[3] {
		"Red",
		"Green",
		"Yellow"
	};

	void start(int iterator, string color) {
		cout << color << endl;
		int size = sizeof(lights) / sizeof(lights[0]);
		int start;
		for (int i = 0; i < 3; i++) {
			if (lights[i] == color) {
				start = i + 1;
			}
		}
		for (int i = start; i < iterator; i++) {
			std::this_thread::sleep_for(chrono::milliseconds(3000));
			cout << lights[i % size] << endl;
		}
	}
};

// Here is the event driven FSM example where we clearly define the states a program is allowed to be in. An input is required to start a transition from one state to the next based on the color input and the stoplight reacts only allowing certain transitions and inputs
enum States {
	RED,
	GREEN,
	YELLOW
};

class FSM {
	public:
	States currentState = States::RED;
	FSM(const string& input) {
		map < string,
		States > transitionMap = {
			{
				"red",
				States::GREEN
			},
			{
				"green",
				States::YELLOW
			},
			{
				"yellow",
				States::RED
			}
		};
		if (transitionMap.find(input) != transitionMap.end()) {
			currentState = transitionMap[input];
			printState();
		} else {
			cout << "Invalid input, no state transition" << endl;
		}
	}
	void printState() const {
		switch(currentState) {
			case States::RED:
			cout << "RED" << endl;
			break;
			case States::GREEN:
			cout << "GREEN" << endl;
			break;
			case States::YELLOW:
			cout << "YELLOW" << endl;
			break;
		}
	}
};

int main() {
	// Procedural stoplight
	StopLight myLight;
	myLight.start(10, "Green");
	// Finite State Machine (FSM)
	while(true) {
		string input;
		cout << "Light color: ";
		cin >> input;
		FSM myStateMachine(input);
	}
	return 0;
}