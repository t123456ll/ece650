//
//  main.cpp
//  a2ece650
//
//  Created by Shuolin Tian on 2018/10/25.
//  Copyright © 2018年 Shuolin Tian. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <queue>
#include <vector>

using namespace std;

//The part of processing input
void getNumFromStr(string str, vector<int> &vec);
void getNumFromStr(string str, vector<int> &vec){
    const char *s = str.c_str();
    const char *pstr;
    int i = 0, j = 0;
    int k, m;
    int e10;
    int digit;
    int ndigit = 0;
    pstr = &s[0];
    
    for (i = 0; *(pstr + i) != '\0'; i++){
        if ((*(pstr + i) >= '0') && (*(pstr + i) <= '9'))
            j++;
        else{
            if (j > 0){
                digit = *(pstr + i - 1) - 48;
                for (k = 1; k < j; k++){
                    e10 = 1;
                    for (m = 1; m <= k; m++)
                        e10 = e10 * 10;
                    digit = digit + (*(pstr + i - 1 - k) - 48)*e10;
                }
                vec.push_back(digit);
                ndigit++;
                j = 0;
            }
        }
    }
    if (j > 0){
        digit = *(pstr + i - 1) - 48;
        for (k = 1; k < j; k++){
            e10 = 1;
            for (m = 1; m <= k; m++)
                e10 = e10 * 10;
            digit = digit + (*(pstr + i - 1 - k) - 48)*e10;
        }
        vec.push_back(digit);
        ndigit++;
        j = 0;
    }
}

//the part of BFS
class Graph{
private:
    int num_vertex;         //the number of vertex
    std::vector< std::list<int> > AdjList;    //using the container in STL
    int *color,             // 0:white(haven't been searched), 1:grey(have been searched), 2:black(have been out)
    *distance,          // 0:start point, infinite:cannot reach the vertex from star point
    *predecessor;       // -1:no predecessor, is start vertex
public:
    Graph():num_vertex(0){};           // default constructor
    Graph(int N):num_vertex(N){        // constructor with input: number of vertex
        // initialize Adjacency List
        AdjList.resize(num_vertex);
    };
    void AddEdgeList(int from, int to);
    int BFS(int Start, int End);
    void PrintResult(int Strat, int End);
};

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
}

void Graph::PrintResult(int Start, int End){
    int original_end = End;
    std::stack<int> route;
    route.push(End);
    while (predecessor[End] != -1){
        route.push(predecessor[End]);
        End = predecessor[End];
        //continue;
    }
    while (!route.empty()){
        if (route.top() == original_end){
            std::cout << route.top() << std::endl;
            route.pop();
        }
        else {
            std::cout << route.top() << "-";
            route.pop();
        }
    }
}

int Graph::BFS(int Start, int End){
    
    //becausing of using number to represent vertex, we can use index of array to represent the vertex
    color = new int[num_vertex];
    predecessor = new int[num_vertex];
    distance = new int[num_vertex];
    int flag = 0;                       // 0: doesn't find the path   1:finds the path
    
    if (Start == End){
        cout << Start <<endl;
        flag = 1;
    }
    else {
        for (int i = 0; i < num_vertex; i++) {  // initialize
            color[i] = 0;                       // 0:white;
            predecessor[i] = -1;                // -1:no predecessor
            distance[i] = num_vertex+1;         // the max of distance, num_vertex vertex,
        }                                       //
    
        std::queue<int> q;
        int i = Start;
        if (color[i] == 0) {                // 第一次i會是起點vertex, 如圖二(c)
            color[i] = 1;                   // 1:灰色
            distance[i] = 0;                // 每一個connected component的起點之距離設成0
            predecessor[i] = -1;            // 每一個connected component的起點沒有predecessor
            
            q.push(i);
            while (!q.empty()) {
                int u = q.front();                  // u 為新的搜尋起點
                for (std::list<int>::iterator itr = AdjList[u].begin();        // for loop 太長
                     itr != AdjList[u].end(); itr++) {                         // 分成兩段
                    //cout << *itr << endl;
                    if (color[*itr] == 0) {                // 若被「找到」的vertex是白色
                        color[*itr] = 1;                   // 塗成灰色, 表示已經被「找到」
                        //cout << color[*itr] << endl;
                        distance[*itr] = distance[u] + 1;  // 距離是predecessor之距離加一
                        //cout << distance[*itr] << endl;
                        predecessor[*itr] = u;             // 更新被「找到」的vertex的predecessor
                        //cout << predecessor[*itr] << endl;
                        q.push(*itr);                      // 把vertex推進queue
                        if (*itr == End ) {
                            PrintResult(Start, End);
                            flag = 1;
                        }
                    }
                }
                q.pop();        // 把u移出queue
                color[u] = 2;   // 並且把u塗成黑色
            }
        }
    }
    return flag;// 若一次回圈沒有把所有vertex走過, 表示graph有多個connected component
}

vector<int> vertex_num;
vector<int> input_edges;

int CommandV(string input_line){
    vertex_num.clear();
    getNumFromStr(input_line, vertex_num);
    int ver_num = vertex_num[0];
    return ver_num;
}


int main(){
    string input_line1;
    string input_line2;
    string input_line3;
    int flag = 0;
    startfrom_V:
    while(getline(cin, input_line1)){;  //接受一个字符串，可以接收空格并输出，需包含“#include<string>”
        if (input_line1.compare(0,1,"V") == 0){
            cout<<input_line1<<endl;
            //vector<int> vertex_num;
            //getNumFromStr(input_line1, vertex_num);
            
            startfrom_E:
            while(getline(cin, input_line2)){  //接受一个字符串，可以接收空格并输出，需包含“#include<string>”
                cout<<input_line2<<endl;
                if (input_line2.compare(0,1,"E") == 0){
                    //vector<int> input_edges;
                    if (flag == 1){
                        input_line1 = input_line3;
                    }
                    int ver_num = CommandV(input_line1);
                    if (ver_num == 0)
                        cerr << "Error: no vertex" << endl;
                    Graph g(ver_num);
                    input_edges.clear();
                    getNumFromStr(input_line2,input_edges);
                    vector<int>::iterator it1;
                    for (it1 = input_edges.begin(); it1 != input_edges.end(); it1++){
                        if (*it1 >= ver_num){
                            cerr << "Error: The vertex " << *it1 << " doesn't exist" << endl;
                            goto startfrom_V;
                        }
                    }
        
                    int kk = 0;
                    for (; kk <input_edges.size(); kk+=2){
                        g.AddEdgeList(input_edges[kk], input_edges[kk+1]);
                        g.AddEdgeList(input_edges[kk+1], input_edges[kk]);  //because of undirected graph
                    }
                    
                    startfrom_s:
                    while(getline(cin, input_line3)){;  //接受一个字符串，可以接收空格并输出，需包含“#include<string>”
//                       cout<<input_line3<<endl;
                        if (input_line3.compare(0,1,"V") == 0){
                            flag = 1;
                            cout<<input_line3<<endl;
                            goto startfrom_E;
                        }
                        if (input_line3.compare(0,1,"s") == 0){
                            vector<int> input_startend;
                            getNumFromStr(input_line3, input_startend);
                            vector<int>::iterator it2;
                            for (it2 = input_startend.begin(); it2 != input_startend.end(); it2++){
                                if (*it2 >= ver_num){
                                    cerr << "Error: The vertex " << *it2 << " doesn't exist" << endl;
                                    goto startfrom_s;
                                }
                            }
                            int start = input_startend[0];
                            int end = input_startend[1];
                            if (g.BFS(start, end) == 1){
                                goto startfrom_s;  //not wrong, just to keep getting line
                            }
                            else {
                                cerr << "Error: the path doesn't eixt " <<endl;
                                goto startfrom_s;
                            }
                        }
                        goto startfrom_s;
                    }
                    goto the_end; //在E输完EOF
                }
                goto startfrom_E;
            }
            goto the_end; //在V输完EOF
        }//while input
        goto startfrom_V;
    }//while getline1
    the_end:    return 0; //什么都不输eEOF
}//main
