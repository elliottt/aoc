#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    {
        ifstream in{argv[1]};
    }

    return 0;
}
