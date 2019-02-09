#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

double pi = 4.0*atan2(1.0, 1.0);

double aj(int j) {

	double ret = 0.0;
	if (j == 0)
		ret = 1.0 / pi;
	else
		ret = (1.0 / pi)*(abs(sin(j*(pi / 8.0))) / (j*(pi / 8.0)));
	return ret;
}

double funcn(int n, double theta)
{
	double ret = 0.0;
	for (int j = 1; j < n; j++)
	{
		ret += (aj(j) * cos(j*theta));
	}
	ret = ret + (aj(0) / 2.0);
	return ret;
}

double midpoint(double a, double b, double nmidpoint, double n) {
	double x0 = 0.0;
	double y0 = 0.0;
	double area = 0.0;
	double sum = 0.0;
	double h = (b - a) / nmidpoint;

	for (int i = 0; i < nmidpoint; i++) {
		x0 = ((double)i + 0.5) * h;
		y0 = funcn(n, x0*pi);
		sum += y0;
	}
	sum = sum * h;
	return sum;
}

int main()
{
	double n = pow(2, 11);
	double nmidpoint = 1000;

	double result = 0.0;
	result = midpoint(0.0, 0.2251, nmidpoint, n);
	cout << "Total area An: " << result << endl;
	system("PAUSE");
	return 0;
}
