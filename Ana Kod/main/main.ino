#include "D:/abcdef/Ana Kod/main/move.ino"
#include "D:/abcdef/Ana Kod/main/pathfind.ino"
#include "D:/abcdef/Ana Kod/main/pins.ino"
#include "D:/abcdef/Ana Kod/main/ui.ino"
#include "D:/abcdef/Ana Kod/main/features.ino"
#include "D:/abcdef/Ana Kod/main/sensors.ino"

static long pathIterator = 0;
static long **pathToFollow;
static long *pathSizeList;
static long pathSizeTotal;
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

        pathToFollow[i] = GetAbsoluteDirectionPath(graph, list, k);
        long newDirection = pathToFollow[i][k - 2];

        pathToFollow[i] = GetRelativeDirectionPath(graph, list, k);
        pathSizeList[i] = k - 1;
        pathSizeTotal += k - 1;

        setCurrentDirection(newDirection);
    }
}

void loop()
{
    GetSensorInfo();
    if (pathIterator == pathSizeTotal)
    {
        while (1)
        {
            stopMoving();
        }
    }

    if (currentSensorInfo[0] == HIGH || currentSensorInfo[4] == HIGH || pathIterator == 0)
    {
        int listCount = 0, pointCount = 0;
        long sum = 0, prevSum = 0;
        for (int i = 0; i < routeLength - 1; i++)
        {
            sum += pathSizeList[i];
            if (pathIterator < sum)
            {
                listCount = i;
                pointCount = pathIterator - prevSum; // ?????????
                break;
            }
            prevSum = sum;
        }

        int direction = pathToFollow[listCount][pointCount];
        if (direction == 0)
        {
            while (currentSensorInfo[4] == HIGH || currentSensorInfo[0] == HIGH)
            {
                GetSensorInfo();
                goForward();
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
        }
        else if (direction == 1)
        {
            while (currentSensorInfo[2] == HIGH)
            {
                GetSensorInfo();
                turnRight();
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
            while (currentSensorInfo[2] == LOW)
            {
                GetSensorInfo();
                turnRight();
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
        }
        else if (direction == 2)
        {
            while (currentSensorInfo[4] == LOW || currentSensorInfo[0] == LOW)
            {
                GetSensorInfo();
                goBackward();
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
        }
        else if (direction == 3)
        {
            while (currentSensorInfo[2] == HIGH)
            {
                GetSensorInfo();
                turnLeft();
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
            while (currentSensorInfo[2] == LOW)
            {
                GetSensorInfo();
                turnLeft();
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
        }
        else
        {
            stopMoving();
        }
        pathIterator++;
        return;
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
