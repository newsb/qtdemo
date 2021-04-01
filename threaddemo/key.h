#ifndef KEY_H
#define KEY_H

class Key {
  public:
    Key() { key = 0; }
    int creatKey() {
        ++key;
        return key;
    }
    int value() const { return key; }

  private:
    int key;
};
#endif // KEY_H
