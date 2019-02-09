#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

double pi = 4.0*atan2(1.0, 1.0);
double p = 1.0 / 6.0;
double s = 5.0 / 4.0;

double func_x(double t)
{
	double ret = 0.0;
	ret = ((1 - s * p)*cos(t)) + (s*p*cos(((1 - p) / p)*t));
	return ret;
}

double func_y(double t)
{
	double ret = 0.0;
	ret = ((1 - s * p)*sin(t)) - (s*p*sin(((1 - p) / p)*t));
	return ret;
}

int root_bisection(double target, double tol_f, double tol_x, int max_iter,
	double x_low, double x_high, double & x, long & num_iter)
{

	double y_low = func_y(x_low);
	double diff_y_low = y_low - target;

	if (abs(diff_y_low) <= tol_f)
	{
		x = x_low;
		return 0;
	}

	double y_high = func_y(x_high);
	double diff_y_high = y_high - target;

	if (abs(diff_y_high) <= tol_f)
	{
		x = x_high;
		return 0;
	}

	for (num_iter = 1; num_iter < max_iter; ++num_iter)
	{
		x = (x_low + x_high) / 2.0;
		double y = func_y(x);
		cout << "x" << x << " f(xi): " << y << endl;
		double diff_y = y - target;
		if (abs(diff_y) > pow(10, 6))
		{
			cout << "fx>10^6" << endl;
			return 0;
		}
		if (abs(diff_y) <= tol_f)
		{
			return 0;
		}

		if (diff_y * diff_y_low > 0.0)
		{
			x_low = x;
		}
		else
		{
			x_high = x;
		}

		if (abs(x_high - x_low) <= tol_x)
		{
			cout << "converged in x" << endl;
			return 0;
		}

	}
	cout << func_y(x) << endl;
	x = 0;
	num_iter = max_iter;
	return 1;

}


int main(int argc, const char * argv[])
{


	double target = 0.0;
	int max_iter = 100;
	double tol_f = 1.0e-4;
	double tol_x = 1.0e-4;
	double x_low = 0.01;
	double x_high = 0.3;
	double x = 0;
	long num_iter = 0;
	int test = 0;
	test = root_bisection(target, tol_f, tol_x, max_iter, x_low, x_high, x, num_iter);
	cout << x << endl;

	system("pause");
	return  0;
}