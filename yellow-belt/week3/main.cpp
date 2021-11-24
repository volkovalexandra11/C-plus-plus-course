#include <iostream>
#include <string>
#include "multi-file projects/PhoneNumber.h"

using namespace std;

int main() {
	string number = "+7-495-111-22-33";
    PhoneNumber p(number);
    number = "+7-495-1112233";
    p = PhoneNumber(number);
	return 0;
}
