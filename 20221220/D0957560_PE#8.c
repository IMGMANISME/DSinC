#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

/* �w�q�ϧε��c */
struct Graph {
	struct Edge {
		int v;  //���{���`�I�s��
		int w;  //�䪺�v��
		struct Edge* next;
	}* edges[MAX_NODES];
	int n;  //�`�I��
	int m;  //���
};

/* �w�q�`�I���c */
struct NodeInfo {
	int id;  // �`�I�s��
	int distance;  // �`�I��_�l�`�I���Z��
};

/* �w�q�̤p�ﵲ�c */
struct MinHeap {
	struct NodeInfo nodes[MAX_NODES];  // �襤���`�I
	int size;  //�諸�j�p
};

/* �N�`�I�[�J�̤p�襤 */
void push(struct MinHeap* heap, struct NodeInfo node) {
	heap->nodes[heap->size] = node;  //�N�`�I��b�侀
	int i = heap->size;
	int parent = (i - 1) / 2;
	while (i > 0 && heap->nodes[i].distance < heap->nodes[parent].distance) {
		/* �洫�`�I��m */
		struct NodeInfo temp = heap->nodes[i];
		heap->nodes[i] = heap->nodes[parent];
		heap->nodes[parent] = temp;
		i = parent;
		parent = (i - 1) / 2;
	}
	heap->size++;
}

/* �q�̤p�襤���X�̤p�� */
struct NodeInfo pop(struct MinHeap* heap) {
	struct NodeInfo min = heap->nodes[0];
	heap->nodes[0] = heap->nodes[heap->size - 1];
	heap->size--;
	int i = 0;
	while (true) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int smallest = i;
		if (left < heap->size && heap->nodes[left].distance < heap->nodes[smallest].distance) {
			smallest = left;
		}
		if (right < heap->size && heap->nodes[right].distance < heap->nodes[smallest].distance) {
			smallest = right;
		}
		if (smallest != i) {
			/* �洫�`�I��m */
			struct NodeInfo temp = heap->nodes[i];
			heap->nodes[i] = heap->nodes[smallest];
			heap->nodes[smallest] = temp;
			i = smallest;
		} else {
			break;
		}
	}
	return min;
}

/* Dijkstra */
int dijkstra(struct Graph* graph, int source, int* distances) {
	/* ��l�Ƴ̤p��M�w���̵u���|���`�I�Ʋ� */
	struct MinHeap heap;
	int i;
	heap.size = 0;
	bool known[MAX_NODES];
	for (i = 0; i < graph->n; i++) {
		distances[i] = -1;
		known[i] = false;
	}
	distances[source] = 0;
	push(&heap, (struct NodeInfo) {
		source, 0
	});

	/* �`������̤p�אּ�šA����H�U�B�J */
	while (heap.size > 0) {
		struct NodeInfo min = pop(&heap);
		int u = min.id;
		known[u] = true;
		struct Edge* e;
		for (e = graph->edges[u]; e != NULL; e = e->next) {
			int v = e->v;
			if (!known[v]) {
				int distance = distances[u] + e->w;
				if (distances[v] == -1 || distance < distances[v]) {
					distances[v] = distance;
					push(&heap, (struct NodeInfo) {
						v, distance
					});
				}
			}
		}
	}

	/* ���̵u���|�̪����`�I */
	int max_distance = 0;
	int max_distance_node = -1;
	for (i = 0; i < graph->n; i++) {
		if (distances[i] > max_distance) {
			max_distance = distances[i];
			max_distance_node = i;
		}
	}

	return max_distance_node;
}

int main() {
	/* ��J�ϧΪ��`�I�ƩM��� */
	while(1) {
		int test;
		scanf("%d",&test);
		if(test == 0) {
			break;
		}
		int i;
		for(i = 0; i < test; i++) {
			int n, m;
			scanf("%d%d", &n, &m);

			/* �Ыعϧ� */
			struct Graph graph;
			graph.n = n;
			graph.m = m;
			int i;
			for (i = 0; i < n; i++) {
				graph.edges[i] = NULL;
			}

			/* ��J�䪺�H���å[�J�ϧ� */
			for (i = 0; i < m; i++) {
				int u, v, w;
				scanf("%d%d%d", &u, &v, &w);
				struct Edge* edge = (struct Edge*)malloc(sizeof(struct Edge));
				edge->v = v;
				edge->w = w;
				edge->next = graph.edges[u];
				graph.edges[u] = edge;
			}

			/* Dijkstra */
			int distances[MAX_NODES];
			int max_distance_node = dijkstra(&graph, 0, distances);

			/* ��X�̤j�d�򤺪��`�I�� */
			int count = 0;
			for (i = 0; i < n; i++) {
				if (distances[i] <= distances[max_distance_node]) {
					count++;
				}
			}
			printf("%d\n", count - 1);
		}
	}
	return 0;
}

