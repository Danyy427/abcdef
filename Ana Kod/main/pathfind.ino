#ifndef _PATHFIND_
#define _PATHFIND_

#define INT_MAX 2147483647
#define INT_MIN -2147483648

/*
 * Robotun karşılaşabileceği noktalar
 */
enum PointTypes
{
    StartingPoint,
    LJunction,
    TJunction,
    Dropoff,
    Barrier
};

typedef struct
{
    unsigned char type;
    unsigned char row;
    unsigned char column;
} point_t;

typedef struct
{
    long size;
    point_t *vertices;
    long **edges;
} graph_t;

graph_t *CreateGraph(long size)
{
    graph_t *graph = (graph_t *)malloc(sizeof(graph_t));
    graph->size = size;

    graph->vertices = (point_t *)malloc(sizeof(point_t) * size);

    graph->edges = (long **)malloc(size * sizeof(long *));
    for (long i = 0; i < size; i++)
    {
        graph->edges[i] = (long *)malloc(size * sizeof(long));

        for (long j = 0; j < size; j++)
        {
            graph->edges[i][j] = 0;
        }
    }

    return graph;
}

void SetVertice(graph_t *graph, long n, int type, char row, char column)
{
    if (n >= graph->size && graph->vertices == 0)
        return;

    graph->vertices[n].column = column;
    graph->vertices[n].row = row;
    graph->vertices[n].type = type;
}

void Connect(graph_t *graph, long src, long dest, long weight)
{
    if (src > graph->size || dest > graph->size)
    {
        return;
    }
    graph->edges[src][dest] = weight;
    graph->edges[dest][src] = weight;
}

/*
 * Bunun sonucu gidilecek yolu verecek
 */

long *getPath(long parent[], long j, long *pathsize)
{
    long a = j;
    long k = 0;
    while (parent[a] != -1)
    {
        k++;
        a = parent[a];
    }

    *pathsize = k;
    long *path = (long *)malloc(sizeof(long) * k);
    a = j;
    while (parent[a] != -1)
    {
        path[--k] = a;
        a = parent[a];
    }

    return path;
}

long minList(long n, long *list, long *isVisited)
{
    long minVal = INT_MAX, minIndex;

    for (long i = 0; i < n; i++)
    {
        if (list[i] < minVal && isVisited[i] == 0)
        {
            minVal = list[i];
            minIndex = i;
        }
    }

    return minIndex;
}

/*
 * Pathfinding yapan fonksiyon
 * edges: graph->edges
 * n: nokta sayısı, graph->size
 * src: başlanılacak nokta
 * Bunun sonucu getPath(); fonksiyonuna gidecek
 */

long *dijkstra(long **edges, long n, long src)
{

    long dist[n];
    long isVisited[n];
    long *tree = (long *)malloc(sizeof(long) * n);
    for (long i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
        tree[i] = -1;
        isVisited[i] = 0;
    }

    dist[src] = 0;

    for (long i = 0; i < n - 1; i++)
    {

        long pickedNode = minList(n, dist, isVisited);

        isVisited[pickedNode] = 1;
        for (long j = 0; j < n; j++)
        {

            if (edges[pickedNode][j] > 0 && isVisited[j] == 0 && dist[pickedNode] + edges[pickedNode][j] < dist[j])
            {
                dist[j] = dist[pickedNode] + edges[pickedNode][j];
                tree[j] = pickedNode;
            }
        }
    }
    return tree;
}

graph_t *GlobalMap;

/*
 * Kullanılacak haritayı hazırlayan fonksiyon
 */

void InitializeGlobalMap()
{
    GlobalMap = CreateGraph(21);
    // Haritanın Üst kismi
    SetVertice(GlobalMap, 0, LJunction, 0, 0);
    SetVertice(GlobalMap, 1, TJunction, 0, 1);
    SetVertice(GlobalMap, 2, TJunction, 0, 2);
    SetVertice(GlobalMap, 3, StartingPoint, 0, 3);
    SetVertice(GlobalMap, 4, TJunction, 0, 4);
    SetVertice(GlobalMap, 5, TJunction, 0, 5);
    SetVertice(GlobalMap, 6, LJunction, 0, 6);

    // Ortadaki bariyerler veya yük noktaları
    SetVertice(GlobalMap, 7, Barrier, 1, 1);
    SetVertice(GlobalMap, 8, Dropoff, 2, 1);
    SetVertice(GlobalMap, 9, Dropoff, 2, 2);
    SetVertice(GlobalMap, 10, Barrier, 3, 3);
    SetVertice(GlobalMap, 11, Dropoff, 2, 4);
    SetVertice(GlobalMap, 12, Dropoff, 2, 5);
    SetVertice(GlobalMap, 13, Barrier, 1, 5);

    // Haritanın Alt kısmı
    SetVertice(GlobalMap, 14, LJunction, 4, 0);
    SetVertice(GlobalMap, 15, TJunction, 4, 1);
    SetVertice(GlobalMap, 16, TJunction, 4, 2);
    SetVertice(GlobalMap, 17, StartingPoint, 4, 3);
    SetVertice(GlobalMap, 18, TJunction, 4, 4);
    SetVertice(GlobalMap, 19, TJunction, 4, 5);
    SetVertice(GlobalMap, 20, LJunction, 4, 6);

    // Bağltanılar
    Connect(GlobalMap, 0, 1, 1);
    Connect(GlobalMap, 1, 2, 1);
    Connect(GlobalMap, 2, 3, 1);
    Connect(GlobalMap, 3, 4, 1);
    Connect(GlobalMap, 4, 5, 1);
    Connect(GlobalMap, 5, 6, 1);

    Connect(GlobalMap, 0, 14, 1);

    Connect(GlobalMap, 1, 7, 1);
    Connect(GlobalMap, 7, 8, 1);
    Connect(GlobalMap, 8, 15, 1);

    Connect(GlobalMap, 2, 9, 1);
    Connect(GlobalMap, 9, 16, 1);

    Connect(GlobalMap, 3, 10, 1);
    Connect(GlobalMap, 10, 17, 1);

    Connect(GlobalMap, 4, 11, 1);
    Connect(GlobalMap, 11, 18, 1);

    Connect(GlobalMap, 5, 13, 1);
    Connect(GlobalMap, 13, 12, 1);
    Connect(GlobalMap, 12, 19, 1);

    Connect(GlobalMap, 6, 20, 1);

    Connect(GlobalMap, 14, 15, 1);
    Connect(GlobalMap, 15, 16, 1);
    Connect(GlobalMap, 16, 17, 1);
    Connect(GlobalMap, 17, 18, 1);
    Connect(GlobalMap, 18, 19, 1);
    Connect(GlobalMap, 19, 20, 1);
}

#endif
