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
            return s1.number > s2.number; // ��ȣ�� ���� ī���͸� ���� �켱������
        }
        return s1.end_time > s2.end_time; // ���� �ð��� ���� ī���͸� ù��° �켱������
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
    for (int customer = 1; customer <= number_of_counter; customer++) { // ó������ ī���Ͱ� �� ��⶧���� �տ��� ī���� ���� ��ŭ�� �մ��� ī���Ϳ� �ִ�
        counter_list[customer].end_time = customer_list[customer].use_time;
        pq.push(counter_list[customer]); // �켱 ���� ť�� ���� = �մ��� ī���� ���� ���̴� (���� ��� �ִ� ī���Ͱ� �켱���� ť�� ����)

        counter_profit_answer[customer] = customer_list[customer].cost;
        total_time_answer = max(total_time_answer, counter_list[customer].end_time);
    }
    for (int customer = number_of_counter + 1; customer <= number_of_customer; customer++) { 
        // ����ϴ� �մԺ��� ������ �մԱ����� ó��
        int counter = pq.top().number; 
        pq.pop(); // ���� �ð��� ���� ī���͸� pop�Ѵ�.
        counter_list[counter].end_time += customer_list[customer].use_time; // �� �մ��� ī���͸� �� ��ŭ �� ī������ ���� Ÿ���� �����Ѵ�.
        pq.push(counter_list[counter]);

        counter_profit_answer[counter] += customer_list[customer].cost; // �� �մ��� ī���Ϳ��� ���� �� ���� �� ī���Ϳ��� ����� ���� ���� �����Ѵ�
        total_time_answer = max(total_time_answer, counter_list[counter].end_time);
    }

    //��� �մ��� ī���� ��� �Ϸ�
    cout << total_time_answer << "\n";
    for (int counter = 1; counter <= number_of_counter; counter++) {
        cout << counter_profit_answer[counter] << "\n";
    }

    return 0;
}
