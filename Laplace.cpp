#include "Laplace.h"

void Laplace::Uniform_distribution()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<double> uniform_distributoin(num_min, num_max);

	for (int i = 0; i < sample_size; i++) {
		//srand(time(NULL));
		//double v = rand() / (double)RAND_MAX * num_max;
		double v = uniform_distributoin(gen); // uniform distribution 값 생성
		++uni[ceil(v * segment) / segment]; // 소수점 3자리에서 반올림하여 해당 값에 해당하는 인덱스에 저장
		uniform_value.push_back(v); // uniform distribution을 생성할 때 나온 random 값 
	}
}

double Laplace::Laplace_CDF(double x, double u, double b) {
	// Laplace Distribution CDF를 평균을 기준으로 절댓값을 벗겨 값을 반환
	if (x < u) { // 만일 x가 평균보다 작으면
		// 아래의 수식을 반환함
		return exp((x - u) / b) / 2; 
	}
	else { // 만일 x가 평균보다 크거나 같으면 
		// 아래의 수식을 반환함
		return 1 - exp((u - x) / b) / 2;
	}
}

double Laplace::T(double x, double u, double b) {
	double y;
	if (x < u) { // 해당 값이 평균보다 작으면 
		// 아래의 수식을 반환함
		y = u + b * log(2.0 * (x / (num_max - num_min)));
	}
	else { // x가 평균 보다 크거나 같으면 
		// 아래의 수식을 반환함
		y = u - b * log(2.0 - (2.0 * (x / (num_max - num_min))));
	}
	return y;
}

void Laplace::Transformation(double u, double b) {
	for (int i = 0; i < uniform_value.size(); i++) {
		double y = T(uniform_value[i], u, b); // 앞서 저장한 uniform distribution 값을 하나씩 꺼내면서 변환 함수로 변환 값 얻음
		++lap[ceil(y * segment) / segment]; // lap 변수에 값을 소수점 3자리에서 반올림하여 값을 저장함
	}
}

void Laplace::Verification(double u, double b) {
	std::ofstream ks;

	ks.open("./ks_test.csv"); // ks_test.csv 파일 열음

	double laplace_cdf = 0.0, real_cdf = 0.0;
	for (auto p = lap.begin(); p != lap.end(); p++) {
		real_cdf = Laplace_CDF(p->first, u, b); // 실제 라플라스 분포 CDF 값을 얻음
		laplace_cdf += p->second / sample_size; // lap변수에 저장된 값을 sample_size로 나눠 cdf를 구함
		ks << real_cdf << "," << laplace_cdf << std::endl; // 파일에 실제 값과 관측 cdf를 저장함
		ks_test.push_back(abs(laplace_cdf - real_cdf)); // 실제 cdf 값과 관측 cdf의 차의 절댓 값을 ks_test에 저장함
	}
	ks.close(); // 파일을 닫음

	double D = *max_element(ks_test.begin(), ks_test.end()); // ks_test 변수에 저정된 값중 가장 큰 값을 얻음

	std::cout << "전체 표본 수 : " << sample_size << "개" << std::endl << std::endl;
	std::cout << "귀무가설 : 변환 후 분포가 라플라스 분포를 따른다." << std::endl;
	std::cout << "대립가설 : 변환 후 분포가 라플라스 분포를 따르지 않는다." << std::endl << std::endl;

	std::cout << "K-S test 검정 통계량 D : " << D << std::endl;
	std::cout << "기각역은 D > d(a, n) = " << 1.07 / sqrt(lap.size()) << std::endl;
	if (D <= 1.07 / sqrt(lap.size())) { // 만일 alpha = 0.1의 유의 수준에서 기각역의 범위에 들지 않으면
		// 아래와 같이 출력함
		std::cout << "따라서 귀무가설은 신뢰도 " << 100 * (1 - 0.1) << "% 에서 기각되지 않는다." << std::endl;
	}
	else { // 만일 alpha = 0.1의 유의 수준에서 기각역의 범위에 들면
		// 아래의 값을 출력함
		std::cout << "따라서 귀무가설은 기각된다." << std::endl;
	}
}

void Laplace::print_uniform_dist(const char* file_path) {
	std::ofstream uniform;

	if (uniform_value.empty()) { // uniform distribution이 없으면 파일에 저장하지 않고 return
		std::cout << "Uniform Distribution에 대한 데이터가 없습니다." << std::endl;
		return;
	}

	uniform.open(file_path); // file_path에 해당하는 위치에 파일을 open
	double sum = 0;
	int count = 1; // 개수를 
	for (auto p = uni.begin(); p != uni.end(); p++) {
		if (count == (int)(num_max - num_min)) { // 만일 count가 uniform distribution의 x범위의 크기와 동일하면 
			// 파일에 해당 값과 해당 값의 개수의 비율을 저장
			uniform << p->first << "," << (p->second + sum) / (sample_size * interval) << std::endl;
			count = 1; sum = 0; // count에 1을 할당하고 sum에 0을 할당한다.
		}
		else {
			count += 1; // count를 1증가함
			sum += p->second; // sum에 현재 위치 값의 개수를 저장
		}
	}
	uniform.close(); // 파일을 닫음
}

void Laplace::print_laplace_dist(const char* file_path) {
	std::ofstream laplace;

	if (lap.empty()) { // lap 변수에 값이 없으면 
		std::cout << "라플라스 분포로 변환되지 않았습니다." << std::endl;
		return; // 아무것도 안하고 반환함
	}
	laplace.open(file_path); // file_path에 해당하는 파일위치에 파일을 열음
	for (auto p = lap.begin(); p != lap.end(); p++) {
		// lap의 변수에 값과 그 값이 전체 갯수에 해당하는 비율로 파일에 저장
		laplace << p->first << "," << p->second / (sample_size * interval) << std::endl;
	}
	laplace.close(); // 파일을 닫음
}
