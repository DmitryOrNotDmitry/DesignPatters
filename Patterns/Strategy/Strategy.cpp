#include <iostream>
#include <vector>
#include <string>

using namespace std;


/*
    1. Наличие множества класов, отличающихся только поведением

    2. Наличие нескольких разновидностей алгоритма
*/


class Validator
{
public:
  virtual void Check(int num) = 0;
};


class EqualsValidator : public Validator
{
  int perfectValue;
public:
  EqualsValidator(int value) : perfectValue(value) { }

  void Check(int num) override
  {
    if (num == perfectValue)
      cout << "Number " << num << " equals perfectValue " << perfectValue << "\n";
    else
      cout << "Number " << num << " not equals perfectValue " << perfectValue << "\n";
  }
};


class RangeValidator : public Validator
{
  int from;
  int to;
public:
  RangeValidator(int from, int to) : from(from), to(to) { }

  void Check(int num) override
  {
    if (num >= from && num <= to)
      cout << "Number " << num << " in range [" << from << ", " << to << "]\n";
    else
      cout << "Number " << num << " not in range [" << from << ", " << to << "]\n";
  }
};


class Client
{
  Validator* validator;
public:
  Client(Validator* validator) : validator(validator) { }

  void CheckNumbers()
  {
    for (int i = 0; i < 110; i += 10)
      validator->Check(i);
  }
};


int main()
{
  EqualsValidator ev(100);
  Client client1(&ev);
  client1.CheckNumbers();
  
  cout << endl;
  
  RangeValidator rv(45, 99);
  Client client2(&rv);
  client2.CheckNumbers();
}