#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>


struct point   //represents a point in the grid
{
    int x;
    int y;
}place,new_point;

char grid[50][50];

static int grid_size;

static char nullchar='z';

static int max_words;

int i;
enum direction //enumerator for direction in the grid in which the word is inserted
{
    UP=1,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT
};
char *countries[]={"india","america","china","japan","russia","canada","brazil","france","spain","australia"};
int countries_size=10;
char *flowers[]={"rose","lily","lotus","marigold","daisy","tulip","orchid","poppy","sunflower","violet"};
int flowers_size=10;
char *boardgames[]={"chess","carrom","ludo","checkers","scrabble","monopoly","gameoflife","battleship","backgammon","pictionary"};
int boardgames_size=10;
char *languages[]={"tamil","english","hindi","french","latin","spanish","greek","sanskrit","japanese","korean"};
int languages_size=10;
char *input[100]; //the words that are inserted in the grid
int input_point[50][3];//the x,y coordinate and direction of the words that are inserted in the grid
int mark[100]={0};//used to mark which all words have been identified by the user so that there is no duplicate answer accepted
int flag=0;
struct point shift_point(struct point start, enum direction d)  //start is the position of the point to be shifted in the grid, d is the direction in which the point has to shift
{
    int i = start.x;
    int j = start.y;
    switch(d)  //final position of the shifted point depends on the direction d
    {
       //eight directions in which the point can move
        case UP:
            new_point.x = i-1; //Move up a row
            new_point.y = j;
            break;
        case DOWN:
            new_point.x = i+1;  //Move down a row
            new_point.y = j;
            break;
        case LEFT:
            new_point.x = i;
            new_point.y = j-1; //Column moves left
            break;
        case RIGHT:
            new_point.x = i;
            new_point.y = j+1; //Column moves right
            break;
        case UP_LEFT:
            new_point.x = i-1; //Row moves up
            new_point.y = j-1; //Column moves left
            break;
        case UP_RIGHT:
            new_point.x = i-1; //Row moves up
            new_point.y = j+1; //Column moves right
            break;
        default:
            new_point.x = i; //Row stays the same
            new_point.y = j; //Column stays the same
            break;
    }
    return new_point;  //return the new point
}
int check_insert(char* word, struct point start, enum direction d)
{
    int i = 0;
    struct point new_point = start;
    while(i < strlen(word)) //loop runs through the word
    {
    //Attempt to shift the point to the new point
        if(grid[new_point.x][new_point.y] == 'z'||grid[new_point.x][new_point.y]==word[i])
        {
            new_point = shift_point(new_point,d);
            i++;
        }
        else
        {
            return 0;   //if cant be inserted return false
        }
    }
    return 1;  //can be inserted so return true
}
int arr[10]={1,3,2,4,5,6,1,3,2,4};  //this array allots 40,40,20 percent division of words to horizontal, vertical and diagonal direction
int p=0;   //used as an index to traverse the above array arr
void insertWordInGrid(char *word,int i)   //function to insert word in the grid
{
    enum direction d;
    do{
        place.x = rand() % grid_size; //random row
        place.y = rand() % grid_size; //random column
        d = (arr[(p++)%10]);          //get a direction according to the rule specified
    }while(!check_insert(word,place,d));//run the loop until we cant insert the word
    int j = 0;
    struct point new_point = place;
    while(j < strlen(word))
    {
        grid[new_point.x][new_point.y] = (char)toupper(word[j]);  //insertion into the grid
        new_point = shift_point(new_point,d);   //shift according to direction
        j++;
    }
    input_point[i][0]=place.x;  //used in changing the grid afterwards when user enters the correct answer
    input_point[i][1]=place.y;
    input_point[i][2]=d;
}
char generate_random_char()    //function to generate a random char
{
    return 'A' + rand()%26;
}
void fill_grid()  //fill the remaining places with random characters
{
    int i,j;
    for(i=0;i<grid_size;i++)
    {
        for(j=0;j<grid_size;j++)
        {
            if(grid[i][j] == 'z')
            {
                grid[i][j] = generate_random_char(); //Set every null value to a random character
            }
        }
    }
}
void printGrid()   //function to print the grid
{
    int i,j;
    for(i=0;i<grid_size;i++)
    {
        for(j=0;j<grid_size;j++)
        {
            printf("%c ",grid[i][j]);
        }
        printf("\n");
    }
}
int checkans(char *str)   //function to check whether str is in the grid or not
{
    int i=0;
    int flag=0;
    for(i=0;i<max_words;i++)//check in input array
    {
        if(strcmp(str,input[i])==0)//condition satisfied and str is in the grid
        {
            if (mark[i]==1)
            {
                return 0;
            }


            flag=1;
            break;
        }

    }
    if(flag==1)//then str is in the grid and change the grid
    {
        mark[i]=1;
        int j=0;
        struct point p;
        p.x=input_point[i][0];
        p.y=input_point[i][1];
        enum direction d=input_point[i][2];
        for(j=0;j<strlen(str);j++)
        {

            grid[p.x][p.y]='*';    //change the grid where the word is there
            p=shift_point(p,d);
        }
        return 1;   //true condition
    }
    else
        return 0;   //false condition
}
int main()
{
    srand(time(NULL));
    printf("Lets play word search !\n\n");
    char name[100];
    int ans;
    printf("Enter your name: ");
    scanf(" %s",&name);
    printf("\nHello %s!!! What category do you want to choose?\n",name);
    printf("Choose 1 for Countries.\n");
    printf("Choose 2 for Flowers.\n");
    printf("Choose 3 for Board Games.\n");
    printf("Choose 4 for Languages.\n");
    printf("Enter your choice:");
    scanf("%d",&ans);
    printf("\nEnter the size of the grid:");
    scanf("%d",&grid_size);
    int i,j;
    for(i=0;i<grid_size;i++)//initialize the grid to null char 'z'
    {
        for(j=0;j<grid_size;j++)
        {
            grid[i][j]='z';
        }
    }
    max_words=grid_size-3;   //maximum words in the grid
    char *item;

    if(ans==1)
    {
        item="countries";
        if(max_words>10)
            max_words=10;
        for(i=0;i<max_words;i++)
        {
            input[i]=countries[i];
            insertWordInGrid(countries[i],i);
        }
    }
    else if(ans==2){

        item="flowers";
        if(max_words>10)
            max_words=10;
        for(i=0;i<max_words;i++)
        {

            input[i]=flowers[i];
            insertWordInGrid(flowers[i],i);
        }
    }
    else if(ans==3){
        item="board games";
        if(max_words>10)
            max_words=10;
        for(i=0;i<max_words;i++)
        {

            input[i]=boardgames[i];
            insertWordInGrid(boardgames[i],i);
        }
    }
    else if(ans==4){
        item="languages";
        if(max_words>10)
            max_words=10;
        for(i=0;i<max_words;i++){

            input[i]=languages[i];
            insertWordInGrid(languages[i],i);
        }
    }
    int t=max_words/3;   //time in minutes in which the user can do the puzzle
    system("cls");
    printf("Okay %s! There are %d %s hidden in this grid. Let's see if you can find them all.\nYou have %d minutes to solve. GOOD LUCK!! \n\n",name,max_words,item,t);
    fill_grid();
    printGrid();
    clock_t start = clock();
    for(i=0;i<max_words;i++)
    {
        char ans[50];
        clock_t end = clock();
        float sec = (float)(end - start) / CLOCKS_PER_SEC;
        printf("\nYou have given %d right answers till now.",i);
        printf("\nTime Remaining: %f seconds",t*60-sec);
        printf("\nEnter answer(in lower case):");
        scanf(" %s",&ans);
        if(sec>t*60|| sec<0)
        {
            system("cls");
            printf("TIME UP!!\nYou lose!!\nBetter Luck Next Time!!\n");
            return 1;
        }
        if(checkans(ans))
        {
            system("cls");
            printf("Your answer was correct!!\n");
            printf("%d words more\n\n",max_words-i-1);
            printGrid();
        }
        else
        {
            system("cls");
            printf("Your answer was wrong!!\n");
            Beep(1000,1500);
            printGrid();
            i--;
        }
    }
    system("cls");
    printf("\nCongratulations!!!You win!!!");
    return 0;
}
