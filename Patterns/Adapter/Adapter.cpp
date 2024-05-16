#include <iostream>

using namespace std;


/*
    Вы хотите использовать существующий класс, но его интерфейс не соответствует вашим потребностям
*/


class TextView
{
public:
  void getExtent()
  {
    cout << "Extent of text view \n";
  }
};


class Shape
{
public:
  virtual void bounsingBox() = 0;
};

class TextShapeObject : public Shape      // Адаптер уровня объекта
{
  TextView* text = new TextView;
public:
  ~TextShapeObject() { delete text; }

  void bounsingBox() override
  {
    text->getExtent();
    cout << "Convert extent to BoundingBox of Shape...\n\n";
  }
};

class TextShapeClass : public Shape, private TextView      // Адаптер уровня класса
{
public:
  void bounsingBox() override
  {
    getExtent();
    cout << "Convert extent to BoundingBox of Shape...\n\n";
  }
};


class Client
{
public:
  void Operation(Shape& shape)
  {
    shape.bounsingBox();
  }
};


int main()
{
  TextShapeClass textShapeClass;
  TextShapeObject textShapeObj;
  Client client;

  client.Operation(textShapeClass);
  client.Operation(textShapeObj);
}