#include <iostream>


class Prism
{
public:
    Prism(double h) {
        high_ = h;
    }
    virtual double Square() const = 0;
    virtual double Volume() const {
        return Square() * high_;
    }
protected:
    double high_;
};

class Box: public Prism
{
public:
    Box(double h, double l): Prism(h) {
        side_ = l;
    }
    virtual double Square() const {
        return side_ * side_;
    }
protected:
    double side_;
};

class Cube : public Box
{
public:
    Cube(double l) : Box(l, l) {
        side_ = l;
    }
};



int main()
{
    const Prism *p, * q, * r;
    Box a(0.5, 2), b(5, 0.2);
    Cube c(0.5);
    p = &a; q = &b; r = &c;
    printf("Squares: %3.31f %3.31f %3.31f\n", 
        p->Square(), q->Square(), r->Square());
    printf("Squares: %3.31f %3.31f %3.31f\n",
        p->Volume(), q->Volume(), r->Volume());
    return 0;
}

