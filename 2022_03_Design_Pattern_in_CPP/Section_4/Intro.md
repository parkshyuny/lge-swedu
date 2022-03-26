## Section 4: 간접층의 원리
03/26/2022

### Adapter Pattern

> Adaption / Wrapping
> 
>- 기존에 있는 인터페이스를 클라이언트가 사용하고자 다른 인터페이스("모습")로 변환("연결")된다.
>- **호환성** 때문에 사용할 수 없었던 클래스 / 객체를 연결해서 사용할 수 있다.

#### Type 1: Class Adapter

```
class Shape {
  public:
    virtual void draw() { ... }
}

class Rect : public Shape {
  ...
}

class Text : public Shape {
  public:
    virtual void draw() { ... }
}
```

만약, `textview.h` 라이브러리가 존재한다면?

```
class Text: public TextView, public Shape {
  public:
    ...
    virtual void draw() { 
      TextView::show(); // TextView라는 클래서의 라이브러리 함수 호출
    }      
}
```

도형 편집기에서 `TextView`가 쓰일 수 있도록 `Text`클래스가 연결해 주며, **상속**을 자주 사용한다.<br/>
기존에 존재하던 클래스의 인터페이스를 변경하지 않고, 클라이언트가 사용할 수 있도록 인터페이스(함수 이름)를 변경한다.


#### Type 2: Object Adapter

```
int main() {
  TextView tv("world");
  vector<Shape*> v;
  
  v.push_back(&tv); // 에러 발생
}
```

`TextView`는 `Shape`의 파생 클래스가 아니기 때문에 에러가 발생한다.

```
class ObjectAdapter : public shape {
  TextView* pView; // 반드시 포인터로 사용
  public:
    ObjectAdapter(TextView* p) {
      pView = p;
    }
    virtual void draw() {
      pView->show();
    }
}

int main() {
  ...
  v.push_back(new ObjectAdapter(&tv));
```

기존에 있는 객체를 사용하기 위해 객체의 인터페이스를 변경한다.<br/>
**Composition**(member 변수)을 자주 사용한다.


### Bridge Pattern

> 구현과 추상화 개념을 분리해서 각각 독립적으로 변형할 수 있게 한다.<br/>
> -**업데이트**에 많이 사용되는 패턴이다.

<p align="center">
  <img width="322" alt="Screen Shot 2022-03-26 at 6 36 48 PM" src="https://user-images.githubusercontent.com/100692678/160233733-a882de19-92c8-440a-b9c1-03a7f8e03cbe.png">
</p>

```
class IMP3 {
  public:
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual ~IMP3() {}

class IPod : public IMP3 { ... }

class People {
  public:
    void useMP3(IMP3* p) {
      p->play()
    }
}
```

만약, `useMP3()` 동작을 변경하고 싶을 때, `IMP3` 인터페이스를 매번 변경해야 하는 건가?<br/>

```
class IPod : public IMP3 { ... } (1) 구현

class MP3 {                      (2) 추상화 (클라이언트가 다른 인터페이스/클래스 모름)
  IMP3* p;
  public:
    MP3() {
      p = new IPod();
    }
    void play() { 
      p->play(); 
    }
    void stop() {
      p->stop();
    }
    void playOneMinute() { // 인터페이스 안 건드리고 새로 추가된 함수
      ...
    }
}
```
<p align="center">
  <img width="332" alt="Screen Shot 2022-03-26 at 6 43 25 PM" src="https://user-images.githubusercontent.com/100692678/160233972-65fd7f5a-d107-4cfa-905f-fdc218404a09.png">
</p>
