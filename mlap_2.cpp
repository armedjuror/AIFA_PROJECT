

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

# define R 9 // rows;
# define C 11 // cols;
# define N 5   // no of bots;
#define T 6    // no of tasks;



typedef pair<int,int> Pair;
typedef pair<int, pair<int, int> > pPair;

struct bot{
    Pair start, end, cur;
};


bot bot_list[N];


struct task{
    Pair pick, delv;
    int to; // assigned to // 0-> not assigned, j->assigned to jth bot, -1 -> not Possible;
};

task task_list[T];
  

Pair grid[R][C];/// first:1->normal,0->blocked,2->ts/pickup/drop/ts, second: index of bot present(-1 -> none);


stack<Pair> Path;



bool is_valid(int i,int j)
{
    if(i < R && i > -1 && j < C && j > - 1) return true;
    else return false;
}

bool unblocked(int i, int j,int bot_j)
{
    if(grid[i][j].first == 0) return false;
    if(grid[i][j].first == 2) return true;
    if(grid[i][j].second == -1) return true;
    if(grid[i][j].second == bot_j) return true;  ///same bot present;
    return false;
}

bool is_dest(int i, int j, Pair dest)
{
    if(i == dest.first && j == dest.second) return true;
    return false;
}

int h_val(int i, int j, Pair dest)
{
    int x = dest.first, y = dest.second;
    int h = abs(i-x) + abs(j-y);  //min steps to reach;
    return h;
}


struct cell {
    
    int parent_i, parent_j;
    int f, g, h;
};

void get_path(cell cellDetails[][C], Pair dest)
{

    int row = dest.first;
    int col = dest.second;
 
 
    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
 
    Path.push(make_pair(row, col));
    
}
 


bool a_star(Pair src, Pair dest, int bot_j)
{
    
    if (is_dest(src.first, src.second, dest)  == true) {
        Path.push(src);
        return true;
    }
    
    bool closedList[R][C];
    memset(closedList, false, sizeof(closedList));
    
    cell cellDetails[R][C];
    int i, j;
 
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            cellDetails[i][j].f = INT_MAX;
            cellDetails[i][j].g = INT_MAX;
            cellDetails[i][j].h = INT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0;
    cellDetails[i][j].g = 0;
    cellDetails[i][j].h = 0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    
    
    set<pPair> openList;
    
    openList.insert(make_pair(0, make_pair(i, j)));
    
    bool foundDest = false;
    
    while(!openList.empty())
    {
        pPair p = *openList.begin();
        openList.erase(openList.begin());
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;
        
    
        int gNew, hNew, fNew;
        // generatin the 4 children of current node
        // (i-1,j),(i+1,j),(i,j-1) & (i,j+1);
        
        if (is_valid(i - 1, j) == true) {
                // If the destination cell is the same as the
                // current successor
                if (is_dest(i - 1, j, dest) == true) {
                    // Set the Parent of the destination cell
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                    
                    get_path(cellDetails, dest);
                    foundDest = true;
                    return true;
                }
        else if (closedList[i - 1][j] == false && unblocked(i - 1, j,bot_j) == true) { //not alredy in close;
                    gNew = cellDetails[i][j].g + 1;
                    hNew = h_val(i - 1, j, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[i - 1][j].f == INT_MAX  // not alredy in open or have better cost than previous;
                        || cellDetails[i - 1][j].f > fNew) {  //update cost;
                        openList.insert(make_pair(
                            fNew, make_pair(i - 1, j)));
     
                        // Update the details of this cell
                        cellDetails[i - 1][j].f = fNew;
                        cellDetails[i - 1][j].g = gNew;
                        cellDetails[i - 1][j].h = hNew;
                        cellDetails[i - 1][j].parent_i = i;
                        cellDetails[i - 1][j].parent_j = j;
                    }
                }
            }
        
        
        
        // second (i+1,j);
        
        if (is_valid(i + 1, j) == true) {
                
                if (is_dest(i + 1, j, dest) == true) {
                    
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                    
                    get_path(cellDetails, dest);
                    foundDest = true;
                    return true;
                }
                
                else if (closedList[i + 1][j] == false
                         && unblocked( i + 1, j,bot_j)
                                == true) {
                    gNew = cellDetails[i][j].g + 1;
                    hNew = h_val(i + 1, j, dest);
                    fNew = gNew + hNew;
     
    
                    if (cellDetails[i + 1][j].f == INT_MAX
                        || cellDetails[i + 1][j].f > fNew) {
                        openList.insert(make_pair(
                            fNew, make_pair(i + 1, j)));
                        
                        cellDetails[i + 1][j].f = fNew;
                        cellDetails[i + 1][j].g = gNew;
                        cellDetails[i + 1][j].h = hNew;
                        cellDetails[i + 1][j].parent_i = i;
                        cellDetails[i + 1][j].parent_j = j;
                    }
                }
            }
            
        // third successor (i, j + 1)
        
        if (is_valid(i, j + 1) == true) {
    
                if (is_dest(i, j + 1, dest) == true) {
                    
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                    
                    get_path(cellDetails,dest);
                    foundDest = true;
                    return true;
                }
     
                
                else if (closedList[i][j + 1] == false
                         && unblocked( i, j + 1,bot_j)
                                == true) {
                    gNew = cellDetails[i][j].g + 1;
                    hNew = h_val(i, j + 1, dest);
                    fNew = gNew + hNew;
     
                    
                    if (cellDetails[i][j + 1].f == INT_MAX
                        || cellDetails[i][j + 1].f > fNew) {
                        openList.insert(make_pair(
                            fNew, make_pair(i, j + 1)));
     
                        
                        cellDetails[i][j + 1].f = fNew;
                        cellDetails[i][j + 1].g = gNew;
                        cellDetails[i][j + 1].h = hNew;
                        cellDetails[i][j + 1].parent_i = i;
                        cellDetails[i][j + 1].parent_j = j;
                    }
                }
            }
        
        // fourth (i, j-1);
        if (is_valid(i, j - 1) == true) {
                
                if (is_dest(i, j - 1, dest) == true) {
                    
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                    
                    get_path(cellDetails, dest);
                    foundDest = true;
                    return true;
                }
     
                
                else if (closedList[i][j - 1] == false
                         && unblocked(i, j - 1,bot_j)
                                == true) {
                    gNew = cellDetails[i][j].g + 1;
                    hNew = h_val(i, j - 1, dest);
                    fNew = gNew + hNew;
     
                    
                    if (cellDetails[i][j - 1].f == INT_MAX
                        || cellDetails[i][j - 1].f > fNew) {
                        openList.insert(make_pair(
                            fNew, make_pair(i, j - 1)));
     
    
                        cellDetails[i][j - 1].f = fNew;
                        cellDetails[i][j - 1].g = gNew;
                        cellDetails[i][j - 1].h = hNew;
                        cellDetails[i][j - 1].parent_i = i;
                        cellDetails[i][j - 1].parent_j = j;
                    }
                }
            }
    }
    
    return foundDest;
}







int main()
{

    Pair src,dest,pickup, drop,p,q,cur_pos,min_task;
    int min_idx, min_cost,cost,x,y,a,b;
    vector<Pair> tmp_path;

    
    int in_grid[R][C]
        = { { 2, 0, 2, 1, 1, 1, 0, 1, 1, 1,1 },
            { 1, 2, 1, 0, 1, 2, 1, 2, 1, 1,0 },
            { 1, 1, 1, 0, 2, 1, 0, 1, 0, 1,1 },
            { 1, 0, 1, 2, 1, 0, 0, 2, 0, 1,1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0,1 },
            { 1, 0, 1, 1, 1, 2, 0, 1, 0, 0,1 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1,1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1,1 },
            { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1,1 } };
    
    for(int i = 0; i < R; ++i)
    {
        for(int j = 0; j < C; ++j) 
        {
            grid[i][j].first = in_grid[i][j];
            grid[i][j].second = -1;
        }    
    }
    //testing;
    //if(unblocked(8,1,1)) cout<<"yes\n";
    
    
    
    int in_task[T][2][2] //picup,delv;
        ={{{0,0},{1,1}},
          {{0,0},{2,4}},
          {{0,0},{3,7}},
          {{0,0},{1,7}},
          {{5,5},{3,3}},
          {{0,2},{1,5}}}; 
    
    for(int i = 0; i < T; ++i)
    {
        int px = in_task[i][0][0];
        int py = in_task[i][0][1];
        int dx = in_task[i][1][0];
        int dy = in_task[i][1][1];
        task_list[i].pick = make_pair(px,py);
        task_list[i].delv = make_pair(dx,dy);
        task_list[i].to = 0;  //not yet assigned;
    }
    
    
    
    int in_bots[N][2][2] //start,end;
    ={{{8,0},{1,2}},
      {{7,0},{2,4}},
      {{1,0},{3,7}},
      {{0,5},{1,7}},
      {{3,0},{3,3}}};
    
    for(int i = 0; i < N; ++i)
    {
        int ix = in_bots[i][0][0];
        int iy = in_bots[i][0][1];
        int fx = in_bots[i][1][0];
        int fy = in_bots[i][1][1];
        bot_list[i].start = make_pair(ix,iy);
        bot_list[i].end = make_pair(fx,fy);
        bot_list[i].cur = bot_list[i].start;
    
        
        x = bot_list[i].cur.first;
        y = bot_list[i].cur.second;
        grid[x][y].second = i;
        
    }
    
    
    
    
    
    
    int t =  0;  //time steps elapsed;

    for(int i = 0; i < T; ++i)
    {
        
        if(task_list[i].to != 0) continue; //alredy done or not Possible;
        pickup = task_list[i].pick;
        drop = task_list[i].delv;
        min_cost = INT_MAX;
        min_idx = -1;
        
        for(int j = 0; j < N; ++j)
        {
            cur_pos = bot_list[j].cur;
            cost = 0;
            if(a_star(cur_pos,pickup,j))
            {
                cost += Path.size() - 1; // alredy at cur_pos;
                while(!Path.empty()) Path.pop();
                
                if(cost < min_cost)
                {
                    if(a_star(pickup,drop,j))
                    {
                        cost += Path.size() - 1;
                        while(!Path.empty()) Path.pop();
                        if(cost < min_cost)
                        {
                            min_cost = cost;
                            min_idx = j;
                        }
                    }
                }
                
            }
            
        }
        if(min_idx == -1) printf("task:%d not Possible\n",i); // no Possible path;
        else
        {
            task_list[i].to = min_idx;
            t += min_cost;
            printf("task:%d by bot:%d delivered at t = %d\nPath: ",i,min_idx,t);
            a_star(bot_list[min_idx].cur,pickup,min_idx);
            while(!Path.empty())
            {
                p = Path.top();
                Path.pop();
                printf("->(%d,%d) ",p.first,p.second);
            }
            
            a_star(pickup,drop,min_idx);
            Path.pop();
            while(!Path.empty())
            {
                p = Path.top();
                Path.pop();
                printf("->(%d,%d) ",p.first,p.second);
            }
            printf("\n");
            p = bot_list[min_idx].cur;
            bot_list[min_idx].cur = drop;
            grid[p.first][p.second].second = -1;
            grid[drop.first][drop.second].second = min_idx;
            
        }
        
    }
    
    // move all bots to their respevtive end points;
    for(int i = 0; i < N; ++i)
    {
        src = bot_list[i].cur;
        dest = bot_list[i].end;
        
        a_star(src,dest,i);
        cost = Path.size() - 1;
        t += cost;
        printf("bot:%d reached home at t = %d\nPath_home_%d:",i,t,i);
        while(!Path.empty())
        {
            p = Path.top();
            Path.pop();
            printf("->(%d,%d) ",p.first,p.second);
        }
        
    }
    
    return 0;
}


