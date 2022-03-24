## "Policy Base" Design

```
template<typename T> class List {
  public:
    void push_front(const T& a) {
      Lock();        (1) 동기화가 필요 없을 시엔 성능 저하
      ...
      Unlock();
    }
}

List<int> s;  // Global variable = 멀티 스레드에 안전하지 않다

int main() {
  Lock();            (2) 번거롭다
  s.push_front(10);
  Unlock();
}
```
### 1. Background

아래 코드는 strategy method를 사용해 동기화한 것이다.

```
class ISync {
  virtual void Lock() = 0;
  virtual void Unlock() = 0;
  virtual ~ISync {}
}

class MutexLock : public ISync {
  mutext m; // Mutex 클래스를 통해 자동화 가능 (예: lock() 제공)
  public:
    virtual void Lock() {
      ...
    }
    virtual void Unlock() {  
      ...
    }
}

template<typename T> class List {
  ...
  ISync* pSync = 0;
  public:
    void setSync(ISync* p) {
      pSync = p;
    }
    void push_front(const T& a) {
      if (pSync != 0) {
        pSync->Lock();
      }
      ...
      if (pSync != 0) {
        pSync->Unlock();
      }
    }
}
```
<p align="center">
  <img width="323" alt="Screen Shot 2022-03-24 at 10 47 46 PM" src="https://user-images.githubusercontent.com/100692678/159930215-ade6ddaf-c2c7-48b9-a51c-b16bd4e1d82c.png">
</p>

그런데, virtual 함수는 일반 함수보다 오버헤드가 있다고 한다. 그렇다면 여기서 좀 더 성능을 발전시킬 수 있을까?

### 2. Policy Base

#### Inline function

- 자주 호출되고 작은 함수일 경우, 호출하는데 소요되는(예: 소스코드 및 인자 값 저장) 시간 > 실행 시간
- Compile 시, 이런 함수의 소스코드 전체를 아예 주소 값 대신 삽입 "inline"
- Virtual 함수 대신 inline 함수 사용하면 성능 개선 시킬 수 있다

```
template<typename T, typename ThreadModel = NoLock> class List {
  ThreadModel tm;
  public:
    void push_front(const T& a) {
      tm.Lock();
      ...
      tm.Unlock();
    }
};

class MutexLock {
  public:
    inline void Lock() { 
      ... 
    }
    
    inline void Unlock() {
      ...
    }
}

class NoLock {
    inline void Lock() {} // 치환될 시, 실제 함수를 호출하지 않는 것과 동일
    inline void Unlock() {}
}

List<int, MutexLock> s;
```

이와 같이 `template` 인자로 정책 클래스를 분리 시키는 기술이며, C++ 라이브러리에서 많이 볼 수 있는 기술이다.<br/>
Template method처럼 실행시간에 정책 교체 불가하다.
