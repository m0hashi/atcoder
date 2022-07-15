using namespace std;
int main(){
    auto f = [](auto& a, auto b){if (a<b) a=b; return a<b};
    return 0;
}

