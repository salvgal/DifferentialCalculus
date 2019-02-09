#include <iostream>
#include <vector>
using namespace std;

const double pi = 4.0 * atan2(1.0, 1.0);

int func(int n, double x, const std::vector<double>& y, std::vector<double>& g) {
	if (n <= 0)
		return 1;
	g[0] = y[1];
	g[1] = -y[0] + cos(x) / pi;
	return 0;
}

int RK4(int n, double x, double h, std::vector<double>& y_in, std::vector<double>& y_out) {
	int i = 0;
	int rc = 0;
	y_out = y_in;
	if ((n < 1) || (y_in.size() < n) || (y_out.size() < n))
		return 1;

	std::vector<double> g1(n, 0.0);
	std::vector<double> g2(n, 0.0);
	std::vector<double> g3(n, 0.0);
	std::vector<double> g4(n, 0.0);
	std::vector<double> y_tmp(n, 0.0);

	rc = func(n, x, y_in, g1);
	if (rc)
		return rc;

	for (i = 0; i < n; i++) {
		y_tmp[i] = y_in[i] + 0.5 * h * g1[i];
	}

	rc = func(n, x + 0.5 * h, y_tmp, g2);
	if (rc)
		return rc;
	for (i = 0; i < n; i++) {
		y_tmp[i] = y_in[i] + 0.5 * h * g2[i];
	}

	rc = func(n, x + 0.5 * h, y_tmp, g3);
	if (rc)
		return rc;
	for (i = 0; i < n; i++) {
		y_tmp[i] = y_in[i] + h * g3[i];
	}
	rc = func(n, x + h, y_tmp, g4);
	if (rc)
		return rc;

	for (i = 0; i < n; i++) {
		y_out[i] = y_in[i] + (h / 6.0) * (g1[i] + 2.0 * g2[i] + 2.0 * g3[i] + g4[i]);
	}
	return 0;
}
void test() {

	std::vector<double> y_in(2, 0.0);
	std::vector<double> y_out(2, 0.0);
	
	y_in[0] = 0;
	y_in[1] = 0;

	int n = 34;
	int i = 0;
	double x = 0;
	double x0 = 0.0;
	double h = 2.5 * pi / n;

	for (i = 0; i < n; ++i) {
		x = x0 + i * h;
		RK4(2, x, h, y_in, y_out);
		y_in = y_out;
	}
	cout << "Value of n: " << n << endl;
	cout << "forward integrate: " << y_out[0] << endl;
	cout << "absolute difference: " << abs(y_out[0] - (5.0/4.0)) << endl;
	
	h = -h;
	for (i = 0; i < n; ++i) {
		x = 2.5 * pi + i * h;
		RK4(2, x, h, y_in, y_out);
		y_in = y_out;
	}
	cout << "backward integrate: " << y_out[0] << endl;
}
int main() {
	test();
	system("PAUSE");
	return 0;