//Main c file
#include "Game.h"
#include <stdbool.h>

//display
void sync()
{
	while(REG_DISPLAY_VCOUNT >= 160);
	while(REG_DISPLAY_VCOUNT < 160);
}

//choose color
uint16 makeColor(uint8 r, uint8 g, uint8 b)
{
	return (r & 0x1f) | ((g & 0x1f) << 5) | ((b & 0x1f) << 10);
}

uint32 clamp(int value, int min, int max)
{
	return (value < min ? min : (value > max ? max : value));
}

//draw rectangle
void drawRect(struct Rect rect, uint16 color)
{
	for(int y = 0; y < rect.h; y++)
	{
		for(int x = 0; x < rect.w; x++)
		{
			SCREENBUFFER[(rect.y + y) * SCREEN_WIDTH + rect.x + x] = color;
		}
	}
}

//player 1 7seg display
void init7seg1()
{
	a.w = 16;
	a.h = 4;
	f.w = 4;
	f.h = 16;
	
	b = c = e = f;
	d = g = a;
	
	a.x = d.x = e.x = f.x = g.x = SCREEN_WIDTH/4;
	b.x = c.x = a.x + a.w;
	
	a.y = b.y = f.y = 0;
	c.y = e.y = g.y = b.y + b.h - a.h;
	d.y = g.y + b.h - a.h;
}

void clear7seg1()
{
	drawRect(a, makeColor(0,0,0));
	drawRect(b, makeColor(0,0,0));
	drawRect(c, makeColor(0,0,0));
	drawRect(d, makeColor(0,0,0));
	drawRect(e, makeColor(0,0,0));
	drawRect(f, makeColor(0,0,0));
	drawRect(g, makeColor(0,0,0));
}

void draw7seg1(uint8 num)
{
	clear7seg1();
	bool w, x, y, z;
	
	w = (num >= 8 ? ((num-=8) ? 1 : 1) : 0);
	x = (num >= 4 ? ((num-=4) ? 1 : 1) : 0);
	y = (num >= 2 ? ((num-=2) ? 1 : 1) : 0);
	z = (num >= 1 ? ((num-=1) ? 1 : 1) : 0);

	if(w || y || (!x && !z) || (x && z))
		drawRect(a, makeColor(0x1f, 0x1f, 0x1f));
	if((y && z) || (!y && !z) || !x)
		drawRect(b, makeColor(0x1f, 0x1f, 0x1f));
	if(w || x || !y || z)
		drawRect(c, makeColor(0x1f, 0x1f, 0x1f));
	if(w || (y && !z) || (!x && !z) || (!x && y) || (x && !y && z))
		drawRect(d, makeColor(0x1f, 0x1f, 0x1f));
	if((y && !z) || (!x && !z))
		drawRect(e, makeColor(0x1f, 0x1f, 0x1f));
	if(w || (x && !y) || (x && !z) || (!y && !z))
		drawRect(f, makeColor(0x1f, 0x1f, 0x1f));
	if(w || (!y && x) || (y && !z) || (y && !x))
		drawRect(g, makeColor(0x1f, 0x1f, 0x1f));
}

//Player 2 7seg display
void init7seg2()
{
	h.w = 16;
	h.h = 4;
	m.w = 4;
	m.h = 16;
	
	i = j = l = m;
	k = n = h;
	
	h.x = k.x = l.x = m.x = n.x = (SCREEN_WIDTH/4) + (SCREEN_WIDTH/2);
	i.x = j.x = h.x + h.w;
	
	h.y = i.y = m.y = 0;
	j.y = l.y = n.y = i.y + i.h - h.h;
	k.y = n.y + i.h - h.h;
}

void clear7seg2()
{
	drawRect(h, makeColor(0,0,0));
	drawRect(i, makeColor(0,0,0));
	drawRect(j, makeColor(0,0,0));
	drawRect(k, makeColor(0,0,0));
	drawRect(l, makeColor(0,0,0));
	drawRect(m, makeColor(0,0,0));
	drawRect(n, makeColor(0,0,0));
}

void draw7seg2(uint8 num)
{
	clear7seg2();
	bool w, x, y, z;
	
	w = (num >= 8 ? ((num-=8) ? 1 : 1) : 0);
	x = (num >= 4 ? ((num-=4) ? 1 : 1) : 0);
	y = (num >= 2 ? ((num-=2) ? 1 : 1) : 0);
	z = (num >= 1 ? ((num-=1) ? 1 : 1) : 0);

	if(w || y || (!x && !z) || (x && z))
		drawRect(h, makeColor(0x1f, 0x1f, 0x1f));
	if((y && z) || (!y && !z) || !x)
		drawRect(i, makeColor(0x1f, 0x1f, 0x1f));
	if(w || x || !y || z)
		drawRect(j, makeColor(0x1f, 0x1f, 0x1f));
	if(w || (y && !z) || (!x && !z) || (!x && y) || (x && !y && z))
		drawRect(k, makeColor(0x1f, 0x1f, 0x1f));
	if((y && !z) || (!x && !z))
		drawRect(l, makeColor(0x1f, 0x1f, 0x1f));
	if(w || (x && !y) || (x && !z) || (!y && !z))
		drawRect(m, makeColor(0x1f, 0x1f, 0x1f));
	if(w || (!y && x) || (y && !z) || (y && !x))
		drawRect(n, makeColor(0x1f, 0x1f, 0x1f));
}

int main()
{
	REG_DISPLAY = VIDEOMODE | BGMODE;
	
	int top = 0;
	int left = 0;
	
	int bottom = SCREEN_HEIGHT;
	int right = SCREEN_WIDTH;

	int ballTop = 130;
	int ballLeft = 80;

	int speedRight = 1;
	int speedDown = 1;
	
	int score1 = 0;
	int score2 = 0;
	
	player1.x = left;
	player1.y = top;
	player1.w = 8;
	player1.h = 32;
	
	prevPlayer1 = player1;
	
	player2.x = right - 8;
	player2.y = bottom - 32;
	player2.w = 8;
	player2.h = 32;

	prevPlayer2 = player2;

	ball.x = ballLeft;
	ball.y = ballTop;
	ball.w = 8;
	ball.h = 8;
	
	init7seg1();
	draw7seg1(score1);

	init7seg2();
	draw7seg2(score1);
	
	prevBall = ball;
	
	while(1)
	{
		sync();
		
		drawRect(prevPlayer1, makeColor(0,0,0));
		drawRect(prevPlayer2, makeColor(0,0,0));
		drawRect(prevBall, makeColor(0,0,0));
		
		ballLeft += speedRight;
		ballTop += speedDown;
		
		if(!((REG_KEY_INPUT) & DOWN)) // player 1 down button 
			top++;
		if(!((REG_KEY_INPUT) & UP)) // player 1 up button
			top--;

		if(!((REG_KEY_INPUT) & A)) // player 2 up button (on keyboard Q)
			bottom = bottom + 2;
		if(!((REG_KEY_INPUT) & B)) // player 2 down button (on keyboard W)
			bottom = bottom - 2;;
		
		top = clamp(top, 0, SCREEN_HEIGHT - player1.h); // stop rectangle going out of the board
		bottom = clamp(bottom, 0, SCREEN_HEIGHT - player2.h); // stop rectangle going out of the board

		ballLeft = clamp(ballLeft, 0, SCREEN_WIDTH-ball.w); // define ball left side
		ballTop = clamp(ballTop, 0, SCREEN_HEIGHT-ball.h); // define ball top side
		
		if(ballLeft == SCREEN_WIDTH-ball.w) // move ball right
			speedRight = -speedRight;

		if(ballTop == 0 || ballTop == SCREEN_HEIGHT - ball.h) // move ball up and down
			speedDown = -speedDown;
		
		if(ballLeft == player1.x + player1.w && 
			(ballTop >= top - ball.h &&
			 ballTop <= top + player1.h)) // when ball touches the Left rectangle
		{
			speedRight = -speedRight;	 
		}

		if(ballLeft + 8 == player2.x && 
			(ballTop >= bottom - ball.h &&
			 ballTop <= bottom + player2.h)) // when ball touches the Right rectangle
		{
			speedRight = -speedRight;	 
		}
		
		if(ballLeft == 0) //when ball touches the left side
		{
			score1++;
			ballLeft = 130;
			ballTop = 80;
		}

		if(ballLeft + 8 == SCREEN_WIDTH) //when ball touches the right side
		{
			score2++;
			ballLeft = 130;
			ballTop = 80;
		}
		
		player1.y = top;
		prevPlayer1 = player1;
		
		player2.y = bottom;
		prevPlayer2 = player2;

		ball.x = ballLeft;
		ball.y = ballTop;
		prevBall = ball;
		
		drawRect(player1, makeColor(0x1f, 0, 0));
		drawRect(player2, makeColor(0, 0, 0x1f));
		drawRect(ball, makeColor(0, 0x1f, 0));
		draw7seg1(score1);
		draw7seg2(score2);
	}
}