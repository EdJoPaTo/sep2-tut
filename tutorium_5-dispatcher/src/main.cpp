/*
 * @file    main.cpp
 * @author  Simon Brummer
 * @desc    Tutorium 5. Grundversion des Dispatchers.
 *          States koennen sich am Dispatcher fuer ein bestimmtes Event registrieren.
 *          Tritt dieses Event ein, wird die zugehoerige Methode des States aufgerufen.
 */
#include <string>

#include "Transitions.h"
#include "Dispatcher.cpp"
#include "State.cpp"

using namespace std;

int main() {
	Dispatcher* disp = new Dispatcher();
	State* s1 = new State("State1");
	State* s2 = new State("State2");

	// Register s1 and s2 to listen on Event TRANSITION1
	disp->addListener(s1, TRANSITION1);
	disp->addListener(s2, TRANSITION1);

	// Event TRANSITION1 happens
	cout << "---- TRANSITION1 happens ----" << endl;
	disp->callListeners(TRANSITION1);

	// Register s1 as Listener on Event TRANSITION2 and s2 on EVENT TRANSITION3
	disp->addListener(s1, TRANSITION2);
	disp->addListener(s2, TRANSITION3);

	// Event TRANSITION1 happens
	cout << "---- TRANSITION1 happens ----" << endl;
	disp->callListeners(TRANSITION1);

	// Event TRANSITION2 happens
	cout << "---- TRANSITION2 happens ----" << endl;
	disp->callListeners(TRANSITION2);

	// Event TRANSITION3 happens
	cout << "---- TRANSITION3 happens ----" << endl;
	disp->callListeners(TRANSITION3);

	// Remove s2 as Listener from TRANSITION1
	disp->remListeners(s2, TRANSITION1);

	// Event TRANSITION1 happens
	cout << "---- TRANSITION1 happens ----" << endl;
	disp->callListeners(TRANSITION1);

	delete s2;
	delete s1;
	delete disp;

	return 0;
}
