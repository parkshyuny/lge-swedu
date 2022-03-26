### Proxy Pattern

> 어떤 객체에 대한 접근을 제어할 수 있게 한다.

#### Background

##### Inter-Process Communication (IPC)

- Client-Server 프로그램에서 사용되는 프로세스간 통신
- Open Source 프로젝트에 흔하다

```
#include "ecourse_dp.hpp" // IPC 관련된 함수
using namespace ecourse;  

class Calc { // Server
  public:
    int add() { ... }
    ind sub() { ... }   
}
class Calc;

int dispatch(int code, int x, int y) { calc.add() ... }

int main() {
  ec_start_server("CalcService", dispatch); // Client 접속 대기 > 접속 시, `dispatch()` 호출 

  int server = ec_find_server("CalcService");     // 서버 찾기
  cout << "server: " << server << endl;
  
  int result = ec_send_server(server, 1, 10, 20); // 서버에 "요청" 전달
}
```

