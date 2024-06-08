#include <iostream>
#include <vector>
#include <string>

using namespace std;


/*
    1. Повторное использование объектов затруднительно, поскольку он обменивается информацией со многими другими объектами.

    2. Понижение связности системы.
*/

class Widget;

class Director
{
public:
  virtual void CreateWidgets() = 0;

  virtual void WidgetChanged(Widget* widget) = 0;
};


class Widget
{
  Director* mediator;
protected:

  Widget(Director* mediator) : mediator(mediator) { }

protected:
  void Changed()
  {
    mediator->WidgetChanged(this);
  }
};


class ListBox : public Widget
{
  vector<string> items;
  int selIndex;

public:
  ListBox(Director* mediator, vector<string> items)
    : Widget(mediator), items(items), selIndex(0) 
  { }
  
  string GetSelection() { return items[selIndex]; }

  void Select(int idx) 
  { 
    selIndex = idx % items.size();
    Changed();
  }
};


class TextBox : public Widget
{
  string value;
public:
  TextBox(Director* mediator, string value)
    : Widget(mediator), value(value) 
  { }

  void SetText(string text) { value = text; }

  string GetText() { return value; }
};


class DialogDirector : public Director
{
  ListBox* listBox;
  TextBox* textBox;

  int count = 0;
public:

  void CreateWidgets() override
  {
    listBox = new ListBox(this, { "One", "Two", "Three" });
    textBox = new TextBox(this, listBox->GetSelection());
  }

  void WidgetChanged(Widget* widget) override
  {
    if (widget == listBox)
    {
      textBox->SetText(listBox->GetSelection());
      cout << "Value of textBox is changed on '" << textBox->GetText() << "'\n";
    }
  }

  void DoSomething()
  {
    listBox->Select(1);
    listBox->Select(2);
    listBox->Select(3);
  }

};


int main()
{
  DialogDirector director;

  director.CreateWidgets();
  director.DoSomething();
}