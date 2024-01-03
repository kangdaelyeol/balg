#include <iostream>
#include <string>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	char buf[101] = {};
	while (true) {
		cin.getline(buf, 101);
		if (cin.eof()) {
			break;
		}
		cout << buf << endl;
	}
	return 0;
}