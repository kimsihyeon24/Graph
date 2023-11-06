#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 10

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}


void dfs_mat(GraphType* g, int v)
{
	int w;
	visited[v] = TRUE;
	printf("%d ", v);
	for (w = 0; w < g->n; w++)
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w);
}

typedef int element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void queue_init(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�.");
	q->front = (q->front + 1) & MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

void bfs_mat(GraphType* g, int v)
{
	int w;
	QueueType q;

	queue_init(&q);
	visited[v] = TRUE;
	printf("%d ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for(w = 0; w<g->n; w++)
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = TRUE;
				printf("%d ", w);
				enqueue(&q, w);
			}
	}
}


int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 19; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 9);
	insert_edge(g, 0, 6);
	insert_edge(g, 0, 4);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 5);
	insert_edge(g, 6, 8);
	insert_edge(g, 6, 4);
	insert_edge(g, 4, 2);
	insert_edge(g, 4, 3);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 1);
	insert_edge(g, 4, 7);
	insert_edge(g, 2, 3);
	insert_edge(g, 5, 1);
	insert_edge(g, 8, 9);
	insert_edge(g, 8, 10);
	insert_edge(g, 7, 10);
	insert_edge(g, 1, 10);


	printf("----------------------\n");
	printf("1   : ���� �켱 Ž��  |\n");
	printf("2   : �ʺ� �켱 Ž��  |\n");
	printf("3   : ����            |\n");
	printf("----------------------\n");
	
	
	while (1)
	{
		int keyNum = 0;
		int num1 = 0;
		int num2 = 0;

		printf("�޴� �Է� :");
		scanf_s("%d", &keyNum);


		switch (keyNum)
		{
		case 1:
			printf("���� ��ȣ�� Ž���� �� �Է� : ");
			scanf_s("%d %d", &num1, &num2);
			dfs_mat(g, 0);
			
			printf("\n");
			break;
		case 2:
			printf("���� ��ȣ�� Ž���� �� �Է� : ");
			scanf_s("%d %d", &num1, &num2);
			bfs_mat(g, 0);
			
			printf("\n");
			break;
		case 3:
			break;
		}
		if (keyNum == 3)
		{
			break;
		}
	}
}


