//
//  main.cpp
//  random input generator
//
//  Created by Shuolin Tian on 2018/10/31.
//  Copyright © 2018年 Shuolin Tian. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <map>
#include <string>
#include <cmath>

using namespace std;
typedef std::map<string, vector<int> > STRING2VECTOR;

int random_number(int min, int max){
    std::ifstream urandom("/dev/urandom");
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int random_value = 0;
    urandom.read((char*)&random_value, sizeof(int));
    
    urandom.close();
    return min + (random_value % (max - min + 1));
}


class Street{
private:
    //char name;
    int segment_num;
    map<string, vector<int> > street_dic;
public:
    Street():segment_num(0){};
    Street(string name, int N):segment_num(N){
        //coordinate.resize(2 * (segment_num + 1));
    };
    vector<int> street_coordinate;
    void AddCoordinate(int x, int y);
    void AddStreet(string name);
    void PrintStreet();
    bool SelfIntersect();
    bool SameCoordination();
};

void Street::AddCoordinate(int x, int y){
    street_coordinate.push_back(x);
    street_coordinate.push_back(y);
}
void Street::AddStreet(string name){
    street_dic.insert(STRING2VECTOR::value_type(name, street_coordinate));
}
void Street::PrintStreet(){
    map<string, vector<int> >::iterator map_it = street_dic.begin();
    for ( ; map_it != street_dic.end(); map_it++){
        cout<<map_it->first<<":";
        vector<int>::iterator mapvec_itor = map_it->second.begin();
        for ( ; mapvec_itor !=  map_it->second.end(); mapvec_itor++){
            cout<<(*mapvec_itor)<<" ";
        }
        cout<<endl;
    }
}
bool Street::SelfIntersect(){
    int i = 0;
    int length = 2*(segment_num+1)-2;
    for (; i < length; i+=2){  //
        int j = i+4; //判断不相邻的两个线段
        for (; j < length; j+=2){
            int x1 = street_coordinate[i];
            int y1 = street_coordinate[i+1];
            int x2 = street_coordinate[i+2];
            int y2 = street_coordinate[i+3];
            int x3 = street_coordinate[j];
            int y3 = street_coordinate[j+1];
            int x4 = street_coordinate[j+2];
            int y4 = street_coordinate[j+3];
            float xnum = ((x1-x3)*(y3-y4) - (y1-y3)*(x3-x4));
            float den = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
            if (den == 0){
                return false;
            }
            float t = (xnum / den);
            float ynum = ((x1-x2)*(y1-y3) - (y1-y2)*(x1-x3));
            float u = - (ynum / den);
            
            if (t>=0 && t<=1 && u>=0 && u<=1){
                return true;  // two segments have intersection
            }
        }
    }
    return false;
}

bool Street::SameCoordination(){
    int i = 0;
    int length = 2*(segment_num+1);
    for (; i < length; i+=2){
        int j = i+2;
        for (; j <= segment_num; j+=2){
            int x1 = street_coordinate[i];
            int y1 = street_coordinate[i+1];
            int x2 = street_coordinate[j];
            int y2 = street_coordinate[j+1];
            
            if (x1 == x2 && y1 == y2){
                return true;   //have same coordination
            }
        }
    }
    return false;
}

string NameStreet(int i){
    int char1 = floor(i / 26);
    int char2 = i % 26;
    string name1(1, char(char1 + 65));
    string name2(1, char(char2 + 65));
    string name = '"' + name1 + name2 + '"';
    return name;
}

bool SameCoordination(map<string, vector<int> > map){
    int i = 0;
    int size_map = map.size();
    for (; i < size_map; i++){ //key of map
        string name_i = NameStreet(i);
        vector<int> vec_i = map[name_i];
        int size_vec_i = vec_i.size();
        int j = i + 1;
        for (; j < size_map; j++){  //key of compared map
            string name_j = NameStreet(j);
            vector<int> vec_j = map[name_j];
            int size_vec_j = vec_j.size();
            int k = 0;
            for (; k < size_vec_i; k+=2){  //value of map
                int l = 0;
                for (; l < size_vec_j; l+=2){  //value of compared map
                    int x1 = map[name_i][k];
                    int y1 = map[name_i][k+1];
                    int x2 = map[name_j][l];
                    int y2 = map[name_j][l+1];
                    if (x1 == x2 && y1 == y2){
                        return true;   //have same coordination
                    }
                }
            }
        }
    }
    return false;
}


bool Overlap(map<string, vector<int> > map){
    int i = 0;
    int size_map = map.size();
    for (; i < size_map; i++){ //key of map
        string name_i = NameStreet(i);
        vector<int> vec_i = map[name_i];
        int size_vec_i = vec_i.size();
        int j = i;  // street need to compare with itself
        for (; j < size_map; j++){  //key of compared map
            string name_j = NameStreet(j);
            vector<int> vec_j = map[name_j];
            int size_vec_j = vec_j.size();
            int k = 0;
            for (; k < size_vec_i-2; k+=2){  //value of map
                int l = 0;
                for (; l < size_vec_j-2; l+=2){  //value of compared map
                    if (i == j && k == l)
                        continue; // same segment of the same street
                    float x1 = vec_i[k];
                    float y1 = vec_i[k+1];
                    float x2 = vec_i[k+2];
                    float y2 = vec_i[k+3];
                    float x3 = vec_j[l];
                    float y3 = vec_j[l+1];
                    float x4 = vec_j[l+2];
                    float y4 = vec_j[l+3];
                    if ((x2-x1)==0 && (x4-x3)==0){ //排除分母为0
                        if (x1 == x3){  //on the same line
                            if ((y3>=min(y1,y2) && y3<=max(y1,y2)) || (y4>=min(y1,y2) && y4<=max(y1,y2)))
                                return true;
                        }
                        continue;
                    }
                    float k1 = (y2-y1)/(x2-x1);
                    float k2 = (y4-y3)/(x4-x3);
                    float c1 = y1 - k1 * x1;
                    float c2 = y3 - k2 * x3;  //要改
                    if ((x2-x1) * (y4-y3) == (x4-x3) * (y2-y1)){  //斜率相等
                        if (c2 == c1 ){ //与y轴截距相等
                            if (((y3>=min(y1,y2) && y3<=max(y1,y2)) || (y4>=min(y1,y2) && y4<=max(y1,y2)))
                                || ((x3>=min(x1,x2) && x3<=max(x1,x2)) || (x4>=min(x1,x2) && x4<=max(x1,x2)))) //在范围内
                                return true;
                        }
                        continue;
                    }
                    continue;
                }
            }
        }
    }
    return false;
} //暴力


string input_line;

int main(int argc, char **argv){
    int opt = 0;
    int street_max = 10;
    int segment_max = 5;
    int wait_max = 5;
    int coordinate_max = 20;
    string value;
    static const char *optString = "s:n:l:c:"; //colon means getting num
    
    //opt = getopt(argc, argv, optString );
    while( (opt = getopt( argc, argv, optString) ) != -1) {
        switch( opt ) {
            case 's':
                street_max = atoi(optarg);
                break;
            case 'n':
                segment_max = atoi(optarg);
                break;
            case 'l':
                wait_max = atoi(optarg);
                break;
            case 'c':
                coordinate_max = atoi(optarg);
                break;
            case '?':
                if (optopt == 'c')
                    std::cerr << "Error: option -" << optopt
                    << " requires an argument." << std::endl;
                else
                    std::cerr << "Error: unknown option: " << optopt << std::endl;
                return 1;
                
            default:
                /* You won't actually get here. */
                break;
        }
    }
    
    //int street_num = random_number(30,30);
    int wait_num = random_number(5, wait_max);
    //cout << "Random street_num: " << street_num << "\n";
    cout << "Random wait_num: " << wait_num << "\n";
    //cout << "Random coordinate_max: " << coordinate_max << "\n";
    
    while(1){
        int street_num = random_number(2, street_max);
        map<string, vector<int> > streets_dic;
        
        int i = 0;
        for (; i < street_num; i++){
            int segment_num = random_number(1, segment_max);
            //int segment_num = random_number(5, 5);
            //cout << "Random segment_num: " << segment_num << "\n";
            
            //char name_c = i+65;
            //char *name_cp = &name_c;
            //string name = name_cp;
            //string name(1,char(i+65));
            string name = NameStreet(i);
            //cout << name << endl;
            Street str(name,segment_num); // name:a    Street class value:str
            int j = 0;
            for (; j<=segment_num; j++){  // "<=" means the number of (x,y) is segment_num + 1
                int coordinate_x = random_number(-coordinate_max, coordinate_max);
                int coordinate_y = random_number(-coordinate_max, coordinate_max);
                str.AddCoordinate(coordinate_x, coordinate_y);
            }
            str.AddStreet(name);
            //str.PrintStreet();//要改。street_dic存的只是用来打印的，线段不一定符合要求
            if (str.SameCoordination()){
                //cout << "have same coordination" << "\n";
                i = i - 1;
                continue;
            }//need to do it again after generating all streets
            else {
                if (str.SelfIntersect()){
                    //cout << "two segments have intersection" << "\n";
                    i = i - 1;
                    continue;
                }
                streets_dic.insert(STRING2VECTOR::value_type(name, str.street_coordinate));
                
            }
            if (SameCoordination(streets_dic)){
                //cout << "outside have same coordination" << "\n";
                streets_dic.erase(name);
                i = i - 1;
                continue;
            };
            if (Overlap(streets_dic)){
                //cout << "overlap" << "\n";
                streets_dic.erase(name);
                i = i - 1;
                continue;
            };
        }
        /*
         vector<int>::iterator vec_it2 = all_coordinate.begin();
         for(; vec_it2 != all_coordinate.end(); vec_it2++){
         cout << *vec_it2 << " ";
         }
         cout<<endl;
         */
        
        map<string, vector<int> >::iterator map_it = streets_dic.begin();
        for ( ; map_it != streets_dic.end(); map_it++){
            cout<<"a"<<" ";
            cout<<map_it->first<<" ";
            vector<int>::iterator mapvec_itor = map_it->second.begin();
            int i = 0;
            for ( ; mapvec_itor !=  map_it->second.end(); mapvec_itor++){
                if (i%2){
                    cout<<(*mapvec_itor)<<") ";
                    
                }
                else {
                    cout<<"("<<(*mapvec_itor)<<",";
                }
                i ++;
                
            }
            cout<<endl;
        }
        cout<<"g"<<endl;
        map_it = streets_dic.begin();
        for ( ; map_it != streets_dic.end(); map_it++){
            cout<<"r"<<" ";
            cout<<map_it->first<<" ";
            cout<<endl;
        }
        sleep(wait_num);
    }
    
}

/*
 bool SameCoordination(vector<int> vec){
 int i = 0;
 unsigned long len_vec = vec.size();
 for (; i < len_vec; i+=2){
 int j = i+2;
 for (; j < len_vec; j+=2){
 int x1 = vec[i];
 int y1 = vec[i+1];
 int x2 = vec[j];
 int y2 = vec[j+1];
 
 if (x1 == x2 && y1 == y2){
 return true;   //have same coordination
 }
 }
 }
 return false;
 }
 
 bool Overlap(vector<int> vec){
 int i = 0;
 unsigned long len_vec = vec.size();
 for (; i < len_vec; i+=2){
 float x1 = vec[i];
 float y1 = vec[i+1];
 float x2 = vec[i+2];
 float y2 = vec[i+3];
 
 int j = i + 2; //the size of segment is 2. dont compare with itself
 for (; j < len_vec; j+=2){
 float x3 = vec[j];
 float y3 = vec[j+1];
 float x4 = vec[j+2];
 float y4 = vec[j+3];
 if ((x2-x1)==0 && (x4-x3)==0){ //排除分母为0
 if (x1 == x3){
 if ((y3>=min(y1,y2) && y3<=max(y1,y2)) || (y4>=min(y1,y2) && y4<=max(y1,y2)))
 return true;
 }
 else
 return false;
 }
 float k1 = (y2-y1)/(x2-x1);
 float k2 = (y4-y3)/(x4-x3);
 float c1 = y1 - k1 * x1;
 float c2 = y3 - k2 * x3;  //要改
 if ((x2-x1) * (y4-y3) == (x4-x3) * (y2-y1)){  //斜率相等
 if (c2 == c1 ){ //与y轴截距相等
 if (((y3>=min(y1,y2) && y3<=max(y1,y2)) || (y4>=min(y1,y2) && y4<=max(y1,y2)))
 || ((x3>=min(x1,x2) && x3<=max(x1,x2)) || (x4>=min(x1,x2) && x4<=max(x1,x2)))) //在范围内
 return true;
 
 else
 return false;
 }
 else
 return false;
 }
 else
 return false;
 }
 }
 return false;
 } //暴力
 
 ******test part*******
 vector<int> test_a;
 vector<int> test_b;
 test_a.push_back(-4); test_a.push_back(0); test_a.push_back(0); test_a.push_back(4); test_a.push_back(-3); test_a.push_back(1); test_a.push_back(-2); test_a.push_back(0);
 test_b.push_back(-4); test_b.push_back(0);test_b.push_back(2); test_b.push_back(0);
 streets_dic.insert(STRING2VECTOR::value_type("A",test_a));
 streets_dic.insert(STRING2VECTOR::value_type("B",test_b));
 if (SameCoordination(streets_dic)){
 cout << "test have same coordination" << "\n";
 }
 if (Overlap(streets_dic)){
 cout << "test overlap" << "\n";
 }
 ***********************
 */
