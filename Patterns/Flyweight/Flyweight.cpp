#include <iostream>
#include <map>
#include <vector>

using namespace std;


/*
    Многие группы объектов можно заменить относительно небольшим количеством совместно используемых объектов
*/


struct Context
{
  int Font;
  int Color;
  bool IsBold;
};
  


class Flyweight
{
public:
  virtual void Operation(Context externalContex) = 0;
};


class Character : public Flyweight
{
  char c;
public:
  Character(char c) : c(c) {}

  void Operation(Context externalContex) override
  {

  }
};


class FlyweightFactory
{
  map<char, Flyweight*> _flyweights;
public:
  ~FlyweightFactory()
  {
    for (auto [key, value] : _flyweights)
      delete _flyweights[key];
  }
  
  Flyweight* GetFlyweight(char key)
  {
    if (!_flyweights.contains(key))
    {
      _flyweights[key] = new Character(key);
    }

    return _flyweights[key];
  }

  size_t size()
  {
    return _flyweights.size();
  }

};


int main()
{
  const char* text = "In statistics, the k-nearest neighbors algorithm (k-NN) is a non-parametric supervised learning method first developed by Evelyn Fix and Joseph Hodges in 1951,[1] and later expanded by Thomas Cover.[2] It is used for classification and regression. In both cases, the input consists of the k closest training examples in a data set. The output depends on whether k-NN is used for classification or regression:  In k-NN classification, the output is a class membership. An object is classified by a plurality vote of its neighbors, with the object being assigned to the class most common among its k nearest neighbors (k is a positive integer, typically small). If k = 1, then the object is simply assigned to the class of that single nearest neighbor. In k-NN regression, the output is the property value for the object. This value is the average of the values of k nearest neighbors. If k = 1, then the output is simply assigned to the value of that single nearest neighbor. k-NN is a type of classification where the function is only approximated locally and all computation is deferred until function evaluation. Since this algorithm relies on distance for classification, if the features represent different physical units or come in vastly different scales then normalizing the training data can improve its accuracy dramatically.[3]  Both for classification and regression, a useful technique can be to assign weights to the contributions of the neighbors, so that the nearer neighbors contribute more to the average than the more distant ones. For example, a common weighting scheme consists in giving each neighbor a weight of 1/d, where d is the distance to the neighbor.[4]  The neighbors are taken from a set of objects for which the class (for k-NN classification) or the object property value (for k-NN regression) is known. This can be thought of as the training set for the algorithm, though no explicit training step is required.  A peculiarity of the k-NN algorithm is that it is sensitive to the local structure of the data.  Statistical setting Suppose we have pairs  ( 𝑋 1 , 𝑌 1 ) , ( 𝑋 2 , 𝑌 2 ) , … , ( 𝑋 𝑛 , 𝑌 𝑛 ) {\displaystyle (X_{1},Y_{1}),(X_{2},Y_{2}),\dots ,(X_{n},Y_{n})} taking values in  𝑅 𝑑 × { 1 , 2 } {\displaystyle \mathbb {R} ^{d}\times \{1,2\}}, where Y is the class label of X, so that  𝑋 | 𝑌 = 𝑟 ∼ 𝑃 𝑟 {\displaystyle X|Y=r\sim P_{r}} for  𝑟 = 1 , 2 {\displaystyle r=1,2} (and probability distributions  𝑃 𝑟 {\displaystyle P_{r}}). Given some norm  ‖ ⋅ ‖{\displaystyle \|\cdot \|} on  𝑅 𝑑 {\displaystyle \mathbb {R} ^{d}} and a point  𝑥 ∈ 𝑅 𝑑 {\displaystyle x\in \mathbb {R} ^{d}}, let  ( 𝑋 ( 1 ) , 𝑌 ( 1 ) ) , … , ( 𝑋 ( 𝑛 ) , 𝑌 ( 𝑛 ) ) {\displaystyle (X_{(1)},Y_{(1)}),\dots ,(X_{(n)},Y_{(n)})} be a reordering of the training data such that  ‖ 𝑋 ( 1 ) − 𝑥 ‖ ≤ ⋯ ≤ ‖ 𝑋 ( 𝑛 ) − 𝑥 ‖{\displaystyle \|X_{(1)}-x\|\leq \dots \leq \|X_{(n)}-x\|}.  Algorithm  Example of k-NN classification. The test sample (green dot) should be classified either to blue squares or to red triangles. If k = 3 (solid line circle) it is assigned to the red triangles because there are 2 triangles and only 1 square inside the inner circle. If k = 5 (dashed line circle) it is assigned to the blue squares (3 squares vs. 2 triangles inside the outer circle).";
  int len = strlen(text);

  vector<Flyweight*> v;
  v.resize(len);

  FlyweightFactory factory;

  for (int i = 0; i < len; i++)
  {
    v[i] = factory.GetFlyweight(text[i]);
  }

  cout << "String length " << len << "(size = "<< len << " bytes), count Flyweight " << factory.size() << "(size = " << sizeof(Flyweight) * factory.size() << " bytes)" << endl;

}