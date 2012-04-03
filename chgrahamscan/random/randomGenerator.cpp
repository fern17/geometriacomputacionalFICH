#include <ctime>
#include <fstream>
#include <cstdlib>
using namespace std;

void randomGenerator(unsigned int w, unsigned int h, unsigned int n){
    ofstream f("input.txt");
    if(!f.is_open()) return;
    srand(time(0));
    f<<n<<'\n';
    for(unsigned int i = 0; i < n; i++){
        unsigned int a = rand() % w + 1;
        unsigned int b = rand() % h + 1;
        f<<a<<' '<<b<<'\n';
    }

    f.close();

}

int main(){
    unsigned int w = 640;
    unsigned int h = 480;
    unsigned int n = 50;
    randomGenerator(w, h, n);
    return 0;
}
