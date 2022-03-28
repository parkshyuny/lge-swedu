// Implementation of "strategy" method
class IPredictor {
  virtual int* predict(int x, int y, int z) = 0;
  virtual ~Predictor() {}
}

class RandomPredictor : public IPredictor {
  RandomPredictor() {}
  virtual int* predict(int x, int y, int z) {
    do {
        x = rand() % 9 + 1;
        y = rand() % 9 + 1;
        z = rand() % 9 + 1;
    } while(x == y || y == z || x == z);
  }
}

class BaseBallGame {
  typedef tuple<int, int, int> INPUT;
  typedef tuple<int, int> RESULT;
  vector<pair<INPUT, RESULT> > v;
  IPredictor* pptr; // Predictor pointer
  
  public:
    BaseBallGame() {
      srand((unsigned)time(0));
    }
    
    void setPredictor(IPredictor* p) {
      pptr = p;
    }
  
    void run() {
      
      while(1) {
        int x = 0, y = 0, z = 0;
        
        int* predicted = predict(x, y, z);
        x = predicted[0];
        y = predicted[1];
        z = predicted[2];
        
        cout << "당신이 생각한 숫자는 " 
             << x << ", " << y << ", " << x << " 입니까?" << endl;
        
        int strike = 0, ball = 0;
        cout << "strike 갯수: ";
        cin >> strike;
        if (strike == 3) {
          cout << "성공!" << endl;
          break;
        }
        cout << "ball 갯수: ";
        cin >> ball;

        v.push_back(make_pair(INPUT(x, y, z), RESULT(strike, ball)));
        dump();        
      }
      
    }

    void dump() {
      printf("--------------------------------\n");
      printf("입력값   s b\n");
      for (auto& p : v) {
          printf(" %d %d %d : %d %d\n",
            get<0>(p.first), get<1>(p.first), get<2>(p.first),
            get<0>(p.second), get<1>(p.second));
      }
      printf("--------------------------------\n");
    }
};

int main(void) {
    BaseBallGame bbg;
    bbg.run();
}
