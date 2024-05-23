#include <iostream>
#include <vector>

using namespace std;


/*
    Виртуальный заместитель создает тяжелый объект по требованию. (Отложенное/ленивое создание)
*/


class Graphic
{
public:
  virtual void Draw() = 0;
  virtual void GetExtent() = 0;
};



class Image : public Graphic
{
  int _extent;
public:
  Image(int extent) :_extent(extent) {}
  
  void Draw() override
  {
    cout << "Draw image \n";
  }

  void GetExtent() override
  {
    cout << "Image's extent " << _extent << "\n";
  }
};


class ImageProxy : public Graphic
{
  int _extent;
  Image* _image;

  Image* GetImage()
  {
    if (!_image)
      _image = new Image(99);

    return _image;
  }

public:
  ImageProxy(int extent) :_extent(extent) {}

  ~ImageProxy() 
  { 
    if (_image) 
      delete _image; 
  }

  void Draw() override
  {
    GetImage()->Draw();
  }

  void GetExtent() override
  {
    if(_image)
      _image->GetExtent();
    else
      cout << "Cached ImageProxy's extent " << _extent << "\n";
  }
};


void drawGraphic(Graphic& g)
{
  g.Draw();
}


int main()
{
  ImageProxy image(10);
  image.GetExtent();

  drawGraphic(image);
 
  image.GetExtent();
}