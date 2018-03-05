#include <iostream>
using namespace std;

int main(){
#ifdef __cplusplus
	cout << "C++!" << endl;
#else
	cout << "C!" << endl;
#endif
}
