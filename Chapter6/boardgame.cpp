#include <iostream>
#include <cstring>
using namespace std ;


char map[22][22];
int ans = 0 ;
int n,m;


int d[4][3][2] = { {  {0,0}, {1,0}, {1,-1}  }, { {0,0},{1,0},{1,1} }, { {0,0},{1,1},{0,1} }, {{0,0},{0,1},{1,0}}  };

bool in_Range(int ypos, int xpos ){
    if ( ypos < 0 || xpos <0 || ypos >= m || xpos  >=n ) return false;
    return true ;
}



bool can_cover (int ypos, int xpos , int idx){
    bool ret= true ;
    for (int i = 0 ; i<3 ; i++ ){
        int ny = ypos + d[idx][i][0];
        int nx = xpos + d[idx][i][1];
        
        if (!in_Range(ny, nx) || map[ny][nx] == '#' ){
            ret= false;
            break ;
        }
    }
    return ret ;
}

void set_cover(int ypos,int xpos ,int idx, int tool ) { // idx : 0~3 , tool : 0 : uncover , 1: cover
    switch (tool) {
        case 0: // uncover
            for (int i = 0 ; i< 3; i ++){
                int ny = ypos + d[idx][i][0];
                int nx = xpos + d[idx][i][1];
                
                map[ny][nx] = '.';
            }
            
            
            break;
        case 1: // cover
            
            for (int i = 0 ; i< 3; i ++){
                int ny = ypos + d[idx][i][0];
                int nx = xpos + d[idx][i][1];
                
                map[ny][nx] = '#';
            }
            
            break;
            
        default:
            break;
    }
}


void solve( ){
    
    
    int first_y =-1, first_x = -1 ;
    for (int i = 0 ; i<m; i++){
        for (int j= 0 ;j<n; j++){
            if( map[i][j] == '.'){
                first_y = i , first_x = j;
                break;
            }
        }
        if ( first_x != -1 )break ;

    }
    
    if ( first_y == -1 ){
        ans ++ ;
        return ;
    }
    
    for (int i = 0 ; i<4; i++){
        if ( can_cover(first_y, first_x, i)){
            set_cover(first_y, first_x, i, 1);
            solve();
            set_cover(first_y, first_x, i, 0);
        }
    }
  
    
}


int main(){
   // freopen("input.txt", "r", stdin);
    int tc;
    cin >> tc;
    
    while (tc--){
        memset ( map ,0 , sizeof(map));
        ans = 0 ;
        scanf("%d%d",&m,&n); //m 이 y, n은 x
        
        for (int i = 0 ; i<m;  i++){
            cin >> map[i];
        }
        
        solve ();
        
        cout << ans <<endl;
    }
}

