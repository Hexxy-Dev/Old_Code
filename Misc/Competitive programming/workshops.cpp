#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops

struct Workshop
{
    void Set(int start, int duration, int end)
    {
        m_start = start;
        m_duration = duration;
        m_end = end;
    }
    int m_start, m_duration, m_end;
};

struct Available_Workshops
{
    int n;
    Workshop* m_Data;
};

Available_Workshops* initialize(int start_time[], int duration[], int n)
{
    Available_Workshops* workshops;
    workshops->n = n;

    workshops->m_Data = new Workshop[n];

    for (int i = 0; i < n; i++)
        workshops->m_Data[i].Set(start_time[i], duration[i], start_time[i] + duration[i]);

    return workshops;
}

int CalculateMaxWorkshops(Available_Workshops* ptr)
{
    int max = 0;

    return max;
}

int main(int argc, char* argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> start_time[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> duration[i];
    }

    Available_Workshops* ptr;
    ptr = initialize(start_time, duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
