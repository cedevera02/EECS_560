#ifndef MY_MAZE_H
#define MY_MAZE_H

#include "myDisjointSets_c952d843.h"
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>   
#include <bits/stdc++.h> 
#include <algorithm>   

using namespace std;

class myMaze : public myDisjointSets
{
    public:
        myMaze(const int m, const int n) : myDisjointSets(m*n)
        {
            m_m = m;
            m_n = n;
            vector<int> v(m*n, -1);
            s = v;
            srand (time(NULL));
        }

        ~myMaze(void)
        {

        }

        void buildMaze(std::vector<std::pair<int, int> > & broken_walls) 
        {
            int m1, n1, m2, n2, room1, room2;
            while(!oneRoot()){
                room1 = getRands(m1, n1);
                room2 = getAdjRoom(m1,n1, m2,n2);
                bool unioned = false;
                int turns = 0;
                do{
                    if (find(room1) != find(room2)){
                        std::pair<int,int> p;
                        if(room1 < room2)
                            p = std::make_pair(room1,room2);
                        else
                            p = std::make_pair(room2,room1);
                        broken_walls.push_back(p);
                        unionSets(find(room1), find(room2));
                        unioned = true;
                        turns = 0;
                     }
                    else{
                        room2 = getAdjRoom(m1,n1, m2,n2);
                        turns++;
                    }
                }while(!unioned && turns != 4);
            }

            brWalls = broken_walls;
        }

        

        void solveMaze(std::vector<int> & path)
        {
            bool sol = mazeWalker(0, 0, path);
        }

    private:
        int m_m;
        int m_n;
        std::vector<std::pair<int, int> > brWalls;

        bool mazeWalker(int m, int n,std::vector<int> & path)
        {
            path.push_back(m*m_n+n);

            if(m*m_n+n == m_m*m_n-1){
                return true;
            }
            if(isValid( m*m_n+n,((m-1)*m_n+n), path ))
            {
                if(mazeWalker(m-1, n, path))
                    return true;
            }
            if (isValid( m*m_n+n,(m*m_n+(n+1)), path ))
            {
                if(mazeWalker(m, n+1, path))
                    return true;
            }
            if(isValid( m*m_n+n,((m+1)*m_n+n), path ))
            {
                if(mazeWalker(m+1, n, path))
                    return true;
            }
            if (isValid( m*m_n+n,(m*m_n+(n-1)), path ))
            {
                if(mazeWalker(m, n-1, path))
                    return true;
            }

            // std::vector<int>::iterator it;
            // it = std::find(path.begin(), path.end(), m*m_m+n);
            path.erase(std::remove(path.begin(), path.end(), m*m_n+n), path.end());
            return false;
        }

        bool isValid(int current, int next, std::vector<int> & path)
        {
            std::pair <int, int> p;
            if(current < next)
                p = std::make_pair(current, next);
            else
                p = std::make_pair(next, current);
            
            bool valid = false;
            if (current >= 0 && current < m_m*m_n)
            {
                if (next >= 0 && next < m_m*m_n)
                {
                    std::vector<std::pair<int,int> >::iterator it1;
                    std::vector<int>::iterator it2;
                    it1 = std::find(brWalls.begin(), brWalls.end(), p);
                    it2 = std::find(path.begin(), path.end(), next);
                    if (it1 != brWalls.end() && it2 == path.end())
                    {
                        valid = true;
                    }
                }
            }
            return valid;
        }

        int getAdjRoom(int m, int n, int& m1, int&n1)
        {
            int dir = rand() % 4;
            do{
                if(dir == 0){
                    if (m-1 >= 0){
                        m1 = m-1;
                        n1 = n;
                        dir = 5;
                    }else  
                        dir++;
                }
                if(dir == 1){
                    if (n+1 < m_n){
                        m1 = m;
                        n1 = n+1;
                        dir = 5;
                    }else
                        dir++;
                }
                if (dir == 2){
                    if(m+1 < m_m){
                        m1 = m+1;
                        n1 = n;
                        dir = 5;
                    }
                    else
                        dir++;
                }
                if (dir == 3){
                    if(n-1 >= 0){
                        m1 = m;
                        n1 = n-1;
                        dir = 5;
                    }
                    else
                        dir = 0;
                }
            }while(dir != 5);
            return m1*m_n+n1;
        }

        bool oneRoot(){
            int j = find(0);
            for (int i = 0; i < m_m*m_n-1; i++){
                if(find(i) != j || (find(0) != find(m_m*m_n-1))){
                    return false;
                }
            }
            return true;
        }

        int getRands(int & randM, int & randN)
        {
            randM = rand() % m_m;
            randN = rand() % m_n;

            return randN + randM*m_n;
        }

};

#endif