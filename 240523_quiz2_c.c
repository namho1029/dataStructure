#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct {
    int benefit;
    int res_type;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// ���� �Լ�
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}
// �ʱ�ȭ �Լ�
void init(HeapType* h) {
    h->heap_size = 0;
}
// ���� ����� ������ heap_size�� �� h�� item�� �����Ѵ�.
void push_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size);

    //  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
    while ((i != 1) && (item.benefit <= h->heap[i / 2].benefit)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;   // ���ο� ��带 ����
}
// ���� �Լ�
element pop_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        // ���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 ã�´�.
        if ((child < h->heap_size) &&
            (h->heap[child].benefit) >= h->heap[child + 1].benefit)
            child++;
        if (temp.benefit < h->heap[child].benefit) break;
        // �� �ܰ� �Ʒ��� �̵�
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

int main() {
    int problem_num = 0;
    scanf("%d", &problem_num);

    for (int problem = 0; problem < problem_num; problem++) {
        int resource_num = 0;
        scanf("%d", &resource_num);

        HeapType* h = create();
        init(h);

        int* A_benefit = (int*)malloc(resource_num * sizeof(int));
        int* B_benefit = (int*)malloc(resource_num * sizeof(int));

        for (int res_type = 0; res_type < resource_num; res_type++) {
            int benefit1, benefit2;
            scanf("%d %d", &benefit1, &benefit2);
            A_benefit[res_type] = benefit1;
            B_benefit[res_type] = benefit2;
            push_min_heap(h, { (benefit1 + benefit2), res_type });
        }

        int A_benefit_sum = 0;
        int B_benefit_sum = 0;
        int is_A_turn = 1; // A�� �������� ���θ� ��Ÿ���� ����. 1�̸� A�� ����, 0�̸� B�� ����.

        // ��ҵ��� �����ư��� �����ϸ� ������ ���
        for (int res_type = 0; res_type < resource_num; res_type++) {
            element item = pop_min_heap(h);
            if (is_A_turn) {
                A_benefit_sum += A_benefit[item.res_type];
            }
            else {
                B_benefit_sum += B_benefit[item.res_type];
            }
            is_A_turn = !is_A_turn;
        }

        printf("%d\n", A_benefit_sum - B_benefit_sum);
        free(h);
    }

    return 0;
}
