//
//  main.cpp
//  driver
//
//  Created by Shuolin Tian on 2018/11/6.
//  Copyright © 2018年 Shuolin Tian. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>
#include <signal.h>
#include <vector>

using namespace std;

int rgen(int argc, char **argv) {
    int mes=execv("./rgen",argv);
    if(mes==-1)
        perror("Error:from rgen");
    return 0;
}

int a1(void) {

//    if(mes==-1)
//        perror("Error:from a1");
    execlp("python", "python","./a1-ece650.py",NULL);
//    cout<<"this is child2"<<endl;
    return 0;
}

int a2(void) {
//    cout<<"this is a2"<<endl;
    execv("./a2-ece650",NULL);
//    cout<<"this is a2 2"<<endl;
//    if(mes==-1)
//        perror("Error:from a2");
    return 0;
}

int a3(void){
    string input;
    while(getline(cin, input)){
        if (input.size () > 0)
            cout<<input<<endl;
    }
    return 0;
}

int main(int argc, char **argv)
{
    std::vector<pid_t> kids;
    int RGenToA1[2];
    pipe(RGenToA1);
    
    pid_t child_pid1,child_pid2,child_pid3,child_pid4;
    int status;
    
    //fork process and launch RGEN
    
    child_pid1 = fork ();
    if (child_pid1 == 0)
    {
        dup2(RGenToA1[1],STDOUT_FILENO);
        close(RGenToA1[0]);
        close(RGenToA1[1]);//每次都要关两遍，因为fork是对main的复制
        return rgen(argc,argv);
    }
    
    kids.push_back(child_pid1);
    //    waitpid(child_pid, &status, 0);
    sleep(2);
    //fork process and launch A1
    int A1toA2[2];
    pipe(A1toA2);
    child_pid2 = fork ();
    if (child_pid2 == 0)
    {
        dup2(RGenToA1[0],STDIN_FILENO);
        close(RGenToA1[0]);
        close(RGenToA1[1]);
        
        dup2(A1toA2[1],STDOUT_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);
    
        return a1();
    }
    kids.push_back(child_pid2);
//    waitpid(child_pid2, &status, 0);
    
    //fork process and launch A2
    child_pid4 = fork ();
    if (child_pid4 == 0){
        dup2(A1toA2[1],STDOUT_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);
        return a3();
    }
    kids.push_back(child_pid3);
    
    child_pid3 = fork ();
    if (child_pid3 == 0){
        dup2(A1toA2[0],STDIN_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);
        return a2();
    }
    kids.push_back(child_pid3);
//    waitpid(child_pid3, &status, 0);

   
    waitpid(child_pid4, &status, 0);
    kids.push_back(child_pid4);
    for (pid_t k : kids){
        kill (k, SIGTERM);
        waitpid(k, &status, 0);
    }
    return 0;
}
