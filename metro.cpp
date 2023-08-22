#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
vector<pair<int, float>> adj[1000];
int E = 22;
unordered_map<int, string> Stations = {

    {1, "Bhatapara"},
    // 3
    {2, "New Airport"},
    // 2.8
    {3, "Airport South"},
    //.9
    {4, "Raipur Airport"},
    // 1.1
    {5, "Ujjwal Nagar"},
    // .850
    {6, "JP Nagar"},
    // 2.5
    {7, "Bilaspur"},
    // 1.5
    {8, "Nipaniya"},
    // 1.1
    {9, "Bhilai"},
    // 1
    {10, "Congress Ngr"},
    // 1.7
    {11, "Sitaburdi"},
    // .700
    {12, "Zero Mile"},
    //.800
    {13, "Kasturchand Prk"},
    // 0.550
    {14, "Indira Gandhi"},
    // 0.9
    {15, "NIT Raipur"},
    //.9
    {16, "Shankar Nagar"},
    // 1.2
    {17, "LAD Chowk"},
    // 2.2
    {18, "Dharampeth Clg"},
    // 2.1
    {19, "Subhas Ngr"},
    // 3
    {20, "Ringroad"},
    // 2.2
    {21, "Vasudev Nagar"},
    // 0.950
    {22, "Bansi Nagar"},
    // 2.8
    {23, "Lokmanya Ngr"},

};
void printLine()
{

    for (int i = 0; i < 40; i++)
    {
        cout << '-';
    }
    cout << endl;
}
void printLine1()
{

    for (int i = 0; i < 130; i++)
    {
        cout << '-';
    }
    cout << endl;
}
void Display_Stations()
{
    cout << "\n\n~~~Metro Stations~~~\n\n\n";
    printLine();
    cout << "STATION NAME\t\t\tSTATION ID"
         << endl;
    printLine();
    for (auto it : Stations)
    {
        cout <<it.second << "\t\t\t" <<it.first << endl;
        printLine();
    }
}
void makeGraph()
{
    vector<vector<float>> list = {
        // Bhatapara To Kasturchand
        {1, 2, 3},
        {2, 3, 2.8},
        {3, 4, 0.9},
        {4, 5, 1.1},
        {5, 6, .850},
        {6, 7, 2.5},
        {7, 8, 1.5},
        {8, 9, 1.1},
        {9, 10, 1},
        {10, 11, 1.7},
        {11, 12, 0.700},
        {12, 13, 0.800},
        // Lokmanya to Sitaburdi
        {11, 14, 0.550},
        {14, 15, 0.9},
        {15, 16, 0.9},
        {16, 17, 1.2},
        {17, 18, 2.2},
        {18, 19, 2.1},
        {19, 20, 3},
        {20, 21, 2.2},
        {21, 22, 0.950},
        {22, 23, 2.8},

    };
    for (auto it : list)
    {
        int u = it[0], v = it[1];
        float d = it[2];
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    }
}
void welcome()
{
    cout << "\n\t\t\t****WELCOME TO THE METRO APP*****\n\n\n";
}
void printPath(vector<int> parent, int source, int dest)
{
    stack<int> st;
    int final = dest;

    while (parent[dest] != source)
    {
        dest = parent[dest];
        st.push(dest);
    }
    printLine1();
    cout << "Stations in Route from " << Stations[source] << " to " << Stations[final] << ":\n\n";

    cout << Stations[source] << " --> ";
    while (!st.empty())
    {
        cout << Stations[st.top()] << " --> ";

        st.pop();
    }
    cout << Stations[final] << endl;
    printLine1();
}
void shortestPath()
{   cout<<endl;
    cout<<endl;
    makeGraph();
    printLine1();
    cout<<endl;
    cout<<endl;
    bool isDesti = true, isInBetween = false;
    cout << "Enter Source(station ID):";
    int src, dest;
    cin >> src;
    cout << "Enter Destination(station ID):";
    cin >> dest;

    if (src == 11 or dest == 11)
        isDesti = false; // src or desti is Sitabuldi

    priority_queue<pair<float, float>, vector<pair<float, float>>, greater<pair<float, float>>> pq;

    vector<float> distTo(E + 2, INT_MAX); // 1-indexed array for calculating shortest paths;
    distTo[src] = 0;
    vector<int> parent(E + 2, -1);
    parent[src] = src;
    pq.push({0, src});

    while (!pq.empty())
    {
        int node = (int)pq.top().second;
        if (node == 11)
            isInBetween = true;
        float dis = pq.top().first;
        pq.pop();

        for (auto it : adj[node])
        {
            int adjNode = (int)it.first;
            float adjDis = it.second;
            if (distTo[adjNode] > dis + adjDis)
            {
                distTo[adjNode] = dis + adjDis;
                pq.push({distTo[adjNode], adjNode});
                parent[adjNode] = node;
            }
        }
    }

    cout <<endl<< Stations[src] << " to " << Stations[dest] << " distance is " << distTo[dest] << " Km\t"
         << endl;
    if (isDesti and isInBetween)
    {
        cout << "and 1 Interchange\n";
    }
    cout<<endl;
    printPath(parent, src, dest);
}
int main()
{
    int ch = 1;

    while (ch != -1)
    {
        welcome();
        printf("\t\t\t\t~~LIST OF ACTIONS~~\n\n");
        printf("1. LIST OF ALL THE STATIONS\n");
        printf("2. GET SHORTEST DISTANCE AND PATH FROM A SOURCE STATION TO DESTINATION STATION\n");
        printf("3. EXIT THE MENU\n");
        printf("\n\nENTER YOUR CHOICE AS SERIAL NUMBER FROM THE ABOVE LIST : ");

        cin >> ch;
        switch (ch)
        {
        case 1:
            Display_Stations();
            break;
        case 2:
            shortestPath();
            break;
        default:
            ch = -1;
        }
    }
    return 0;
}
