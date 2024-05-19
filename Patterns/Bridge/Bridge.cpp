#include <iostream>
#include <vector>

using namespace std;


/*
    Вы хотите использовать существующий класс, но его интерфейс не соответствует вашим потребностям
*/


class WindowImp
{
public:
  virtual void DrawTextImp() = 0;
  virtual void DrawLineImp() = 0;
};

class XWindowImp : public WindowImp
{
public:
  void DrawTextImp() override
  {
    cout << "XWindow draw text \n";
  }

  void DrawLineImp() override
  {
    cout << "XWindow draw line \n";
  }
};

class LinuxWindowImp : public WindowImp
{
public:
  void DrawTextImp() override
  {
    cout << "Linux draw text \n";
  }

  void DrawLineImp() override
  {
    cout << "Linux draw line \n";
  }
};



class Window 
{
  WindowImp* imp;

protected:
  Window()
    : imp(new LinuxWindowImp())
  {
  }

public:

  ~Window() { delete imp; }
  
  void DrawText()
  {
    imp->DrawTextImp();
  }

  void DrawRect()
  {
    imp->DrawLineImp();
    imp->DrawLineImp();
    imp->DrawLineImp();
    imp->DrawLineImp();
  }
};

class IconWindow : public Window
{
public:
  IconWindow() {}

  void DrawBorder()
  {
    DrawRect();
    DrawText();
  }
};

class TransientWindow : public Window
{
public:
  TransientWindow() {}

  void DrawCloseBox()
  {
    DrawRect();
  }
};



int main()
{
  IconWindow icon;
  icon.DrawBorder();

  TransientWindow tranWin;
  tranWin.DrawCloseBox();
}