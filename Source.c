#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>





typedef struct playersdata{
	char* name;                   // four txt file...
	int gamehours;
	char* favoritgun;
	int price;
}PLAYER;
typedef struct players{
	PLAYER data;           
	struct players*next;
	struct players *prev;
}players;

void print(players*str)
{
	players*act=str->next;
	while(act->next!=NULL)
	{
		printf("%d\n", act->data.gamehours);
		act=act->next;
	}
}

players* emptylist()    //make emptylist
{
	players*str1;
	players*str2;
	str1=(players*)malloc(sizeof(players));
	str2=(players*)malloc(sizeof(players));
	str1->next=str2;
	str1->prev=NULL;
	str2->prev=str1;
	str2->next=NULL;
	return str1;
}
void newnode(players*head,char* name,int gamehours,int price,char* favourite)   //új elem létrehozása
{
	players* ujelem=(players*)malloc(sizeof(players));
	ujelem->data.name=(char*)malloc(sizeof(char)*21);
	ujelem->data.favoritgun=(char*)malloc(sizeof(char)*26);
	ujelem->data.price=price;
	ujelem->data.gamehours=gamehours;
	strcpy(ujelem->data.name,name);
	strcpy(ujelem->data.favoritgun,favourite);
	ujelem->next=head->next;
	head->next->prev=ujelem;
	head->next=ujelem;
	ujelem->prev=head;

}
int sizeof_list(players*str)
{
	players*act=str->next;
	int cnt=0;
	while(act->next!=NULL)
	{
		act=act->next;
		cnt++;
	}
	return cnt;
}
void change(players*act)
{
	players*tmp;
	tmp=act;
	act=act->next;
	tmp->next=act->next;
	act->next->prev=tmp;
	act->next= tmp;
	act->prev= tmp->prev;
	tmp->prev->next= act;
	tmp->prev=act;
	
}
void settlement(players*str)   //elsõ elem
{
	players*act=str->next;
	int cnt= sizeof_list(str);
	int i;
	int j;
	  for (i = cnt-1; i > 0; --i)
	  {
      /* egymás utáni párok ciklusa */
		  for (j = 0; j < i; ++j)
		  {
			  if(act->data.gamehours<act->next->data.gamehours)
			  {
				  change(act);
			  }
			  act=act->next;
		  }
		  act=str->next;
	  }


	
}


double awg(players*str)
{
	double cnt=0.0;
	double sum= 0.0;

	players*act=str->next;
	while(cnt<4.0)
	{
		sum=sum+act->data.price;
		cnt++;
		act=act->next;}
	return sum/cnt;
}


void upload(players*str)
{
	FILE* ellenorzes=fopen("ellenorzes.txt", "w");
	players* act= str->next;
	while(act->next!=NULL)
	{
		fprintf(ellenorzes, "%s:%d, %s, %d\n", act->data.name, act->data.gamehours, act->data.favoritgun, act->data.price);
		printf("%s: Gamehours:%d, His favourite gun:%s, Price of this:%d$\n", act->data.name, act->data.gamehours, act->data.favoritgun, act->data.price);
		act=act->next;
	}
	fclose(ellenorzes);
}



int main()
{
	double awarage;
	FILE*name=fopen("nev.txt", "r");
	FILE*price=fopen("price.txt", "r");
	FILE* gamehours= fopen("gamehours.txt", "r");
	FILE* favoritgun= fopen("favorit.txt", "r");
	players*str1=emptylist();
	players*act=str1->next;
	char NAME[21];
	int PRICE;
	int GAMEHOURS;
	char FAVORITGUN[26];
	while (fscanf(name,"%s", NAME)==1)
	{
		fscanf(price, "%d", &PRICE);
		fscanf(gamehours, "%d", &GAMEHOURS);
		fscanf(favoritgun,"%s", FAVORITGUN);
		/*printf("%s,%d,%d,%s", NAME,PRICE,GAMEHOURS,FAVORITGUN);*/
		newnode(str1,NAME, GAMEHOURS,PRICE,FAVORITGUN);
		
	}
	fclose(name);
	fclose(price);
	fclose(gamehours);
	fclose(favoritgun);
	settlement(str1);
	awarage=awg(str1);
	printf("Avarage:%lf $\n", awarage); 
	upload(str1);
	while(act->next!=NULL)
	{
		players*megjegyez=act->next;
		free(act->next->data.favoritgun);
		free(act->next->data.name);
		free(act->next);
		act=megjegyez->next;
	}


	return 0;
}
	
