## Adapter Pattern
03/26/2022

### Introduction

> Adaption / Wrapping
> 
>- 기존에 있는 인터페이스를 클라이언트가 사용하고자 다른 인터페이스("모습")로 변환("연결")된다.
>- 호환성 때문에 사용할 수 없었던 클래스 / 객체를 연결해서 사용할 수 있다.

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

도형 편집기에서 `TextView`가 쓰일 수 있도록 `Text`클래스가 연결해 주었다.<br/>
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
멤버 변수를 사용하는 경우가 많다 -- "Composition".
