#include <iostream>
#include <vector>
#include <string>

using namespace std;


/*
    1. ѕоведение обьекта зависит от его состо€ни€ и должно измен€тьс€ динамически

    2. «амена множественных ветвлений иерархией классов
*/


class TCPState
{
public:
  virtual void Open() { }
  virtual void Send() { }
  virtual void Close() { }
};


class TCPEstablished : public TCPState
{
  static TCPEstablished* instance;

public:
  static TCPEstablished* Instance()
  {
    if (!instance)
      instance = new TCPEstablished();
    return instance;
  }

  void Close() override 
  { 
    cout << "Close established state \n";

  }
};


class TCPListen : public TCPState
{
  static TCPListen* instance;

public:
  static TCPListen* Instance()
  {
    if (!instance)
      instance = new TCPListen();
    return instance;
  }

  void Send() override
  {
    cout << "Send message \n";
  }

  void Close() override
  {
    cout << "Close listening state \n";
  }
};


class TCPClosed : public TCPState
{
  static TCPClosed* instance;

public:
  static TCPClosed* Instance()
  {
    if (!instance)
      instance = new TCPClosed();
    return instance;
  }

  void Open() override
  {
    cout << "Open connection \n";
  }

  void Close() override
  {
    cout << "Close connection \n";
  }
};


class TCPConnection
{
  TCPState* state;
public:
  TCPConnection() { state = TCPClosed::Instance(); }

  void Open() 
  {
    state->Open();
  }
  
  void Send() 
  {
    state->Send();
  }

  void Close() 
  { 
    state->Close();
  }

  void ChangeState(TCPState* s)
  {
    state = s;
  }
};


TCPClosed* TCPClosed::instance = nullptr;
TCPEstablished* TCPEstablished::instance = nullptr;
TCPListen* TCPListen::instance = nullptr;


void processTCPCon(TCPConnection* con)
{
  con->Open();
  con->Send();
  con->Close();
}


int main()
{
  TCPConnection con;
  processTCPCon(&con);

  con.ChangeState(TCPEstablished::Instance());
  processTCPCon(&con);

  con.ChangeState(TCPListen::Instance());
  processTCPCon(&con);
}