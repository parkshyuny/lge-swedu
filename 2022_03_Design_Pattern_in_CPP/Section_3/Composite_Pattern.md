## Section 3: 재귀적 포함
03/26/2022

### Introduction

> 객체를 tree 구조로 구성하여 "part-whole" hierarchy를 만들 수 있다.<br/>
> (Any object is a _part_ of the _whole_ composition)

> 개별 객체와 복합 객체를 구별하지 않고 동일한 방법으로 다룰 수 있다.

<p align="center">
  <img width="311" alt="Screen Shot 2022-03-25 at 10 58 32 AM" src="https://user-images.githubusercontent.com/100692678/160039622-9b22b5e3-438a-4645-a4e5-94386ea61660.png">
</p>

그림에서 보이듯, 팝업 메뉴는 또 다른 팝업 메뉴나 일반 메뉴를 가질 수 있다. 이것을 구현하기 위해 `MenuItem`과 `PopupMenu`를 묶어서 공통의 클래스인 `BaseMenu`로 만들고, `PopupMenu`가 여러 종류의 메뉴를 가질 수 있게 할 수 있다.

```
class BaseMenu {
  string title;
  public:
    BaseMenu(string s): title(s) { ... }
    virtual void command() = 0;
}

class MenuItem : public BaseMenu {
  int id;
  public:
    MenuItem(int n, string s): id(n), BaseMenu(s) { // Base 클래스에 디폴트 생성자(인자 없는 생성자) 없을 시 호출 필요
      ... 
    } 
    virtual void command() { ... }
}

class PopupMenu : public BaseMenu {
  vector<BaseMenu*> v; // 핵심
  public:
    PopupMenu(string s): BaseMenu(s) {
      ...
    }
    void addMenu(BaseMenu* p) { 
      v.push_back(p);
    }
    virtual void command() {
      ...
    }
}
```

실제 사용 모습은 아래와 같다.

```
int main() {
  PopupMenu* menubar = new PopupMenu("menuBar");
  PopupMenu* pm1 = new PopupMenu("화면 설정");
  PopupMenu* pm2 = new PopupMenu("소리 설정");
  MenuItem* m1 = new MenuItem("정보 확인", 1);
  
  menubar->addMenu(pm1);
  menubar->addMenu(pm2);
  menubar->addMenu(m1);
  
  pm1->addMenu(new menuItem("해상도 변경", 2);
  ...
}
```
<p align="center">
  <img width="358" alt="Screen Shot 2022-03-26 at 10 32 16 AM" src="https://user-images.githubusercontent.com/100692678/160219442-b8a99a5b-ca8a-4bc9-aaab-416cf0cee749.png">
</p>


