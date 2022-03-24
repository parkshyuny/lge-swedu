## Section 2: "공통성과 가변성의 분리"
03/24/2022

### Introduction

#### Problem 1: 멤버 함수

> 변하지 않는 코드 안에 변해야 하는 부분이 있다면 분리 하는 것이 좋다.

```
class Edit {
  string data;
  public:
    string getData() {
      char c = getch();
      
      if (isdigit(c)) { # 만약 입력 값이 문자여야 한다면?
        data.push_back(c);
        cout << c;
      }
      
      cout << endl;
      return data;
    }
}
```

만약 위 코드가 하나의 library라면 입력 값의 validation(정책)을 유연하게 변경할 수 있도록 해야 한다.<br/>
그렇지 않으면 입력 값의 유연성이 바뀔 때마다 `getData()`를 변경시켜야 한다. 
```
if (validate(c)) {
  ...
}
```

분리하는 방법은 두 가지가 있다.
1. Template method
2. Strategy method

#### 1.1 Template Method

```
virtual bool validate(char c) {
   return isdigit(c);
}

string getData() {
   ...
   if (validate(c)) {
     ...
   }
}
```
여기서 `validate()`를 포함해 기본적인 정책이 정의되어 있다. 정책을 바꾸게 되면 이 코드를 변경하지 않아도, Edit 클래스의 자녀 클래스를 만들어서 `validate()`를 재정의 가능하다. 따라서 Edit 클래스는 변하지 않는 "template"이 된다.<br/>
장점:
- 기본적인 구현이 만들어져 있는 상태이고, 자녀 클래스가 일부 재정의만 하면 된다.

```
class AddressEdit: public Edit
{
  virtual bool validate(char c) {
    return true;
  }
}
```

#### 1.2 Strategy Method

```
class IValidator # 인터페이스
{
  virtual bool validate(char c) = 0;
  virtual ~IValidator() {}
}

class LimitDigitValidator : public IValidator
{
  ...
}

class Edit
{
  ...
  IValidator* pVal = 0;
  public:
    void setValidator(IValidator* p) { 
      pVal = p;
    }
  
    string getData() {
      if(pVal == 0 || pVal->validate(c)) {
        ...
      }
    }
}
```
정책을 바꾸게 되면 이 코드를 변경하지 않아도, 인터페이스를 구현한 클래스로 `validate()`를 재정의 가능하다.<br/>
장점:
- Encapsulation
- 실행 시간에 정책을 변경할 수 있다.
```
class LimitDigitValidator : public IValidator
{
  int value;
  public:
    LimitDigitValidator(int n) : value(n) { ...}
    ...
}

int main() {
  Edit edit;
  LimitDigitValidator v(5);
  LimitDigitValidator v(10);
  
  edit.setValidator(&v); // 어떤 정책을 사용할 것인가?
}
```

#### Problem 2: 일반 함수

```
void Sort(int* arr, bool(*cmp)(int, int)) {
  ...
  if (cmp(x[i], x[j]) { // Ascending or descending order?
    swap(x[i], x[j]);
  }
  ...
}

bool cmp1(int a, int b) { ... }
bool cmp2(int a, int b) { ... }

int main() {
  (1) Sort(x, [](int a, int b){ ...} ); // Lambda 함수
  (2) Sort(x, &cmp1);
}
```

일반 함수 내에서 변하는 정책이 있다면, 함수 포인터의 인자로 받게 한다.
