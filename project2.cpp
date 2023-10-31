#include<graphics.h>
#include<string>
#include<cstdlib>
#include<time.h>
using namespace std;

class displayRect
{
    private:
    int x,y,width,height,color;

    public:
    displayRect(int _x=((getmaxwidth()/2)-100),int _y=50,int w=200,int h=70,int c=LIGHTBLUE)
    {
        x=_x;
        y=_y;
        width=w;
        height=h;
        color=c;
    }
    void set(int _x=((getmaxwidth()/2)-100),int _y=50,int w=200,int h=70,int c=LIGHTBLUE)
    {
        x=_x;
        y=_y;
        width=w;
        height=h;
        color=c;
    }
    void setColor(int c)
    {
        color=c;
    }
    void draw()
    {
        setfillstyle(SOLID_FILL,color);
        bar(x,y,x+width,y+height);
    }

};

class Tile 
{
    private:
    int numbers;

    public:
    Tile ()
    {
        numbers=0;
    }
    void setNumTile(int random)
    {
        numbers=random;
    }

    int getNumTile() const  //retrieve the value store at numbers[i][j]
    {
        return numbers;
    }
};

class Selector 
{
private:
    int size;
    int x, x0, y, y0; // Initial position of the square selector
    int color;
    int i, j,i0,j0;
    Tile tile[3][3];
public:
    Selector(int squareSize=150, int posX=550, int posY=200, int fillColor=RED, int _i=2, int _j=2)
    {
        size=squareSize;
        x0=posX;
        y0=posY;
        color=fillColor;
        i=_i;
        j=_j;
        i0=_i;
        j0=_j;
    }
    
    void set(int squareSize=0,int posX=0,int posY=0,int fillColor=0,int _i=0,int _j=0)
    {
        size=squareSize;
        x0=posX;
        y0=posY;
        color=fillColor;
        i=_i;
        j=_j;
    }
    void setxyByIndex() {
        x = x0 + size * getJ();
        y = y0 + size * getI();
    }
    void draw() {
        setxyByIndex();
        setcolor(color);
        
        for (int thickness = 1; thickness <= 6; thickness++) {
            setlinestyle(0, 0, thickness); // Set line style with increasing thickness
            rectangle(x + thickness, y + thickness, x + size - thickness, y + size - thickness);
        }
    }

    void undraw() {
        setxyByIndex();
        setcolor(BLACK);
        
        for (int thickness = 6; thickness >= 1; thickness--) {
            setlinestyle(0, 0, thickness); // Set line style with decreasing thickness
            rectangle(x + thickness, y + thickness, x + size - thickness, y + size - thickness);
        }
    }


    void setI(int _i) {
        i = _i;
    }

    void setJ(int _j) {
        j = _j;
    }

    int getI() const {
        return i;
    }

    int getJ() const {
        return j;
    }
    int getI0() const {
        return i0;
    }
    int getJ0() const {
        return j0;
    }
    void swabNum()
    {
        int temp;

        temp=tile[i0][j0].getNumTile();
        tile[i0][i0].setNumTile(tile[i][j].getNumTile());
        tile[i][j].setNumTile(temp);
    }
    void moveUp()
    {
        undraw();
        if (i>0){
            i--;
            swabNum();
        }
        i0=i;
    }

    void moveDown() {
        undraw();
        if (i < 2) {
            i++;
            swabNum();
        }
        i0=i;
    }

    void moveLeft() {
        undraw();
        if (j > 0) {
            j--;
            swabNum();
        }
        j0=j;
    }

    void moveRight() {
        undraw();
        if (j < 2) {
            j++;
            swabNum();
        }
        j0=j;
    }
};
class Puzzle
{
    int x,y,x0,y0,height,color,i0,j0;
    Tile tile[3][3];
    Selector selector;

    public:
    Puzzle (int _x=550,int _y=200,int h=150,int c=LIGHTMAGENTA)
    {
        x0=_x;
        y0=_y;
        height=h;
        color=c;
        i0=2;
        j0=2;
    }
    void set (int _x=550,int _y=200,int h=150,int c=LIGHTMAGENTA)
    {
        x0=_x;
        y0=_y;
        height=h;
        color=c;
    }
    void getRandomNumber();
    Tile getNumberTile(int i,int j) const;
    bool check(); //check sequence 1-8
    bool verifyPattern();
    void setColor(int c)
    {
        color=c;
        setbkcolor(c);
    }
    void setXYValue(int i,int j)
    {
        x=x0+height*j;
        y=y0+height*i;
    }
    void setFontPosition(int i,int j)
    {
        x=590+height*j;
        y=215+height*i;
    }
    void draw()
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                setXYValue(i,j);
                setfillstyle(SOLID_FILL,color);
                bar(x,y,x+height,y+height);
                setcolor(BLACK);
                setlinestyle(0,0,15);
                rectangle(x,y,x+height,y+height);
            }
        }
    }
    void undraw()
    {
        int num;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                setXYValue(i,j);
                setfillstyle(SOLID_FILL,BLACK);
                bar(x,y,x+height,y+height);
                setcolor(BLACK);
                setlinestyle(0,0,15);
                rectangle(x,y,x+height,y+height);
            }
        }
    }
    void dispNumber()
    {
        int no;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                settextstyle(3,HORIZ_DIR,10);
                setcolor(BLUE);
                setFontPosition(i,j);
                no=tile[i][j].getNumTile();
                if (no==0)
                    continue;
                else 
                {
                    string num=to_string(no);
                    outtextxy(x,y,(char*)num.c_str());
                }
            }
        }
    }
    
};
void Puzzle::getRandomNumber()
{
    srand(time(0));

    int random;
    bool used[9] = {false}; //no num are marked as used
    
    do
    {
         for(int i=0;i<3;i++) //row
        {
            for(int j=0;j<3;j++) //column
            {
                if (i==2 && j==2)
                {
                    //tile[i][j].setNumTile(9); //empty tile,fix the no9 to be empty space
                    continue; //skip the remain code and start next iteration
                }

             do
             {
                random = 1 + (rand()%8);
             } while(used[random]||random == 9); //generate new randNum while random number has been used

             tile[i][j].setNumTile(random); //set numTile to class Tile

            used[random] = true;  //record this number has been used to avoid repeated
        }  
        }       
    } while(check());
       
}

//Tile Puzzle::getNumberTile(int i,int j) const
//{ 
//        return tile[i][j];
//}

bool Puzzle::check()
{
    int count=0,num,n[8];

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
             num = tile[i][j].getNumTile(); 

             if(num != 0)
             {
                n[count] = num;
                count ++;
             }
        }

        for(int i=0;i<8;i++)
        {
            if(n[i] == i+1) { return true;}
            else {return false;}
        }
    }

}

bool Puzzle::verifyPattern()
{
    bool status;
    if (tile[2][2].getNumTile() == 0) {status = check();}

    return status;
}
class Shape
{
    private:
    displayRect displayRect[4];
    Puzzle puzzle;
    Selector selector;
    
    public:
    Shape(int x=0,int y=0,int color=BLUE,int width=50,int height=50,int _i=0,int _j=0)
    {
        puzzle.set(x,y+100,height+100,color);
        displayRect[0].set(x,y,width,height,color);
        displayRect[1].set(x+100,y,width+100,height,color);
        displayRect[2].set(x+300,y,width+100,height,color);
        displayRect[3].set(x+height+100,700,width+100,height,color);
        selector.set(150,550,200,RED,2,2);
    }
    void readImage()
    {
        int maxw=getmaxwidth(),maxh=getmaxheight();
        string num="3 X 3";

        puzzle.getRandomNumber();
        draw(LIGHTBLUE);
        dispNum(LIGHTBLUE);
        readimagefile("resource/reset.gif",379,50,maxw,maxh);
        readimagefile("resource/best.gif",490,60,maxw-100,maxh-100);
        //settextstyle(3,HORIZ_DIR,5);
        //setcolor(BLUE);
        //outtextxy(665,98,(char*)num.c_str());
        readimagefile("resource/timer.gif",250,300,maxw-350,maxh);
    }
    void draw(int c)
    {  
        puzzle.draw();
        for(int i=0;i<4;i++)
        {
            displayRect[i].draw();
        }
        selector.draw();
    }
    void redraw()
    {
        puzzle.undraw();
        selector.undraw();
        selector.moveUp();
        draw(LIGHTBLUE);
        puzzle.dispNumber();
    }
    void dispNum(int c)
    {
        int x=590,y=215,i=1;
        setbkcolor(c);
        settextstyle(3,HORIZ_DIR,10);
        setcolor(BLUE);
        while(i<=7)
        {
            for(int x=590;x<=890;x+=150)
            {
                if((x==890)&&(y==515))
                    break;
                string num=to_string(i++);
                outtextxy(x,y,(char*)num.c_str());
            }
            y+=150;
        }
    }
    void setColor(int c)
    {
        puzzle.setColor(c);
        for (int i=0;i<4;i++)
        {
            displayRect[i].setColor(c);
        }
        draw(c);
        puzzle.dispNumber();
    }
};

int main()
{
    initwindow(getmaxwidth(),getmaxheight(),"Mystic Square");
    Shape shape(550,100,LIGHTBLUE,50,50,2,2);
    Selector selector;
    Puzzle puzzle;
    bool isRunning=true;
    char ch;

    shape.readImage();
    getch();
    
    while (isRunning)
    {
        if(kbhit())
        {
            ch=getch();
            switch (ch)
            {
                case ' ':  puzzle.dispNumber();
                            break;
                case 'l': shape.setColor(LIGHTBLUE);
                            break;
                case 'g':shape.setColor(LIGHTMAGENTA);
                        break;
                case 'f':shape.setColor(LIGHTCYAN);
                        break;
                case 'k':shape.setColor(LIGHTGRAY);
                        break;
                case 'w':
                case KEY_UP:
                    shape.redraw();
                    break;
                case 's':
                case KEY_DOWN:
                    selector.moveDown();
                    puzzle.dispNumber();
                    break;
                case 'a':
                case KEY_LEFT:
                    selector.moveLeft();
                    puzzle.dispNumber();
                    break;
                case 'd':
                case KEY_RIGHT:
                    selector.moveRight();
                    puzzle.dispNumber();
                    break;
                case 27: isRunning=false;
                        break;
            }
            selector.draw();
        }
    }

    return 0;
}

