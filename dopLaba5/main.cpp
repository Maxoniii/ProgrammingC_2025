#include <iostream>
#include <cmath>


int main() {
	int x1, y1, r1, x2, y2, r2;
	std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

	const double p = 3.14159265358979323846;

	double sq1 = p * r1 * r1;
	double sq2 = p * r2 * r2;

	double dx = x2 - x1;
	double dy = y2 - y1;
	double rast = sqrt(dx * dx + dy * dy);
	double peresech = 0.0;

	if (rast >= r1 + r2) {
		peresech = 0.0;
	}
	else {
		double raz_rad;
		if (r1 > r2) {
			raz_rad = r1 - r2;
		}
		else {
			raz_rad = r2 - r1;
		}
		if (rast <= raz_rad) {
			double mensh_rad;
			if (r1 < r2) {
				mensh_rad = r1;
			}
			else {
				mensh_rad = r2;
			}
			peresech = p * mensh_rad * mensh_rad;
		}
		else {
			double cos_a = (r1 * r1 + rast * rast - r2 * r2) / (2 * r1 * rast);
			double cos_b = (r2 * r2 + rast * rast - r1 * r1) / (2 * r2 * rast);

			double a = acos(cos_a);
			double b = acos(cos_b);
			double seg1 = r1 * r1 * a - r1 * r1 * sin(a) * cos_a;
			double seg2 = r2 * r2 * b - r2 * r2 * sin(b) * cos_b;

			peresech = seg1 + seg2;

		}
	}

	double final_sq = sq1 + sq2 - peresech;
	long long okrug_sq = (long long)(final_sq * 1000 + 0.5);

	long long cel = okrug_sq / 1000;
	long long drob = okrug_sq % 1000;
	std::cout << cel << ".";

	if (drob < 10) {
		std::cout << "00" << okrug_sq << std::endl;
	}
	else if (drob < 100) {
		std::cout << "0" << drob << std::endl;
	}
	else {
		std::cout << drob << std::endl;
	}
	return 0;
}