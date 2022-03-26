#include <iostream>
#include <list>
using namespace std;

// Class Adapter
template<typename T> class Queue : private list<T> {
  public:
    void Push(const T& a) {
      list<T>::push_back(a);
    }
    T Pop() {
      T top = list<T>::front();
      list<T>::pop_front();

      return top;
    }
}

/* Object Adapter
template<typename T> class Queue {
  list<T>* pSt;
  public:
    Queue(list<T>* p) : pSt(p) {}
    void Push(const T& a) {
      pSt->push_back(a);
    }
    T Pop() {
      T top = pSt->front();
      pSt->pop_front();

      return top;
    }
}
*/

int main() {
  Queue<int> q;
  q.Push(10);
  q.Push(20);
  
  /*
  list<int> st;
  Queue<int> q(&st);
  */
  
  cout << q.Pop() << endl;
  cout << q.Pop() << endl;
}
