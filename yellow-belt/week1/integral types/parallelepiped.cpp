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

int main() {
//	SolveAvgTemperature();
	SolveRectPar();
//	cout << std::boolalpha;
//	cout << numeric_limits<double>::max() << endl;
//	cout << (pow(10,19) > static_cast<double>(numeric_limits<uint64_t>::max()));
}