#include <iostream>
#include <vector>

using namespace std;


/*
    ѕредорставление простого интерфейса к сложной подсистеме. —нижение св€зей между разными подсистемами.
*/


class CodeGenerator
{
public:
  void GenerateCode()
  {
    cout << "Generate code... \n";
  }
};

class Scanner
{
public:
  void ScanCode()
  {
    cout << "Scan code... \n";
  }
};

class Parser
{
public:
  void ParseCode()
  {
    cout << "Parse code... \n";
  }
};

class ProgramNodeBuilder
{
public:
  void BuildNodes()
  {
    cout << "Build program nodes... \n";
  }
};


class Compiler // Facade
{
public:
  void Compile()
  {
    Scanner scanner;
    ProgramNodeBuilder builder;
    Parser parser;

    scanner.ScanCode();
    parser.ParseCode();

    CodeGenerator gen;
    gen.GenerateCode();

    builder.BuildNodes();
  }
};


int main()
{
  Compiler compiler;
  compiler.Compile();
}