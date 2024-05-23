#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {
	int problem_num = 0;
	cin >> problem_num;

	for (int problem = 0; problem < problem_num; problem++) {
		int resource_num = 0;
		cin >> resource_num;

		vector<int> A_benefit(resource_num);
		vector<int> B_benefit(resource_num);
		priority_queue <pair<int, int>> resource_sum;
		for (int res_type = 0; res_type < resource_num; res_type++) {
			cin >> A_benefit[res_type] >> B_benefit[res_type];
			resource_sum.push(make_pair(A_benefit[res_type] + B_benefit[res_type], res_type));
		}

		int A_benefit_sum = 0;
		int B_benefit_sum = 0;
		bool is_A_turn = true; //if this parameter is false, current turn is B's one.
		for (int res_type = 0; res_type < resource_num; res_type++) {
			if (is_A_turn) {
				A_benefit_sum += A_benefit[resource_sum.top().second];
			}
			else {
				B_benefit_sum += B_benefit[resource_sum.top().second];
			}
			resource_sum.pop();
			is_A_turn = !is_A_turn;
		}

		cout << A_benefit_sum - B_benefit_sum << "\n";
	}
}
