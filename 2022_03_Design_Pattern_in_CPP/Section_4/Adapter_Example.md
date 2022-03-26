### Example

List의 인터페이스를 stack처럼 보이도록 변경해보자.

#### Type 1: Class Adapter

```
#include <list>

template<typename T> class Stack : private list<T> {
  public:
    void push(const T& a) {
      list<T>::push_back(a);
    }
    void pop() {
      list<T>::pop_back();
    }
    T& top() {
      return list<T>::back();
    }
}

int main() {
  Stack<int> s;
  s.push(10);
  s.push(20);
  
  s.push_front(20); // Private 함수를 외부에서 호출 불가
}
```

#### Type 2: Object Adapter

```
#include <list>

template<typename T> class Stack {
  list<T> st;
  public:
    void push(const T& a) {
      st.push_back(a);
    }
    void pop() {
      st.pop_back();
    }
    T& top() {
      st.back();
    }
}
```
