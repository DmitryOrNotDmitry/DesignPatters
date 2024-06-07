#include <iostream>
#include <vector>

using namespace std;


/*
    1. Обращение к содержимому агрегированных объектов без раскрытия их внутреннего представления.

    2. Поддержка нескольких типов обходов.
*/


class List
{
  vector<int> items;
public:
  size_t size() const { return items.size(); }
  
  void Add(int item) { items.push_back(item); }

  int Get(int index) const { return items[index]; }
};


class Iterator
{
public:
  virtual void First() = 0;
  virtual void Next() = 0;
  virtual bool IsDone() = 0;
  virtual int CurrentItem() = 0;
};


class ListIterator : public Iterator
{
protected:
  const List* list;
  int current;
public:
  ListIterator(List* l) : list(l), current(0) {}

  virtual void First() { current = 0; }
  virtual void Next() { current++; }
  virtual bool IsDone() { return current >= list->size(); }
  virtual int CurrentItem() { return list->Get(current); }
};


class ReverseListIterator : public ListIterator
{
public:
  ReverseListIterator(List* l) : ListIterator(l) {}

  virtual void First() { current = list->size() - 1; }
  virtual void Next() { current--; }
  virtual bool IsDone() { return current < 0; }
};


void Print(Iterator* iter)
{
  for (iter->First(); !iter->IsDone(); iter->Next())
  {
    cout << iter->CurrentItem() << ' ';
  }
  cout << endl;
}


int main()
{
  List list;
  list.Add(1);
  list.Add(2);
  list.Add(3);
  list.Add(4);

  ListIterator iter(&list);
  ReverseListIterator riter(&list);

  Print(&iter);
  Print(&riter);
}