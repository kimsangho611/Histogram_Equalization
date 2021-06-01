#include "Laplace.h"
using namespace std;

int main(void) {
	double uni_a, uni_b; // uniform distribution�� �ִ� �ּ� ���� �����ϱ� ���� ���� ����
	double u, b; // laplace ������ ���ϱ� ���� u, b�� int������ ����

	cout << "Uniform Distribution�� �ּڰ� a : ";
	cin >> uni_a; // uni_a �������� �Է� ����
	cout << "Uniform Distribution�� �ִ� b : ";
	cin >> uni_b; // uni_b ���� ���� �Է� ����

	while (uni_a < 0 || uni_a >= uni_b) { // uni_a ���� 0���� �۰ų� a < b�̸� �ٽ� �Է��� ����
		cout << "Uniform Distribution�� �ּڰ� a : ";
		cin >> uni_a; // uni_a �������� �Է� ����
		cout << "Uniform Distribution�� �ִ� b : ";
		cin >> uni_b; // uni_b ���� ���� �Է� ����
	}
	
	// ǥ�� ���� ����, uni_a, uni_b�� ���� Ŭ���� ��ü ����
	Laplace random_variable(400000, 1000, uni_a, uni_b);

	random_variable.Uniform_distribution(); // uniform distribution�� ������
	random_variable.print_uniform_dist("./uniform_distribution.csv"); // uniform distribution�� ���Ϸ� ����

	cout << "u���� �Է��� �ּ��� : ";
	cin >> u; // laplace distribution���� ��ȯ�� ��� �Է�
	cout << "b���� �Է��� �ּ��� : ";
	cin >> b; // laplace distribution���� ��ȯ�� ǥ������ �Է�

	random_variable.Transformation(u, b); // u, b���� ����� ���ö� ������ ��ȯ
	random_variable.print_laplace_dist("./laplace_distribution.csv"); // laplace distribution�� ���Ϸ� ����
	cout << "���ö� ������ ��ȯ�� �Ϸ� �Ǿ����ϴ�. ������ Ȯ�����ּ���." << endl << endl;
	random_variable.Verification(u, b); // ���ö� ������ �ٲ� ���� ����

	return 0; // 0�� ��ȯ��
}