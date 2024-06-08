#include <iostream>
#include <vector>
#include <string>

using namespace std;


/*
    1. Необходимость сохранения снимка состояния объекта для последующего восстановления
*/


class Memento
{
  string state;

  Memento(string s) : state(s) { }

  string GetState() { return state; }
  
  void SetState(string state) { this->state = state; }

  friend class Originator;
};


class Originator
{
  string state;
public:
  Originator(string s) : state(s) { }

  void SetMemento(Memento m) { state = m.GetState(); }

  Memento CreateMemento() { return Memento(state); }
  
  void SetState(string state) { this->state = state; }

  string GetState() { return state; }
};



int main()
{
  Originator origin("Bad");
  Memento startMemento = origin.CreateMemento();

  cout << "Originator's state - '" << origin.GetState() << "'\n";

  origin.SetState("Good");
  cout << "Originator's state - '" << origin.GetState() << "'\n";
  
  origin.SetState("Amazing");
  cout << "Originator's state - '" << origin.GetState() << "'\n";

  origin.SetMemento(startMemento);
  cout << "Originator's state - '" << origin.GetState() << "'\n";
}