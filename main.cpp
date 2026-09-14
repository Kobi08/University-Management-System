#include <iostream>
#include "TimeSlot.h"
using namespace std;

int main(){

    cout<<"University Management System PROJECT 1";

    TimeSlot slot1("Monday",9,11,"Lab A");
    TimeSlot slot2("Monday",10,12,"LT-3");
    TimeSlot slot3("Tuesday",9,11,"Lab B");

    cout<<"Slot 1: "<<slot1<<std::endl;
    cout<<"Slot 2: "<<slot2<<std::endl;
    cout<<"Slot 3: "<<slot3<<std::endl;

    cout<<"\nSlot1 clashes Slot2: "
             <<(slot1==slot2)<<endl;

    cout<<"Slot1 clashes Slot3: "
             <<(slot1==slot3)<<endl;

    return 0;
}