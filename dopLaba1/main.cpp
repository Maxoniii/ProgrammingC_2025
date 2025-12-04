#include <iostream>
#include <climits>
int main() {
	long long q1, p1, q2, p2, A;
	std::cout << "Input values of tracks and their prices: " << std::endl;
	std::cin >> q1 >> p1 >> q2 >> p2 >> A;
	if ((q1 <= 0) || (p1 <= 0) || (q2 <= 0) || (p2 <= 0)) {
		std::cout << "Values must be more than 0" << std::endl;
		return 1;
	}
	if ((q1 > 1000) || (p1 > 1000) || (q2 > 1000) || (p2 > 1000) || (A > 1000)) {
		std::cout << "Values must be less than 1000" << std::endl;
		return 1;
	}

	long long min_p = LLONG_MAX;
	long long max_tr1 = (A/q1)+1;

	
	for (long long tr1 = 0; tr1 <= max_tr1; tr1++) {
		long long ton1 = tr1 * q1;

		if (ton1 >= A) {
			long long p = tr1 * p1;
			if (p < min_p) {
				min_p = p;
			}
		}
		else {
			long long ost_ton = A - ton1;
			long long tr2 = ost_ton / q2;
			if (ost_ton % q2 != 0) {
				tr2++;
			}
			long long final_p = tr1 * p1 + tr2 * p2;
			if (final_p < min_p) {
				min_p = final_p;
			}
		}
	}

	std::cout << min_p << std::endl;
	return 0;
}
