#include <iostream>
#include <vector>

using namespace std;


/*
    1. Параметризация объектов выполняемым действием.

    2. Определение, постановка в очередь и выполнение запросов в разное время.

    3. Поддержка отмены операций, логгирования изменений.
*/


class Command
{
public:
  virtual void Execute() = 0;
};


class MenuItem
{
  Command* command;
public:
  void SetCommand(Command* command)
  {
    this->command = command;
  }

  void Click()
  {
    command->Execute();
  }
};


class Menu
{
  vector<MenuItem*> items;
public:
  void Add(MenuItem* item)
  {
    items.push_back(item);
  }
};


class Document
{
  const char* name;
public:
  Document(const char* name) : name(name) {}

  void Open()
  {
    cout << "Open document '" << name << "' \n";
  }

  void Paste()
  {
    cout << "Paste into document '" << name << "' \n";
  }
};


class Application
{
  vector<Menu*> menus;
  vector<Document*> docs;
public:

  void Add(Document* doc)
  {
    docs.push_back(doc);
  }

  void Add(Menu* menu)
  {
    menus.push_back(menu);
  }
};


class OpenCommand : public Command
{
  Application* app;

  const char* AskUesr()
  {
    return "file.txt";
  }

public:
  OpenCommand(Application* app) : app(app) { }

  void Execute() override
  {
    const char* name = AskUesr();
    Document* doc = new Document(name);
    app->Add(doc);
    doc->Open();
  }
};


class PasteCommand : public Command
{
  Document* doc;
public:
  PasteCommand(Document* doc) : doc(doc) { }

  void Execute() override
  {
    doc->Paste();
  }
};


int main()
{
  Application app;
  
  Document doc(".gitignore");
  app.Add(&doc);

  Menu menu;
  
  MenuItem pasteMenu;
  menu.Add(&pasteMenu);
  PasteCommand paste(&doc);
  pasteMenu.SetCommand(&paste);
 
  MenuItem openMenu;
  menu.Add(&openMenu);
  OpenCommand open(&app);
  openMenu.SetCommand(&open);


  openMenu.Click();
  pasteMenu.Click();

}