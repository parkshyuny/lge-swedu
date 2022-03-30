### Section 5: 통보, 열거, 방문

#### 1. Observer Pattern

> 객체 사이의 1:N 또는 1:1 종속성(dependency): 한 객체의 상태(state)가 변하면, 종속된 다른 객체에 _통보하고_ 자동으로 수정이 일어나게 한다.
> - 관찰자(observer) vs. 관찰자의 대상(subject)
> - 핵심 요소: 공통의 인터페이스, 통보 함수, 통보되는 시점

##### Example

<p align="center">
  <img width="325" alt="Screen Shot 2022-03-30 at 9 45 29 PM" src="https://user-images.githubusercontent.com/100692678/160837342-abd5272a-de31-47d8-af4a-d48f3d69ff24.png">
</p>

```
class IGraph { // 공통의 인터페이스
  virtual void update(int) = 0; // 통보할 수 있는 함수 정의
  virtual ~IGraph() {}
}

class Table {
  vector<IGraph*> v;
  int data;
  public:
    void attach(IGraph* p) { ... }
    void detach(IGraph* p) { ... }
    void setData(int d) { // 변경되는 시점에 통보하는 함수 호출
      data = d;
      for(auto p: v) {
        p->update(data);
      }
```

#### 2. Container Pattern

> 일반형의 데이터를 저장할 수 있게 한다.
> 종류:
>   1. Base 클래스(인터페이스)를 포인터로
>   2. Template

##### 2.1 Interface

```
class SingleList {
  Node* head = 0;
  public:
    void push_front(Object* n) {
      head = new Node(n, head);
    }
};
```

##### 2.2 Template

```
template<typename T> class SingleList {
  Node<T>* head = 0;
  public:
    void push_front(const T& n) {
      ...
    }
};
```

#### 3. Iterator / Enumerator Pattern

> 필요한 자료구조를 모두 동일한 인터페이스를 통해 loop 할 수 있도록 한다.
> - 핵심 요소: 반복자(인터페이스), 반복자 구현
> - 예를 들어, Linked List(포인터)와 array(+1)는 다른 방법으로 접근해야 한다.<br/>
> - 반복자 함수:
>   1. `GetObject()`: 가리키는 곳의 요소 접근 
>   2. `MoveNext()` : 다음 요소로 이동
>   3. 

##### Example

```
template<typename T> class IEnumerator { // 반복자
  virtual ~IEnumerator() {}
  virtual bool MoveNext() = 0;
  virtual T& GetObject() = 0;
}

template<typename T> class SingleList {
  Node<T>* current = 0;
  virtual bool MoveNext() {
  }
  virtual T& GetObject() {
    
  }
```

#### 4. Visitor Pattern
