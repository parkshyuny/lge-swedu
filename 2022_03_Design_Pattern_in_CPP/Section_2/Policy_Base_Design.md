### "Policy Base" Design

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
