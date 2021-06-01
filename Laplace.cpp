#include "Laplace.h"

void Laplace::Uniform_distribution()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<double> uniform_distributoin(num_min, num_max);

	for (int i = 0; i < sample_size; i++) {
		//srand(time(NULL));
		//double v = rand() / (double)RAND_MAX * num_max;
		double v = uniform_distributoin(gen); // uniform distribution �� ����
		++uni[ceil(v * segment) / segment]; // �Ҽ��� 3�ڸ����� �ݿø��Ͽ� �ش� ���� �ش��ϴ� �ε����� ����
		uniform_value.push_back(v); // uniform distribution�� ������ �� ���� random �� 
	}
}

double Laplace::Laplace_CDF(double x, double u, double b) {
	// Laplace Distribution CDF�� ����� �������� ������ ���� ���� ��ȯ
	if (x < u) { // ���� x�� ��պ��� ������
		// �Ʒ��� ������ ��ȯ��
		return exp((x - u) / b) / 2; 
	}
	else { // ���� x�� ��պ��� ũ�ų� ������ 
		// �Ʒ��� ������ ��ȯ��
		return 1 - exp((u - x) / b) / 2;
	}
}

double Laplace::T(double x, double u, double b) {
	double y;
	if (x < u) { // �ش� ���� ��պ��� ������ 
		// �Ʒ��� ������ ��ȯ��
		y = u + b * log(2.0 * (x / (num_max - num_min)));
	}
	else { // x�� ��� ���� ũ�ų� ������ 
		// �Ʒ��� ������ ��ȯ��
		y = u - b * log(2.0 - (2.0 * (x / (num_max - num_min))));
	}
	return y;
}

void Laplace::Transformation(double u, double b) {
	for (int i = 0; i < uniform_value.size(); i++) {
		double y = T(uniform_value[i], u, b); // �ռ� ������ uniform distribution ���� �ϳ��� �����鼭 ��ȯ �Լ��� ��ȯ �� ����
		++lap[ceil(y * segment) / segment]; // lap ������ ���� �Ҽ��� 3�ڸ����� �ݿø��Ͽ� ���� ������
	}
}

void Laplace::Verification(double u, double b) {
	std::ofstream ks;

	ks.open("./ks_test.csv"); // ks_test.csv ���� ����

	double laplace_cdf = 0.0, real_cdf = 0.0;
	for (auto p = lap.begin(); p != lap.end(); p++) {
		real_cdf = Laplace_CDF(p->first, u, b); // ���� ���ö� ���� CDF ���� ����
		laplace_cdf += p->second / sample_size; // lap������ ����� ���� sample_size�� ���� cdf�� ����
		ks << real_cdf << "," << laplace_cdf << std::endl; // ���Ͽ� ���� ���� ���� cdf�� ������
		ks_test.push_back(abs(laplace_cdf - real_cdf)); // ���� cdf ���� ���� cdf�� ���� ���� ���� ks_test�� ������
	}
	ks.close(); // ������ ����

	double D = *max_element(ks_test.begin(), ks_test.end()); // ks_test ������ ������ ���� ���� ū ���� ����

	std::cout << "��ü ǥ�� �� : " << sample_size << "��" << std::endl << std::endl;
	std::cout << "�͹����� : ��ȯ �� ������ ���ö� ������ ������." << std::endl;
	std::cout << "�븳���� : ��ȯ �� ������ ���ö� ������ ������ �ʴ´�." << std::endl << std::endl;

	std::cout << "K-S test ���� ��跮 D : " << D << std::endl;
	std::cout << "�Ⱒ���� D > d(a, n) = " << 1.07 / sqrt(lap.size()) << std::endl;
	if (D <= 1.07 / sqrt(lap.size())) { // ���� alpha = 0.1�� ���� ���ؿ��� �Ⱒ���� ������ ���� ������
		// �Ʒ��� ���� �����
		std::cout << "���� �͹������� �ŷڵ� " << 100 * (1 - 0.1) << "% ���� �Ⱒ���� �ʴ´�." << std::endl;
	}
	else { // ���� alpha = 0.1�� ���� ���ؿ��� �Ⱒ���� ������ ���
		// �Ʒ��� ���� �����
		std::cout << "���� �͹������� �Ⱒ�ȴ�." << std::endl;
	}
}

void Laplace::print_uniform_dist(const char* file_path) {
	std::ofstream uniform;

	if (uniform_value.empty()) { // uniform distribution�� ������ ���Ͽ� �������� �ʰ� return
		std::cout << "Uniform Distribution�� ���� �����Ͱ� �����ϴ�." << std::endl;
		return;
	}

	uniform.open(file_path); // file_path�� �ش��ϴ� ��ġ�� ������ open
	double sum = 0;
	int count = 1; // ������ 
	for (auto p = uni.begin(); p != uni.end(); p++) {
		if (count == (int)(num_max - num_min)) { // ���� count�� uniform distribution�� x������ ũ��� �����ϸ� 
			// ���Ͽ� �ش� ���� �ش� ���� ������ ������ ����
			uniform << p->first << "," << (p->second + sum) / (sample_size * interval) << std::endl;
			count = 1; sum = 0; // count�� 1�� �Ҵ��ϰ� sum�� 0�� �Ҵ��Ѵ�.
		}
		else {
			count += 1; // count�� 1������
			sum += p->second; // sum�� ���� ��ġ ���� ������ ����
		}
	}
	uniform.close(); // ������ ����
}

void Laplace::print_laplace_dist(const char* file_path) {
	std::ofstream laplace;

	if (lap.empty()) { // lap ������ ���� ������ 
		std::cout << "���ö� ������ ��ȯ���� �ʾҽ��ϴ�." << std::endl;
		return; // �ƹ��͵� ���ϰ� ��ȯ��
	}
	laplace.open(file_path); // file_path�� �ش��ϴ� ������ġ�� ������ ����
	for (auto p = lap.begin(); p != lap.end(); p++) {
		// lap�� ������ ���� �� ���� ��ü ������ �ش��ϴ� ������ ���Ͽ� ����
		laplace << p->first << "," << p->second / (sample_size * interval) << std::endl;
	}
	laplace.close(); // ������ ����
}
