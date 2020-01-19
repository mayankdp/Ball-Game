//Header file
#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	160

typedef unsigned char	uint8; 		//unsigned int 8 bits
typedef unsigned short	uint16; 	//unsigned int 16 bits
typedef unsigned int	uint32;		//unsigned int 32 bits

#define MEM_IO			0x04000000
#define VRAM			0x06000000

#define VIDEOMODE		0x0003
#define BGMODE			0x0400

#define REG_DISPLAY			(*(volatile uint32 *) (MEM_IO))
#define REG_DISPLAY_VCOUNT	(*(volatile uint32 *) (MEM_IO + 0x0006))
#define REG_KEY_INPUT		(*(volatile uint32 *) (MEM_IO + 0x0130))

#define A		1
#define B		2
#define SELECT	4
#define START	8
#define RIGHT	16
#define LEFT	32
#define UP		64
#define DOWN	128
#define R		256 
#define L 		512

#define SCREENBUFFER	((volatile uint16 *) VRAM)

struct Rect {
	uint32 x, x1, y;
	uint32 w, h; 
} player1, player2, prevPlayer1, prevPlayer2, ball, prevBall,
	a,b,c,d,e,f,g,
	h,i,j,k,l,m,n;
