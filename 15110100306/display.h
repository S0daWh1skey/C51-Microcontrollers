
static unsigned char i=0;
void Display(unsigned char FirstBit,unsigned char Num);
#define DataPort P0 
sbit LATCH1=P2^2;// ¶ÎËø´æ
sbit LATCH2=P2^3;// Î»Ëø´æ
unsigned char code dofly_WeiMa[];
extern unsigned char TempData[8]; 
