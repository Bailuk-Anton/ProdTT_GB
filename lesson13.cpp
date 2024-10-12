#include "lesson13.h"

void Lesson13::task1()
{
    Dog fido;
    std::string toyName = "ball";

    fido.getToy(toyName);
    fido.dropToy();

    Dog spot;
    spot.getToy(toyName);
}

void Lesson13::task2()
{
    shared_ptr_toy ball = make_shared_toy("ball");
    shared_ptr_toy copy_of_ball = make_shared_toy(ball);

    std::cout << "Name of first toy: " << ball.ptr_->getNmae() << std::endl;
    std::cout << "Name of second toy: " << copy_of_ball.ptr_->getNmae() << std::endl;
}

void Lesson13::task3(){

}

Lesson13::Lesson13()
{

}
