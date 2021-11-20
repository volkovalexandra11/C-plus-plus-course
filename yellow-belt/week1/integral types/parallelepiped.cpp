#include <iostream>
#include <vector>

using namespace std;

uint64_t GetVolume(uint64_t width, uint64_t height, uint64_t depth) {
	return width * height * depth;
}

uint64_t GetMass(int width, int height, int depth, int density) {
	return GetVolume(width, height, depth) * density;
}

void SolveRectPar() {
	int n;
	uint64_t sum = 0, density;
	cin >> n >> density;
	for (int i = 0; i < n; i++) {
		int w, h, d;
		cin >> w >> h >> d;
		sum += GetVolume(w, h, d);
	}
	cout << sum * density;
}

int main2() {
	SolveRectPar();
	return 0;
}