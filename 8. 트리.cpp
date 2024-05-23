#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 50000
#define MAX_LENGTH 100

typedef int TreeNode;
TreeNode tree[MAX_NODES + 1];

int num_of_tests;
int num_of_directories;
int num_of_conns;

int path_length[MAX_NODES + 1];

void traversal(int node) {
	int parent_node = node / 2;
	if (parent_node != 0) {
		path_length[node] += (path_length[parent_node] + 1);
	}
	for (int pos = 2 * node; pos <= 2 * node + 1 && pos <= num_of_directories; pos++) {
		traversal(pos);
	}
}

int main() {
	scanf("%d", &num_of_tests);
	for (int test = 0; test < num_of_tests; test++) {
		scanf("%d", &num_of_directories);
		num_of_conns = num_of_directories - 1;

		for (int dir = 1; dir <= num_of_directories; dir++) {
			tree[dir] = 0;
			path_length[dir] = 0;
		}
		for (int dir = 1; dir <= num_of_directories; dir++) {
			char dir_name[MAX_LENGTH];
			scanf("%s", dir_name);
			path_length[dir] = strlen(dir_name);
		}
		traversal(1);
		for (int dir = 1; dir <= num_of_directories; dir++) {
			printf("%d\n", path_length[dir]);
		}
	}
	return 0;
}
