#include<iostream>
#include<string>
#include<cstdlib>
#include<thread>
#include<chrono>
#include<queue>
using namespace std;

/*
  0
 / \
/\-/\
 v v
*/

struct Asteroid{
int x;
int y;
int speed;
char sign;
};

const int Max_X=120,Max_Y=40;
char image [Max_X][Max_Y];
bool not_game_over=true;

void refresh_screen(){

cout<<endl;
for(int counter=0;counter<Max_Y;counter++){
    for(int _counter=0;_counter<Max_X;_counter++){
        cout<<image[_counter][counter];
    }
    cout<<endl;
}
}



const int Max_ship_X=5,Max_ship_Y=4;
int x_ship=50,y_ship=30;
int ship_speed_left=5,ship_speed_right=5;

char ship [Max_ship_X][Max_ship_Y];

void initialise_ship(){
for(int counter=0;counter<Max_ship_X;counter++){
    for(int _counter=0;_counter<Max_ship_Y;_counter++){
        ship[counter][_counter]=' ';
    }
}
ship [2][0]='o';
ship [1][1]='/';
ship [3][1]=(char) 92;
ship [0][2]='/';
ship [1][2]=(char) 92;
ship [2][2]='-';
ship [3][2]='/';
ship [4][2]=(char) 92;
ship [0][3]=' ';
ship [1][3]='v';
ship [2][3]=' ';
ship [3][3]='v';
}

bool draw_ship_at(int x,int y){
if(x<1 or x+Max_ship_X>Max_X-2){
    return false;
}
for(int counter=0;counter<Max_ship_Y;counter++){
    for(int _counter=0;_counter<Max_ship_X;_counter++){
        image[x+_counter][y+counter]=ship[_counter][counter];
    }
}
return true;
}

void clear_ship(int x,int y){
for(int counter=0;counter<Max_ship_Y;counter++){
    for(int _counter=0;_counter<Max_ship_X;_counter++){
        image[x+_counter][y+counter]=' ';
    }
}
return;
}

void move_ship_to(bool is_left){
if(is_left){
    if(x_ship-ship_speed_left<1){
        return;
    }
    clear_ship(x_ship,y_ship);
    x_ship-=ship_speed_left;
    draw_ship_at(x_ship,y_ship);
}else{
    if(x_ship+Max_ship_X+ship_speed_right>Max_X-2){
        return;
    }
    clear_ship(x_ship,y_ship);
    x_ship+=ship_speed_right;
    draw_ship_at(x_ship,y_ship);
}
return;
}

queue<Asteroid> astreroid_queue;
int number_of_asteroids=0;
int Max_asteroid_x_size=5,Max_asteroid_y_size=5;





void generate_new_Asteroids(){
    cout<<"asdbfgsbfsbfkd"<<endl;
    Asteroid new_asteroid;
for(int i=1;i<Max_X-1;i++){
    if(rand()%100<2){
                cout<<"asdbfgsbfsbfkd"<<endl;
        for(int counter=0;counter<Max_asteroid_y_size;counter++){
           for(int _counter=0;_counter<Max_asteroid_x_size;_counter++){
               cout<<i<<" "<<_counter<<" "<<counter<<endl;
                if(_counter>0 and _counter<Max_X-1 and counter>0 and counter<Max_Y-1){
                    if(rand()%100>20*(abs(Max_asteroid_x_size/2-_counter)+abs(Max_asteroid_x_size/2-_counter))){
                            cout<<"yes";
                        new_asteroid.x=i+_counter;
                        new_asteroid.y=counter;
                        new_asteroid.speed=1;
                    cout<<"yes";
                        new_asteroid.sign=(char) (rand()%93 +33);
                        number_of_asteroids++;
                        cout<<new_asteroid.x<<" "<<new_asteroid.y<<" "<<new_asteroid.sign<<endl;
                        astreroid_queue.push(new_asteroid);
                        cout<<"yes";
                    }
                }
           }
        }
    }
}
return;
}







void update_asteroids(){
Asteroid current;
for(int counter=0;counter<number_of_asteroids;counter++){
current=astreroid_queue.front();
astreroid_queue.pop();
image[current.x][current.y]=' ';
current.y+=current.speed;
if(current.y<Max_ship_Y-1){
    image[current.x][current.y]=current.sign;
    astreroid_queue.push(current);
}else{
number_of_asteroids--;
}
}
return;
}


void Constant_refresh_Asteroids(){
while(not_game_over){
    this_thread::sleep_for(std::chrono::milliseconds(350));
    generate_new_Asteroids();
    update_asteroids();
}
return;
}




string entered;

void initialise_image_start(){
for(int counter=0;counter<Max_X;counter++){
    for(int _counter=0;_counter<Max_Y;_counter++){
        image[counter][_counter]=' ';
    }
}
for(int counter=1;counter<Max_X;counter++){
    image [counter][0]='_';
}
for(int counter=1;counter<Max_X;counter++){
    image [counter][Max_Y-1]='_';
}
for(int counter=1;counter<Max_Y;counter++){
    image [0][counter]='|';
}
for(int counter=1;counter<Max_X;counter++){
    image [Max_X-1][counter]='|';
}
initialise_ship();
draw_ship_at(x_ship,y_ship);
return;
}



int life=5;
char entered_;

void constant_refresh(){
while(not_game_over){
    refresh_screen();
    cout<<"asdbfgsbfsbfkd"<<endl;
    generate_new_Asteroids();
    cout<<"asdbfgsbfsbfkd"<<endl;
    update_asteroids();
    std::this_thread::sleep_for(std::chrono::milliseconds(350));
}
return;
}

int main(){
initialise_ship();
initialise_image_start();
thread th1(constant_refresh);
//thread th2(Constant_refresh_Asteroids);
while(not_game_over){
if(entered_=='a'){
    move_ship_to(true);
}
if(entered_=='d'){
    move_ship_to(false);
}
}
th1.join();
cout<<"Game Over!";
return 0;
}
