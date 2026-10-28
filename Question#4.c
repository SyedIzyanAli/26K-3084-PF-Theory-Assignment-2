#include <stdio.h>

float _total_sales = 0;
float _avg_order = 0;
float _highest_order = 0;
float _festival_total = 0;
int _best_day = 0;

int getValidDays();
float calculateDailySales(int dayNumber);
int findHighestSalesDay(float dailySales[], int numberOfDays);
void displayBarChart(float dailySales[], int numberOfDays);

int main(void)
{
    int days;

    days = getValidDays();
    float dailySales[days];

    for (int i = 0; i < days; i++)
    {
        printf("\n");
        dailySales[i] = calculateDailySales(i + 1);
    }

    for (int i = 0; i < days; i++)
    {
        _festival_total += dailySales[i];
    }

    _best_day = findHighestSalesDay(dailySales, days);

    printf("\n\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", _festival_total);
    printf("Day with highest sales: Day %d\n", _best_day);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[_best_day - 1]);

    displayBarChart(dailySales, days);

    return 0;
}

int getValidDays()
{
    int days = 0;
    while (days < 1 || days > 7)
    {
        printf("Enter Number of Days: ");
        scanf("%d", &days);
        if (days < 1 || days > 7)
        {
            printf("Invalid input! Please enter a value between 1 and 7.\n");
        }
    }
    return days;
}

float calculateDailySales(int dayNumber)
{
    int orders;
    _total_sales = 0;
    _highest_order = 0;

    printf("Day %d - Number of orders: ", dayNumber);
    scanf("%d", &orders);

    float amounts[orders];
    printf("Order amounts:\t");
    for (int j = 0; j < orders; j++)
    {
        scanf("%f", &amounts[j]);
        while (amounts[j] <= 0)
        {
            printf("Invalid amount! Amount must be greater than zero. Enter again: ");
            scanf("%f", &amounts[j]);
        }
        _total_sales += amounts[j];
        if (amounts[j] > _highest_order)
        {
            _highest_order = amounts[j];
        }
    }

    _avg_order = _total_sales / orders;

    printf("\nTotal sales: Rs. %.2f\n", _total_sales);
    printf("Average order: Rs. %.2f\n", _avg_order);
    printf("Highest order: Rs. %.2f\n", _highest_order);

    return _total_sales;
}

int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    float max_sales = 0;
    int highest_day = 1;

    for (int i = 0; i < numberOfDays; i++)
    {
        if (dailySales[i] > max_sales)
        {
            max_sales = dailySales[i];
            highest_day = i + 1;
        }
    }
    return highest_day;
}

void displayBarChart(float dailySales[], int numberOfDays)
{
    printf("\n===== DAILY SALES BAR CHART =====\n");
    for (int i = 0; i < numberOfDays; i++)
    {
        printf("Day %d:\t", i + 1);
        int asterisks = (int)(dailySales[i] / 100);
        for (int k = 0; k < asterisks; k++)
        {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}