#include <iostream>
#include <vector>

using namespace std;


/*
    1. Ёкземпл€ры классов могут находитьс€ в 1 из немногих числа различных состо€ний.
       ”добнее создать их прототипы и потом уже клонировать их, чем посто€нно создавать
       экземпл€ры с одним и тем же состо€нием.
*/



class Prototype
{
public:
  virtual Prototype* Clone() = 0;
};



class PrototypeWall : public Prototype
{
  Prototype* Clone() override
  {
    cout << "Cloning wall prototype \n";
    return new PrototypeWall(*this);
  }
};


class PrototypeMaze : public Prototype
{
  Prototype* Clone() override
  {
    cout << "Cloning maze prototype \n";
    return new PrototypeMaze(*this);
  }
};



class Client
{

  Prototype* prototype;

public:

  Client()
    : prototype(new PrototypeWall)
  {
  }

  ~Client() { delete prototype; }

  void Operation()
  {
    for (int i = 0; i < 10; i++)
    {
      Prototype* p = prototype->Clone();
      // ...
      delete p;
    }
  }
};



int main()
{
  Client client;
  client.Operation();
}