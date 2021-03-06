#include <string>
#include <iostream>
#include <list>
using namespace std;

struct Entity {
  string fname;
  public:
    Entity(string name): fname(name) {}
    virtual ~Entity() {}
    virtual int getSize() = 0;
    virtual void print() = 0;
};
  
class Folder : public Entity {
  list<Entity*> lst;
  
  public:
    Folder(string name): Entity(name) {}
    /*~Folder() {
        delete lst;    
    }*/
  
    void add(Entity* p) {
      lst.push_back(p);
    }
  
    virtual int getSize() {
      int total = 0;
      for (auto& element : lst) {
        total += element->getSize();
      }
      return total;
    }
    
    virtual void print() {
      cout << "[" << fname << "]" << endl;
      
      for (auto& element : lst) {
        cout << " : ";
        element->print();
      }
    }
};

class File : public Entity {
  int fsize;
  public:
    File(string name, int size): fsize(size), Entity(name) {}
  
    virtual int getSize() {
      return fsize;
    }
  
    virtual void print() {
      cout << "(" << fname << ", " << fsize << ")" << endl;
    }
};

int main() {
  Folder* rootFolder = new Folder("ROOT");
  Folder* aaaaFolder = new Folder("AAAA");
  Folder* bbbbFolder = new Folder("BBBB");
  
  File* file1 = new File("a.txt", 10);
  File* file2 = new File("b.txt", 20);
  File* file3 = new File("c.txt", 30);
  File* file4 = new File("d.txt", 40);
  
  rootFolder->add(aaaaFolder);
  rootFolder->add(bbbbFolder);
  rootFolder->add(file1);
  
  aaaaFolder->add(file2);
  aaaaFolder->add(file3);
  
  bbbbFolder->add(file4);
  
  cout << file1->getSize()      << endl;
  cout << aaaaFolder->getSize() << endl;
  cout << rootFolder->getSize() << endl;
  
  //file1->print();
  rootFolder->print();
}
