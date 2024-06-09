#include <iostream>
#include <vector>
#include <string>

using namespace std;


/*
    1. При модификации 1 объекта требуется изменить и другие, и вы не знаете, сколько именно объектов требуется изменить.

    2. Один объект должен оповещать другие, не делая предположений об уведомляемых объектах.
*/

class Observer;


class Subject
{
  vector<Observer*> observers;
public:
  void Attach(Observer* observer)
  {
    observers.push_back(observer);
  }

  void Detach(Observer* observer)
  {
    observers.erase(find(observers.begin(), observers.end(), observer));
  }
protected:
  void Notify();
};


class Observer
{
  Subject* subject;
public:
  Observer(Subject* subject) : subject(subject)
  {
    subject->Attach(this);
  }

  ~Observer()
  {
    subject->Detach(this);
  }

  virtual void Update() = 0;
};
  

void Subject::Notify()
{
  for (size_t i = 0; i < observers.size(); i++)
    observers[i]->Update();
}


class DataStorage : public Subject
{
public:
  void AddData()
  {
    cout << "Update DataStorage's data \n";
    Notify();
  }
};


class Table : public Observer
{
public:
  Table(Subject* subject) : Observer(subject) { }

  void Update() override
  {
    cout << "Update Table \n";
  }
};


class Diagram : public Observer
{
public:
  Diagram(Subject* subject) : Observer(subject) { }

  void Update() override
  {
    cout << "Update Diagram \n";
  }
};


int main()
{
  DataStorage store;

  Table table(&store);
  Diagram diagram(&store);

  store.AddData();
}