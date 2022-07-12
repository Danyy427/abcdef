#include "D:/abcdef/Ana Kod/main/move.ino"
#include "D:/abcdef/Ana Kod/main/pathfind.ino"
#include "D:/abcdef/Ana Kod/main/pins.ino"
#include "D:/abcdef/Ana Kod/main/ui.ino"
#include "D:/abcdef/Ana Kod/main/features.ino"
#include "D:/abcdef/Ana Kod/main/sensors.ino"

static long pathIterator = 0;
static long **pathToFollow;
static long *pathSizeList;
static long route[5] = {0, 2, 5, 4, 1};
static long routeLength = 5;
static graph_t *graph;

void setup()
{
    initializeSensors();
    Serial.begin(9600);

    graph = CreateGraph(6);

    SetVertice(graph, 0, LJunction, 0, 0);
    SetVertice(graph, 1, TJunction, 0, 1);
    SetVertice(graph, 2, LJunction, 0, 2);

    SetVertice(graph, 3, LJunction, 1, 0);
    SetVertice(graph, 4, TJunction, 1, 1);
    SetVertice(graph, 5, LJunction, 1, 2);

    Connect(graph, 0, 1, 1);
    Connect(graph, 1, 2, 1);

    Connect(graph, 0, 3, 1);
    Connect(graph, 1, 4, 1);
    Connect(graph, 2, 5, 1);

    Connect(graph, 3, 4, 1);
    Connect(graph, 4, 5, 1);

    setCurrentDirection(1);

    pathToFollow = (long **)malloc(sizeof(long *) * (routeLength - 1));
    pathSizeList = (long *)malloc(sizeof(long) * (routeLength - 1));

    for (int i = 0; i < routeLength - 1; i++)
    {
        long k = 0;
        long src = route[i];
        long dest = route[i + 1];
        long *list = getPath(dijkstra(graph->edges, 6, src), dest, &k);
        pathToFollow[i] = GetRelativeDirectionPath(list, k);
        pathSizeList[i] = k - 1;
    }
}

void loop()
{
    GetSensorInfo();

    if (currentSensorInfo[0] == HIGH || currentSensorInfo[4] == HIGH || pathIterator == 0)
    {
        int listCount = 0, pointCount = 0;
        long sum = 0;
        for (int i = 0; i < routeLength - 1; i++)
        {
            sum += pathSizeList[i];
            if (pathIterator < sum)
            {
                listCount = i;
                pointCount = sum - pathIterator; // ?????????
            }
        }

        int direction = pathToFollow[listCount][pointCount];
        if (direction == 0)
        {
            goForward();
        }
        else if (direction == 1)
        {
            turnRight();
        }
        else if (direction == 2)
        {
            goBackward();
        }
        else if (direction == 3)
        {
            turnLeft();
        }
        else
        {
            stopMoving();
        }
        pathIterator++;
    }

    long left = currentSensorInfo[1];
    long middle = currentSensorInfo[2];
    long right = currentSensorInfo[3];

    // HIGH = siyah
    // LOW = beyaz
    if (left == LOW && middle == HIGH && right == LOW)
    {
        goForward();
    }
    else if (left == HIGH && right == LOW)
    {
        turnLeft();
    }
    else if (left == LOW && right == HIGH)
    {
        turnRight();
    }
}
