#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX
#define MAX_N 1000

struct Edge {
	int u;
	int v;
	int w;
};

struct Graph {
	int n;
	int m;
	struct Edge edges[MAX_N];
};

struct HeapNode {
	int v;
	int dist;
};

struct Heap {
	int size;
	int capacity;
	int *pos;
	struct HeapNode **nodes;
};

struct Graph *create_graph(int n, int m) {
	struct Graph *graph = malloc(sizeof(struct Graph));
	graph->n = n;
	graph->m = m;
	return graph;
}

void add_edge(struct Graph *graph, int u, int v, int w) {
	graph->edges[graph->m].u = u;
	graph->edges[graph->m].v = v;
	graph->edges[graph->m].w = w;
	graph->m++;
}

struct HeapNode *create_heap_node(int v, int dist) {
	struct HeapNode *node = malloc(sizeof(struct HeapNode));
	node->v = v;
	node->dist = dist;
	return node;
}

struct Heap *create_heap(int capacity) {
	struct Heap *heap = malloc(sizeof(struct Heap));
	heap->pos = malloc(capacity * sizeof(int));
	heap->size = 0;
	heap->capacity = capacity;
	heap->nodes = malloc(capacity * sizeof(struct HeapNode*));
	return heap;
}

void swap_heap_node(struct HeapNode **a, struct HeapNode **b) {
	struct HeapNode *temp = *a;
	*a = *b;
	*b = temp;
}

void min_heapify(struct Heap *heap, int idx) {
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < heap->size && heap->nodes[left]->dist < heap->nodes[smallest]->dist)
		smallest = left;

	if (right < heap->size && heap->nodes[right]->dist < heap->nodes[smallest]->dist)
		smallest = right;

	if (smallest != idx) {
		HeapNode *smallest_node = heap->nodes[smallest];
		HeapNode *idx_node = heap->nodes[idx];

		heap->pos[smallest_node->v] = idx;
		heap->pos[idx_node->v] = smallest;

		swap_heap_node(&heap->nodes[smallest], &heap->nodes[idx]);
		min_heapify(heap, smallest);
	}
}

int is_empty(struct Heap *heap) {
	return heap->size == 0;
}

struct HeapNode *extract_min(struct Heap *heap) {
	if (is_empty(heap))
		return NULL;

	struct HeapNode *root = heap->n;
	root = heap->nodes[0];
	struct HeapNode *last_node = heap->nodes[heap->size - 1];
	heap->nodes[0] = last_node;

	heap->pos[root->v] = heap->size - 1;
	heap->pos[last_node->v] = 0;

	--heap->size;
	min_heapify(heap, 0);

	return root;
}

void decrease_key(struct Heap *heap, int v, int dist) {
	int i = heap->pos[v];
	heap->nodes[i]->dist = dist;

	while (i && heap->nodes[i]->dist < heap->nodes[(i - 1) / 2]->dist) {
		heap->pos[heap->nodes[i]->v] = (i - 1) / 2;
		heap->pos[heap->nodes[(i - 1) / 2]->v] = i;
		swap_heap_node(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);

		i = (i - 1) / 2;
	}
}

bool is_in_min_heap(struct Heap *heap, int v) {
	return heap->pos[v] < heap->size;
}

void dijkstra(struct Graph *graph, int src, int *dist, int *predecessor) {
	int V = graph->n;
	struct Heap *heap = create_heap(V);

	for (int v = 0; v < V; ++v) {
		dist[v] = INF;
		predecessor[v] = -1;
		heap->nodes[v] = create_heap_node(v, dist[v]);
		heap->pos[v] = v;
	}

	heap->nodes[src] = create_heap_node(src, dist[src]);
	heap->pos[src] = src;
	dist[src] = 0;
	decrease_key(heap, src, dist[src]);

	heap->size = V;

	while (!is_empty(heap)) {
		struct HeapNode *min_node = extract_min(heap);
		int u = min_node->v;
		free(min_node);

		for (int i = 0; i < graph->m; ++i) {
			int v = graph->edges[i].v;
			int w = graph->edges[i].w;

			if (dist[u] != INF && dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				predecessor[v] = u;

				if (is_in_min_heap(heap, v))
					decrease_key(heap, v, dist[v]);
			}
		}
	}
}

int compute_largest_possible_number_of_planets(struct Graph *graph, int src) {
	int n = graph->n;
	int m = graph->m;
	int dist[n];
	int predecessor[n];
	dijkstra(graph, src, dist, predecessor);

	int max_distance = 0;
	int max_distance_planet = src;
	for (int i = 0; i < n; ++i) {
		if (i == src)
			continue;
		if (dist[i] > max_distance) {
			max_distance = dist[i];
			max_distance_planet = i;
		}
	}

	dijkstra(graph, max_distance_planet, dist, predecessor);
	int max_diameter = 0;
	for (int i = 0; i < n; ++i) {
		if (dist[i] > max_diameter)
			max_diameter = dist[i];
	}

	return max_diameter;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	struct Graph *graph = create_graph(n, m);

	for (int i = 0; i < m; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add_edge(graph, u, v, w);
		add_edge(graph, v, u, w);
	}

	int src = 0;
	printf("%d\n", compute_largest_possible_number_of_planets(graph, src));

	return 0;
}



