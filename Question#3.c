#include <stdio.h>

float _total = 0;
float _avg = 0;
float Minimum = 0;
float Maxmimum = 0;
int _warning = 0;
int _critical = 0;
int counter = 0;
int _streak = 0;
float _highest_avg = 0;
int trigger = 0;


void input(int sensors, int readings, float array[sensors][readings]);
void print(int sensors, int readings, float array[sensors][readings]);
float total(int sensors, int readings, float array[sensors][readings]);
float average(float total, int readings);
float Min(int sensors, int readings, float array[sensors][readings]);
float Max(int sensors, int readings, float array[sensors][readings]);
int critical(int sensors, int readings, float array[sensors][readings]);
int warning(int sensors, int readings, float array[sensors][readings]);
int streak(int sensors, int readings, float array[sensors][readings]);
float highest_avg(int sensor, int reading, float array[sensor][reading]);

int main(void){

    int sensor;
    int reading;

    printf("Enter Number of Sensors: ");
    scanf("%d", &sensor);

    printf("Enter Nuber of Readings: ");
    scanf("%d", &reading);

    float array[sensor][reading];

    input(sensor, reading, array);
    print(sensor, reading, array);

    for (int i = 0; i < sensor; i++)
    {
        printf("\n");
        printf("Sensor %d:\t", i + 1);
        printf("Total: %.0f\t", total(i, reading, array));
        printf("Average: %.2f\t", average(total(i, reading, array), reading));
        printf("Max: %.0f\t", Max(i, reading, array));
        printf("Min: %.0f\t", Min(i, reading, array));
        printf("\n");
        printf("\t\tCritical: %d\t", critical(i, reading, array));
        printf("Warning: %d\t", warning(i, reading, array));
        printf("Longest Hot Streak: %d", streak(i, reading, array));
    }

    highest_avg(sensor,reading,array);



    return 0;
}

void input(int sensors, int readings, float array[sensors][readings])
{
    printf("\nEnter Data: ");
    for (int i = 0; i < sensors; i++)
    {
        for (int j = 0; j < readings; j++)
        {
            printf("\nS%d: R%d: ", i + 1, j + 1);
            scanf("%f", &array[i][j]);
        }
    }
}

void print(int sensors, int readings, float array[sensors][readings])
{
    printf("\n");
    for (int i = 0; i < sensors; i++)
    {
        printf("\nSensor %d:\t", i + 1);
        for (int j = 0; j < readings; j++)
        {
            printf("%.0f\t", array[i][j]);
        }
    }
    printf("\n\n");
}
float total(int sensors, int readings, float array[sensors][readings])
{
    _total = 0;
    for (int j = 0; j < readings; j++)
    {
        _total += array[sensors][j];
    }
    return _total;
}
float average(float total, int readings)
{
    _avg = 0;
    _avg = total / readings;
    return _avg;
}

float Min(int sensors, int readings, float array[sensors][readings])
{
    Minimum = array[sensors][0];
    for (int j = 0; j < readings; j++)
    {
        if (array[sensors][j] < Minimum)
        {
            Minimum = array[sensors][j];
        }
    }
    return Minimum;
}

float Max(int sensors, int readings, float array[sensors][readings])
{
    Maxmimum = 0;
    for (int j = 0; j < readings; j++)
    {
        if (array[sensors][j] > Maxmimum)
        {
            Maxmimum = array[sensors][j];
        }
    }
    return Maxmimum;
}
int warning(int sensors, int readings, float array[sensors][readings])
{
    _warning = 0;
    for (int j = 0; j < readings; j++)
    {
        if ((array[sensors][j] >= 35) && (array[sensors][j] <= 39))
        {
            _warning += 1;
        }
    }
    return _warning;
}

int critical(int sensors, int readings, float array[sensors][readings])
{
    _critical = 0;
    for (int j = 0; j < readings; j++)
    {
        if (array[sensors][j] >= 40)
        {
            _critical += 1;
        }
    }
    return _critical;
}

int streak(int sensors, int readings, float array[sensors][readings])
{

    _streak = 0;
    trigger = 0;
    counter = 0;

    for (int j = 0; j < readings; j++)
    {
        if (array[sensors][j] >= 35)
        {
            _streak += 1;
        }
        else
        {
            if (counter < _streak)
            {
                trigger = 1;
                counter = _streak;
            }
            _streak = 0;
        }
    }
    if (trigger == 1)
    {
        return counter;
    }
    else
    {
        return _streak;
    }
}

float highest_avg(int sensor, int reading, float array[sensor][reading])
{

    float total_array[sensor];
    float Highest_total = 0;
    float total = 0;
    float Highest_Average = 0;
    int sensor_number;

    for (int i = 0; i < sensor; i++)
    {
        total = 0;
        for(int j = 0; j < reading; j++){
            total += array[i][j];

         
        }
        total_array[i] = total;
    }

    for (int i = 0; i < sensor; i++)
    {
        if (total_array[i] > Highest_total)
        {
            Highest_total = total_array[i];
            sensor_number = i+1;
        }
    }

    Highest_Average = Highest_total / reading;
    printf("\n\nHighest Average: Sensor: %d (%.2f)\n",sensor_number,Highest_Average);
    return sensor_number;
}
