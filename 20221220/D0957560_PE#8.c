#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

/* 定義圖形結構 */
struct Graph {
	struct Edge {
		int v;  //相臨的節點編號
		int w;  //邊的權重
		struct Edge* next;
	}* edges[MAX_NODES];
	int n;  //節點數
	int m;  //邊數
};

/* 定義節點結構 */
struct NodeInfo {
	int id;  // 節點編號
	int distance;  // 節點到起始節點的距離
};

/* 定義最小堆結構 */
struct MinHeap {
	struct NodeInfo nodes[MAX_NODES];  // 堆中的節點
	int size;  //堆的大小
};

/* 將節點加入最小堆中 */
void push(struct MinHeap* heap, struct NodeInfo node) {
	heap->nodes[heap->size] = node;  //將節點放在堆底
	int i = heap->size;
	int parent = (i - 1) / 2;
	while (i > 0 && heap->nodes[i].distance < heap->nodes[parent].distance) {
		/* 交換節點位置 */
		struct NodeInfo temp = heap->nodes[i];
		heap->nodes[i] = heap->nodes[parent];
		heap->nodes[parent] = temp;
		i = parent;
		parent = (i - 1) / 2;
	}
	heap->size++;
}

/* 從最小堆中取出最小值 */
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
			/* 交換節點位置 */
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
	/* 初始化最小堆和已知最短路徑的節點數組 */
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

	/* 循環直到最小堆為空，執行以下步驟 */
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

	/* 找到最短路徑最長的節點 */
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
	/* 輸入圖形的節點數和邊數 */
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

			/* 創建圖形 */
			struct Graph graph;
			graph.n = n;
			graph.m = m;
			int i;
			for (i = 0; i < n; i++) {
				graph.edges[i] = NULL;
			}

			/* 輸入邊的信息並加入圖形 */
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

			/* 輸出最大範圍內的節點數 */
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

