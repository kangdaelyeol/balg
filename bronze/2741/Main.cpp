#include <iostream>
#include <string>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	char buf[7] = {};

	cin.getline(buf, 7);
	n = stoi(buf);

	for (int i = 1; i <= n; i++) {
		cout << i << '\n';
	}

	// string  사용 해서 std::getline 사용하는 경우
	/*
	    string s;
				getline(cin, s);
				n = stoi(s);
				for(int i = 1; i <= n; i++)
				cout << n << '\n';
	*/

	return 0;
}