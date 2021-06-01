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
	int sample_size; // ǥ�� ��
	double interval; // ������ ����
	int segment; // �ش� ������ ��� ������ ����
	double num_min, num_max; // uniform distribution�� �ִ� �ּ� �� ���� ����
	std::vector<double> uniform_value; // uniform distribution�� ���� ������ vector ����
	std::map<double, double> lap; // laplace distribution�� �����ϱ� ���� map ����
	std::map<double, double> uni; // uniform distribution�� �����ϱ� ���� map ����
	std::vector<double> ks_test; // ���� ���� �����ϱ� ���� ����

public:
	Laplace(int sample, int seg, double min, double max) { // �����ڸ� ���� private ������ ���� ����
		sample_size = sample; segment = seg;
		num_min = min; num_max = max;
		interval = (max - min) / (double)seg;
	}
	~Laplace() {};

	void Uniform_distribution();
	double Laplace_CDF(double x, double u, double b); // ���ö� ������ CDF�� ����ϴ� �Լ�
	double T(double x, double u, double b); // uniform distribution�� laplace distribution���� ��ȯ�ϴ� �Լ�
	void Transformation(double u, double b); // ��� uniform distribution���� ��ȯ�ϴ� �Լ�
	void Verification(double u, double b); // ��ȯ ��� ���� �����ϴ� �Լ�

	void print_uniform_dist(const char* file_path); // uniform distribution�� �����ϴ� �Լ�
	void print_laplace_dist(const char* file_path); // ��ȯ �� laplace distribution�� �����ϴ� �Լ�
};

