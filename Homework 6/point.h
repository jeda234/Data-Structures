class point {
public:
  point (int row, int col);
  int getR();
  int getC();
private:
  int r;
  int c;
};

point::point(int row, int col) {
    r = row;
    c = col;
}

bool operator== (point p1, point p2) { 
    return p1.getR() == p2.getR() && p1.getC() == p2.getC(); 
}

bool operator!= (point p1, point p2) { 
    return p1.getR() != p2.getR() && p1.getC() != p2.getC(); 
}

int point::getR() {
    return r;
}

int point::getC() {
    return c;
}