#pragma once
#include<iostream>
#include<random>
#include<fstream>
#include<vector>
#include<cmath>
#include<string>
#include<algorithm>
#include<map>
#include<time.h>

class Laplace
{
private:
	int sample_size; // 표본 수
	double interval; // 저장할 간격
	int segment; // 해당 범위를 몇개로 나눌지 선언
	double num_min, num_max; // uniform distribution의 최대 최소 값 저장 변수
	std::vector<double> uniform_value; // uniform distribution의 값을 저장할 vector 변수
	std::map<double, double> lap; // laplace distribution을 저장하기 위한 map 변수
	std::map<double, double> uni; // uniform distribution을 저장하기 위한 map 변수
	std::vector<double> ks_test; // 검증 값을 저장하기 위한 변수

public:
	Laplace(int sample, int seg, double min, double max) { // 생성자를 통해 private 변수에 값을 저장
		sample_size = sample; segment = seg;
		num_min = min; num_max = max;
		interval = (max - min) / (double)seg;
	}
	~Laplace() {};

	void Uniform_distribution();
	double Laplace_CDF(double x, double u, double b); // 라플라스 분포의 CDF를 계산하는 함수
	double T(double x, double u, double b); // uniform distribution을 laplace distribution으로 변환하는 함수
	void Transformation(double u, double b); // 모든 uniform distribution값을 변환하는 함수
	void Verification(double u, double b); // 변환 결과 값을 검증하는 함수

	void print_uniform_dist(const char* file_path); // uniform distribution을 저장하는 함수
	void print_laplace_dist(const char* file_path); // 변환 후 laplace distribution을 저장하는 함수
};

