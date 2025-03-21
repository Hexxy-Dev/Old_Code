#pragma once


void InitWindowsAbstractionLayer();

//0 = Black		8 = Gray
//1 = Blue			9 = Light Blue
//2 = Green		10 = Light Green
//3 = Aqua		11 = Light Aqua
//4 = Red			12 = Light Red
//5 = Purple		13 = Light Purple
//6 = Yellow		14 = Light Yellow
//7 = White		15 = Bright White
int SetTextColor(const char foreground, const char background);
//HEX VALUE IS:	 BACKGROUND	FOREGROUND
//values:
//0 = Black		8 = Gray
//1 = Blue			9 = Light Blue
//2 = Green		a = Light Green
//3 = Aqua		b = Light Aqua
//4 = Red			c = Light Red
//5 = Purple		d = Light Purple
//6 = Yellow		e = Light Yellow
//7 = White		f = Bright White
int SetTextColor(const int color);