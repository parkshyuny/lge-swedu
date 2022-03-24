## Section 2: "공통성과 가변성의 분리"
03/24/2022

### 1. Introduction

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

#### Problem
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
여기서 `validate()`에서는 기본적인 정책이 정의되어 있다. 정책을 바꾸게 되면 이 코드를 변경하지 않아도, Edit 클래스의 자녀 클래스를 만들어서 `validate()`를 재정의 가능하다.
따라서 Edit 클래스는 변하지 않는 "template"이 된다.

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
정책을 바꾸게 되면 이 코드를 변경하지 않아도, 인터페이스를 구현한 클래스로 `validate()`를 재정의 가능하다.

### 2. "Policy Base" Design

Note on C++ Syntax

- if 문에서 첫번째 operand가 true 여야 두번째 실행된다.
- 인터페이스 정의 시, 반드시 virtual deconstructor가 구현되어 있어야 한다.
