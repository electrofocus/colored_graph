#include "interface.h"

using namespace std;

int main() {

    Interface interface("input.txt", "output.txt");
    interface.start();

    return 0;
}


