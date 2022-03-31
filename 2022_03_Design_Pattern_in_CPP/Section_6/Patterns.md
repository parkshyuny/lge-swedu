### 1. Singleton

>  객체 생성을 1개로 제어한다.

```
class Cursor {
  int x, y;
  static Cursor instance;
  private:
    Cursor() {}
  public:
    static Cursor& getInstance() {
      static Cursor instance; // 객체 생성을 한 번만
      return instance;
    }
};

int main() {
  Cursor c1 = Cursor::getInstance();
}
```

위 코드에서, `Cursor c2 = c1;`의 결과는 어떻게 될까? 디폴트 생성자가 자동으로 호출이 되며, 생성자를 `private`으로 선언한 것이 무의미해진다. 
이 경우 복사 생성자 호출 및 연산자 사용을 아래와 같이 막을 수 있다.

```
private:
  Cursor() {}
  Cursor(const Cursor&) = delete; // 복사 생성자 삭제
  Cursor& operator== (const Cursor&) = delete; // 연산자 삭제
```

### 2. Factory
### 3. Abstract Factory
### 4. Builder
