#include <iostream>
#include <vector>
#include <string>

using namespace std;


/*
    1. Вычленение и локализация в 1 классе алгоритма общего для всех подклассов

    2. Однократное определение общего алгоритма, который конкретизируют подклассы с помощью более примитивных операций, использованных в этом алгоритме
*/


class Document
{
  const char* name;
public:
  Document(const char* name) : name(name) {}

  void Open()
  {
    cout << "Open document '" << name << "' \n";
  }

  virtual void DoRead() = 0;
};


class XMLDocument : public Document
{
public:
  XMLDocument(const char* name) : Document(name) {}

  void DoRead() override
  {
    cout << "Read xml document \n";
  }
};


class Application
{
  vector<Document*> docs;
public:

  void AddDocument(Document* doc)
  {
    docs.push_back(doc);
  }

  void OpenDocument(const char* name)
  {
    if (!CanOpenDocument(name))
    {
      return;
    }

    Document* doc = DoCreateDocument(name);

    if (doc)
    {
      AddDocument(doc);
      doc->Open();
      doc->DoRead();
    }
  }

  virtual Document* DoCreateDocument(const char* name) = 0;
  virtual bool CanOpenDocument(const char* name) = 0;
};


class MyApplication : public Application
{
public:

  Document* DoCreateDocument(const char* name)
  {
    return new XMLDocument(name);
  }

  bool CanOpenDocument(const char* name)
  {
    string tmp(name);
    if (tmp.find(".xml") != static_cast<size_t>(-1))
    {
      cout << "MyApp may open the document '" << name << "'\n";
      return true;
    }

    cout << "MyApp may not open the document '" << name << "'\n";
    return false;
  }
};


int main()
{
  MyApplication app;

  app.OpenDocument("file.xml");
  cout << endl;
  app.OpenDocument("file.txt");
}