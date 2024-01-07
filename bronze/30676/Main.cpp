#include <iostream>
#include <string>

using namespace std;

int main() {
	int spectrum;
	cin >> spectrum;
	string s;
	if (spectrum <= 780) {
		if (spectrum >= 620)
			s = "Red";
		else if (spectrum >= 590)
			s = "Orange";
		else if (spectrum >= 570)
			s = "Yellow";
		else if (spectrum >= 495)
			s = "Green";
		else if (spectrum >= 450)
			s = "Blue";
		else if (spectrum >= 425)
			s = "Indigo";
		else if (spectrum >= 380)
			s = "Violet";
	}

	cout << s << endl;
	return 0;
}
