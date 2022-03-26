### Bridge Pattern

> 구현과 추상화 개념을 분리해서 각각 독립적으로 변형할 수 있게 한다.<br/>
> - **업데이트**에 많이 사용되는 패턴이다.

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

만약, `useMP3()` 동작을 변경하고 싶을 때, `IMP3` 인터페이스를 매번 변경해야 하는 건가?

<p align="center">
  <img width="332" alt="Screen Shot 2022-03-26 at 6 43 25 PM" src="https://user-images.githubusercontent.com/100692678/160233972-65fd7f5a-d107-4cfa-905f-fdc218404a09.png">
</p>

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
