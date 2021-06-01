#include "Laplace.h"
using namespace std;

int main(void) {
	double uni_a, uni_b; // uniform distribution의 최대 최소 값을 저장하기 위한 변수 선언
	double u, b; // laplace 분포를 구하기 위한 u, b를 int형으로 선언

	cout << "Uniform Distribution의 최솟값 a : ";
	cin >> uni_a; // uni_a 변수값을 입력 받음
	cout << "Uniform Distribution의 최댓값 b : ";
	cin >> uni_b; // uni_b 변수 값을 입력 받음

	while (uni_a < 0 || uni_a >= uni_b) { // uni_a 값이 0보다 작거나 a < b이면 다시 입력을 받음
		cout << "Uniform Distribution의 최솟값 a : ";
		cin >> uni_a; // uni_a 변수값을 입력 받음
		cout << "Uniform Distribution의 최댓값 b : ";
		cin >> uni_b; // uni_b 변수 값을 입력 받음
	}
	
	// 표본 수와 단위, uni_a, uni_b를 통해 클래스 객체 선언
	Laplace random_variable(400000, 1000, uni_a, uni_b);

	random_variable.Uniform_distribution(); // uniform distribution을 생성함
	random_variable.print_uniform_dist("./uniform_distribution.csv"); // uniform distribution을 파일로 저장

	cout << "u값을 입력해 주세요 : ";
	cin >> u; // laplace distribution으로 변환할 평균 입력
	cout << "b값을 입력해 주세요 : ";
	cin >> b; // laplace distribution으로 변환할 표준편차 입력

	random_variable.Transformation(u, b); // u, b값을 사용해 라플라스 분포로 변환
	random_variable.print_laplace_dist("./laplace_distribution.csv"); // laplace distribution을 파일로 저장
	cout << "라플라스 분포로 변환이 완료 되었습니다. 파일을 확인해주세요." << endl << endl;
	random_variable.Verification(u, b); // 라플라스 분포로 바꾼 값을 검증

	return 0; // 0을 반환함
}