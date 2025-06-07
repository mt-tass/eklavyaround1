// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// //analyzing input file suggested lsa threshold = 0.8+0.3/2 = 0.55 and ir sensor threshold = 80
// #define LsaThresh 0.55
// #define IRThresh 80
// typedef enum Direction{NORTH,EAST,SOUTH,WEST};
// const char* directionString(Direction dir) {
//     switch (dir) {
//         case NORTH: return "North";
//         case EAST:  return "East";
//         case SOUTH: return "South";
//         case WEST:  return "West";
//         default:    return "invalid";
//     }
// }

// void findpath(int lsa[5] , int ir , FILE *fout , Direction* dir){
//     if(ir == 1){
//         fprintf(fout,"U-TURN        MINE DETECTED       %S\n", directionString(*dir));
//         *dir = (*dir+2)%4;
//         return;
//     }
//     if(ir==0){
//         if(lsa[0]==0 && lsa[1]==1 && lsa[2]==1 && lsa[3]==1 && lsa[4]==0){
//             fprintf(fout,"STRAIGHT        STRAIGHT       %S\n", directionString(*dir));
//         }
//     }
// }
// int main(){
//     //reading input files
//     FILE *fin = fopen("LSA_IR.txt","r");
//     FILE *fout = fopen("output.txt","w");
//     char line[500]; //every line of input file

//     fprintf(fout,"START\n"); 
//     //reading lines
//     int lsa[5] , ir;
//     while(fgets(line,sizeof(line),fin)){
//         float LSAraw[5];
//         int IRraw;
//         sscanf(line ,"%f, %f, %f, %f, %f , %d",&LSAraw[0],&LSAraw[1],&LSAraw[2],&LSAraw[3],&LSAraw[4],&IRraw);
//         for(int i = 0 ; i < 5 ; i++){
//             if(LSAraw[i] > LsaThresh){
//                 lsa[i] = 1;
//             }
//             else{
//                 lsa[i]=0;
//             }

//         }
//         if(IRraw > IRThresh){
//             ir=1;
//         }
//         else{
//             ir=0;
//         }

//     }
// }
#include <stdio.h>
#include <stdlib.h>

#define MAZE_SIZE 20
#define SAFE 0
#define MINE 1
#define WALL 2

typedef struct {
    int x, y;
} Point;

int maze[MAZE_SIZE][MAZE_SIZE];
int visited[MAZE_SIZE][MAZE_SIZE];
Point parent[MAZE_SIZE][MAZE_SIZE];

int dx[4] = {0, 1, 0, -1}; // right, down, left, up
int dy[4] = {1, 0, -1, 0};

int in_bounds(int x, int y) {
    return (x >= 0 && x < MAZE_SIZE && y >= 0 && y < MAZE_SIZE);
}

int get_cell_type(float sensors[5], float ir_sensor) {
    float avg_line = 0.0;
    for (int i = 0; i < 5; i++) avg_line += sensors[i];
    avg_line /= 5.0;

    // Basic thresholds, tune as needed
    if (ir_sensor < 10) return MINE;      // mine detected by IR sensor
    else if (avg_line > 0.8) return SAFE; // safe path (line detected strongly)
    else return WALL;                      // wall or no line detected
}

void print_path(FILE *fp, Point end) {
    Point path[MAZE_SIZE * MAZE_SIZE];
    int length = 0;
    Point cur = end;

    // Backtrack from end to start
    while (!(cur.x == 0 && cur.y == 0)) {
        path[length++] = cur;
        cur = parent[cur.x][cur.y];
    }
    path[length++] = (Point){0, 0};

    // Print path in reverse (start to end)
    for (int i = length - 1; i >= 0; i--) {
        fprintf(fp, "(%d, %d)\n", path[i].x, path[i].y);
    }
}

int bfs(FILE *fp) {
    Point queue[MAZE_SIZE * MAZE_SIZE];
    int front = 0, rear = 0;

    queue[rear++] = (Point){0, 0};
    visited[0][0] = 1;
    parent[0][0] = (Point){-1, -1};

    while (front < rear) {
        Point curr = queue[front++];

        if (curr.x == MAZE_SIZE - 1 && curr.y == MAZE_SIZE - 1) {
            // Reached end, print path
            fprintf(fp, "Path from START to END:\n");
            print_path(fp, curr);
            return 1;
        }

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (in_bounds(nx, ny) && !visited[nx][ny] && maze[nx][ny] == SAFE) {
                visited[nx][ny] = 1;
                parent[nx][ny] = curr;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }

    fprintf(fp, "No safe path found.\n");
    return 0;
}

int main() {
    FILE *fp = fopen("LSA_IR.txt", "r");
    if (!fp) {
        printf("Error opening input file\n");
        return 1;
    }

    char line[256];
    int line_count = 0;

    // Initialize maze and visited
    for (int i = 0; i < MAZE_SIZE; i++)
        for (int j = 0; j < MAZE_SIZE; j++) {
            maze[i][j] = WALL;
            visited[i][j] = 0;
            parent[i][j] = (Point){-1, -1};
        }

    while (fgets(line, sizeof(line), fp) != NULL) {
        float sensors[5], ir_sensor;
        if (sscanf(line, "%f, %f, %f, %f, %f , %f",
                   &sensors[0], &sensors[1], &sensors[2], &sensors[3], &sensors[4], &ir_sensor) == 6) {
            int x = line_count / MAZE_SIZE;
            int y = line_count % MAZE_SIZE;

            if (x < MAZE_SIZE && y < MAZE_SIZE) {
                maze[x][y] = get_cell_type(sensors, ir_sensor);
            }
            line_count++;
        }
    }

    fclose(fp);

    FILE *outfp = fopen("path_output.txt", "w");
    if (!outfp) {
        printf("Error opening output file\n");
        return 1;
    }

    if (!bfs(outfp)) {
        printf("No safe path found.\n");
    } else {
        printf("Path written to path_output.txt\n");
    }

    fclose(outfp);

    return 0;
}
