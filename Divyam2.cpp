#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>
#include <string>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;
const int width(25);
const int height(25);

int headx, heady;
const int size = height*width;
int map[size];
int dirn;
int length = 3;
int lvl;
int s1;
int num1=0, num2=0;

void run();
void getmap();
char getvalue(int );
void getfood();
void print();
void direction(char);
void update();
void cls();
void move(int,int);
void getlvl();
void getsleep();
void info();
void opsw();
void geths();
void inst();
void getback();
void getinp();
void getsp();

int main(){
	//for random food generation
	unsigned seed = time(NULL);
	srand(seed);
	
	cout<<"\t\t\tWELCOME TO SNAKE X.0"<<endl;
	
	//introduction options
	info();
	return 0;
}
	
//boolean to check game running status
bool running;
	
//MAIN MENU
void info(){
	cout<<"1) Play Now"<<endl; //begins gameplay
	cout<<"2) Leader Board"<<endl;  //Shows the top 5 scores ever
	cout<<"3) Instructions"<<endl;  //for the usrers benefit the controls and instructions have been mentioned here
	cout<<"4) Exit"<<endl; //Exit the program 
	
	//switch statement
	opsw();

}

//switch statement
void opsw(){
	
	int x;
	cin>>x;
	
	//CLEAR SCREEN
	cls();
	
	switch(x){
		case 1:
			run();  //main game function
			break;
		case 2:
			geths();  //contains the high score list
			break;
		case 3:
			inst();  //contains the set of instructions 
			break;
		case 4:
			exit(0);
			break;
	}

}

//INSTRUCTIONS
void inst(){
	cout<<"\t\t\t GENERAL INSTRUCTIONS"<<endl;
	cout<<"\n\n\'0\' - food [snakes length will increase]"<<endl;
	cout<<"\'W\' - special particle [snakes length will increase by 3]"<<endl;
	cout<<"\'X\' - boundary [hit this and the game is over]"<<endl;
	cout<<"\n\t\t\t CONTROLS"<<endl;
	cout<<"1) W/arrow up - moves snake up"<<endl;
	cout<<"2) A/left arrow - moves snake left"<<endl;
	cout<<"3) S/down arrow - moves snake down"<<endl;
	cout<<"4) D/right arrow - moves snake right"<<endl;
	cout<<"\n\nPress Enter to return to the Main Menu"<<endl;
	getch();
	//BACK TO MAIN MENU
	getback();	

}

void getback(){
	
	//CIN.GET() IS ABLE TO DETECT THE ENTER KEY
	if(cin.get() == '\n'){
		//clear screen
		cls();
		
		//BACK TO MAIN MENU
		info();
	}
	
	
}

//DISPLAY HIGHSCORERS LIST
void geths(){
	int score;
	string name;
	int id;
	ifstream FILE("High Score.txt");
	// prints the HIGH SCORE list
	while(FILE>>id>>name>>score){
		cout<<id<<"  "<<name<<"  "<<score<<endl;
		
	}
 	
 	cout<<"Press Enter to return to the MAIN MENU"<<endl;
 	getch();
 	getback();
}

	
	//MAIN GAME FUNCTION
void run(){
	
	//choose the level of games difficulty
	getlvl();
	
	//intialize the map
	getmap();
	
	running = true;
	
	while(running){
		
		getsp();
	
		//check user input and change direction accordingly
		if(kbhit()){
		
			direction(getch());
		}
		
		//update the map
		update();
	
		//clear the screen
		cls();
	
		//print the map
		print();
	 
		//make the program stop a bit for the users benefit
		getsleep();
		
		}
		
		s1 = length;
		cout<<"Game Over!!!"<<endl<<"Your score is:"<<s1<<endl;
		getinp();
		getch();
		
}


//initialize map
void getmap(){

		headx= width/2;
		heady= height/2;
		
		//place the left and right boundaries
		for(int x=0; x<width; x++){
			map[x]= -1;
			map[x + (width -1)*height] = -1;
		}
		
		//places the top and bottom boundaries
		for(int y=0; y<height; y++){
		
			map[y*width]= -1;
			map[(height -1) + y*width]= -1;
		}
		
		//generate first food
		getfood();
	
}

//prints the map 
void print(){

	for(int x=0; x<width; x++){
		for(int y=0; y<height; y++){
			cout<<getvalue(map[x + y*width]);
		}
	cout<<endl;
	}
}

char getvalue(int value){

	//printing the constituents
	if(value >0){
		return 'o';
	}
	switch(value){
		case -1: return 'X';
		case -2: return '0';
		case -3: return 'W';
	}
}

void direction(char dir){

	//switch for w   a   s  d input to output
	switch(dir){
		case 'w':
			if(dirn != 8) dirn =1;
			break;
		case 'a':
			if(dirn != 7) dirn= 2;
			break;
		case 'd':
			if (dirn != 6) dirn= 3;
			break;
		case 's':
			if(dirn != 5) dirn= 4;
			break;
		case KEY_UP:
			if(dirn!= 8)dirn=1;
			break;
		case KEY_DOWN:
			if(dirn != 5)dirn = 4;
			break;
		case KEY_LEFT:
			if(dirn!= 7)dirn = 2;
			break;
		case KEY_RIGHT:
			if(dirn != 6)dirn = 3;
			break;
	}

}

void cls(){
	system("CLS");
}

void update(){
	
	//the move function defined later will help in modulating the snakes head position 
	//using the integer values from the switch statement of the following funtion
	switch(dirn){
		case 1:
			move(-1,0);
			break;
		case 2:
			move(0,-1);
			break;
		case 3:
			move(0,1);
			break;
		case 4:
			move(1, 0);
			break;
	}
	
	//to maintain the integrity of the game
	for(int i = 0; i<size; i++){
	
		if(map[i]>0) map[i]--;
	}
	
}

//px and py are the values to be added to defined coordinate system
void move(int px, int py){
	
	//nx and ny WILL BE THE NEW HEAD POSITIONS OF THE SNAKE
	int nx, ny;
	
	nx = headx + px;
	ny = heady + py;
	
	//CHECK WHETHER THE SNAKE EATS FOOD OR NOT	
	if(map[nx + ny*width]==-2){
		length++;
		
		//GENERATE NEW FOOD PARTICLE
		getfood();
	}
	
	if(map[nx + ny*width]==-3){
		length = length +3;
		
	}
	
	//IF SNAKE HITS THE WALL
	else if(map[nx + ny*width]== -1){
		running = false;
	}
	
	//IF SNAKE HITS ITSELF
	else if(map[nx + ny*width]>0){
		running = false;
	}
	//INC LENGTH BY 1
	headx = nx;
	heady = ny;
	map[headx + heady*width] = length+1;
}

//generate food
void getfood(){
	int x = 0;
	int y = 0;
	
	//random generation
	do{
		x = rand()%width;
		y = rand()%height;
	}
	//will check if space is empty or not
	while(map[x + y*width] != 0);
	
	
	map[x + y*width]= -2;
	
	
}

void getlvl(){

	cout<<"Choose the level of difficulty:"<<endl;
	cout<<"1) Easy"<<endl;  //sleep=100 
	cout<<"2) Moderate"<<endl;  //sleep = 50
	cout<<"3) Hard"<<endl;  //sleep = 5
	cin>>lvl;
	
}

void getsleep(){

	switch(lvl){
		case 1:
			_sleep(100);
			break;
		case 2:
			_sleep(50);
			break;
		case 3:
			_sleep(5);
			break;
	
	}
}

//SAVES HIGH SCORES IN THE MAIN DATABASE
void getinp(){
	int score;
	string name; 
	int id;
	
	ifstream FILE("High Score.txt");

	cout<<s1;
	//ACCESS DATABASE
	while(FILE>>id>>name>>score){
		if(s1>score){
			string user;
			
			cout<<"Enter your Name:"<<endl;
			cin>>user;
			
			name.assign(user);
			score = s1;
			
			//REPLACE TEXT IN DATABASE
			ofstream FILE1;
			FILE1.open("High Score.txt");
			FILE1<<id<<" "<<name<<" "<<score<<endl; 
			break;
			FILE.close();	
		

		}
	}

}

//GENEREATE SPECIAL FOOD PARTICLE
void getsp(){
	int p=0;
	if(kbhit()){
		num1++;
		
		}
	if(num1 == 4*(num2+2)){
		int x = 0;
	    int y = 0;
		num2++;
	//random generation
	do{
		x = (rand()+4)%width;
		y = (rand()+6)%height;
	}
	//will check if space is empty or not
	while(map[x + y*width] != 0 );
	
	//PREVENTS MUTIPLE GENERATION OF SP. PARTICLE
	for(int i=0; i<size; i++){
		if (map[i]==-3){
			
			p++;
		}
	
	}
	if(p==0){ 
		map[x+y*width]=-3;
	}
	
		
	}
}	
