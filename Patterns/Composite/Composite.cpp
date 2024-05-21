#include <iostream>
#include <vector>

using namespace std;


/*
    Требуется представить иерархию составных и простых объектов (например узлов и листов) вида "часть - целое"
*/


void outOffset(int offset)
{
  for (int i = 0; i < offset; i++)
    cout << "    ";
}


class Graphic
{
public:

  virtual void Draw(int offset = 0) = 0;

  virtual void Add(Graphic* g) {}
  virtual void Remove(Graphic* g) {}
  virtual Graphic* GetChild(int i) { return nullptr; }

};


class Line : public Graphic
{
public:
  void Draw(int offset = 0) override
  {
    outOffset(offset);
    cout << "Draw line \n";
  }
};


class Circle : public Graphic
{
public:
  void Draw(int offset = 0) override
  {
    outOffset(offset);
    cout << "Draw circle \n";
  }
};


class Picture : public Graphic
{

  vector<Graphic*> graps;

public:

  void Draw(int offset = 0) override
  {
    outOffset(offset);
    cout << "Draw picture... \n";
    for (auto g : graps)
      g->Draw(offset + 1);
  }

  void Add(Graphic* g) override
  {
    graps.push_back(g);
  }
  
  void Remove(Graphic* g) override
  {
    graps.erase(find(graps.begin(), graps.end(), g));
  }

  Graphic* GetChild(int i) override
  {
    return graps[i];
  }

};


int main()
{
  Line line;
  Circle circle;
  Picture inner;
  Picture outer;

  inner.Add(&line);
  inner.Add(&circle);
  
  outer.Add(&line);
  outer.Add(&inner);
  outer.Add(&line);

  outer.Draw();

}