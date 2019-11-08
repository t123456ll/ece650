//
//  main.cpp
//  assignment4
//
//  Created by Shuolin Tian on 2018/11/17.
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
#include "minisat/core/Solver.h"
#include "minisat/core/SolverTypes.h"
#include <algorithm>

using namespace std;
using namespace Minisat;
//using Minisat::mkLit;
//using Minisat::lbool;

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



int CommandV(string input_line){
    vector<int> vertex_num;
    vertex_num.clear();
    getNumFromStr(input_line, vertex_num);
    int ver_num = vertex_num[0];
    return ver_num;
}

int main() {
    string input_line;
    //string input_line;
    int ver_num;
    vector<int> edges;
    
    
    while(getline(cin, input_line)){;
        if (input_line.compare(0, 1, "V") == 0){
            ver_num = CommandV(input_line);
            continue;
        }
        if (input_line.compare(0, 1, "E") == 0){
            edges.clear();
            getNumFromStr(input_line, edges);
            
            for (int k=1; k < ver_num; k++){
                Minisat::Solver s;
                // Create variables

                Var v[ver_num][k];
                Lit l[ver_num][k];
                
                for (int i = 0; i < ver_num; i++) {  // initialize
                    int j = 0;
                    for (; j < k; j++){
                        v[i][j] = s.newVar();
                        l[i][j] = mkLit(v[i][j]);
                    }
                }
                
                
            // Create the clauses
            // At least one vertex is the jth vertex in the vertex cover
                //cout<<"rule1"<<endl;
                int j = 0;
                for (; j < k; j++) {
                    int i = 0;
                    vec<Lit> c1;
                    c1.clear();
                    for (; i < ver_num; i++){
                        //cout<<var(l[i][j])<<" ";
                        c1.push(l[i][j]);
                    }
                    //cout<<endl;
                    s.addClause(c1);
                }
                
            // the following rule is only useful when k>1
                if (k > 1){
            // No one vertex can appear twice in a vertex cover.
                    //cout<<"rule2"<<endl;
                    int i = 0;
                    for (; i < ver_num; i++) {
                        int j1 = 0;   // the ith vertex in pth vertex cover
                        for (; j1 < k-1; j1++){
                            int j2 = j1+1;   // compare one
                            for (; j2 < k; j2++){
                                //cout<<"-"<<var(l[i][j1])<<" "<<"-"<<var(l[i][j2]);
                                s.addClause(~l[i][j1], ~l[i][j2]);
                            }
                            //cout<<endl;
                        }
                    }
                }
                    
        // No more than one vertex appears in the jth position of the vertex cover
                //cout<<"rule3"<<endl;
                j = 0;
                for (; j < k; j++) {
                    int i1 = 0;   // the jth vertex in i1th vertex cover
                    for (; i1 < ver_num-1; i1++){
                        int i2 = i1+1;   // compare one
                        for (; i2 < ver_num; i2++){
                            //cout<<"-"<<var(l[i1][j])<<" "<<"-"<<var(l[i2][j]);
                            s.addClause(~l[i1][j], ~l[i2][j]);
                            //cout<<endl;
                        }
                        
                    }
                }
                
                
        // Every edge is incident to at least one vertex in the vertex cover.
        // v1,v2 are the two vertice of an edge
                //cout<<"rule4"<<endl;
                int k1 = 0;
                int len_edges = edges.size();
                
                for (; k1 < len_edges-1; k1 += 2){
                    int v1 = edges[k1];
                    int v2 = edges[k1 + 1];
                    int k2 = 0;
                    vec<Lit> c2;
                    c2.clear();
                    for (; k2 < k; k2++){
                        
                        c2.push(l[v1][k2]);
                        c2.push(l[v2][k2]);
                        //cout<<var(l[v1][k2])<<" "<<var(l[v2][k2])<<" ";
                    }
                    //cout<<endl;
                    s.addClause(c2);
                }
                
                
                // Check for solution and retrieve model if found
                auto sat = s.solve();
                vector<int> vc;
                if (sat) {
                    // update
                    for (int i = 0; i < ver_num; ++i) {
                        for (j = 0; j < k; ++j){
                            lbool cnm = s.modelValue(l[i][j]);
                            if (cnm == l_True){
                                vc.push_back(i);
                            }
                        }
                    }
//                    cout << "k:" << k << " " << sat << endl;
                    //cout<<"solve"<<endl;
                    int len_vc = vc.size();
                    int vertex_cover[len_vc];
                    int i = 0;
                    for (; i < len_vc; i++){
                        vertex_cover[i] = vc[i];
                    }
                    
                    sort(vertex_cover, vertex_cover+len_vc);
                    for(i = 0; i < len_vc; i++)
                        cout << vertex_cover[i] << " ";
                    cout << endl;
                    break;
                }
            }
        }
    }
}
/*
V 3
E {(0,1)(0,2)}
*/
