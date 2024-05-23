#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

typedef struct customer_info {
    int use_time;
    int cost;
} customer_info;

typedef struct counter_info {
    int end_time;
    int number;
} counter_info;

struct compare {
    bool operator()(const counter_info& s1, const counter_info& s2) {
        if (s1.end_time == s2.end_time) {
            return s1.number > s2.number; // 번호가 작은 카운터를 다음 우선순위로
        }
        return s1.end_time > s2.end_time; // 종료 시간이 빠른 카운터를 첫번째 우선순위로
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int number_of_counter, number_of_customer;
    cin >> number_of_counter >> number_of_customer;

    vector<counter_info> counter_list(number_of_counter + 1);
    for (int counter = 1; counter <= number_of_counter; counter++) {
        counter_list[counter].number = counter;
    }
    vector<customer_info> customer_list(number_of_customer + 1);
    for (int customer = 1; customer <= number_of_customer; customer++) {
        cin >> customer_list[customer].use_time >> customer_list[customer].cost;
    }

    int total_time_answer = 0;
    vector<int> counter_profit_answer(number_of_counter + 1);

    priority_queue<counter_info, vector<counter_info>, compare> pq;
    for (int customer = 1; customer <= number_of_counter; customer++) { // 처음에는 카운터가 다 비기때문에 앞에서 카운터 숫자 만큼의 손님은 카운터에 있다
        counter_list[customer].end_time = customer_list[customer].use_time;
        pq.push(counter_list[customer]); // 우선 순위 큐에 들어갔다 = 손님이 카운터 쓰는 중이다 (현재 사람 있는 카운터가 우선순위 큐에 들어간다)

        counter_profit_answer[customer] = customer_list[customer].cost;
        total_time_answer = max(total_time_answer, counter_list[customer].end_time);
    }
    for (int customer = number_of_counter + 1; customer <= number_of_customer; customer++) { 
        // 대기하는 손님부터 마지막 손님까지의 처리
        int counter = pq.top().number; 
        pq.pop(); // 종료 시간이 빠른 카운터를 pop한다.
        counter_list[counter].end_time += customer_list[customer].use_time; // 새 손님이 카운터를 쓴 만큼 그 카운터의 종료 타임을 갱신한다.
        pq.push(counter_list[counter]);

        counter_profit_answer[counter] += customer_list[customer].cost; // 새 손님이 카운터에서 쓰고 간 돈을 그 카운터에서 계산한 돈에 더해 갱신한다
        total_time_answer = max(total_time_answer, counter_list[counter].end_time);
    }

    //모든 손님이 카운터 사용 완료
    cout << total_time_answer << "\n";
    for (int counter = 1; counter <= number_of_counter; counter++) {
        cout << counter_profit_answer[counter] << "\n";
    }

    return 0;
}
