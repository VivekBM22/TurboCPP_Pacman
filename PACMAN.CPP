#include<fstream.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
#include<stdlib.h>
#include<stdio.h>

//CONTROLS
char left[3]={'a',0,0},right[3]={'d',0,0},up[3]={'w',0,0},down[3]={'s',0,0},accept[3]={13,0,0},back[3]={27,0,0},input[3]={0,0,0};

//GAME DEF
int wallcolor=9,level;
char gst[2]={219,0};

void Input()
{
	input[1]=0;
	input[0]=getch();
	if(!input[0])
	{
		input[1]=1;
		input[0]=getch();
	}
}

void Namein(char name[4],int x,int y)
{
	char charpointer[2]={127,0};
	int namecursor=0;
	strcpy(name,"AAA");
	while(!(input[0]==accept[0]&&input[1]==accept[1]))
	{
		bar(x,y,x+24,y+16);
		setcolor(4);
		outtextxy(x,y,name);
		outtextxy(x+(8*namecursor),y+8,charpointer);
			Input();
		if(input[0]==left[0]&&input[1]==left[1]&&namecursor>0)
			namecursor--;
		if(input[0]==right[0]&&input[1]==right[1]&&namecursor<2)
			namecursor++;
		if(input[0]==up[0]&&input[1]==up[1])
			name[namecursor]--;
		if(input[0]==down[0]&&input[1]==down[1])
			name[namecursor]++;
		if(name[namecursor]>'Z')
			name[namecursor]='A';
		if(name[namecursor]<'A')
			name[namecursor]='Z';
	}
	input[0]=input[1]=0;
}

float Distance(int x1,int y1,int x2,int y2)
{
	float z=pow((x2-x1),2)+pow((y2-y1),2);
	return sqrt(z);
}

struct pacdot
{
	int x,y,eat;
};

struct powerpellet
{
	int x,y,eat;
};

struct Cherry
{
	int x,y,eat,disp;
	void Disp()
	{
		setfillstyle(1,4);
		bar(x,y,x+5,y+5);
		bar(x-5,y-2,x,y+3);
		setfillstyle(1,6);
		setcolor(6);
		bar(x+5,y-6,x+6,y-6);
		line(x+4,y-5,x+1,y-4);
		line(x+1,y-4,x-2,y-1);
		line(x+4,y-5,x+4,y-3);
		line(x+4,y-3,x+2,y-1);
		line(x+2,y-1,x+2,y+1);
		putpixel(x-5,y-2,0);
		putpixel(x-5,y+3,0);
		putpixel(x,y-2,0);
		putpixel(x,y,0);
		putpixel(x,y+5,0);
		putpixel(x+5,y,0);
		putpixel(x+5,y+5,0);
		setcolor(0);
		line(x-1,y+1,x-1,y+3);
		putpixel(x-4,y+1,15);
		putpixel(x-3,y+2,15);
		putpixel(x+1,y+3,15);
		putpixel(x+2,y+4,15);
	}
};

struct Strawberry
{
	int x,y,eat,disp;
	void Disp()
	{
		setfillstyle(1,4);
		bar(x-5,y-4,x+5,y+5);
		setcolor(10);
		line(x-3,y-5,x+3,y-5);
		line(x-2,y-4,x+2,y-4);
		putpixel(x,y-3,10);
		putpixel(x,y-6,15);
		putpixel(x,y-5,15);
		putpixel(x+4,y-3,15);
		putpixel(x-4,y-2,15);
		putpixel(x+2,y-2,15);
		putpixel(x,y-1,15);
		putpixel(x-2,y-1,15);
		putpixel(x+3,y,15);
		putpixel(x,y+1,15);
		putpixel(x-3,y+1,15);
		putpixel(x-1,y+3,15);
		putpixel(x+2,y+3,15);
		putpixel(x-5,y-4,0);
		putpixel(x+5,y-4,0);
		putpixel(x-3,y+4,0);
		putpixel(x+3,y+4,0);
		setcolor(0);
		line(x-5,y+1,x-5,y+4);
		line(x-4,y+3,x-4,y+4);
		line(x-5,y+5,x-1,y+5);
		line(x+5,y+1,x+5,y+4);
		line(x+4,y+3,x+4,y+4);
		line(x+5,y+5,x+1,y+5);
	}
};

struct Peach
{
	int x,y,eat,disp;
	void Disp()
	{
		setfillstyle(1,12);
		bar(x-5,y-3,x+6,y+5);
		setcolor(10);
		line(x+2,y-6,x+3,y-6);
		line(x+1,y-5,x+5,y-5);
		line(x+2,y-4,x+4,y-4);
		setcolor(12);
		line(x,y-5,x,y-4);
		setcolor(0);
		line(x-5,y-3,x-4,y-3);
		line(x+5,y-3,x+6,y-3);
		line(x-5,y+3,x-5,y+4);
		line(x+6,y+3,x+6,y+4);
		line(x-5,y+5,x-3,y+5);
		line(x+4,y+5,x+6,y+5);
		putpixel(x-5,y-2,0);
		putpixel(x+6,y-2,0);
	}
};

struct Apple
{
	int x,y,eat,disp;
	void Disp()
	{
		setfillstyle(1,4);
		bar(x-5,y-5,x+6,y+5);
		setcolor(6);
		putpixel(x+1,y-6,6);
		line(x,y-5,x,y-4);
		setcolor(0);
		line(x+5,y-5,x+6,y-5);
		line(x-5,y+2,x-5,y+5);
		line(x-4,y+4,x-4,y+5);
		line(x+6,y+2,x+6,y+5);
		line(x+5,y+4,x+5,y+5);
		putpixel(x-5,y-5,0);
		putpixel(x-1,y-5,0);
		putpixel(x+1,y-5,0);
		putpixel(x+6,y-4,0);
		putpixel(x-3,y+5,0);
		putpixel(x,y+5,0);
		putpixel(x+4,y+5,0);
		putpixel(x+4,y,15);
		putpixel(x+4,y+1,15);
		putpixel(x+3,y+2,15);
	}
};

struct Grapes
{
	int x,y,eat,disp;
	void Disp()
	{
		setfillstyle(1,10);
		bar(x-4,y-3,x+4,y+5);
		setcolor(10);
		line(x-1,y-4,x+1,y-4);
		line(x-5,y,x-5,y+2);
		line(x+5,y,x+5,y+2);
		line(x-1,y+6,x+1,y);
		putpixel(x-4,y-3,0);
		putpixel(x-4,y+5,0);
		putpixel(x+4,y-3,0);
		putpixel(x+4,y+5,0);
		setcolor(2);
		line(x,y-3,x-4,y+1);
		line(x-4,y+1,x-1,y+4);
		line(x-2,y+5,x+1,y+2);
		line(x,y+1,x+3,y+4);
		line(x+3,y+4,x+1,y+6);
		line(x,y+1,x+3,y-2);
		line(x+2,y-1,x+4,y+1);
		putpixel(x-3,y-2,2);
		line(x,y-6,x,y-5);
		line(x-2,y-6,x+2,y-6);
		putpixel(x,y-4,15);
		putpixel(x-2,y-2,15);
		putpixel(x-4,y,15);
		putpixel(x-4,y+2,15);
		putpixel(x-1,y+1,15);
		putpixel(x-1,y+3,15);
		putpixel(x+1,y+3,15);
		putpixel(x+1,y-1,15);
		putpixel(x+3,y+1,15);
	}
};

struct Galaxian
{
	int x,y,eat,disp;
	void Disp()
	{
		setcolor(4);
		line(x,y-5,x,y-1);
		line(x-1,y-4,x+1,y-4);
		line(x-2,y-3,x+2,y-3);
		line(x-3,y-2,x-2,y-2);
		line(x+3,y-2,x+2,y-2);
		setcolor(14);
		line(x-4,y-1,x-1,y-1);
		line(x+4,y-1,x+1,y-1);
		line(x-3,y,x+3,y);
		line(x,y,x,y+5);
		putpixel(x-4,y-2,14);
		putpixel(x-1,y-2,14);
		putpixel(x+1,y-2,14);
		putpixel(x+4,y-2,14);
		putpixel(x-2,y+1,14);
		putpixel(x+2,y+1,14);
		setcolor(1);
		line(x-5,y-4,x-5,y-2);
		line(x-5,y-1,x-2,y+2);
		line(x-5,y,x-2,y+3);
		line(x+5,y-4,x+5,y-2);
		line(x+5,y-1,x+2,y+2);
		line(x+5,y,x+2,y+3);
	}
};

struct Bell
{
	int x,y,eat,disp;
	void Disp()
	{
		setfillstyle(1,14);
		bar(x-5,y-5,x+6,y+5);
		setcolor(14);
		line(x,y-6,x+1,y-6);
		setcolor(0);
		line(x-4,y-5,x-3,y-5);
		line(x-5,y-5,x-5,y+1);
		line(x-4,y-4,x-4,y-4);
		line(x+4,y-5,x+5,y-5);
		line(x+6,y-5,x+6,y+1);
		line(x+5,y-4,x+5,y-4);
		line(x,y-5,x+1,y-5);
		setfillstyle(1,3);
		bar(x-4,y+5,x+5,y+6);
		setfillstyle(1,15);
		setcolor(15);
		bar(x+1,y+5,x+2,y+6);
		putpixel(x-1,y-3,15);
		line(x-2,y-2,x-2,y);
		line(x-3,y+2,x-3,y+3);
	}
};

struct Key
{
	int x,y,eat,disp;
	void Disp()
	{
		setfillstyle(1,3);
		bar(x-3,y-5,x+3,y-2);
		setcolor(3);
		line(x-1,y-6,x+1,y-6);
		setcolor(0);
		line(x-1,y-5,x+1,y-5);
		setcolor(7);
		line(x-1,y-1,x-1,y+5);
		line(x+1,y-1,x+1,y+1);
		line(x+1,y+3,x+1,y+5);
		putpixel(x+2,y,7);
		putpixel(x+2,y+4,7);
		putpixel(x,y+6,7);
	}
};

void dispac(int x,int y)
{
	int i;
	setcolor(14);
	setfillstyle(1,14);
	pieslice(x,y,0,360,4);
	setcolor(0);
	for(i=-3;i<=3;i++)
		line(x,y,x+4,y+i);
}

void itoa(int n,char a[7])
{
	char chard;
	int i,intd,sign=1;
	if(n<0)
	{
		sign=-1;
		n*=-1;
	}
	a[0]='\0';
	if(n==0)
	{
		a[0]='0';
		a[1]='\0';
	}
	while(n>0)
	{
		intd=n%10;
		n/=10;
		for(i=5;i>0;i--)
			a[i]=a[i-1];
		if(intd>=0&&intd<=9)
			chard=intd+48;
		else
			chard=' ';
		a[0]=chard;
	}
	if(sign<0)
	{
		for(i=6;i>0;i--)
			a[i]=a[i-1];
		a[0]='-';
	}
}

class HMENU
{
	char menu[20][13];
	int n,control;
	int x,y;
	public:
		HMENU()
		{
			for(int i=0;i<20;i++)
				menu[i][0]='\0';
			n=3;
			control=0;
		}
		HMENU(HMENU &HM)
		{
			for(int i=0;i<20;i++)
			{
				for(int j=0;j<12;j++)
					menu[i][j]=HM.menu[i][j];
				menu[i][j]='\0';
			}
			n=HM.n;
			control=0;
		}
		HMENU(char list[][13],int m)
		{
			for(int i=0;i<20;i++)
				menu[i][0]='\0';
			control=0;
			n=m;
			for(i=0;i<m;i++)
			{
				for(int j=0;list[i][j]!='\0';j++)
					menu[i][j]=list[i][j];
				menu[i][j]='\0';
			}
		}
		void Forward()
		{
			control=(control+1)%n;
		}
		void Backward()
		{
			control--;
			if(control<0)
				control+=n;
		}
		void getcord(int a,int b)
		{
			x=a;
			y=b;
		}
		int getcurrent()
		{	return ((control+1)%n);
		}
		void display(int s,int clr)
		{
			setfillstyle(1,clr);
			bar(x,y,x+208+s*96,y+16);
			settextstyle(0,0,1);
			outtextxy(x,y,menu[control]);
			outtextxy(x+112+s*96,y,menu[((control+2)%n)]);
			settextstyle(0,0,s);
			outtextxy(x+104,y,menu[((control+1)%n)]);
		}
};

class PROFILE
{
	char name[7],cnowins[7],cmaxlvl[7],cmaxscore[7];
	int nowins,maxlvl,maxscore,accno;
	char passwrd[26];
	public:
		PROFILE()
		{
			nowins=maxscore=accno=0;
			maxlvl=1;
			strcpy(name,"PLAYER");
			strcpy(passwrd,"\0");
			strcpy(cnowins,"\0");
			strcpy(cmaxlvl,"\0");
			strcpy(cmaxscore,"\0");
		}
		int retmaxlvl()
		{	return maxlvl;
		}
		int retmaxscore()
		{	return maxscore;
		}
		char* retname()
		{	return name;
		}
		char* retcnowins()
		{	itoa(nowins,cnowins);
			return cnowins;
		}
		char* retcmaxlvl()
		{	itoa(maxlvl,cmaxlvl);
			return cmaxlvl;
		}
		char* retcmaxscore()
		{	itoa(maxscore,cmaxscore);
			return cmaxscore;
		}
		char* retpasswrd()
		{	return passwrd;
		}
		int retaccno()
		{	return accno;
		}
		void reset()
		{
			nowins=maxscore=0;
			maxlvl=1;
		}
		void getname(char str[])
		{	strcpy(name,str);
		}
		void getpasswrd(char str[])
		{	strcpy(passwrd,str);
		}
		void getaccno(int num)
		{	accno=num;
		}
		void nowinspp()
		{	nowins++;
		}
		void maxlvlpp()
		{	maxlvl++;
		}
		void getmaxscore(int max)
		{	maxscore=max;
		}
};

void shaveul(int x,int y)
{
	setcolor(9);
	putpixel(x,y,0);
	putpixel(x+1,y,0);
	putpixel(x,y+1,0);
	line(x+2,y,x,y+2);
}

void shaveur(int x,int y)
{
	setcolor(9);
	putpixel(x,y,0);
	putpixel(x-1,y,0);
	putpixel(x,y+1,0);
	line(x-2,y,x,y+2);
}

void shavedl(int x,int y)
{
	setcolor(9);
	putpixel(x,y,0);
	putpixel(x,y-1,0);
	putpixel(x+1,y,0);
	line(x,y-2,x+2,y);
}

void shavedr(int x,int y)
{
	setcolor(9);
	putpixel(x,y,0);
	putpixel(x,y-1,0);
	putpixel(x-1,y,0);
	line(x,y-2,x-2,y);
}

void sbar(int x1,int y1,int x2,int y2,char a,char b,char c,char d)
{
	bar(x1,y1,x2,y2);
	if(a)
		shaveul(x1,y1);
	if(b)
		shaveur(x2,y1);
	if(c)
		shavedr(x2,y2);
	if(d)
		shavedl(x1,y2);
}

class  PACMAN
{
	int x,y,checkcol[12],uwall,dwall,lwall,rwall,phase,jn,jx,jy;
	double initial,elapsed;
	char dir,mortal;
	public:
		PACMAN()
		{
			x=y=phase=jn=0;
			uwall=dwall=lwall=rwall=1;
			jx=jy=0;
			dir='r';
			mortal=1;
		}
		void colcheck(int X,int Y)
		{
			checkcol[0]=getpixel(X-4,Y-7);	//UP
			checkcol[1]=getpixel(X,Y-7);
			checkcol[2]=getpixel(X+4,Y-7);
			if(checkcol[0]!=wallcolor&&checkcol[1]!=wallcolor&&checkcol[2]!=wallcolor)
				uwall=0;
			else
				uwall=1;
			checkcol[0]=getpixel(X-4,Y+7);	//DOWN
			checkcol[1]=getpixel(X,Y+7);
			checkcol[2]=getpixel(X+4,Y+7);
			if(checkcol[0]!=wallcolor&&checkcol[1]!=wallcolor&&checkcol[2]!=wallcolor)
				dwall=0;
			else
				dwall=1;
			checkcol[0]=getpixel(X-7,Y-4);	//LEFT
			checkcol[1]=getpixel(X-7,Y);
			checkcol[2]=getpixel(X-7,Y+4);
			if(checkcol[0]!=wallcolor&&checkcol[1]!=wallcolor&&checkcol[2]!=wallcolor)
				lwall=0;
			else
				lwall=1;
			checkcol[0]=getpixel(X+7,Y-4);	//RIGHT
			checkcol[1]=getpixel(X+7,Y);
			checkcol[2]=getpixel(X+7,Y+4);
			if(checkcol[0]!=wallcolor&&checkcol[1]!=wallcolor&&checkcol[2]!=wallcolor)
				rwall=0;
			else
				rwall=1;
		}
		void wallcheck()
		{
			if(!jn)
				colcheck(x,y);
			else
				colcheck(jx,jy);
			if(jn)
			{
				if((x<jx-5)||(x>jx+5)||(y<jy-5)||(y>jy+5))
					jn=0;
			}
			if(!jn)
			{
				checkcol[0]=getpixel(x-3,y-7);
				checkcol[1]=getpixel(x-4,y-7);
				checkcol[2]=getpixel(x-3,y-8);
				checkcol[3]=getpixel(x-5,y-7);
				checkcol[4]=getpixel(x-4,y-8);
				checkcol[5]=getpixel(x-3,y-9);
				checkcol[6]=getpixel(x-3,y+7);
				checkcol[7]=getpixel(x-4,y+7);
				checkcol[8]=getpixel(x-3,y+8);
				checkcol[9]=getpixel(x-5,y+7);
				checkcol[10]=getpixel(x-4,y+8);
				checkcol[11]=getpixel(x-3,y+9);
				if((dir=='r')&&((checkcol[0]==0&&checkcol[1]==0&&checkcol[2]==0)&&(checkcol[3]==wallcolor&&checkcol[4]==wallcolor&&checkcol[5]==wallcolor)||(checkcol[6]==0&&checkcol[7]==0&&checkcol[8]==0&&checkcol[9]==wallcolor&&checkcol[10]==wallcolor&&checkcol[11]==wallcolor)))
				{
					jn=1;
					jx=x+4;
					jy=y;
				}
				checkcol[0]=getpixel(x-7,y-3);
				checkcol[1]=getpixel(x-8,y-3);
				checkcol[2]=getpixel(x-7,y-4);
				checkcol[3]=getpixel(x-9,y-3);
				checkcol[4]=getpixel(x-8,y-4);
				checkcol[5]=getpixel(x-7,y-5);
				checkcol[6]=getpixel(x+7,y-3);
				checkcol[7]=getpixel(x+8,y-3);
				checkcol[8]=getpixel(x+7,y-4);
				checkcol[9]=getpixel(x+9,y-3);
				checkcol[10]=getpixel(x+8,y-4);
				checkcol[11]=getpixel(x+7,y-5);
				if((dir=='d')&&((checkcol[0]==0&&checkcol[1]==0&&checkcol[2]==0)&&(checkcol[3]==wallcolor&&checkcol[4]==wallcolor&&checkcol[5]==wallcolor)||(checkcol[6]==0&&checkcol[7]==0&&checkcol[8]==0&&checkcol[9]==wallcolor&&checkcol[10]==wallcolor&&checkcol[11]==wallcolor)))
				{
					jn=1;
					jx=x;
					jy=y+4;
				}
				checkcol[0]=getpixel(x+3,y-7);
				checkcol[1]=getpixel(x+4,y-7);
				checkcol[2]=getpixel(x+3,y-8);
				checkcol[3]=getpixel(x+5,y-7);
				checkcol[4]=getpixel(x+4,y-8);
				checkcol[5]=getpixel(x+3,y-9);
				checkcol[6]=getpixel(x+3,y+7);
				checkcol[7]=getpixel(x+4,y+7);
				checkcol[8]=getpixel(x+3,y+8);
				checkcol[9]=getpixel(x+5,y+7);
				checkcol[10]=getpixel(x+4,y+8);
				checkcol[11]=getpixel(x+3,y+9);
				if((dir=='l')&&((checkcol[0]==0&&checkcol[1]==0&&checkcol[2]==0)&&(checkcol[3]==wallcolor&&checkcol[4]==wallcolor&&checkcol[5]==wallcolor)||(checkcol[6]==0&&checkcol[7]==0&&checkcol[8]==0&&checkcol[9]==wallcolor&&checkcol[10]==wallcolor&&checkcol[11]==wallcolor)))
				{
					jn=1;
					jx=x-4;
					jy=y;
				}
				checkcol[0]=getpixel(x-7,y+3);
				checkcol[1]=getpixel(x-8,y+3);
				checkcol[2]=getpixel(x-7,y+4);
				checkcol[3]=getpixel(x-9,y+3);
				checkcol[4]=getpixel(x-8,y+4);
				checkcol[5]=getpixel(x-7,y+5);
				checkcol[6]=getpixel(x+7,y+3);
				checkcol[7]=getpixel(x+8,y+3);
				checkcol[8]=getpixel(x+7,y+4);
				checkcol[9]=getpixel(x+9,y+3);
				checkcol[10]=getpixel(x+8,y+4);
				checkcol[11]=getpixel(x+7,y+5);
				if((dir=='u')&&((checkcol[0]==0&&checkcol[1]==0&&checkcol[2]==0)&&(checkcol[3]==wallcolor&&checkcol[4]==wallcolor&&checkcol[5]==wallcolor)||(checkcol[6]==0&&checkcol[7]==0&&checkcol[8]==0&&checkcol[9]==wallcolor&&checkcol[10]==wallcolor&&checkcol[11]==wallcolor)))
				{
					jn=1;
					jx=x;
					jy=y-4;
				}
			}
			if(x==321&&y==151)
				dwall=1;
			if(!jn&&!(x==321&&y==235&&(dir=='u'||dir=='d')))
			{
				if(dir=='u'||dir=='d')
				{
					lwall=1;
					rwall=1;
				}
				else
				{
					uwall=1;
					dwall=1;
				}
			}
		}
		void motion()
		{
			int centerchk=1;
			changemort();
			wallcheck();
			while(kbhit())
				getch();
			if(input[0]==up[0]&&input[1]==up[1]&&uwall==0)
				dir='u';
			else if(input[0]==down[0]&&input[1]==down[1]&&dwall==0)
				dir='d';
			else if(input[0]==left[0]&&input[1]==left[1]&&lwall==0)
				dir='l';
			else if(input[0]==right[0]&&input[1]==right[1]&&rwall==0)
				dir='r';
			if(jn)
			{
				if(dir=='l'||dir=='r')
				{
					if(y<jy)
						y++;
					else if(y>jy)
						y--;
				}
				else if(dir=='u'||dir=='d')
				{
					if(x<jx)
						x++;
					else if(x>jx)
						x--;
				}
				if(dir=='u'&&y>jy)
				{
					y--;
					centerchk=0;
					phase++;
				}
				else if(dir=='d'&&y<jy)
				{
					y++;
					centerchk=0;
					phase++;
				}
				else if(dir=='l'&&x>jx)
				{
					x--;
					centerchk=0;
					phase++;
				}
				else if(dir=='r'&&x<jx)
				{
					x++;
					centerchk=0;
					phase++;
				}
				else
					centerchk=1;
			}
			if(dir=='u'&&uwall==0&&centerchk)
			{
				y--;
				phase++;
			}
			else if(dir=='d'&&dwall==0&&centerchk)
			{
				y++;
				phase++;
			}
			else if(dir=='l'&&lwall==0&&centerchk)
			{
				x--;
				phase++;
			}
			else if(dir=='r'&&rwall==0&&centerchk)
			{
				x++;
				phase++;
			}
			if(phase>6)
				phase=0;
			if(x==321&&y==151)
				dwall=1;
			if(x<225)
				x=414;
			else if(x>414)
				x=225;
		}
		void changemort(char a='n')
		{
			double fright_t;
			if(a!='n')
			{
				mortal=0;
				initial=clock()/CLK_TCK;
			}
			elapsed=clock()/CLK_TCK;
			if(level==1)
				fright_t=6;
			if(level==2||level==6||level==10)
				fright_t=5;
			if(level==3)
				fright_t=4;
			if(level==4||level==14)
				fright_t=3;
			if(level==5||level==7||level==8||level==11)
				fright_t=2;
			if(level==9||level==12||level==13||level==15||level==16||level==18)
				fright_t=1;
			if(level>=19||level==17)
				fright_t=0;
			if(!mortal&&(elapsed-initial>=fright_t))
				mortal=1;
		}
		void getcoord(int X,int Y)
		{
			x=X;
			y=Y;
		}
		void display()
		{
			int i;
			setcolor(14);
			setfillstyle(1,14);
			pieslice(x,y,0,360,4);
			setcolor(0);
			if(dir=='r')
			{
				if(phase==1||phase==6)
					for(i=-1;i<=1;i++)
						line(x,y,x+4,y+i);
				else if(phase==2||phase==5)
					for(i=-3;i<=3;i++)
						line(x,y,x+4,y+i);
				else if(phase==3||phase==4)
					for(i=-4;i<=4;i++)
						line(x,y,x+4,y+i);
			}
			else if(dir=='l')
			{
				if(phase==1||phase==6)
					for(i=-1;i<=1;i++)
						line(x,y,x-4,y+i);
				else if(phase==2||phase==5)
					for(i=-3;i<=3;i++)
						line(x,y,x-4,y+i);
				else if(phase==3||phase==4)
					for(i=-4;i<=4;i++)
						line(x,y,x-4,y+i);
			}
			else if(dir=='d')
			{
				if(phase==1||phase==6)
					for(i=-1;i<=1;i++)
						line(x,y,x+i,y+4);
				else if(phase==2||phase==5)
					for(i=-3;i<=3;i++)
						line(x,y,x+i,y+4);
				else if(phase==3||phase==4)
					for(i=-4;i<=4;i++)
						line(x,y,x+i,y+4);
			}
			else if(dir=='u')
			{
				if(phase==1||phase==6)
					for(i=-1;i<=1;i++)
						line(x,y,x+i,y-4);
				else if(phase==2||phase==5)
					for(i=-3;i<=3;i++)
						line(x,y,x+i,y-4);
				else if(phase==3||phase==4)
					for(i=-4;i<=4;i++)
						line(x,y,x+i,y-4);
			}
		}
		int retx()
		{	return x;}
		int rety()
		{	return y;}
		char retdir()
		{       return dir;}
		int retmortal()
		{	return mortal;}
		void setdir(char d)
		{	dir=d;}
};

class GHOST
{
	protected:
		int x,y,color,orgcol,uwall,dwall,lwall,rwall;
		char dir,mortal;
		double elapsed,initial,fright_t;
	public:
		void getcolor(int C)
		{	color=C;}
		void wallcheck()
		{
			int checkcol[6],jn=0;
			checkcol[0]=getpixel(x-6,y-7);	//UP
			checkcol[1]=getpixel(x,y-7);
			checkcol[2]=getpixel(x+6,y-7);
			if((checkcol[0]!=wallcolor)&&(checkcol[1]!=wallcolor)&&(checkcol[2]!=wallcolor))
				uwall=0;
			else
				uwall=1;
			checkcol[0]=getpixel(x-6,y+7);	//DOWN
			checkcol[1]=getpixel(x,y+7);
			checkcol[2]=getpixel(x+6,y+7);
			if((checkcol[0]!=wallcolor)&&(checkcol[1]!=wallcolor)&&(checkcol[2]!=wallcolor))
				dwall=0;
			else
				dwall=1;
			checkcol[0]=getpixel(x-7,y-6);	//LEFT
			checkcol[1]=getpixel(x-7,y);
			checkcol[2]=getpixel(x-7,y+6);
			if((checkcol[0]!=wallcolor)&&(checkcol[1]!=wallcolor)&&(checkcol[2]!=wallcolor))
				lwall=0;
			else
				lwall=1;
			checkcol[0]=getpixel(x+7,y-6);	//RIGHT
			checkcol[1]=getpixel(x+7,y);
			checkcol[2]=getpixel(x+7,y+6);
			if((checkcol[0]!=wallcolor)&&(checkcol[1]!=wallcolor)&&(checkcol[2]!=wallcolor))
				rwall=0;
			else
				rwall=1;
			if(dir=='u')
				dwall=1;
			if(dir=='d')
				uwall=1;
			if(dir=='l')
				rwall=1;
			if(dir=='r')
				lwall=1;
			if(x==321&&y==151)
				dwall=1;
			if(x==321&&y==151&&dir=='d')
				lwall=rwall=0;
			if(x==321&&y==165)
				lwall=rwall=1;
			if(x==321&&y==165&&dir=='d')
				lwall=rwall=0;
			if(!mortal&&(y==151||y==235)&&(x==310||x==331))
				uwall=1;
			checkcol[0]=getpixel(x-7,y-7);
			checkcol[1]=getpixel(x-8,y-7);
			checkcol[2]=getpixel(x-7,y-8);
			checkcol[3]=getpixel(x-9,y-7);
			checkcol[4]=getpixel(x-8,y-8);
			checkcol[5]=getpixel(x-7,y-9);
			if((dir=='d'||dir=='r')&&(checkcol[0]==0&&checkcol[1]==0&&checkcol[2]==0)&&(checkcol[3]==wallcolor&&checkcol[4]==wallcolor&&checkcol[5]==wallcolor))
				jn=1;
			checkcol[0]=getpixel(x+7,y-7);
			checkcol[1]=getpixel(x+8,y-7);
			checkcol[2]=getpixel(x+7,y-8);
			checkcol[3]=getpixel(x+9,y-7);
			checkcol[4]=getpixel(x+8,y-8);
			checkcol[5]=getpixel(x+7,y-9);
			if((dir=='d'||dir=='l')&&(checkcol[0]==0&&checkcol[1]==0&&checkcol[2]==0)&&(checkcol[3]==wallcolor&&checkcol[4]==wallcolor&&checkcol[5]==wallcolor))
				jn=1;
			checkcol[0]=getpixel(x-7,y+7);
			checkcol[1]=getpixel(x-8,y+7);
			checkcol[2]=getpixel(x-7,y+8);
			checkcol[3]=getpixel(x-9,y+7);
			checkcol[4]=getpixel(x-8,y+8);
			checkcol[5]=getpixel(x-7,y+9);
			if((dir=='u'||dir=='r')&&(checkcol[0]==0&&checkcol[1]==0&&checkcol[2]==0)&&(checkcol[3]==wallcolor&&checkcol[4]==wallcolor&&checkcol[5]==wallcolor))
				jn=1;
			checkcol[0]=getpixel(x+7,y+7);
			checkcol[1]=getpixel(x+8,y+7);
			checkcol[2]=getpixel(x+7,y+8);
			checkcol[3]=getpixel(x+9,y+7);
			checkcol[4]=getpixel(x+8,y+8);
			checkcol[5]=getpixel(x+7,y+9);
			if((dir=='u'||dir=='l')&&(checkcol[0]==0&&checkcol[1]==0&&checkcol[2]==0)&&(checkcol[3]==wallcolor&&checkcol[4]==wallcolor&&checkcol[5]==wallcolor))
				jn=1;
			if(!jn&&!(x==321&&y==151&&dir=='u')&&!(x==321&&y==165))
			{
				if(dir=='u'||dir=='d')
				{
					lwall=1;
					rwall=1;
				}
				else
				{
					uwall=1;
					dwall=1;
				}
			}
			if(x==321&&y==165)
				uwall=0;
			if(x==309&&y==165)
				rwall=0;
			if(x==333&&y==165)
				lwall=0;

		}
		GHOST()
		{
			x=y=0;
			uwall=dwall=lwall=rwall=1;
			dir='u';
			fright_t=0;
			mortal=0;
		}
		void randir()
		{
			wallcheck();
			int randnum,check=0;
			while(check==0)
			{
				check=1;
				randnum=random(4);
				if(randnum==0&&uwall==0)
					dir='u';
				else if(randnum==1&&dwall==0)
					dir='d';
				else if(randnum==2&&lwall==0)
					dir='l';
				else if(randnum==3&&rwall==0)
					dir='r';
				else
					check=0;
				if(uwall==1&&dwall==1&&lwall==1&&rwall==1)
					exit(0);
			}
		}
		void gmove()
		{
			changemort();
			if(dir=='u'&&uwall==0)
				y--;
			if(dir=='d'&&dwall==0)
				y++;
			if(dir=='l'&&lwall==0)
				x--;
			if(dir=='r'&&rwall==0)
				x++;
			if(x<225)
				x=414;
			if(x>414)
				x=225;
		}
		void RandMove()
		{
			wallcheck();
			randir();
			gmove();
		}
		void Dispghost()
		{
			setcolor(color);
			setlinestyle(0,0,1);
			line(x-5,y-1,x-5,y+5);
			outtextxy(x-4,y-5,gst);
			putpixel(x-4,y-5,0);
			putpixel(x-3,y-5,0);
			putpixel(x+3,y-5,0);
			putpixel(x-4,y-4,0);
			setfillstyle(1,15);
			bar(x-3,y-1,x-1,y+1);
			bar(x+1,y-1,x+3,y+1);
			line(x-4,y+3,x-4,y+5);
			line(x-1,y+3,x-1,y+5);
			line(x-2,y+3,x-2,y+5);
			line(x+1,y+3,x+1,y+5);
			line(x+2,y+3,x+2,y+5);
			line(x+4,y-3,x+4,y+5);
			line(x+5,y-1,x+5,y+5);
			putpixel(x-2,y,0);
			putpixel(x+2,y,0);
			if(dir=='r'||dir=='d')
			{
				putpixel(x-1,y,0);
				putpixel(x-1,y+1,0);
				putpixel(x-2,y+1,0);
				putpixel(x+2,y+1,0);
				putpixel(x+3,y,0);
				putpixel(x+3,y+1,0);
			}
			if(dir=='u')
			{
				putpixel(x-1,y,0);
				putpixel(x-1,y-1,0);
				putpixel(x-2,y-1,0);
				putpixel(x+3,y,0);
				putpixel(x+3,y-1,0);
				putpixel(x+2,y-1,0);
			}
			if(dir=='l')
			{
				putpixel(x-2,y+1,0);
				putpixel(x-3,y+1,0);
				putpixel(x-3,y,0);
				putpixel(x+2,y+1,0);
				putpixel(x+1,y+1,0);
				putpixel(x+1,y,0);
			}
		}
		void revdir()
		{
			if(!(x>=309&&x<=333&&y<=165&&y>151))
			{
				if(dir=='u')
				{
					dir='d';
					wallcheck();
					if(dwall)
						randir();
				}
				else if(dir=='d')
				{
					dir='u';
					wallcheck();
					if(uwall)
						randir();
				}
				else if(dir=='l')
				{
					dir='r';
					wallcheck();
					if(rwall)
						randir();
				}
				else if(dir=='r')
				{
					dir='l';
					wallcheck();
					if(lwall)
						randir();
				}
			}
		}
		void changemort(char a='k')
		{
			if(a=='y')
			{
				mortal=1;
				initial=clock()/CLK_TCK;
				if(level==1)
					fright_t=6;
				if(level==2||level==6||level==10)
					fright_t=5;
				if(level==3)
					fright_t=4;
				if(level==4||level==14)
					fright_t=3;
				if(level==5||level==7||level==8||level==11)
					fright_t=2;
				if(level==9||level==12||level==13||level==15||level==16||level==18)
					fright_t=1;
				if(level>=19||level==17)
					fright_t=0;
				orgcol=color;
				color=1;
			}
			if(a=='n')
				fright_t=0;
			elapsed=clock()/CLK_TCK;
			if(mortal&&fright_t>0&&(elapsed-initial>=fright_t-0.2))
				color=15;
			else if(mortal&&fright_t>0&&(elapsed-initial>=fright_t-0.4))
				color=1;
			else if(mortal&&fright_t>0&&(elapsed-initial>=fright_t-0.6))
				color=15;
			else if(mortal&&fright_t>0&&(elapsed-initial>=fright_t-0.8))
				color=1;
			else if(mortal&&fright_t>0&&(elapsed-initial>=fright_t-1))
				color=15;
			else if(mortal&&fright_t>1&&(elapsed-initial>=fright_t-1.2))
				color=1;
			else if(mortal&&fright_t>1&&(elapsed-initial>=fright_t-1.4))
				color=15;
			else if(mortal&&fright_t>1&&(elapsed-initial>=fright_t-1.6))
				color=1;
			else if(mortal&&fright_t>1&&(elapsed-initial>=fright_t-1.8))
				color=15;
			if(mortal&&(elapsed-initial>=fright_t))
			{
				mortal=0;
				color=orgcol;
				fright_t=0;
			}
		}
		void Find(int pacx,int pacy)
		{
			int relx,rely;
			relx=pacx-x;
			rely=y-pacy;
			wallcheck();
			if(rely-relx<=0&&rely+relx>0&&rwall==0)
				dir='r';
			else if(rely-relx>0&&rely+relx>=0&&uwall==0)
				dir='u';
			else if(rely-relx>=0&&rely+relx<0&&lwall==0)
				dir='l';
			else if(rely-relx<0&&rely+relx<=0&&dwall==0)
				dir='d';
			else
				randir();
			gmove();
		}
		void setdir(char a)
		{	dir=a;}
		void getcoord(int X,int Y)
		{
			x=X;
			y=Y;
		}
		int retx()
		{	return x;}
		int rety()
		{	return y;}
		char retdir()
		{	return dir;}
		int retmortal()
		{	return mortal;}
		double retfright()
		{	return fright_t;}
};

class REDG:public GHOST                       //OIKKAKE
{
	public:
		void Chase(int a,int b)
		{	Find(a,b);}
		void Scatter()
		{	Find(397,56);}
};

class PINKG:public GHOST                      //MACHIBUSE
{
	public:
		void Chase(int a,int b,char pdir)
		{
			if(pdir=='l')
				a-=28;
			if(pdir=='r')
				a+=28;
			if(pdir=='u')
				b-=28;
			if(pdir=='d')
				b+=28;
			Find(a,b);
		}
		void Scatter()
		{	Find(244,56);}
};

class BLUEG:public GHOST                      //KIMAGURE
{
	public:
		void Chase(int a,int b,char pdir,int redx,int redy)
		{
			if(pdir=='l')
				a-=14;
			if(pdir=='r')
				a+=14;
			if(pdir=='u')
				b-=14;
			if(pdir=='d')
				b+=14;
			a=2*a-redx;
			b=2*b-redy;
			Find(a,b);
		}
		void Scatter()
		{	Find(411,295);}
};

class ORANGEG:public GHOST
{
	public:
		void Chase(int a,int b)
		{
			if(Distance(a,b,x,y)>56)
				Find(a,b);
			else
				Find(230,295);
		}
		void Scatter()
		{	Find(230,295);}
};

int size=sizeof(PROFILE);

int VMENU(char menu[][26],int n,int color)
{
	int x,y,i,pos=1,initial=0,length,maxlen;
	x=getx();
	y=gety();
	int maxy=(29-(y/12)<n)?29-(y/12):n;
	maxy*=12;
	maxlen=strlen(menu[0]);
	for(i=1;i<n;i++)
	{
		length=strlen(menu[i]);
		if(length>maxlen)
			maxlen=length;
	}
	maxlen+=1;
	char selector[3]={0,0,0};
	while(!(selector[0]==accept[0]&&selector[1]==accept[1])&&!(selector[0]==back[0]&&selector[1]==back[1]))
	{
		setfillstyle(1,color);
		bar(x-2,y-3,x+(8*maxlen)+2,y+maxy+3);
		for(i=0;i<n&&i<29-(y/12);i++)
		{
			moveto(x,y+12*i);
			if(i==pos-1)
				outtext("*");
			if(i+initial<n)
				outtext(menu[i+initial]);
			else
				outtext(menu[i+initial-n]);
		}
		selector[1]=0;
		selector[0]=getch();
		if(!selector[0])
		{
			selector[1]=1;
			selector[0]=getch();
		}

		if(selector[0]==up[0]&&selector[1]==up[1])
		{
			if(pos==1&&n>29-(y/12))
				initial--;
			else
				pos--;
			if(initial<0)
				initial=n-1;
		}
		if(selector[0]==down[0]&&selector[1]==down[1])
		{
			if(pos==29-(y/12)&&n>29-(y/12))
				initial++;
			else
				pos++;
			if(initial==n)
				initial=0;
		}
		if(pos==0)
			pos=maxy/12;
		if(pos==maxy/12+1)//30-(y/12))
			pos=1;
	}
	if(selector[0]==back[0]&&selector[1]==back[1])
		return -1;
	else if(pos+initial-1<n)
		return (pos+initial-1);
	else
		return (pos+initial-n-1);
}

void VDISP(int n,int color=getbkcolor())
{
	int x,y,i,initial=0;
	x=getx();
	y=gety();
	setcolor(14);
	int maxy=(29-(y/12)<n)?29-(y/12):n;
	PROFILE prof;
	ifstream fs("PROFILES.dat",ios::binary);
	maxy*=12;
	fs.read((char*)&prof,size);
	char selector[3]={0,0,0},caccno[7];
	while(!(selector[0]==accept[0]&&selector[1]==accept[1])&&!(selector[0]==back[0]&&selector[1]==back[1]))
	{
		setfillstyle(1,color);
		bar(x-2,y-3,x+314,y+maxy+15);
		outtextxy(x,y," ACCNO  NAME  NOWINS  MAXLVL MAXSCORE ");
		for(i=0;i<n&&i<29-(y/12);i++)
		{
			if(i+initial<n)
				fs.seekg((i+initial)*size);//outtextxy(x,y+i*12,menu[i+initial]);
			else
				fs.seekg((i+initial-n)*size);
			fs.read((char*)&prof,size);
			itoa(prof.retaccno(),caccno);
			outtextxy(x+8,y+(i+1)*12,caccno);
			outtextxy(x+64,y+(i+1)*12,prof.retname());
			outtextxy(x+112,y+(i+1)*12,prof.retcnowins());
			outtextxy(x+176,y+(i+1)*12,prof.retcmaxlvl());
			outtextxy(x+240,y+(i+1)*12,prof.retcmaxscore());
		}
		selector[1]=0;
		selector[0]=getch();
		if(!selector[0])
		{
			selector[1]=1;
			selector[0]=getch();
		}
		if(selector[0]==up[0]&&selector[1]==up[1]&&maxy!=n*12)
		{
			initial--;
			if(initial<0)
				initial=n-1;
		}
		if(selector[0]==down[0]&&selector[1]==down[1]&&maxy!=n*12)
		{
			initial++;
			if(initial==n)
				initial=0;
		}
	}
	fs.close();
}

struct HIGHSCORE
{
	int score,lvl;
	char name[4],cscore[7],clvl[7];
};

void PRESS_KEY(int Color)
{
	char check='\0';
	int y=350,x,speed,spdchk,txtcolor=4;
	int colorcount=0;
	randomize();
	setfillstyle(1,Color);

	while(check=='\0')
	{
		spdchk=random(3);
		if(spdchk==0)
			speed=4;
		if(spdchk==1)
			speed=6;
		if(spdchk==2)
			speed=8;

		x=5+(random(631)%631);
		y=350;

		for(int i=0;i<381;i+=speed)
		{
			cleardevice();

			settextstyle(0,0,1);
			setcolor(txtcolor);
			colorcount++;
			if(colorcount%4==0||colorcount%4==1)
				txtcolor=6;
			else
				txtcolor=4;

			outtextxy(270,180,"PRESS ANY KEY");

			setcolor(Color);

			if(y>=0&&y<350)
				pieslice(x,y,0,180,5);
			if(y+8>=0&&y+8<350)
				circle(x,y+8,2);
			if(y+16>=0&&y+16<350)
				circle(x,y+16,2);
			if(y+24>=0&&y+24<350)
				circle(x,y+24,2);
			if(y+32>=0&&y+32<350)
				circle(x,y+32,1);
			if(y+40>=0&&y+40<350)
				circle(x,y+40,1);
			if(y+48>=0&&y+48<350)
				putpixel(x,y+48,Color);
			if(y+56>=0&&y+56<350)
				putpixel(x,y+56,Color);
			y-=speed;
			delay(40);

			if(kbhit())
			{
				check=getch();
				cleardevice();
				break;
			}

		}
	}
}

void out(char a[],int x,int y)
{
	char uarrow[2]={24,0},darrow[2]={25,0},larrow[2]={27,0},rarrow[2]={26,0},b[2]={a[0],0};
	char fnkey[4]={'F',0,0,0};
	setcolor(LIGHTGRAY);
	if(a[0]==8&&a[1]==0)
		outtextxy(x,y,"Backspace");
	else if(a[0]==9&&a[1]==0)
		outtextxy(x,y,"Tab");
	else if(a[0]==13&&a[1]==0)
		outtextxy(x,y,"Enter");
	else if(a[0]==27&&a[1]==0)
		outtextxy(x,y,"Esc");
	else if(a[0]==32&&a[1]==0)
		outtextxy(x,y,"Spacebar");
	else if(a[0]==72&&a[1]==1)
		outtextxy(x,y,uarrow);
	else if(a[0]==80&&a[1]==1)
		outtextxy(x,y,darrow);
	else if(a[0]==75&&a[1]==1)
		outtextxy(x,y,larrow);
	else if(a[0]==77&&a[1]==1)
		outtextxy(x,y,rarrow);
	else if((a[0]>=59&&a[0]<=68&&a[1]==1)||(a[0]==-123&&a[1]==1)||(a[0]==-122&&a[1]==1))
	{	fnkey[1]=a[0]-10;
		if(fnkey[1]==58)
		{
			fnkey[1]=49;
			fnkey[2]=48;
		}
		else if(a[0]==-123)
			fnkey[1]=fnkey[2]=49;
		else if(a[0]==-122)
		{
			fnkey[1]=49;
			fnkey[2]=50;
		}
		outtextxy(x,y,fnkey);
	}
	else if(a[0]==71&&a[1]==1)
		outtextxy(x,y,"Home");
	else if(a[0]==73&&a[1]==1)
		outtextxy(x,y,"Pg Up");
	else if(a[0]==76&&a[1]==1)
		outtextxy(x,y,"Num 5");
	else if(a[0]==79&&a[1]==1)
		outtextxy(x,y,"End");
	else if(a[0]==81&&a[1]==1)
		outtextxy(x,y,"Pg Dn");
	else if(a[0]==82&&a[1]==1)
		outtextxy(x,y,"Insert");
	else if(a[0]==83&&a[1]==1)
		outtextxy(x,y,"Delete");
	else
		outtextxy(x,y,b);
}

int NUMMENU(int color,int lwr=1,int upr=32767)
{
	int x,y;
	long opt=lwr;
	char copt[7];
	input[0]=input[1]=0;
	x=getx();
	y=gety();
	setfillstyle(1,color);
	while(kbhit())
		getch();
	while(!(input[0]==accept[0]&&input[1]==accept[1]))
	{
		moveto(x+3,y+2);
		bar(x,y,x+62,y+12);
		if(opt<1000)
			outtext(" ");
		if(opt<10)
			outtext(" ");
		itoa(opt,copt);
		outtext(copt);
		Input();
		if(input[0]==left[0]&&input[1]==left[1])
			opt--;
		if(input[0]==right[0]&&input[1]==right[1])
			opt++;
		if(input[0]==up[0]&&input[1]==up[1])
			opt+=10;
		if(input[0]==down[0]&&input[1]==down[1])
			opt-=10;
		if(input[0]==back[0]&&input[1]==back[1])
			return -1;
		if(opt<lwr)
			opt=upr;
		else if(opt>upr)
			opt=lwr;
	}
	return opt;
}

void main()
{
	clrscr();
	//GRAPHICS DRIVER AND MODE
	int gd=3,gm=1;
	//CIRCLE
	int i,x1,x2,y1,y2,t1,Color;
	float a=320,b=175,r,fy1,fy2,ft1,thickness;
	//COORDINATES
	int x,y;
	//MENU
	char SMdetails[5][13]={"  OPTIONS"," START GAME"," HIGHSCORE","  PROFILES","    QUIT"};
	HMENU smenu(SMdetails,5);
	//GAME
	PACMAN pac;
	REDG red;
	PINKG pink;
	BLUEG blue;
	ORANGEG orange;
	pacdot pdot[240];
	powerpellet ppellet[4];
	Cherry cherry;
	Strawberry strawberry;
	Peach peach;
	Apple apple;
	Grapes grapes;
	Galaxian galaxian;
	Bell bell;
	Key key;
	clock_t current,pacinit,redinit,pinkinit,blueinit,orangeinit,modeinit,dotinit,fruitinit;
	double pacturn,redturn,pinkturn,blueturn,orangeturn,frightime,fruittime;
	int pdotcount,bdotcount,odotcount,gdotcount,pelletcount,elroy1,elroy2,cruiser,dotcount,doteat,pelleteat,pelcheck[4],reat,peat,beat,oeat,killbonus,mode;
	float pacspeed,redspeed,pinkspeed,bluespeed,orangespeed;
	int score,lives,multiplier,died,oneup,namecursor,scorepos,pblock,bblock,oblock;
	int ingameresult,ingamecheck=0;
	char round[7],charpointer[2]={127,0},name[4]="AAA",cscore[7],clevel[7];
	char ingamem[3][26]={"RESUME GAME","QUIT TO MAIN MENU","QUIT TO DESKTOP"};
	//HIGHSCORE
	HIGHSCORE player[10];
	char rank[7];
	fstream filestream;
	//OPTIONS
	char optmenu[3][26]={"CONTROL CONFIG","SET NUMBER OF LIVES","BACK TO MAIN MENU"};
	char ctrlmenu[6][26]={"UP","DOWN","LEFT","RIGHT","ACCEPT","BACK"};
	int maxlife=3,noprofile=1,opt,ctrl;
	char cmaxlife[7];
	//PROFILES
	PROFILE profile,temprof;
	ifstream ifilestream;
	ofstream ofilestream;
	int login=-1,profsearch;
	int passopt,profopt,breakprof;
	char inname[4]="AAA",passtry,inpass[26];
	char cnowins[7],cnolosses[7],cnornds[7];
	char loginm[3][26]={"LOGIN","CREATE ACCOUNT","BACK TO MAIN MENU"};
	char passm[3][26]={"ENTER PASSWORD","USE ANOTHER USERNAME","QUIT TO MAIN MENU"};
	char profm[5][26]={"LOG OUT","VIEW PROFILE","EDIT PROFILE","RESET PROFILE","DELETE PROFILE"};
	char adminm[8][26]={"LOG OUT","VIEW PROFILE","EDIT PROFILE","RESET PROFILE","VIEW ALL PROFILES","DELETE A PROFILE","DELETE ALL PROFILES","CLEAR HIGHSCORES"};
	char editm[2][26]={"CHANGE USERNAME","CHANGE PASSWORD"};
	char aeditm[1][26]={"CHANGE PASSWORD"};
	char deletem[2][26]={"BASED ON ACCOUNT NUMBER","BASED ON USERNAME"};
	int accopt,editopt,delno;

	initgraph(&gd,&gm,"C:\\TurboC3\\BGI");

	//START UP
	/*setbkcolor(15);
	setcolor(RED);
	moveto(205,170);
	settextstyle(0,0,6);
	outtext("Hello");
	for(r=370,Color=0;r>0;r-=5)
	{
		thickness=5;
		if(Color==3)
			Color=0;
		else if(Color==0)
			Color=3;
		x1=a-r;
		x2=a+r;
		for(int i=0;i<r+1;i++)
		{
			fy1=b-sqrt((r-x1+a)*(r+x1-a));
			fy2=b+sqrt((r-x1+a)*(r+x1-a));
			if(((r-thickness-x1+a)*(r-thickness+x1-a))>=0&&x1>=a-r+thickness&&x1<=a+r-thickness)
				ft1=b-sqrt((r-thickness-x1+a)*(r-thickness+x1-a));
			else
				ft1=b;

			if(fy1-(int)fy1>0.5)
				y1=fy1+1;
			else
				y1=fy1;

			if(fy2-(int)fy2>0.5)
				y2=fy2+1;
			else
				y2=fy2;

			if(ft1-(int)ft1>0.5)
				t1=ft1+1;
			else
				t1=ft1;

			while(y1<=t1)
			{
				if(y1>=0&&y1<=350&&y1<=b&&x1>=0&&x1<=640&&x2>=0&&x2<=640)
				{
					putpixel(x1,y1,Color);
					putpixel(x2,y1,Color);
					putpixel(x1,y2,Color);
					putpixel(x2,y2,Color);
				}
				y1++;
				y2--;
			}

			x1++;
			x2--;
		}
	}
	for(r=5,Color=3;r<=370;r+=5)
	{
		thickness=5;

		x1=a-r;
		x2=a+r;
		for(int i=0;i<r+1;i++)
		{
			fy1=b-sqrt((r-x1+a)*(r+x1-a));
			fy2=b+sqrt((r-x1+a)*(r+x1-a));
			if(((r-thickness-x1+a)*(r-thickness+x1-a))>=0&&x1>=a-r+thickness&&x1<=a+r-thickness)
				ft1=b-sqrt((r-thickness-x1+a)*(r-thickness+x1-a));
			else
				ft1=b;

			if(fy1-(int)fy1>0.5)
				y1=fy1+1;
			else
				y1=fy1;

			if(fy2-(int)fy2>0.5)
				y2=fy2+1;
			else
				y2=fy2;

			if(ft1-(int)ft1>0.5)
				t1=ft1+1;
			else
				t1=ft1;

			while(y1<=t1)
			{
				if(y1>=0&&y1<=350&&y1<=b&&x1>=0&&x1<=640&&x2>=0&&x2<=640)
				{
					putpixel(x1,y1,Color);
					putpixel(x2,y1,Color);
					putpixel(x1,y2,Color);
					putpixel(x2,y2,Color);
				}
				y1++;
				y2--;
			}

			x1++;
			x2--;
		}
	}
	cleardevice(); */
	setbkcolor(CYAN);

	while(kbhit())
		getch();
	setcolor(WHITE);
	PRESS_KEY(1);
	cleardevice();

	filestream.open("HIGHSCORE.dat",ios::in|ios::binary);
	if(filestream)
	{
		for(i=0;i<10;i++)
			filestream.read((char*)&player[i],sizeof(player[i]));
	}
	else
		for(i=0;i<10;i++)
		{
			strcpy(player[i].name,"---");
			player[i].score=0;
			player[i].lvl=0;
			itoa(player[i].score,player[i].cscore);
			itoa(player[i].lvl,player[i].clvl);
		}
	filestream.close();

	filestream.open("SETTINGS.dat",ios::in|ios::binary);
	if(filestream)
	{
		filestream.read((char*)&noprofile,sizeof(noprofile));
		filestream.read((char*)&login,sizeof(login));
		filestream.read((char*)&maxlife,sizeof(maxlife));
		filestream.read((char*)&up,sizeof(up));
		filestream.read((char*)&down,sizeof(down));
		filestream.read((char*)&left,sizeof(left));
		filestream.read((char*)&right,sizeof(right));
		filestream.read((char*)&accept,sizeof(accept));
		filestream.read((char*)&back,sizeof(back));
	}
	filestream.close();

	filestream.open("PROFILES.dat",ios::noreplace|ios::out);
	if(filestream)
	{
		temprof.getname("ADM");
		temprof.getpasswrd("ControlFreak101");
		filestream.write((char*)&temprof,size);
	}
	filestream.close();

	if(login!=-1)
	{
		filestream.open("PROFILES.dat",ios::in|ios::binary);
		if(filestream)
		{
			filestream.read((char*)&profile,sizeof(profile));
			while(login!=profile.retaccno())
				filestream.read((char*)&profile,sizeof(profile));
		}
		filestream.close();
	}

	while(smenu.getcurrent()!=4)
	{
		//MENU
		setbkcolor(CYAN);
		settextstyle(0,0,1);
		setfillstyle(9,9);
		setcolor(9);
		setaspectratio(9000,10000);
		pieslice(320,330,45,135,325);
		setcolor(BLUE);
		moveto(3,170);
		outtext("CONTROLS:");
		setcolor(MAGENTA);
		outtextxy(0,186," Left:");
		outtextxy(0,200," Right:");
		outtextxy(0,214," Up:");
		outtextxy(0,228," Down:");
		outtextxy(0,242," Accept:");
		outtextxy(0,256," Back:");
		out(left,48,186);
		out(right,56,200);
		out(up,32,214);
		out(down,48,228);
		out(accept,64,242);
		out(back,48,256);

		setcolor(YELLOW);
		settextstyle(0,0,3);
		outtextxy(263,10,"P");
		outtextxy(321,10,"M");
		settextstyle(0,0,2);
		outtextxy(287,10,"AC ");
		line(287,26,317,26);
		outtextxy(345,10,"AN ");
		line(345,26,375,26);

		setcolor(8);
		settextstyle(0,0,1);
		outtextxy(498,326,"VIVEK B MALIKAYIL");
		outtextxy(498,338,"XII B");

		smenu.getcord(120,100);
		setcolor(BROWN);
		while(!(input[0]==accept[0]&&input[1]==accept[1]))
		{
			smenu.display(2,9);
			Input();
			if(input[0]==left[0]&&input[1]==left[1])
				smenu.Backward();
			if(input[0]==right[0]&&input[1]==right[1])
				smenu.Forward();
			if(input[0]==back[0]&&input[1]==back[1])
			{	while(smenu.getcurrent()!=4)
					smenu.Forward();
			}
		}
		input[1]=0;
		input[0]=0;
		cleardevice();
		setaspectratio(10000,10000);
		settextstyle(0,0,1);

		//INSTRUCTIONS
		/*
			The objective of the game is to clear all the 256 levels
		in a single run. To clear a level, the player must eat every
		pacdot(small yellow dots) and power pellet(bigger yellow dots)
		in the level. When a ghost catches the player, a life is lost.
		If all  the lives of the player is lost, he/she loses the game.
		Whenever pacman(yellow character controlled by the player) eats a
		power pellet, he momentarily gains the power to eat ghosts which
		is indicated by the change in color of the ghosts(to blue).When
		the ghosts are blue, pacman can eat the ghosts and the more number
		of ghosts he eats in a single power-up, more his score will be.
		Beware, as the level increases ,the 'blue time' for the ghosts
		will keep decreasing and eventually the ghosts will not	change
		color at all! When a certain number of pacdots are eaten, a bonus
		fruit appears which last only for a short period of time and if
		eaten will award the player a better score.

			GOOD LUCK!!
		*/

		//GAME
		if(smenu.getcurrent()==1)
		{
			setaspectratio(10000,10000);
			score=ingamecheck=0;
			oneup=1;
			randomize();
			setbkcolor(0);
			setcolor(9);
			setlinestyle(0,0,1);
			setfillstyle(1,9);
			line(226,74,317,74);
			line(317,74,317,102);
			line(317,102,324,102);
			line(324,102,324,74);
			line(324,74,415,74);
			line(226,74,226,137);
			line(415,74,415,137);
			line(226,137,261,137);
			line(380,137,415,137);
			line(261,137,261,165);
			line(380,137,380,165);
			line(226,165,261,165);
			line(380,165,415,165);
			line(226,179,261,179);
			line(380,179,415,179);
			line(261,179,261,207);
			line(380,179,380,207);
			line(226,207,261,207);
			line(380,207,415,207);
			line(226,207,226,242);
			line(415,207,415,242);
			line(226,242,240,242);
			line(401,242,415,242);
			line(226,249,240,249);
			line(401,249,415,249);
			line(240,242,240,249);
			line(401,242,401,249);
			line(226,249,226,284);
			line(415,249,415,284);
			line(226,284,415,284);
			sbar(240,88,261,102,1,1,1,1);
			sbar(275,88,303,102,1,1,1,1);
			sbar(338,88,366,102,1,1,1,1);
			sbar(380,88,401,102,1,1,1,1);
			sbar(240,116,261,123,1,1,1,1);
			sbar(380,116,401,123,1,1,1,1);
			sbar(296,116,345,123,1,1,1,1);
			sbar(275,116,282,165,1,1,1,1);
			sbar(359,116,366,165,1,1,1,1);
			sbar(282,137,303,144,0,1,1,0);
			sbar(338,137,359,144,1,0,0,1);
			sbar(317,123,324,144,0,0,1,1);
			sbar(275,179,282,207,1,1,1,1);
			sbar(359,179,366,207,1,1,1,1);
			sbar(296,200,345,207,1,1,1,1);
			sbar(317,207,324,228,0,0,1,1);
			sbar(296,242,345,249,1,1,1,1);
			sbar(317,249,324,270,0,0,1,1);
			sbar(275,221,303,228,1,1,1,1);
			sbar(338,221,366,228,1,1,1,1);
			sbar(380,221,387,249,1,0,1,1);
			sbar(254,221,261,249,0,1,1,1);
			sbar(240,263,303,270,1,1,1,1);
			sbar(359,242,366,263,1,1,0,0);
			sbar(338,263,401,270,1,1,1,1);
			sbar(275,242,282,263,1,1,0,0);
			sbar(240,221,254,228,1,0,0,1);
			sbar(387,221,401,228,0,1,1,0);
			sbar(296,158,345,186,1,1,1,1);
			setfillstyle(1,0);
			bar(303,159,339,171);
			setcolor(0);
			line(315,158,327,158);
			shavedl(317,102);       //Line corners
			shavedr(324,102);
			shaveur(261,137);
			shaveul(380,137);
			shavedr(261,165);
			shavedl(380,165);
			shaveur(261,179);
			shaveul(380,179);
			shavedr(261,207);
			shavedl(380,207);
			shaveur(240,242);
			shaveul(401,242);
			shavedr(240,249);
			shavedl(401,249);
			for(y=81,x=233,i=0;y<284;x+=7)
			{
				if(getpixel(x,y)!=wallcolor&&getpixel(x+4,y)!=wallcolor&&getpixel(x,y+4)!=wallcolor&&getpixel(x-4,y)!=wallcolor&&getpixel(x,y-4)!=wallcolor&&((x==268)||(x==373)||(y<137)||(y>207))&&!(x==233&&y==95)&&!(x==408&&y==95)&&!(x==233&&y==235)&&!(x==408&&y==235)&&!(x==317&&y==235)&&!(x==324&&y==235))
				{
					pdot[i].x=x;
					pdot[i].y=y;
					i++;
				}
				if(x==415)
				{
					y+=7;
					x=226;
				}
			}
			cherry.x=strawberry.x=peach.x=apple.x=grapes.x=galaxian.x=bell.x=key.x=321;
			cherry.y=strawberry.y=peach.y=apple.y=grapes.y=galaxian.y=bell.y=key.y=193;
			cherry.eat=strawberry.eat=peach.eat=apple.eat=grapes.eat=galaxian.eat=bell.eat=key.eat=0;
			cherry.disp=strawberry.disp=peach.disp=apple.disp=grapes.disp=galaxian.disp=bell.disp=key.disp=0;
			ppellet[0].x=233;
			ppellet[0].y=95;
			ppellet[1].x=408;
			ppellet[1].y=95;
			ppellet[2].x=233;
			ppellet[2].y=235;
			ppellet[3].x=408;
			ppellet[3].y=235;
			level=1;                                                                                                                                                                                                                                                                                                                                                                                        /*BY VIVEK B MALIKAYIL  XII-B  ROLL NO:38*/
			lives=maxlife;
			while(lives>0&&level<257)
			{
				if(level>profile.retmaxlvl())
					profile.maxlvlpp();
				for(i=0;i<240;i++)
				{
					pdot[i].eat=0;
					if(i<4)
					{
						ppellet[i].eat=0;
						pelcheck[i]=0;
					}
				}
				pdotcount=bdotcount=odotcount=gdotcount=dotcount=pelletcount=elroy1=elroy2=cruiser=multiplier=died=0;
				reat=peat=beat=oeat=killbonus=0;
				pacspeed=redspeed=pinkspeed=bluespeed=orangespeed=multiplier=mode=1;
				pac.getcoord(321,235);
				pac.setdir('r');
				pac.display();
				red.getcolor(4);
				red.getcoord(321,151);
				red.wallcheck();
				red.changemort('n');
				red.setdir('l');
				red.Dispghost();
				pink.getcolor(13);
				pink.getcoord(321,165);
				pink.wallcheck();
				pink.changemort('n');
				pink.Dispghost();
				blue.getcolor(3);
				blue.getcoord(309,165);
				blue.changemort('n');
				blue.setdir('r');
				blue.wallcheck();
				blue.Dispghost();
				orange.getcolor(6);
				orange.getcoord(333,165);
				orange.changemort('n');
				orange.setdir('l');
				orange.wallcheck();
				orange.Dispghost();
				setfillstyle(1,14);
				setcolor(14);
				for(i=0;i<240;i++)
				{
					putpixel(pdot[i].x,pdot[i].y,14);
					pdot[i].eat=0;
					if(i<4)
					{
						pieslice(ppellet[i].x,ppellet[i].y,0,360,2);
						ppellet[i].eat=0;
					}
				}
				input[1]=input[0]=0;
				while(kbhit())
					getch();
				pacinit=redinit=pinkinit=blueinit=orangeinit=dotinit=modeinit=(clock()/CLK_TCK)*1000;
				pblock=bblock=oblock=0;
				setcolor(7);
				outtextxy(299,190,"READY!");
				setfillstyle(1,0);
				bar(391,290,415,299);
				setcolor(5);
				itoa(level,clevel);
				outtextxy(343,290,"LEVEL:");
				outtextxy(391,290,clevel);
				delay(2000);
				setfillstyle(1,0);
				bar(299,190,347,198);
				while(lives>0&&(dotcount<240||pelletcount<4))
				{
					//Display Score
					setcolor(5);
					setfillstyle(1,0);
					bar(314,58,362,66);
					bar(278,290,319,299);
					itoa(score,cscore);
					outtextxy(266,58,"SCORE:");
					outtextxy(314,58,cscore);
					outtextxy(228,290,"LIVES:");
					for(i=0,x=0;i<lives;i++,x+=11)
						dispac(282+x,294);
					//Pacman Motion
					if(level==1)
					{
						pacspeed=0.8;
						if(!pac.retmortal())
							pacspeed=0.9;
					}
					else if((level>=2&&level<=4)||level>=21)
					{
						pacspeed=0.9;
						if(!pac.retmortal())
							pacspeed=0.95;
					}
					else
						pacspeed=1;
					pacturn=12.987/pacspeed+0.5;
					if(doteat)
						pacturn+=17;
					if(pelleteat)
						pacturn+=50;
					setfillstyle(1,0);
					current=(clock()/CLK_TCK)*1000;
					if(current-pacinit>=pacturn)
					{
						input[0]=input[1]=0;
						if(kbhit())
						{
							Input();
						}
						ingameresult=-1;
						setcolor(2);
						if(input[0]==back[0]&&input[1]==back[1])
						{
							outtextxy(37,88,"MENU");
							moveto(40,100);
							ingameresult=VMENU(ingamem,3,0);
							setcolor(0);
							bar(37,88,184,136);
						}
						if(ingameresult==1)
						{
							ingamecheck=1;
							break;
						}
						else if(ingameresult==2)
							exit(0);
						bar(pac.retx()-4,pac.rety()-4,pac.retx()+4,pac.rety()+4);
						pac.motion();
						pacinit=(clock()/CLK_TCK)*1000;
						doteat=pelleteat=0;
					}
					//One Up
					if(score>10000&&oneup)
					{
						lives++;
						oneup=0;
					}
					//Pacdot and Power Pellet
					setfillstyle(1,14);
					setcolor(14);
					for(i=0;i<240;i++)
					{
						if(Distance(pdot[i].x,pdot[i].y,pac.retx(),pac.rety())<4&&pdot[i].eat==0)
						{
							putpixel(pdot[i].x,pdot[i].y,0);
							pdot[i].eat=1;
							score+=10;
							doteat=1;
							dotcount++;
							if((dotcount>=220&&level==1)||(dotcount>=210&&level==2)||(dotcount>=200&&level>=3&&level<=5)||(dotcount>=190&&level>=6&&level<=8)||(dotcount>=180&&level>=9&&level<=11)||(dotcount>=160&&level>=12&&level<=14)||(dotcount>=140&&level>=15&&level<=18)||(dotcount>=120&&level<=19))
							{
								elroy1=1;
								cruiser=1;
							}
							if((dotcount>=230&&level==1)||(dotcount>=225&&level==2)||(dotcount>=220&&level>=3&&level<=5)||(dotcount>=215&&level>=6&&level<=8)||(dotcount>=210&&level>=9&&level<=11)||(dotcount>=200&&level>=12&&level<=14)||(dotcount>=190&&level>=15&&level<=18)||(dotcount>=180&&level<=19))
								elroy2=1;
							//Fruit Spawn
							if(dotcount==70||dotcount==170)
							{
								fruitinit=(clock()/CLK_TCK)*1000;
								fruittime=9000+random(1000);
								if(level==1)
									cherry.disp=1;
								else if(level==2)
									strawberry.disp=1;
								else if(level==3||level==4)
									peach.disp=1;
								else if(level==5||level==6)
									apple.disp=1;
								else if(level==7||level==8)
									grapes.disp=1;
								else if(level==9||level==10)
									galaxian.disp=1;
								else if(level==11||level==12)
									bell.disp=1;
								else if(level>=13)
									key.disp=1;
							}
							//Ghost Counter
							if(died)
								gdotcount++;
							else if(pink.retx()==321&&pink.rety()==165)
								pdotcount++;
							else if(blue.retx()==309&&blue.rety()==165)
								bdotcount++;
							else if(orange.retx()==333&&orange.rety()==165)
								odotcount++;
							dotinit=(clock()/CLK_TCK)*1000;
						}
						if(!pdot[i].eat)
							putpixel(pdot[i].x,pdot[i].y,14);
						if(Distance(ppellet[i].x,ppellet[i].y,pac.retx(),pac.rety())<4&&ppellet[i].eat==0&&i<4)
						{
							setfillstyle(1,0);
							setcolor(0);
							pieslice(ppellet[i].x,ppellet[i].y,0,360,2);
							ppellet[i].eat=1;
							pelletcount++;
							score+=50;
							red.revdir();
							red.changemort('y');
							modeinit+=red.retfright();
							if(pblock)
							{
								pink.revdir();
								pink.changemort('y');
							}
							if(bblock)
							{
								blue.revdir();
								blue.changemort('y');
							}
							if(oblock)
							{
								orange.revdir();
								orange.changemort('y');
							}
							pac.changemort('y');
						}
						if(!ppellet[i].eat&&i<4)
							pieslice(ppellet[i].x,ppellet[i].y,0,360,2);
					}
					setfillstyle(1,0);
					bar(315,187,327,199);
					//Fruit Display and Eat
					current=(clock()/CLK_TCK)*1000;
					if(current-fruitinit<=fruittime)
					{
						if(cherry.disp&&Distance(cherry.x,cherry.y,pac.retx(),pac.rety())<4)
						{
							cherry.disp=0;
							score+=100;
						}
						else if(strawberry.disp&&Distance(cherry.x,cherry.y,pac.retx(),pac.rety())<4)
						{
							strawberry.disp=0;
							score+=300;
						}
						else if(peach.disp&&Distance(cherry.x,cherry.y,pac.retx(),pac.rety())<4)
						{
							peach.disp=0;
							score+=500;
						}
						else if(apple.disp&&Distance(cherry.x,cherry.y,pac.retx(),pac.rety())<4)
						{
							apple.disp=0;
							score+=700;
						}
						else if(grapes.disp&&Distance(cherry.x,cherry.y,pac.retx(),pac.rety())<4)
						{
							grapes.disp=0;
							score+=1000;
						}
						else if(galaxian.disp&&Distance(cherry.x,cherry.y,pac.retx(),pac.rety())<4)
						{
							galaxian.disp=0;
							score+=2000;
						}
						else if(bell.disp&&Distance(cherry.x,cherry.y,pac.retx(),pac.rety())<4)
						{
							bell.disp=0;
							score+=3000;
						}
						else if(key.disp&&Distance(cherry.x,cherry.y,pac.retx(),pac.rety())<4)
						{
							key.disp=0;
							score+=5000;
						}
						if(cherry.disp)
							cherry.Disp();
						if(strawberry.disp)
							strawberry.Disp();
						if(peach.disp)
							peach.Disp();
						if(apple.disp)
							apple.Disp();
						if(grapes.disp)
							grapes.Disp();
						if(galaxian.disp)
							galaxian.Disp();
						if(bell.disp)
							bell.Disp();
						if(key.disp)
							key.Disp();
					}
					setcolor(0);
					setfillstyle(1,0);
					//Ghost House
					current=(clock()/CLK_TCK)*1000;
					if((!died&&!pblock&&pdotcount>=0)||(died&&gdotcount==7)||(current-dotinit>=4000&&level<5&&!pblock)||(current-dotinit>=3000&&level>=5&&!pblock))
					{
						pblock=1;
						if(!died)
							pdotcount=0;
						 dotinit=(clock()/CLK_TCK)*1000;
					}
					else if((!died&&!bblock&&((bdotcount>=30&&level==1)||(bdotcount>=0&&level>1)))||(died&&gdotcount==17)||(current-dotinit>=4000&&level<5&&!bblock)||(current-dotinit>=3000&&level>=5&&!bblock))
					{
						bblock=1;
						if(!died)
							bdotcount=0;
						dotinit=(clock()/CLK_TCK)*1000;
					}
					else if((!died&&!oblock&&((odotcount>=60&&level==1)||(odotcount>=30&&level==2)||(odotcount>=0&&level>2)))||(died&&gdotcount>=32)||(current-dotinit>=4000&&level<5)||(current-dotinit>=3000&&level>=5))
					{
						oblock=1;
						if(!died)
							odotcount=0;
						else
						{
							gdotcount=0;
							died=0;
						}
						if(elroy1)
							cruiser=1;
						dotinit=(clock()/CLK_TCK)*1000;
					}
					//Ghost Update
					if(level==1)
					{
						redspeed=pinkspeed=bluespeed=orangespeed=0.75;
						if(elroy1&&cruiser)
							redspeed=0.8;
						if(elroy2&&cruiser)
							redspeed=0.85;
						if(red.retmortal())
							redspeed=0.50;
						if(pink.retmortal())
							pinkspeed=0.50;
						if(blue.retmortal())
							bluespeed=0.50;
						if(orange.retmortal())
							orangespeed=0.50;
					}
					else if(level>=2&&level<=4)
					{
						redspeed=pinkspeed=bluespeed=orangespeed=0.85;
						if(elroy1&&cruiser)
							redspeed=0.90;
						if(elroy2&&cruiser)
							redspeed=0.95;
						if(red.retmortal())
							redspeed=0.50;
						if(pink.retmortal())
							pinkspeed=0.50;
						if(blue.retmortal())
							bluespeed=0.50;
						if(orange.retmortal())
							orangespeed=0.50;
					}
					else
					{
						redspeed=pinkspeed=bluespeed=orangespeed=0.95;
						if(elroy1&&cruiser)
							redspeed=1;
						if(elroy2&&cruiser)
							redspeed=1.05;
						if(red.retmortal())
							redspeed=0.50;
						if(pink.retmortal())
							pinkspeed=0.50;
						if(blue.retmortal())
							bluespeed=0.50;
						if(orange.retmortal())
							orangespeed=0.50;
					}
					if(red.retx()<=232||red.retx()>=409)
						redspeed=(redspeed+0.05)/2;
					if(pink.retx()<=232||pink.retx()>=409)
						pinkspeed=(pinkspeed+0.05)/2;
					if(blue.retx()<=232||blue.retx()>=409)
						bluespeed=(bluespeed+0.05)/2;
					if(orange.retx()<=232||orange.retx()>=409)
						orangespeed=(orangespeed+0.05)/2;
					redturn=12.987/redspeed+0.5;
					pinkturn=12.987/pinkspeed+0.5;
					blueturn=12.987/bluespeed+0.5;
					orangeturn=12.987/orangespeed+0.5;
					setfillstyle(1,0);
					current=(clock()/CLK_TCK)*1000;
					if(current-redinit>=redturn)
					{
						bar(red.retx()-5,red.rety()-5,red.retx()+5,red.rety()+5);
						if(!red.retmortal())
						{
							if(mode==1&&((level>=1&&level<=4&&current-modeinit>=7000)||(level>=5&&current-modeinit>=5000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==2&&current-modeinit>=20000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==3&&((level>=1&&level<=4&&current-modeinit>=7000)||(level>=5&&current-modeinit>=5000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==4&&current-modeinit>=20000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==5&&current-modeinit>=5000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==6&&((level==1&&current-modeinit>=20000)||(level>=2&&level<=4&&current-modeinit>=1033000)||(level>=5&&current-modeinit>=1037000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==7&&((level==1&&current-modeinit>=5000)||(level>=2&&current-modeinit>=17)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							if(mode==1||mode==3||mode==5||mode==7)
								red.Scatter();
							else
								red.Chase(pac.retx(),pac.rety());
						}
						else
							red.RandMove();
						redinit=(clock()/CLK_TCK)*1000;
					}
					if(pblock&&current-pinkinit>=pinkturn)
					{
						bar(pink.retx()-5,pink.rety()-5,pink.retx()+5,pink.rety()+5);
						if(!pink.retmortal())
						{
							if(mode==1&&((level>=1&&level<=4&&current-modeinit>=7000)||(level>=5&&current-modeinit>=5000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==2&&current-modeinit>=20000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==3&&((level>=1&&level<=4&&current-modeinit>=7000)||(level>=5&&current-modeinit>=5000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==4&&current-modeinit>=20000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==5&&current-modeinit>=5000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==6&&((level==1&&current-modeinit>=20000)||(level>=2&&level<=4&&current-modeinit>=1033000)||(level>=5&&current-modeinit>=1037000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==7&&((level==1&&current-modeinit>=5000)||(level>=2&&current-modeinit>=17)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							if(mode==1||mode==3||mode==5||mode==7)
								pink.Scatter();
							else
								pink.Chase(pac.retx(),pac.rety(),pac.retdir());
						}
						else
							pink.RandMove();
						pinkinit=(clock()/CLK_TCK)*1000;
					}
					if(bblock&&current-blueinit>=blueturn)
					{
						bar(blue.retx()-5,blue.rety()-5,blue.retx()+5,blue.rety()+5);
						if(!blue.retmortal())
						{
							if(mode==1&&((level>=1&&level<=4&&current-modeinit>=7000)||(level>=5&&current-modeinit>=5000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==2&&current-modeinit>=20000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==3&&((level>=1&&level<=4&&current-modeinit>=7000)||(level>=5&&current-modeinit>=5000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==4&&current-modeinit>=20000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==5&&current-modeinit>=5000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==6&&((level==1&&current-modeinit>=20000)||(level>=2&&level<=4&&current-modeinit>=1033000)||(level>=5&&current-modeinit>=1037000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==7&&((level==1&&current-modeinit>=5000)||(level>=2&&current-modeinit>=17)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							if(mode==1||mode==3||mode==5||mode==7)
								blue.Scatter();
							else
								blue.Chase(pac.retx(),pac.rety(),pac.retdir(),red.retx(),red.rety());
						}
						else
							blue.RandMove();
						blueinit=(clock()/CLK_TCK)*1000;
					}
					if(oblock&&current-orangeinit>=orangeturn)
					{
						bar(orange.retx()-5,orange.rety()-5,orange.retx()+5,orange.rety()+5);
						if(!orange.retmortal())
						{
							if(mode==1&&((level>=1&&level<=4&&current-modeinit>=7000)||(level>=5&&current-modeinit>=5000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==2&&current-modeinit>=20000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==3&&((level>=1&&level<=4&&current-modeinit>=7000)||(level>=5&&current-modeinit>=5000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==4&&current-modeinit>=20000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==5&&current-modeinit>=5000)
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==6&&((level==1&&current-modeinit>=20000)||(level>=2&&level<=4&&current-modeinit>=1033000)||(level>=5&&current-modeinit>=1037000)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							else if(mode==7&&((level==1&&current-modeinit>=5000)||(level>=2&&current-modeinit>=17)))
							{
								mode++;
								modeinit=(clock()/CLK_TCK)*1000;
							}
							if(mode==1||mode==3||mode==5||mode==7)
								orange.Scatter();
							else
								orange.Chase(pac.retx(),pac.rety());
						}
						else
							orange.RandMove();
						orangeinit=(clock()/CLK_TCK)*1000;
					}
					//Death and Ghost Eat
					if(pac.retmortal())
						multiplier=0;
					if(Distance(red.retx(),red.rety(),pac.retx(),pac.rety())<4)
					{
						bar(red.retx()-5,red.rety()-5,red.retx()+5,red.rety()+5);
						red.getcoord(321,151);
						bar(pink.retx()-5,pink.rety()-5,pink.retx()+5,pink.rety()+5);
						bar(blue.retx()-5,blue.rety()-5,blue.retx()+5,blue.rety()+5);
						bar(orange.retx()-5,orange.rety()-5,orange.retx()+5,orange.rety()+5);
						bar(pac.retx()-4,pac.rety()-4,pac.retx()+4,pac.rety()+4);
						red.setdir('l');
						if(!red.retmortal())
						{
							pac.getcoord(321,235);
							pac.setdir('l');
							pink.getcoord(321,165);
							pblock=0;
							blue.getcoord(309,165);
							bblock=0;
							orange.getcoord(333,165);
							oblock=0;
							modeinit=(clock()/CLK_TCK)*1000;
							mode=1;
							lives--;
							died=1;
							cruiser=0;
						}
						else
						{
							red.changemort('n');
							score+=200*pow(2,multiplier);
							multiplier++;
							if(pac.retx()==233&&pac.rety()==95&&reat==0&&pelcheck[0]==0)
							{
								pelcheck[0]=1;
								reat=1;
							}
							else if(pac.retx()==408&&pac.rety()==95&&reat==0&&pelcheck[1]==0)
							{
								pelcheck[1]=1;
								reat=1;
							}
							else if(pac.retx()==233&&pac.rety()==235&&reat==0&&pelcheck[2]==0)
							{
								pelcheck[2]=1;
								reat=1;
							}
							else if(pac.retx()==408&&pac.rety()==235&&reat==0&&pelcheck[3]==0)
							{
								pelcheck[3]=1;
								reat=1;
							}
						}
					}
					if(Distance(pink.retx(),pink.rety(),pac.retx(),pac.rety())<4)
					{
						bar(pink.retx()-5,pink.rety()-5,pink.retx()+5,pink.rety()+5);
						pink.getcoord(321,165);
						bar(red.retx()-5,red.rety()-5,red.retx()+5,red.rety()+5);
						bar(blue.retx()-5,blue.rety()-5,blue.retx()+5,blue.rety()+5);
						bar(orange.retx()-5,orange.rety()-5,orange.retx()+5,orange.rety()+5);
						bar(pac.retx()-4,pac.rety()-4,pac.retx()+4,pac.rety()+4);
						pblock=0;
						if(!pink.retmortal())
						{
							pac.getcoord(321,235);
							pac.setdir('l');
							red.getcoord(321,151);
							red.setdir('l');
							blue.getcoord(309,165);
							bblock=0;
							orange.getcoord(333,165);
							oblock=0;
							modeinit=(clock()/CLK_TCK)*1000;
							mode=1;
							lives--;
							died=1;
						}
						else
						{
							pink.changemort('n');
							score+=200*pow(2,multiplier);
							multiplier++;
							if(pac.retx()==233&&pac.rety()==95&&peat==0&&pelcheck[0]==0)
							{
								pelcheck[0]=1;
								peat=1;
							}
							else if(pac.retx()==408&&pac.rety()==95&&peat==0&&pelcheck[1]==0)
							{
								pelcheck[1]=1;
								peat=1;
							}
							else if(pac.retx()==233&&pac.rety()==235&&peat==0&&pelcheck[2]==0)
							{
								pelcheck[2]=1;
								peat=1;
							}
							else if(pac.retx()==408&&pac.rety()==235&&peat==0&&pelcheck[3]==0)
							{
								pelcheck[3]=1;
								peat=1;
							}
						}
					}
					if(Distance(blue.retx(),blue.rety(),pac.retx(),pac.rety())<4)
					{
						bar(blue.retx()-5,blue.rety()-5,blue.retx()+5,blue.rety()+5);
						blue.getcoord(309,165);
						bar(red.retx()-5,red.rety()-5,red.retx()+5,red.rety()+5);
						bar(pink.retx()-5,pink.rety()-5,pink.retx()+5,pink.rety()+5);
						bar(orange.retx()-5,orange.rety()-5,orange.retx()+5,orange.rety()+5);
						bar(pac.retx()-4,pac.rety()-4,pac.retx()+4,pac.rety()+4);
						bblock=0;
						if(!blue.retmortal())
						{
							pac.getcoord(321,235);
							pac.setdir('l');
							red.getcoord(321,151);
							red.setdir('l');
							pink.getcoord(321,165);
							pblock=0;
							orange.getcoord(333,165);
							oblock=0;
							modeinit=(clock()/CLK_TCK)*1000;
							mode=1;
							lives--;
							died=1;
						}
						else
						{
							blue.changemort('n');
							score+=200*pow(2,multiplier);
							multiplier++;
							if(pac.retx()==233&&pac.rety()==95&&beat==0&&pelcheck[0]==0)
							{
								pelcheck[0]=1;
								beat=1;
							}
							else if(pac.retx()==408&&pac.rety()==95&&beat==0&&pelcheck[1]==0)
							{
								pelcheck[1]=1;
								beat=1;
							}
							else if(pac.retx()==233&&pac.rety()==235&&beat==0&&pelcheck[2]==0)
							{
								pelcheck[2]=1;
								beat=1;
							}
							else if(pac.retx()==408&&pac.rety()==235&&beat==0&&pelcheck[3]==0)
							{
								pelcheck[3]=1;
								beat=1;
							}
						}
					}
					if(Distance(orange.retx(),orange.rety(),pac.retx(),pac.rety())<4)
					{
						bar(orange.retx()-5,orange.rety()-5,orange.retx()+5,orange.rety()+5);
						orange.getcoord(333,165);
						bar(red.retx()-5,red.rety()-5,red.retx()+5,red.rety()+5);
						bar(pink.retx()-5,pink.rety()-5,pink.retx()+5,pink.rety()+5);
						bar(blue.retx()-5,blue.rety()-5,blue.retx()+5,blue.rety()+5);
						bar(pac.retx()-4,pac.rety()-4,pac.retx()+4,pac.rety()+4);
						oblock=0;
						if(!orange.retmortal())
						{
							pac.getcoord(321,235);
							pac.setdir('l');
							red.getcoord(321,151);
							red.setdir('l');
							pink.getcoord(321,165);
							pblock=0;
							blue.getcoord(309,165);
							bblock=0;
							modeinit=(clock()/CLK_TCK)*1000;
							mode=1;
							lives--;
							died=1;
						}
						else
						{
							orange.changemort('n');
							score+=200*pow(2,multiplier);
							multiplier++;
							if(pac.retx()==233&&pac.rety()==95&&oeat==0&&pelcheck[0]==0)
							{
								pelcheck[0]=1;
								oeat=1;
							}
							else if(pac.retx()==408&&pac.rety()==95&&oeat==0&&pelcheck[1]==0)
							{
								pelcheck[1]=1;
								oeat=1;
							}
							else if(pac.retx()==233&&pac.rety()==235&&oeat==0&&pelcheck[2]==0)
							{
								pelcheck[2]=1;
								oeat=1;
							}
							else if(pac.retx()==408&&pac.rety()==235&&oeat==0&&pelcheck[3]==0)
							{
								pelcheck[3]=1;
								oeat=1;
							}
						}
					}
					if(reat&&peat&&beat&&oeat&&(!killbonus))
					{
						score+=12000;
						killbonus=1;
					}
					//Display Pacman and Ghost
					pac.display();
					red.Dispghost();
					pink.Dispghost();
					blue.Dispghost();
					orange.Dispghost();
				}
				setfillstyle(1,0);
				bar(red.retx()-5,red.rety()-5,red.retx()+5,red.rety()+5);
				bar(pink.retx()-5,pink.rety()-5,pink.retx()+5,pink.rety()+5);
				bar(blue.retx()-5,blue.rety()-5,blue.retx()+5,blue.rety()+5);
				bar(orange.retx()-5,orange.rety()-5,orange.retx()+5,orange.rety()+5);
				bar(pac.retx()-4,pac.rety()-4,pac.retx()+4,pac.rety()+4);
				if(score>profile.retmaxscore())
					profile.getmaxscore(score);
				level++;
				if(ingamecheck==1)
					break;
			}
			input[0]=input[1]=0;
			cleardevice();
			if(level>256)
			{
				setbkcolor(6);
				setcolor(14);
				settextstyle(0,0,2);
				outtextxy(248,159,"YOU WON!!");
				while(kbhit())
					getch();
				getch();
				settextstyle(0,0,1);
				profile.nowinspp();
			}
			else
			{
				setbkcolor(0);
				setcolor(1);
				settextstyle(0,0,2);
				outtextxy(240,159,"GAME OVER");
				while(kbhit())
					getch();
				getch();
				settextstyle(0,0,2);
			}
			if(score>player[9].score&&!ingamecheck)
			{
				setbkcolor(6);
				setcolor(4);
				cleardevice();
				for(i=9;i>=0&&player[i].score<score;i--)
					scorepos=i;
				for(i=9;i>scorepos;i--)
				{
					player[i].score=player[i-1].score;
					player[i].lvl=player[i-1].lvl;
					strcpy(player[i].name,player[i-1].name);
					strcpy(player[i].cscore,player[i-1].cscore);
					strcpy(player[i].clvl,player[i-1].clvl);
				}
				namecursor=0;
				strcpy(name,"AAA");
				settextstyle(0,0,2);
				outtextxy(208,150,"NEW HIGHSCORE!");
				settextstyle(0,0,1);
				player[scorepos].score=score;
				itoa(player[scorepos].score,player[scorepos].cscore);
				player[scorepos].lvl=level-1;
				itoa(player[scorepos].lvl,player[scorepos].clvl);
				if(login==-1)
				{
					settextstyle(0,0,1);
					outtextxy(256,166,"ENTER YOUR NAME:");
					Namein(name,308,178);
					strcpy(player[scorepos].name,name);
				}
				else
				{
					strcpy(player[scorepos].name,profile.retname());
					getch();
				}
			}
			input[0]=input[1]=0;
		}
		cleardevice();

		//HIGHSCORE
		if(smenu.getcurrent()==2)
		{
			setbkcolor(2);
			setcolor(11);
			settextstyle(0,0,2);
			outtextxy(21,19,"HIGHSCORES");
			setfillstyle(1,14);
			bar(6,97,276,110);
			setfillstyle(1,10);
			bar(6,112,276,245);
			setfillstyle(1,6);
			bar(6,61,276,95);
			setcolor(4);
			setlinestyle(0,0,1);
			for(i=0;i<11;i++)
				line(5,96+15*i,277,96+15*i);
			line(5,60,277,60);
			line(5,60,5,246);
			line(53,60,53,246);
			line(101,60,101,246);
			line(157,60,157,246);
			line(277,60,277,246);
			settextstyle(0,0,1);
			setcolor(9);
			outtextxy(13,75,"RANK");
			outtextxy(61,75,"NAME");
			outtextxy(109,75,"SCORE");
			outtextxy(165,75,"LEVEL REACHED");
			setcolor(1);
			for(i=0;i<10;i++)
			{
				itoa(i+1,rank);
				outtextxy(21,98+i*15,rank);
				outtextxy(61,98+i*15,player[i].name);
				outtextxy(103,98+i*15,player[i].cscore);
				outtextxy(189,98+i*15,player[i].clvl);
			}
			while(kbhit())
				getch();
			while(!(input[0]==accept[0]&&input[1]==accept[1])&&!(input[0]==back[0]&&input[1]==back[1]))
				Input();
			input[0]=input[1]=0;
			cleardevice();
		}

		//PROFILES
		else if(smenu.getcurrent()==3)
		{
			setbkcolor(1);
			settextstyle(0,0,1);
			if(login==-1)
			{
				setcolor(14);
				moveto(5,12);
				profopt=VMENU(loginm,3,1);
				cleardevice();
				if(profopt==0)  //LOGIN
				{
					passtry='Y';
					while(login==-1&&passtry=='Y')
					{
						profsearch=0;
						setcolor(14);
						outtextxy(244,108,"ENTER YOUR USERNAME");
						Namein(inname,308,120);
						filestream.open("PROFILES.dat",ios::in|ios::binary);
						if(filestream)
						{
							while((!filestream.eof())&&profsearch==0)
							{
								filestream.read((char*)&profile,sizeof(profile));
								if(!strcmpi(inname,profile.retname()))
									profsearch=1;
							}
						}
						filestream.close();
						if(profsearch==0||(!filestream))
						{
							setcolor(14);
							outtextxy(228,156,"USERNAME does not exist");
							outtextxy(156,168,"Would you like to enter another username?");
							namecursor=0;
							while(!(input[0]==accept[0]&&input[1]==accept[1]))
							{
								bar(308,180,332,196);
								setcolor(4);
								outtextxy(308,180,"Y N");
								outtextxy(308+(8*namecursor),188,charpointer);
								Input();
								if(input[0]==left[0]&&input[1]==left[1]&&namecursor>0)
									namecursor-=2;
								if(input[0]==right[0]&&input[1]==right[1]&&namecursor<2)
									namecursor+=2;
							}
							input[0]=input[1]=0;
							bar(156,156,484,196);
							if(namecursor==0)
								passtry='Y';
							else
								passtry='N';
						}
						else
						{
							while(login==-1)
							{
								cleardevice();
								moveto(5,12);
								setcolor(14);
								passopt=VMENU(passm,3,1);
									cleardevice();
								if(passopt==0)
								{
									passtry='Y';
									while(passtry=='Y'&&login==-1)
									{
										setcolor(4);
										outtextxy(5,12,"USERNAME:");
										outtextxy(77,12,profile.retname());
										setcolor(14);
										outtextxy(244,114,"ENTER YOUR PASSWORD");
										gotoxy(32,10);
										cin>>inpass;
										if(!strcmp(profile.retpasswrd(),inpass))
											login=profile.retaccno();
										else
										{
											setcolor(14);
											outtextxy(256,150,"Invalid PASSWORD");
											outtextxy(208,162,"Would you like to try again?");
											namecursor=0;
											while(!(input[0]==accept[0]&&input[1]==accept[1]))
											{
												bar(308,174,332,190);
												setcolor(4);
												outtextxy(308,174,"Y N");
												outtextxy(308+(8*namecursor),182,charpointer);
												Input();
												if(input[0]==left[0]&&input[1]==left[1]&&namecursor>0)
													namecursor-=2;
												if(input[0]==right[0]&&input[1]==right[1]&&namecursor<2)
													namecursor+=2;
											}
											input[0]=input[1]=0;
											bar(208,126,432,190);
											if(namecursor==0)
												passtry='Y';
											else
												passtry='N';
										}
									}
								}
								if(passopt==1||passopt==-1)
									break;
								if(passopt==2)
								{
									breakprof=1;
									break;
								}
							}
						}
						if(breakprof==1)
						{
							breakprof=0;
							break;
						}
					}
					if(login==-1)
					{
						profile.getname("PLAYER");
						profile.reset();
					}
				}
				else if(profopt==1) //CREATE ACCOUNT
				{
					passtry='Y';
					while(login==-1&&passtry=='Y')
					{
						profsearch=0;
						setcolor(14);
						outtextxy(244,108,"ENTER YOUR USERNAME");
						Namein(inname,308,120);
						filestream.open("PROFILES.dat",ios::in|ios::binary);
						if(filestream)
						{
							while((!filestream.eof())&&profsearch==0)
							{
								filestream.read((char*)&profile,sizeof(profile));
								if(!strcmpi(inname,profile.retname()))
									profsearch=1;
							}
						}
						filestream.close();
						if(profsearch==1)
						{
							setcolor(14);
							outtextxy(228,156,"USERNAME already exists");
							outtextxy(156,168,"Would you like to enter another username?");
							namecursor=0;
							while(!(input[0]==accept[0]&&input[1]==accept[1]))
							{
								bar(308,180,332,196);
								setcolor(4);
								outtextxy(308,180,"Y N");
								outtextxy(308+(8*namecursor),188,charpointer);
								Input();
								if(input[0]==left[0]&&input[1]==left[1]&&namecursor>0)
									namecursor-=2;
								if(input[0]==right[0]&&input[1]==right[1]&&namecursor<2)
									namecursor+=2;
							}
							input[0]=input[1]=0;
							bar(156,156,484,196);
							if(namecursor==0)
								passtry='Y';
							else
								passtry='N';
						}
						else
						{
							while(login==-1)
							{
								cleardevice();
								moveto(5,12);
								setcolor(14);
								passopt=VMENU(passm,3,1);
								cleardevice();
								if(passopt==0)
								{
									setcolor(4);
									outtextxy(5,12,"USERNAME:");
									outtextxy(77,12,inname);
									setcolor(14);
									outtextxy(244,114,"ENTER YOUR PASSWORD");
									gotoxy(32,10);
									cin>>inpass;
									login=noprofile;
									noprofile++;
								}
								if(passopt==1||profopt==-1)
									break;
								if(passopt==2)
								{
									breakprof=1;
									break;
								}
							}
						}
						if(breakprof==1)
						{
							breakprof=0;
							break;
						}
					}
					profile.getname(inname);
					profile.getpasswrd(inpass);
					profile.reset();
					profsearch=0;
					profile.getaccno(login);
					filestream.open("PROFILES.dat",ios::app|ios::binary);
					filestream.write((char*)&profile,sizeof(profile));
					filestream.close();
				}
				cleardevice();
			}
			if(login!=-1)
			{
			//LOGGED IN
				accopt=-2;
				setcolor(14);
				while(kbhit())
					getch();
				while(accopt!=-1&&login!=-1)
				{
					outtextxy(538,5,"LOGGED IN:");
					outtextxy(616,5,profile.retname());
					settextstyle(0,0,2);
					outtextxy(21,19,"PROFILE");
					settextstyle(0,0,1);
					moveto(16,51);
					if(login==0)
					{
						accopt=VMENU(adminm,8,2);
						x=32;
						y=-12;
					}
					else
					{
						accopt=VMENU(profm,5,2);
						x=0;
						y=0;
					}
					setfillstyle(1,1);
					if(accopt==0)    //LOG OUT
					{
						filestream.open("PROFILES.dat",ios::in|ios::out|ios::binary);
						while(filestream.read((char*)&temprof,size))
						{
							if(filestream.eof())
								break;
							filestream.seekg(-1*size,ios::cur);
							if(temprof.retaccno()==profile.retaccno())
								filestream.write((char*)&profile,sizeof(profile));
							else
								filestream.write((char*)&temprof,size);
						}
						filestream.close();
						login=-1;
						profile.getname("PLAYER");
					}
					if(accopt==1)         //VIEW PROFILE
					{
						outtextxy(152+x,63,"PLAYER NAME:");
						outtextxy(248+x,63,profile.retname());
						outtextxy(152+x,87,"HIGHEST SCORE ATTAINED:");
						outtextxy(336+x,87,profile.retcmaxscore());
						outtextxy(152+x,99,"NUMBER OF WINS:");
						outtextxy(272+x,99,profile.retcnowins());
						outtextxy(152+x,111,"HIGHEST LEVEL REACHED:");
						outtextxy(328+x,111,profile.retcmaxlvl());
						getch();
					}
					if(accopt==2)         //EDIT PROFILE
					{
						moveto(154+x,78);
						if(login!=0)
							editopt=VMENU(editm,2,1);
						else
							editopt=VMENU(aeditm,1,1);
						if(editopt==0&&login!=0)
						{
							outtextxy(154+x,99,"ENTER NEW USERNAME:");
							Namein(inname,226+x,111);
							profile.getname(inname);
						}
						if(editopt==1||(login==0&&editopt==0))
						{
							outtextxy(154+x,116+y,"ENTER NEW PASSWORD:");
							gotoxy(21+(x/8),10+(y/12));
							cin>>inpass;
							profile.getpasswrd(inpass);
						}
					}
					if(accopt==3)                   //RESET PROFILE
					{
						profile.reset();
					}
					if(accopt==4&&login!=0)         //DELETE PROFILE
					{
						profile.getname("PLAYER");
						ofstream out("COPY.dat",ios::binary);
						filestream.open("PROFILES.dat",ios::in|ios::binary);
						while(filestream.read((char*)&temprof,size))
						{
							if(filestream.eof())
								break;
							if(temprof.retaccno()!=login)
								out.write((char*)&temprof,size);
						}
						filestream.close();
						out.close();
						remove("PROFILES.dat");
						rename("COPY.dat","PROFILES.dat");
						login=-1;
						noprofile--;
					}
					if(accopt==4)                   //VIEW ALL PROFILES
					{
						moveto(184,99);
						VDISP(noprofile);
					}
					if(accopt==5&&login==0)         //DELETE A PROFILE
					{
						moveto(184,111);
						editopt=VMENU(deletem,2,1);
						if(editopt==0)
						{
							if(noprofile>1)
							{
								int check=0;
								moveto(384,111);
								delno=NUMMENU(1);
								ofstream out("COPY.dat",ios::binary);
								filestream.open("PROFILES.dat",ios::in|ios::binary);
								while(filestream.read((char*)&temprof,size))
								{
									if(filestream.eof())
										break;
									if(temprof.retaccno()!=delno)
										out.write((char*)&temprof,size);
									else
									{
										check=1;
										noprofile--;
									}
								}
								if(!check)
									outtextxy(440,111,"Not Found");
								else
									outtextxy(440,111,"Account Deleted");
								getch();
								filestream.close();
								out.close();
								remove("PROFILES.dat");
								rename("COPY.dat","PROFILES.dat");
							}
							else
							{
								setcolor(4);
								outtextxy(384,111,"*Insufficient number of accounts to delete");
								setcolor(14);
								getch();
							}
						}
						else if(editopt==1)
						{
							if(noprofile>1)
							{
								int check=0;
								Namein(name,384,123);
								setcolor(14);
								ofstream out("COPY.dat",ios::binary);
								filestream.open("PROFILES.dat",ios::in|ios::binary);
								while(filestream.read((char*)&temprof,size))
								{
									if(filestream.eof())
										break;
									if(strcmpi(temprof.retname(),name))
										out.write((char*)&temprof,size);
									else
									{
										check=1;
										noprofile--;
									}
								}
								if(!check)
									outtextxy(440,123,"Not Found");
								else
									outtextxy(440,123,"Account Deleted");
								getch();
								filestream.close();
								out.close();
								remove("PROFILES.dat");
								rename("COPY.dat","PROFILES.dat");
							}
							else
							{
								setcolor(4);
								outtextxy(384,123,"*Insufficient number of accounts to delete");
								setcolor(14);
								getch();
							}
						}
					}
					if(accopt==6)                   //DELETE ALL PROFILES
					{
						remove("PROFILES.dat");
						filestream.open("PROFILES.dat",ios::out);
						if(filestream)
							filestream.write((char*)&profile,size);
						filestream.close();
						noprofile=1;
					}
					if(accopt==7)                         //CLEAR HIGHSCORES
					{
						for(i=0;i<10;i++)
						{
							strcpy(player[i].name,"---");
							player[i].score=0;
							itoa(player[i].score,player[i].cscore);
						}
						filestream.open("HIGHSCORE.dat",ios::out|ios::binary);
						for(i=0;i<10;i++)
							filestream.write((char*)&player[i],sizeof(player[i]));
						filestream.close();
					}
					bar(152+x,63,640,350);
				}
				cleardevice();
			}
		}

		//OPTIONS
		if(smenu.getcurrent()==0)
		{
			setbkcolor(0);
			setcolor(2);
			settextstyle(0,0,2);
			outtextxy(21,19,"OPTIONS");
			settextstyle(0,0,1);
			setcolor(10);
			opt=0;
			ctrl=-1;
			while(opt!=2&&opt!=-1)
			{
				moveto(53,67);
				itoa(maxlife,cmaxlife);
				outtextxy(233,79,cmaxlife);
				if(ctrl==-1)
					opt=VMENU(optmenu,3,0);
				if(opt==0)
				{
					out(up,279,67);
					out(down,279,79);
					out(left,279,91);
					out(right,279,103);
					out(accept,279,115);
					out(back,279,127);
					setcolor(10);
					moveto(217,67);
					ctrl=VMENU(ctrlmenu,6,0);
					if(ctrl>-1)
						outtextxy(361,67+(ctrl*12),"[SELECTED]");
					if(ctrl==0)
					{
						Input();
						if(strcmpi(input,down)&&strcmpi(input,left)&&strcmpi(input,right)&&strcmpi(input,accept)&&strcmpi(input,back))
							strcpy(up,input);
					}
					if(ctrl==1)
					{
						Input();
						if(strcmpi(input,up)&&strcmpi(input,left)&&strcmpi(input,right)&&strcmpi(input,accept)&&strcmpi(input,back))
							strcpy(down,input);
					}
					if(ctrl==2)
					{
						Input();
						if(strcmpi(input,up)&&strcmpi(input,down)&&strcmpi(input,right)&&strcmpi(input,accept)&&strcmpi(input,back))
							strcpy(left,input);
					}
					if(ctrl==3)
					{
						Input();
						if(strcmpi(input,up)&&strcmpi(input,down)&&strcmpi(input,left)&&strcmpi(input,accept)&&strcmpi(input,back))
							strcpy(right,input);
					}
					if(ctrl==4)
					{
						Input();
						if(strcmpi(input,up)&&strcmpi(input,down)&&strcmpi(input,left)&&strcmpi(input,right)&&strcmpi(input,back))
							strcpy(accept,input);
					}
					if(ctrl==5)
					{
						Input();
						if(strcmpi(input,up)&&strcmpi(input,down)&&strcmpi(input,left)&&strcmpi(input,right)&&strcmpi(input,accept))
							strcpy(back,input);
					}
				}
				if(opt==1)
				{
					moveto(217,77);
					maxlife=NUMMENU(0,1,3);
				}
				setfillstyle(1,0);
				bar(217,67,441,139);
			}
			input[0]=input[1]=0;
			cleardevice();
		}

		//INSTRUCTIONS
		/*if(smenu.getcurrent()==3)
		{
		}*/

		if(login!=-1)
		{
			filestream.open("PROFILES.dat",ios::in|ios::out|ios::binary);
			while(filestream.read((char*)&temprof,size))
			{
				if(filestream.eof())
					break;
				filestream.seekg(-1*size,ios::cur);
				if(temprof.retaccno()==profile.retaccno())
					filestream.write((char*)&profile,sizeof(profile));
				else
					filestream.write((char*)&temprof,size);
			}
			filestream.close();
		}
	}

	filestream.open("SETTINGS.dat",ios::out|ios::binary);

	filestream.write((char*)&noprofile,sizeof(noprofile));
	filestream.write((char*)&login,sizeof(login));
	filestream.write((char*)&maxlife,sizeof(maxlife));
	filestream.write((char*)&up,sizeof(up));
	filestream.write((char*)&down,sizeof(down));
	filestream.write((char*)&left,sizeof(left));
	filestream.write((char*)&right,sizeof(right));
	filestream.write((char*)&accept,sizeof(accept));
	filestream.write((char*)&back,sizeof(back));

	filestream.close();

	filestream.open("HIGHSCORE.dat",ios::out|ios::binary);
	for(i=0;i<10;i++)
		filestream.write((char*)&player[i],sizeof(player[i]));
	filestream.close();

	closegraph();
}