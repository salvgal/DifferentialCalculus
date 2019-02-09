#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <complex>
using namespace std;

const double pi = 4.0 * atan2(1.0, 1.0);

int Tridiagonal_solve(const int n, const std::vector<double>& a,
	const std::vector<double>& b,
	const std::vector<double>& c,
	const std::vector<double>& rhs, std::vector<double>& x)
{
	const double tol = 1.0e-14;
	x.clear();
	if ((n < 1) || (a.size() < n) || (b.size() < n) || (c.size() < n) || (rhs.size() < n))
		return 1; // fail
NOTE: Not used double alpha[n]; because the Visual studio compiler does not accept it.
	if n changes, needs to be changed below, ore use another compiler to pass n at run time.
		double alpha[20000]; // temporary storage
	  x.reserve(n);
	  std::fill(x.begin(), x.end(), 0.0);

	  int i = 0;
	  double gamma = a[i];
	  if (fabs(gamma) <= tol)
		  return 1; // fail
	  x[i] = rhs[i] / gamma;
	  alpha[i] = c[i] / gamma;

	  for (i = 1; i < n - 1; ++i) {
		  gamma = a[i] - b[i] * alpha[i - 1];
		  if (fabs(gamma) <= tol)
			  return 1; // fail
		  x[i] = (rhs[i] - b[i] * x[i - 1]) / gamma;
		  alpha[i] = c[i] / gamma;
	  }

	  i = n - 1;
	  gamma = a[i] - b[i] * alpha[i - 1];
	  if (fabs(gamma) <= tol)
		  return 1; // fail
	  x[i] = (rhs[i] - b[i] * x[i - 1]) / gamma;

	  for (i = n - 2; i >= 0; --i) {
		  x[i] -= alpha[i] * x[i + 1];
	  }
	  return 0;
}

void test()
{
	const int n = 20000;
	const int size = n + 1;
	std::vector<double> a(size, 0.0);
	std::vector<double> b(size, 0.0);
	std::vector<double> c(size, 0.0);
	std::vector<double> r(size, 0.0);
	std::vector<double> y(size, 0.0);
	double xmin = 0;
	double xmax = 20;
	double h = (xmax - xmin) / double(n);
	double nu = 1.5;
	for (int i = 1; i <= n - 1; ++i) {
		double x_i = i * h;
		a[i] = -2.0 * x_i * x_i + h * h * (x_i * x_i - nu * nu);
		b[i] = x_i * x_i - 0.5 * h * x_i;
		c[i] = x_i * x_i + 0.5 * h * x_i;
	}
	a[0] = 1.0;
	a[n] = 1.0;
	r[0] = 0.0;
	r[n] = -0.064663;
	int rc = Tridiagonal_solve(n + 1, a, b, c, r, y);
	for (int i = 1; i < n; ++i) {
		double x_i = i * h;
		if (y[i] * y[i + 1] <= 0.0) {
			std::cout << std::setw(16) << x_i + 0.5 * h << " ";
			std::cout << std::setw(16) << y[i] << " ";
			std::cout << std::setw(16) << y[i + 1] << " ";
			std::cout << std::endl;
		}
	}
}

int main() {
	test();
	system("PAUSE");
	return 0;
}