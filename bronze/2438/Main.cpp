#include <iostream>
#include <string>

using namespace std;

int main() {
	int a;
	cin >> a;
	string s;
	for (int i = 0; i < a; i++) {
		s += "*";
		cout << s << endl;
	}
	return 0;
}