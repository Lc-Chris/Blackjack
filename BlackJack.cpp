// 21-point game

# include <iostream>
# include <ctime>
# include <cstdlib>
# include <cstring>
using namespace std;

int assignCards();
void display(int);
double player();
void computer();
extern int playercardnum;  // The number of player's cards 
extern int com_card[20],player_card[20];      

int main()
{
	char yorn[100],Yorn;       // Create an array to accept the input.
	srand(time(NULL));
	
	while(true){
		try{	                             //Using try-throw-catch structure to report wrong inputs. 
			cout <<"Do you want to play? (Y or N) ";
			cin>>yorn;
			if (strlen(yorn) != 1) throw(1);
	    	Yorn = yorn[0];
			if(Yorn != 'N' && Yorn != 'n' && Yorn != 'Y' && Yorn != 'y') throw(1);
		}
		catch(int) {cout << "Wrong input! Plese enter again!\n"; continue;}
		if (Yorn=='y' || Yorn=='Y')	computer();
		else if (Yorn=='n' || Yorn=='N') break;
	}
	
	return 0;	
} 

int assignCards()           // To generate a card.
{
	int cardNum;	
	cardNum=rand()%52;	
	return cardNum;
}

void display( int cardNum)    // To display the color and number of the card.
{
	int number;
	number=cardNum%13+1;
	
	switch (cardNum/13){
		case 0: cout << "Heart ";break; 
		case 1: cout << "Spade "; break;
		case 2: cout << "Club "; break;
		case 3: cout << "Diamond "; break;
	}
	
	if (number<=10 && number>=1) cout <<number;
	else{
		switch (number){
			case 1 :cout << 'A';break;
			case 11 :cout << 'J';break;
			case 12 :cout << 'Q';break;
			case 13 :cout << 'K';break;
		}
	}
	cout <<' ';	
}

double player()                      // The player's turn.
{
	int player_card[20]={0};
	int i,j=2,k,number,playercardnum;   //playercardnum represents the number of player's cards 
	double player_sum;                  // The sum of card numbers of hte player.
	char yorn[100],Yorn;
	bool isSame;                  //To make sure that each two cards are different.
	
	cout<<"Player's turn."<<endl;
	cout<<"The player got the cards: ";
	
	player_card[0]=assignCards();
	do player_card[1]=assignCards(); 
		while(player_card[1]==player_card[0]);
	display(player_card[0]);display(player_card[1]);
	for (k=0;k<=1;++k) {	
	 	number=player_card[k]%13+1;
	 	if (number<=10) player_sum+=number;
	 	else player_sum+=0.5;
	}
			
 	while (true){
	 	try{
	 		cout<<"\nDo you want another card? (Y or N)  ";
	 		cin>>yorn;
	 		if (strlen(yorn) != 1) throw(1);
		    Yorn = yorn[0];
			if(Yorn != 'N' && Yorn != 'n' && Yorn != 'Y' && Yorn != 'y') throw(1);
		}
		catch(int) {cout << "Wrong input! Plese enter again!\n"; continue;}
 		if (Yorn=='y'|| Yorn=='Y'){
 			player_sum=0;	
 			player_card[j]=assignCards();
 			while (true){                   //To make sure that each two cards are different.
 				isSame=false;
				for (k=0;k<j;++k) isSame=(player_card[j]==player_card[k]) || isSame;
				if (isSame==false) break;
				player_card[j]=assignCards();
			}
			 				
		 	cout<<"Another card wanted: ";
		 	
		 	for (k=0;k<=j;++k) {	
			 	display(player_card[k]);
			 	number=player_card[k]%13+1;
			 	if (number<=10) player_sum+=number;
			 	else player_sum+=0.5;
			}
		 	++j;	
		 	if (player_sum>21.0) {
		 		cout<< "\nComputer wins!"<<endl;
		 		break;
			 }
		}
		if (Yorn=='n'||Yorn=='N')  break;
	 	playercardnum=k;       // To remember the cards' number of the player. 
	}                          
	return player_sum;
}

void computer()              // The computer's turn.
{
	int com_card[20]={0};
	int k,j=1,number,playercardnum;
	double com_sum,player_sum;
	bool goOn=true;                //To determine whether player's sum is greater than 21.
	bool isSame;                  //To make sure that each two cards are different.
	
	player_sum=player();               // Accept the return value and execute the "player" function.
	if (player_sum>21.0) goOn=false;  // This means the player has already lost the game.
		
	if(goOn){
		cout<<"Computer's turn.\nThe computer got the cards: ";	
		com_card[0]=assignCards();
		do com_card[1]=assignCards(); 
			while(com_card[1]==com_card[0]);
		display(com_card[0]);display(com_card[1]);
		
		while (true){
			com_sum=0;
			for (k=0;k<=j;++k){
				number=com_card[k]%13+1;
				if (number<=10) com_sum+=number;
			 	else com_sum+=0.5;
			}		
			if (com_sum>player_sum && com_sum<=21) {                     // To judge who is winner.
				cout<<"\nComputer wins!"<<endl;	break;
			} 
			else if (com_sum==player_sum && player_sum==21){
				if (k==playercardnum) cout<<"It is a tie!" <<endl;
				else cout<<(k<playercardnum? "\nComputer wins!":"\nPlayer win!")<<endl;
				break;
			}
			else if (com_sum>21){	
				cout<<"\nYou win!"<<endl;break;
			}					
			++j;
			com_card[j]=assignCards();
			while (true){
				isSame=false;
				for (k=0;k<j;++k) isSame=(com_card[j]==com_card[k]) || isSame;
				if (isSame==false) break;
				com_card[j]=assignCards();
			}
			cout<<"\nAnother card got:";
	 		for (k=0;k<=j;++k)	display(com_card[k]);
		}
	}	 		
}
















