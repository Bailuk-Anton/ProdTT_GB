#include "lesson11.h"

void Lesson11::task1()
{
    Dog dog1("Steve");

    dog1.addTalent(new Dancing());
    dog1.addTalent(new Swimming());

    dog1.show_talents();

    delete dog1.removeTalent(dog1.talents[0]);

    dog1.show_talents();

    return 0;
}

void Lesson11::task2()
{
    Circle circle(5);
    printParams(&circle);

    Rectangle rect(10, 5);
    printParams(&rect);

    Triangle tri(3, 4, 5);
    printParams(&tri);
}

Lesson11::Lesson11()
{

}
