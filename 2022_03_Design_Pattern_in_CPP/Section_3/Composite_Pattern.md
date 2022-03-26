## Introduction

<p align="center">
  <img width="311" alt="Screen Shot 2022-03-25 at 10 58 32 AM" src="https://user-images.githubusercontent.com/100692678/160039622-9b22b5e3-438a-4645-a4e5-94386ea61660.png">
</p>

`MenuItem`과 `PopupMenu`를 묶어서 공통의 클래스인 `BaseMenu`로 만들어서, `PopupMenu`가 여러 종류의 메뉴를 가질 수 있게 할 수 있다.

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

int main() {
  MenuItem m("sound", 11);
}
```

