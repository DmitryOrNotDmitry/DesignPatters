#include <iostream>
#include <vector>

using namespace std;


/*
    1. Классу заранее неизвестно, объекты каких классов ему необходимо создавать

    2. Класс спроектирован так, чтобы объекты, которые он создает, определялись подклассами
*/


class Document
{
public:
  virtual void Open() {}
};

class XmlDocument : public Document
{
public:
  void Open() override
  {
    cout << "Open xml document \n";
  }
};



class Application
{
  vector<Document*> docs;
public:
  ~Application()
  {
    for (auto doc : docs)
      delete doc;
  }
  
  virtual Document* createDocument() { return new Document(); }
  
  void newDocument()
  {
    Document* doc = createDocument();
    docs.push_back(doc);
    doc->Open();
  }
};

class MyApplication : public Application
{
  Document* createDocument() override
  {
    return new XmlDocument();
  }
};



class Client
{
public:
  void newDoc(Application& app)
  {
    app.newDocument();
  }
};



int main()
{
  Application* app = new MyApplication();
  Client client;

  client.newDoc(*app);

  delete app;
}