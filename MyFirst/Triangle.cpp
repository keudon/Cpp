#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    float area, base, height;

    cout << "Enter Base\n";
    cin >> base;

    cout << "base typeid : " << typeid(base).name() << "\n" <<endl;

    if (strcmp(typeid(base).name(),"i")!=0) {
        cout << "base typeid is not Integer\n";
    } else {
        cout << "base is Integer\n";
    }

    cout << "Enter Height\n";
    cin >> height;

    area=base*height*0.5;

    cout << "Area is " << area <<endl;

    return 0;

}


