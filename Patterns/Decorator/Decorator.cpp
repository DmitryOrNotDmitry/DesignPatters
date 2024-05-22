#include <iostream>
#include <vector>

using namespace std;


/*
    1. Для уменьшения порождения подклассов типа BorderedTextView, ScrolledTextView, BorderedScrolledTextView.

    2. Динамическое добавление обязанностей объекту, которое прозрачно для клиента.
*/


class VisualComponent
{
public:
  virtual void Draw() = 0;
};


class TextView : public VisualComponent
{
public:
  void Draw() override
  { 
    cout << "Draw text \n";
  }
};


class Decorator : public VisualComponent
{
  VisualComponent& _component;
public:
  Decorator(VisualComponent& component) : _component(component) {}

  void Draw() override
  {
    _component.Draw();
  }
};


class ScrollDecorator : public Decorator
{
  int _scrollPosition;
public:
  ScrollDecorator(VisualComponent& component, int scrollPosition) 
    : Decorator(component)
    , _scrollPosition(scrollPosition) {}

  void Draw() override
  {
    cout << "Scroll to " << _scrollPosition << " position \n";
    Decorator::Draw();
  }
};


class BorderDecorator : public Decorator
{
  int _width;
public:
  BorderDecorator(VisualComponent& component, int width)
    : Decorator(component)
    , _width(width) {}

  void Draw() override
  {
    Decorator::Draw();
    cout << "Border with " << _width << " width \n";
  }

};

void drawComponent(VisualComponent& comp)
{
  comp.Draw();
}

int main()
{
  TextView text;
  drawComponent(text);

  cout << endl;

  ScrollDecorator scroll(text, 144);
  BorderDecorator border(scroll, 10);
  drawComponent(border);
}