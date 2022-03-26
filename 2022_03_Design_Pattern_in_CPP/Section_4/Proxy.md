### Proxy Pattern

> 어떤 객체에 대한 접근을 제어할 수 있게 한다.

#### Background

##### Inter-Process Communication (IPC)

- Client-Server 프로그램에서 사용되는 프로세스간 통신
- Open Source 프로젝트에 흔하다

```
#include "ecourse_dp.hpp" // IPC 관련된 함수
using namespace ecourse;  

class ICalc {
  public:
    virtual int add(int x, int y) = 0;
    virtual int sub(int x, int y) = 0;
    virtual ~ICalc() {}
}

class Calc : public ICalc{
  public:
    int add(int x, int y) {
      return x + y;
    }
    ind sub(int x, int y) {
      return x - y;
    }   
}
class calc;

int dispatch(int code, int x, int y) {
  switch(code) {
    case 1: return calc.Add(x, y);
    case 2: return calc.Sub(x, y);
  }
  return -1;
}

int main() {
  ec_start_server("CalcService", dispatch);       // Client 접속 시, `dispatch()` 호출 
  
  int server = ec_find_server("CalcService");     // 서버 찾기 (ID로 식별)
  cout << "server: " << server << endl;
  int result = ec_send_server(server, 1, 10, 20); // 서버에 "요청" 전달
}
```
Server 요청을 좀 더 간결하게 만들 수 없을까?

#### Proxy Pattern

```
class CalcProxy {
  int server;
  public:
    Calc() {
      ec_find_server("CalcService");
    int add(int a, int b) {
      return ec_send_server(server, 1, a, b);
    }
    int sub(int a, int b) { ... }
}

int main() {
  CalcProxy p;
  
  cout << p.add(1, 2) << endl;
  cout << p.sub(10, 8) << endl;
}
```

여기서 `CalcProxy` 클래스는 server `CalcService` 와 Client 사이에서 통신 역할을 해준다.<br/>
Proxy의 장점:

- 간결한 서버 요청
- 잘못된 호출 방지
- Client는 IPC에 대해 알 필요가 없다.
- 기능 추가(예: 보안, 캐쉬)

**Remote Procedure Call (RPC)**: Server에 있는 함수(대부분 _동일한_ signature를 쓴다) 호출

```
p.add(1,2);   // CalcProxy가 실제 덧셈하는 X
p.sub(10,8);
```
