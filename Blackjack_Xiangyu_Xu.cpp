#include <iostream>   
#include <ctime> 
#include <iomanip>  
#include "game_define.h"
using namespace std;

//Initialize the related variables
void initialize()  
{
		p_t=d_t=0;
		p_po=d_po=0;
		p_st=false;
		p_l=false;
		d_l=false;
		p_jack=false;
		push=false;
		
}

//Set the gambling information
void Info()
{
	cout<<"You have played "<<nWin+nLose+nDraw<<" rounds in total, "<<"won "<<nWin<<" rounds, "<<"lost "
	<<nLose<<" rounds, "<<"and drew "<<nDraw<<" rounds.\n\n";
	cout<<"You have $"<<nChips<<" in your pocket.\n\n";
} 

//Gambling rules
int SetGam(int gamble)
 {
 	if(nChips-gamble<0) //You don't have enough money
 	    return 1;
    if(gamble<1)
    {
    	cout<<"\nI assume that you are chipping in $1.\n\n";
		nGam=1;  //Every amount smaller than $1 will be viewed as $1
	}
	else
	  nGam=gamble;
	  nChips-=nGam;
	  return 0;
 }
   
//Deal the Player
void d_p()
{
	deal();
	int i=0;
	while(C_card.abbr[i]!= '\0')
	{
		p_h[p_po]=C_card.abbr[i];
		i++;
		p_po++;
	}
	p_h[p_po] = '\0';
	p_po++;
	switch(C_card.name)
	{
		case two:case three:case four:case five:case six:case seven:case eight:case nine:case ten:
		p_t+=C_card.name+1;break;
		case jack:case queen:case king:
		p_t+=10;break;
		case ace:
		p_t+=11;break; 
	}
}

// Deal the Dealer
void d_d()
{
	deal();
	int i=0;
	while(C_card.abbr[i]!= '\0')
	{
		d_h[d_po]=C_card.abbr[i];
		i++;
		d_po++;
	}
	d_h[d_po]='\0';
	d_po++;
	switch(C_card.name)
	{
		case two:case three:case four:case five:case six:case seven:case eight:case nine:case ten:
		d_t+=C_card.name+1;break;
		case jack:case queen:case king:
		d_t+=10;break;
		case ace:
		d_t+=11;break; 
	}
}

// Deal
void deal()
{
	int name,suit;
	do
	{
	name=rand()%13;
	suit=rand()%4;
	}
	while(cards[name][suit]);
	C_card.name=name;
	C_card.suit=suit;
	cards[name][suit]=true;
	
	for(int i=0;i<4;i++) C_card.abbr[i]='\0';  //Display the card number and suit 
	switch(name)
	{
		case ace:
		C_card.abbr[0]='A';
		C_card.abbr[1]=' ';break;
		case two:case three:case four:case five:case six:case seven:case eight:case nine:
		C_card.abbr[0]='0'+name+1;
		C_card.abbr[1]=' ';break;
		case ten:
		C_card.abbr[0]='1';
		C_card.abbr[1]='0';break;
		case jack:
		C_card.abbr[0]='J';
		C_card.abbr[1]=' ';break;
		case queen:
		C_card.abbr[0]='Q';
		C_card.abbr[1]=' ';break;
		case king:
		C_card.abbr[0]='K';
		C_card.abbr[1]=' ';break;
	}
	C_card.abbr[2]=suit+3;
}

// Dealer's Move
void m_d()
{
	if(p_jack)  // Player's Blackjack while dealer's not
		{
			w_p();
			return;
		}
	if(p_l)  // Normal player's lose case(dealer's Blackjack or player's bust)
		{
			w_d();
			return;
		}
	if(push)  // Both player and dealer have Blackjack
		{
			cout<<"\n***PUSH***\n";
			nDraw++;
			nChips+=nGam;
			return;
		}
	if(d_st)  // Dealer's first two card add up to a value greater than 17
		{
			cout<<setw(100)<<"\nYour Hand: "<<setw(49)<<"Dealer's Hand: \n"<<"----------"<<setw(51)<<"--------------- \n"<<setw(61)   
        	<<"The hole card is "<<&back_up[0]<<"\n\n"<<"TOTAL : "<<p_t<<setw(42)<<"TOTAL : "<<d_t<<"\n\n";
			wait(2);
		}
	else	// Deal the dealer
		{
			d_d();
			outcome_2();
			wait(2);
		}
	
	while(d_t<p_t&&d_t<17) // Deal the dealer again
		{
			d_d();
			outcome_2();
			wait(2);
		}
	if(d_t==p_t)
		{
			cout<<"\n***PUSH***\n";
			push=true;
			nDraw++;
			nChips+=nGam;
			return;
		}
	if(d_t>21)
		{
			cout<<"\n***DAMN, I BUST***\n";
			w_p();
			return;
		}
	if(d_t>p_t)
 		w_d();
	else
		w_p();
	return;
}

// Reset Hand Card
void reset_h()
{
	for(int i=0;i<32;i++)
	p_h[i]=d_h[i]='0';
}

//The Rules
void rules()
{
	if(rules_f)  //First round, each side has 2 cards
	{
		if(p_t==21) //Player has Blackjack
		{   
      		cout<<"\n***You have BLACKJACK!!***\n";
      		wait(1);
			cout<<setw(100)<<"\nYour Hand: "<<setw(49)<<"Dealer's Hand: \n"<<"----------"<<setw(51)<<"--------------- \n"<<setw(61)   
        	<<"The hole card is "<<&back_up[0]<<"\n\n"<<"TOTAL : "<<p_t<<setw(42)<<"TOTAL : "<<d_t<<"\n\n";
			wait(1);
			if(d_t==21) //Dealer also has Blackjack, leading to a push
				{
					p_st = true;
					push = true;
					wait(2);
				}     
   			else  //Dealer doesn't have Blackjack, and the player wins
			   {
	   				cout<<"\n***You win!! And you get extra 1x wager back!!!***\n";
			   		p_jack = true;   
      				p_st = true;
					nChips+=nGam;     
      				wait(2);
			   }
    	}
		else if(d_t==21) //Dealer has Blackjack while player doesn't
		{
			cout<<setw(100)<<"\nYour Hand: "<<setw(49)<<"Dealer's Hand: \n"<<"----------"<<setw(51)<<"--------------- \n"<<setw(61)   
        	<<"The hole card is "<<&back_up[0]<<"\n\n"<<"TOTAL : "<<p_t<<setw(42)<<"TOTAL : "<<d_t<<"\n\n";
			wait(1);
			cout<<"\n***I have BLACKJACK!!***\n";
			wait(1);
			p_st = true;
			p_l = true;
			wait(2);
		}
		else if (d_t>=17) //None has Blackjack, and dealer reaches over 17, no more dealing to the dealer
		{
			d_st = true;
		}   
	}
	
	else
	{
		if(p_t==21)
		{
			cout<<"\n***You reach 21 and stand.***\n";
			p_st= true;
			wait(2);
		}
		else if(p_t>21)
		{
			cout<<"\n***Bad luck, you bust.***\n";
			p_l = true;
		}
	}
	rules_f=false;
	return;
}

//Shuffle
void shuffle()
{
	for(int i=1;i<13;i++)
		for(int j=3;j<6;j++)
			cards[i][j]=false;
}

//Output
void outcome()  //Display the cards on both sides, with dealer's hole card facing down
{   
       cout<<setw(100)<<"\nYour Hand: "<<setw(49)<<"Dealer's Hand: \n"<<"----------"<<setw(51)<<"--------------- \n"<<&p_h[0]<<"  "<<&p_h[4]<<setw(39)   
        <<&d_h[0]<<"  "<<&d_h[4]<<"\n\n"<<"TOTAL : "<<p_t<<setw(42)<<"TOTAL : "<<"You don't know!"<<"\n\n";   
       
}   

void outcome_1()  //Display the player's new card, with dealer's hole card facing down
{   
       cout<<setw(100)<<"\nYour Hand: "<<setw(49)<<"Dealer's Hand: \n"<<"----------"<<setw(51)<<"--------------- \n"<<&p_h[p_po-4]<<setw(45)   
        <<&d_h[0]<<"  "<<&d_h[4]<<"\n\n"<<"TOTAL : "<<p_t<<setw(42)<<"TOTAL : "<<"You don't know!"<<"\n\n";   
       
}   

void outcome_2()  //Dealer's move, display the dealer's hole card and new card
{   
       cout<<setw(100)<<"\nYour Hand: "<<setw(49)<<"Dealer's Hand: \n"<<"----------"<<setw(51)<<"--------------- \n"<<setw(61)   
        <<"The hole card is "<<&back_up[0]<<"\n"<<setw(214)<<"New card: "<<&d_h[d_po-4]<<"\n\n"<<"TOTAL : "<<p_t<<setw(42)<<"TOTAL : "<<d_t<<"\n\n";   
       
}   

//Pause in the game
void wait(int a=1) 
{   
  if(a<1) return;   
  int i;   
  for(int x=0;x<a;x++) 
  {   
    i = (unsigned)time(NULL);   
    while(i==time(NULL));   
  }   
}

//Outcomes
void w_d()
{
	cout<<"\n***Dealer Wins!***\n";
	nLose++;
}
void w_p()
{
	cout<<"\n***Player Wins!***\n";
	nWin++;
	nChips+=2*nGam;
}

//Play again?
char try_again()
{   
    char again='n';   
    do
	{   
        cout<<"\nYou have $"<<nChips<<" in your pocket.\n\n";
		cout<<"\n***Another try (Y/y or N/n)?***\n";   
        cin>>again;   
        if ((again!='n')&&(again!='N')&&(again!='y')&&(again!='Y'))   
        {   
            cout<<"\n"<<again<<" is not acceptable, re-enter please\n"<<endl;   
        }   
    }
	while((again!='n')&&(again!='N')&&(again!='y')&&(again!='Y'));   
    return(again);   
}   

//Main Function
int main()
{
	cout<<"Hi!! I'm Xiangyu Xu! Welcome to my world and try your luck with Blackjack!\n\n";
	srand((unsigned)time(NULL));
	bool playing=true;
	nChips=100;
	nGam=0;
	nWin=nLose=nDraw=0;
	
	do
	{
		while(nChips<=0)   //When your pocket is empty, you are expelled from the gambling 
		{
			cout<<"\nSorry kid, but you've lost all your money. Now go coding, and come on your next pay day!!\n\n";
			wait(3);
			exit(0);
		}
		initialize();
		Info();
		
		int Logic=0; 
		do   // Chip in: input string that contains anything other than numbers will be viewed invalid
		{
			int nMoney=0;
			cout<<"\nNow, how much do you like to chip in?? (1 chip at least)\n\n";
			char c;
			while(c = cin.get(), c!='\n')
				{
					if(isdigit(c))
						{
                    		nMoney = nMoney*10 + c-'0'; 
                		}
    				else
						{
                    	nMoney = -1;
                    	while (cin.get() != '\n') continue;
                    	cout<<"\nPlease enter a valid number for chipping in!\n\n";
                    	break;
                		}
            	}
     		if(nMoney != -1)
			 	{
                	Logic=SetGam(nMoney);
					if(Logic)
						{
							cout<<"\nYou don't have enough money, plz chip in again! \n\n";
						}
            	}
			else
				{
                	nMoney = 0;
                	Logic = 1;
            	}
		}while (Logic);
		
		shuffle();
		reset_h();
		cout<<"\nPress (H/h) to hit, (S/s) to stay, and (L/l) to leave, good luck~\n\n";
		d_p();d_p();
		d_d();
		back_up[0]=d_h[0];back_up[1]=d_h[1];back_up[2]=d_h[2];  //tricks of displaying the hole card
		d_d();
		
		d_h[0]='?';
		d_h[1]='?';
		d_h[2]='?';
	 	outcome();
	 	rules_f=true;
	 	rules();
	 	
	 	while(!p_st && !p_l)
	 	{
	 		c=0x00000000;
	 		while(c!='h'&&c!='H'&&c!='s'&&c!='S'&&c!='l'&&c!='L')
 			c= getchar();
	 	
	 		switch(c)
			 	{
		 		case 'l': case 'L': //Quit the game 
				  cout<<"\nAre you sure to quit game?? (Y/y to quit or any other key to remain)\n";
				  char quit;
				  cin>>quit;
				  while(quit=='y'||quit=='Y')
			  	   {
				  cout<<"\n-->QUIT\n";   
			 	  exit(0);
				   }
				  cout<<"\nHit or stay, man??\n";    
				  playing = true; p_st = false; break;   
        		case 'h': case 'H':
				  cout<<"\n-->HIT!\n"; wait(1);  //Choose to hit   
                  d_p(); outcome_1(); rules();   
                  if(p_l) wait(1); break;   
        		 
        		case 's': case 'S':
				  cout<<"\n-->STAND.\n"; wait(1);  //Choose to stand   
                  p_st = true; break;   
		 	    }
	 	}
	 	m_d();
	 	run_again=try_again();
	 	if((run_again=='Y')||(run_again=='y'))
	 	{
	 		cout<<endl;
	 		cout<<"*****************************************"<<endl;
	 		cin.clear();
        	cin.ignore();
	 	}
	 	else if((run_again=='N')||(run_again=='n'))
	 	{
	 		cout<<endl;
	 		cout<<"\nSee you next time!!\n\n";
			wait(2); 
	 		break;
	 	}
	}while ((run_again!='n') && (run_again!='N'));
}
