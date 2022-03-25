## State Pattern

> 객체의 내부 상태에 따라 동작이 변경하도록 한다. 

### 1. Background
```
class Character {
  int item = 0;
  public:
    void run() {
      // item에 따른 조건문 (if, switch) 
    }
    
    void attack() {
      // 조건문 (if, switch)
    }
}
```
새로운 `item`이 등장할 때마다 코드를 변경해야 한다.

### 2. State Pattern

#### Template Method X

```
Character* p = new NormalCharacter;
p->run();

p = new PowerItemCharacter; // 객체에 대한 변화가 아닌 "클래스"에 의한 변화
p->run();
```

#### Strategy Method

```
class IState {
  virtual void run() = 0;
  virtual void attack() = 0;
  virtual ~IState() {}
}

class NormalState : public IState { ... }
class PowerItemState : public IState { ... }

class Character {
  IState* state;
  public:
    void changeState(IState* p) {
      state = p;
    }
   ...
}
```

