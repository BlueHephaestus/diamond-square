#include "dsquareConfig.h"
#include <QApplication>
#include <QtWidgets>
#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QColor>

#include <array>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

//The dimensions of the matrix. Has to be a number 2^n + 1, and currently this program only supports up to 513x513.
//You also have to do a regex or a find/replace to replace all instances of 513 and actually get it working. 
int matrix_len = 513;

//The initial magnitude of the random offset
double rand_max = 1;

//The rate at which the magnitude of the random offset decreases every iteration. My default is 50%, or .5
double rand_decrease_rate = .5;

//The initial corner value for all 4 corners. Feel free to modify the corners to be different on lines 257-260
double corner_init_value = .2;

//Initial min and max for the random generator
float rand_init_min = -1;
float rand_init_max = 1;

//Inits
int compare_interval = (matrix_len-1);
int point_interval = (matrix_len-1)/2;
float init_point;
float hor_point;
float vert_point;
float diag_point;

float new_point;
float new_vert_point;
float new_hor_point;

std::vector<std::vector<int>> diamond_step_points;
std::vector<std::vector<int>> square_step_points;

std::vector<float> square_step_adj_points;
float square_step_adj_points_sum;
double rand_offset;
double rand_init_value;
double cell;
long int input_seed;
unsigned char input_seed_arr[8];

float shade;

std::array<std::array<float, 513>, 513> empty_matrix(std::array<std::array<float, 513>, 513> matrix){
  for(int x=0;x<matrix.size();x++){
    matrix[x].fill(0.0);
  }
  return matrix;
}

void print_matrix(std::array<std::array<float, 513>, 513> matrix){
  for(int x=0;x<matrix.size();x++){
    for(int y=0;y<matrix[x].size();y++){
      printf("%f ", matrix[x][y]);
    }
    printf("\n");
  }
  printf("\n");
}

float get_matrix_avg(std::array<std::array<float, 513>, 513> matrix){
  float sum;
  for(int x=0;x<matrix.size();x++){
    for(int y=0;y<matrix[x].size();y++){
      sum += matrix[x][y];
    }
  }
  return sum/(matrix_len*matrix_len);
}

void display_matrix(std::array<std::array<float, 513>, 513> matrix){

  //Apparently only need to use * notation when using it, not doing actions ON it
  QMainWindow *window = new QMainWindow;
  QWidget *widget = new QWidget;
  QHBoxLayout *layout = new QHBoxLayout(widget);
  QLabel *label = new QLabel();
  QFont *font = new QFont("Courier");
  QPixmap *pix = new QPixmap(513,513);

  pix->fill(Qt::white);
  QPainter *painter = new QPainter(pix);
  //Where the magic happens

  //matrix_extrema = get_matrix_extrema(matrix);
  float min = 0;
  float max = 0;
  for(int x=0;x<matrix.size();x++){
    for(int y=0;y<matrix[x].size();y++){
      if (matrix[x][y] < min){
        min = matrix[x][y];
      }else if(matrix[x][y] > max){
        max = matrix[x][y];
      }
    }
  }
  float avg = get_matrix_avg(matrix);
  printf("Max:%f\nMin:%f\nAvg:%f\n", max, min, avg);
  for(int x=0;x<matrix.size();x++){
    for(int y=0;y<matrix[x].size();y++){
      //various stuff to display
      //shade = 255-((pow(matrix[x][y]-4, 3))*(-4.5) + 100);
      //shade = 255-((matrix[x][y]/max)*255);
      //shade = 255-((1+matrix[x][y])*100);
      //shade = 255-255*((matrix[x][y]-min)/(max-min));
      cell = matrix[x][y];
      //shade = ((cell*.5)+.5)*255;
      /*
      if (cell < 0){
        shade = cell*-255;
        painter->setPen(QColor(shade,255,255,255));
        painter->setBrush(QColor(shade,255,255,255));
      }else{
        shade = cell*255;
        painter->setPen(QColor(255,255,shade,255));
        painter->setBrush(QColor(255,255,shade,255));
      }
      */
      if (cell < -.9){
        painter->setPen(QColor(0,0,21,255));
        painter->setBrush(QColor(0,0,21,255));
      }else if(cell < -.8){
        painter->setPen(QColor(0,0,64,255));
        painter->setBrush(QColor(0,0,64,255));
      }else if(cell < -.7){
        painter->setPen(QColor(0,0,106,255));
        painter->setBrush(QColor(0,0,106,255));
      }else if(cell < -.6){
        painter->setPen(QColor(0,0,149,255));
        painter->setBrush(QColor(0,0,149,255));
      }else if(cell < -.5){
        painter->setPen(QColor(0,0,212,255));
        painter->setBrush(QColor(0,0,212,255));
      }else if(cell < -.4){
        painter->setPen(QColor(0,97,159,255));
        painter->setBrush(QColor(0,97,159,255));
      }else if(cell < -.3){
        painter->setPen(QColor(0,114,187,255));
        painter->setBrush(QColor(0,114,187,255));
      }else if(cell < -.2){
        painter->setPen(QColor(0,178,183,255));
        painter->setBrush(QColor(0,178,183,255));
      }else if(cell < -.1){
        painter->setPen(QColor(64,197,137,255));
        painter->setBrush(QColor(64,197,137,255));
      }else if(cell < 0){
        painter->setPen(QColor(149,223,76,255));
        painter->setBrush(QColor(149,223,76,255));
      }else if(cell < .1){
        painter->setPen(QColor(255,255,0,255));
        painter->setBrush(QColor(255,255,0,255));
      }else if(cell < .2){
        painter->setPen(QColor(191,255,0,255));
        painter->setBrush(QColor(191,255,0,255));
      }else if(cell < .3){
        painter->setPen(QColor(149,255,0,255));
        painter->setBrush(QColor(149,255,0,255));
      }else if(cell < .4){
        painter->setPen(QColor(106,255,0,255));
        painter->setBrush(QColor(106,255,0,255));
      }else if(cell < .5){
        painter->setPen(QColor(43,255,0,255));
        painter->setBrush(QColor(43,255,0,255));
      }else if(cell < .6){
        painter->setPen(QColor(0,255,0,255));
        painter->setBrush(QColor(0,255,0,255));
      }else if(cell < .7){
        painter->setPen(QColor(140,197,63,255));
        painter->setBrush(QColor(140,197,63,255));
      }else if(cell < .8){
        painter->setPen(QColor(130,139,117,255));
        painter->setBrush(QColor(130,139,117,255));
      }else if(cell < .9){
        painter->setPen(QColor(128,128,128,255));
        painter->setBrush(QColor(128,128,128,255));
      }else{
        painter->setPen(QColor(255,255,255,255));
        painter->setBrush(QColor(255,255,255,255));
      }
      
      //painter->setPen(QColor(255-shade,255-shade,shade,255));
      //painter->setBrush(QColor(255-shade,255-shade,shade,255));
      painter->drawRect(y*2,x*2,2,2);
      //painter->drawRect(y,x,1,1);
    }
  }
  //painter->setBrush(Qt::black);

  window->setWindowTitle("Diamond Square Testing");
  window->resize(513,513);
  window->setCentralWidget(widget);

  layout->addWidget(label);
  label->setPixmap(*pix);
  window->show();
}

void print_vectors(std::vector<std::vector<int>> vector, std::array<std::array<float, 513>, 513> matrix){
  //vector[[x, y][x, y]]
  for(int i=0;i<vector.size();i++){
    int x = vector[i][0];
    int y = vector[i][1];
    printf("%f \n", matrix[x][y]);
  }
  printf("\n");
}

int get_vector_sum(std::vector<int> vector){
  int sum = 0;
  for(int i=0;i<vector.size();i++){
    sum+=i;
  }
  return sum;
}

double get_rand_int(float min, float max, std::mt19937 rgen){
  std::uniform_real_distribution<double> idist(min,max);
  return idist(rgen);
}

int main(int argc, char **argv){

  QApplication app (argc, argv);

  std::array<std::array<float, 513>, 513> grid;
  grid = empty_matrix(grid);
  //
  /*
  From wikipedia:
  The diamond step. For each square in the array, set the midpoint of that square to be the average of the four corner points plus a random value.

  The square step. For each diamond in the array, set the midpoint of that diamond to be the average of the four corner points plus a random value.

  At each iteration, the magnitude of the random value should be reduced.
  */

  input_seed = std::hash<std::string>{}(argv[1]);
  std::random_device rseed;
  //std::mt19937 rgen(rseed()); // mersenne_twister
  //std::mt19937 rgen(420); // mersenne_twister
  std::mt19937 rgen(input_seed); // mersenne_twister
  std::uniform_real_distribution<double> idist(rand_init_min,rand_init_max);
  
  grid[0][0] = corner_init_value;
  grid[matrix_len-1][0] = corner_init_value;
  grid[0][matrix_len-1] = corner_init_value;
  grid[matrix_len-1][matrix_len-1] = corner_init_value;
  /*
  rand_init_value = idist(rgen);
  grid[0][0] = rand_init_value;
  rand_init_value = idist(rgen);
  grid[matrix_len-1][0] = rand_init_value;
  rand_init_value = idist(rgen);
  grid[0][matrix_len-1] = rand_init_value;
  rand_init_value = idist(rgen);
  grid[matrix_len-1][matrix_len-1] = rand_init_value;
  */
  /*
  grid[0][0] = 0.001;
  grid[matrix_len-1][0] = 1;
  grid[0][matrix_len-1] = 1;
  grid[matrix_len-1][matrix_len-1] = 90;
  */


  int count = 0;
  while(true){
    diamond_step_points.clear();
    square_step_points.clear();
    square_step_adj_points.clear();
    square_step_adj_points_sum = 0;

    for(int x=0;x<grid.size()-1;x++){
      for(int y=0;y<grid[x].size()-1;y++){
        if (grid[x][y] != 0){
          //Only add those that are not == len-1 on x and y
          diamond_step_points.push_back({x,y});
        }
      }
    }

    for (int i=0;i<diamond_step_points.size();i++){
      int x = diamond_step_points[i][0];
      int y = diamond_step_points[i][1];
      init_point = grid[x][y];
      hor_point = grid[x+compare_interval][y];
      vert_point = grid[x][y+compare_interval];
      diag_point = grid[x+compare_interval][y+compare_interval];

      //rand_offset = idist(rgen);
      rand_offset *= rand_max;
      //rand_offset = get_rand_int(-.5*rand_max, .5*rand_max, rgen);
      new_point = (init_point + hor_point + vert_point + diag_point)/4;// + rand_offset;
      grid[x+point_interval][y+point_interval] = new_point;

    }

    for(int x=0;x<grid.size()-1;x++){
      for(int y=0;y<grid[x].size()-1;y++){
        if (grid[x][y] != 0){
          //Only add those that are not == len-1 on x and y
          square_step_points.push_back({x,y});
        }
      }
    }
        
    for (int i=0;i<square_step_points.size();i++){
      int x = square_step_points[i][0];
      int y = square_step_points[i][1];

      square_step_adj_points.clear();
      square_step_adj_points_sum = 0;
      //new_points are just grid[x+point_interval][y] and grid[x][y+point_interval];
      init_point = grid[x][y];
      square_step_adj_points.push_back(init_point);

      //first we get the new vertical point
      if (y+compare_interval < matrix_len){
        square_step_adj_points.push_back(grid[x][y+compare_interval]);
      }
      if ((x+point_interval < matrix_len) && (y+point_interval < matrix_len)){
        square_step_adj_points.push_back(grid[x+point_interval][y+point_interval]);
      }
      if ((x-point_interval >= 0) && (y+point_interval < matrix_len)){
        square_step_adj_points.push_back(grid[x-point_interval][y+point_interval]);
      }
      for (int square_step_adj_point=0;square_step_adj_point<square_step_adj_points.size();square_step_adj_point++){
        square_step_adj_points_sum += square_step_adj_points[square_step_adj_point];
      }
      rand_offset = idist(rgen);
      rand_offset *= rand_max;
      //rand_offset = get_rand_int(-.5*rand_max, .5*rand_max, rgen);
      //rand_offset = .5;
      new_vert_point = square_step_adj_points_sum/square_step_adj_points.size() + rand_offset;
      grid[x][y+point_interval] = new_vert_point;
      square_step_adj_points.clear();
      square_step_adj_points_sum = 0;
      square_step_adj_points.push_back(init_point);

      //now we get the new horizontal point
      if (x+compare_interval < matrix_len){
        square_step_adj_points.push_back(grid[x+compare_interval][y]);
      }
      if ((x+point_interval < matrix_len) && (y-point_interval >= 0)){
        square_step_adj_points.push_back(grid[x+point_interval][y-point_interval]);
      }
      if ((x+point_interval < matrix_len) && (y+point_interval < matrix_len)){
        square_step_adj_points.push_back(grid[x+point_interval][y+point_interval]);
      }
      for (int square_step_adj_point=0;square_step_adj_point<square_step_adj_points.size();square_step_adj_point++){
        square_step_adj_points_sum += square_step_adj_points[square_step_adj_point];
      }
      rand_offset = idist(rgen);
      rand_offset *= rand_max;//rand_max;
      new_hor_point = square_step_adj_points_sum/square_step_adj_points.size() + rand_offset;
      grid[x+point_interval][y] = new_hor_point;
      square_step_adj_points.clear();

    }

    if (point_interval == 1){
      //print_matrix(grid);
      display_matrix(grid);
      return app.exec();
    }
    //decrease random value max
    rand_max = rand_max * rand_decrease_rate;
    //print_matrix(grid);

    //decrease the other intervals
    compare_interval = compare_interval/2;
    point_interval = point_interval/2;
    count++;
  }
}
