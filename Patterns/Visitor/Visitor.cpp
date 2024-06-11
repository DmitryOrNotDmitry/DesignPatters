#include <iostream>
#include <vector>
#include <string>
#include <numbers>

using namespace std;


/*
    1. Ќад объектами должны выполн€тьс€ разнообразные действи€, но вы не хотите "засор€ть" классы такими операци€ми

    2.  лассы, определ€ющую структуру объектов, измен€ютс€ редко, но новые операции над этой структурой добавл€ютс€ часто
*/


#define PI numbers::pi

class Rect;
class Circle;


class Visitor
{
public:
  virtual double VisitRect(Rect* square) = 0;
  virtual double VisitCircle(Circle* circle) = 0;
};


class Shape
{
public:
  virtual double Calculate(Visitor* visitor) = 0;
};


class Rect : public Shape
{
  double width;
  double height;
public:
  Rect(double width, double height) : width(width), height(height) { }

  double Calculate(Visitor* visitor) override
  {
    return visitor->VisitRect(this);
  }

  double Width() { return width; }
  double Height() { return height; }
};


class Circle : public Shape
{
  double radius;
public:
  Circle(double radius) : radius(radius) { }

  double Calculate(Visitor* visitor) override
  {
    return visitor->VisitCircle(this);
  }
 
  double Radius() { return radius; }
};


class SquareVisitor : public Visitor
{
public:
  double VisitRect(Rect* square) override
  {
    return square->Height() * square->Width();
  }

  double VisitCircle(Circle* circle) override
  {
    return PI * circle->Radius() * circle->Radius();
  }
};


class PerimeterVisitor : public Visitor
{
public:
  double VisitRect(Rect* square) override
  {
    return square->Height() * 2 + square->Width() * 2;
  }

  double VisitCircle(Circle* circle) override
  {
    return 2 * PI * circle->Radius();
  }
};


int main()
{
  Circle circle(4);
  Rect rect(3, 5);

  SquareVisitor sv;
  cout << "Circle square = " << circle.Calculate(&sv) << endl;
  cout << "Rect square = " << rect.Calculate(&sv) << endl;

  cout << endl;

  PerimeterVisitor pv;
  cout << "Circle perimeter = " << circle.Calculate(&pv) << endl;
  cout << "Rect perimeter = " << rect.Calculate(&pv) << endl;
}