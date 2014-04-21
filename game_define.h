#define hearts 0
#define diamonds 1
#define clubs 2
#define spades 3

#define ace 0 
#define two 1 
#define three 2 
#define four 3 
#define five 4 
#define six 5 
#define seven 6 
#define eight 7 
#define nine 8 
#define ten 9 
#define jack 10
#define queen 11 
#define king 12

int nChips;  //Your money
int nGam;  //How much you chip in
int nWin;  //number of rounds you've won
int nLose; 
int nDraw;
void win();  // Calculate the chips if you win
void lose();
void draw();
int SetGam(int); // Decide chip in number, returns '-1' if not enough money
void initialize ();
void Info();  //Display the game information

class card 
{   
public:   
  char abbr[4]; // display cards 
  int name;    //card's name   
  int suit;    //card's suit    
} C_card;   
   
void d_p(); //deal player   
void d_d(); //deal dealer   
void deal();        //deal the cards   
void m_d();    //dealer's move   
void reset_h();  //reset the handcards   
void rules();      //game rules   
void shuffle();    //shuffle the cards  
void outcome();   //print out the result 
void outcome_1();
void outcome_2(); 
void wait(int a);  //pause in the game   
void w_p();  //final result if player wins   
void w_d();  //final result if dealer wins   
      
bool cards[13][4];      //cards[name][suit]   
int p_t;       //player's handcards value sum up   
int d_t;       //dealer's handcards value sum up   
char p_h[32];   //player's hand   
char d_h[32];   //dealer's hand
char back_up[4];   
int p_po;            
int d_po;   
bool rules_f;   //first round    
bool p_l;      //player loses this round   
bool d_l;   
bool p_jack; //player gets a blackjack   
bool p_st; //player stands 
bool d_st; //dealer stands
bool push;   //decide whether the player and dealer pushes   
char c, run_again;   
