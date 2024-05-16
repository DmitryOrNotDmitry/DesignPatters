#include <iostream>
#include <vector>

using namespace std;


/*
    1. Алгоритм создания сложного объекта не должен зависеть от того, 
       из каких частей состоит объект и как они стыкуются между собой
*/


class TextConverter // Builder
{
public:
  virtual void convertChar() = 0;
  virtual void convertFontChange() = 0;
};


class ASCIIText // Product
{
};


class ASCIIConverter : public TextConverter // Concrete Builder
{
  ASCIIText text;
public:

  ASCIIText& getText()
  {
    return text;
  }

  void convertChar() override
  {
    cout << "Convert char to ASCII \n";
  }

  void convertFontChange() override
  {
    cout << "Convert font change to ASCII \n";
  }
};



class RTFReader // Director
{
public:
  void parseRTF(TextConverter& converter)
  {
    converter.convertChar();
    converter.convertChar();
    converter.convertChar();
    converter.convertFontChange();
    converter.convertChar();
  }
};



int main()
{
  ASCIIConverter converter;
  RTFReader rtfReader;

  rtfReader.parseRTF(converter);
}