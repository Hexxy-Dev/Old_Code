#pragma once
#include <iostream>
#include <string>

extern std::string Input;
extern size_t Input_index;
extern char Look;
extern size_t LCount;

#define ASSERT() if(!(x)) __debugbreak();
//#define HALT() __debugbreak()
#define HALT()

inline void GetChar() { Look = Input[Input_index++]; }

inline void Error(const std::string& s) { printf("Error: %s.\n", s.c_str()); }
inline void Abort(const std::string& s) { Error(s); HALT(); }
inline void Expected(const std::string& s) { Abort(s + " Expected"); }

inline void Emit(const std::string& s) { printf("\t%s", s.c_str()); }
inline void EmitLn(const std::string& s) { Emit(s); puts(""); }

inline char UpCase(char c) { return  (c > 'Z' ? c - 'a' + 'A' : c); }

inline bool IsAlpha(char c) { return (UpCase(c) >= 'A' && UpCase(c) <= 'Z'); }
inline bool IsDigit(char c) { return (c >= '0' && c <= '9'); }
inline bool IsAlNum(char c) { return (IsAlpha(c) || IsDigit(c)); }
inline bool IsWhite(char c) { return (c == ' ' || c == '\t'); }

inline bool IsMulop(char c) { return (c == '*' || c == '/'); }
inline bool IsAddop(char c) { return (c == '+' || c == '-'); }

inline void SkipWhite() { while (IsWhite(Look)) GetChar(); }


inline bool IsBoolean(char c) { return (UpCase(c) == 'T' || UpCase(c) == 'F'); }
inline bool IsOrOp(char c) { return (c == '|' || c == '~'); }
inline bool IsRelop(char c) { return (c == '=' || c == '#' || c == '<' || c == '>'); }

inline void InternalVariableReset()
{
	Input = "";
	Input_index = 0;
	Look = '\0';
	LCount = 0;
}

inline void Init() {
	GetChar();
	SkipWhite();
}

inline void Match(char x)
{
	if (Look != x)
		Expected(std::string("\"") + x + '"');
	else {
		GetChar();
		SkipWhite();
	}
}

inline bool IsIn(char c, const std::string& s)
{
	for (char i = 0; i < s.size(); i++)
		if (c == s[i])
			return true;
	return false;
}
inline bool IsNotIn(char c, const std::string& s)
{
	for (char i = 0; i < s.size(); i++)
		if (c == s[i])
			return false;
	return true;
}

inline void NewLine()
{
	if (Look == '\r')
		GetChar();
	if (Look == '\n')
		GetChar();
	SkipWhite();
}

inline void Fin() { NewLine(); }

inline char GetName()
{
	if (!IsAlpha(Look))
		Expected("Name");
	char output = UpCase(Look);
	GetChar();
	SkipWhite();
	return output;
}
/*
inline std::string GetName()
{
	std::string Token = "";
	if (!IsAlpha(Look))
		Expected("Name");
	while (IsAlNum(Look)) {
		Token += UpCase(Look);
		GetChar();
	}
	SkipWhite();
	return Token;
}//*/

inline bool GetBoolean()
{
	if (!IsBoolean(Look))
		Expected("Boolean Literal");
	char output = UpCase(Look) == 'T';
	GetChar();
	SkipWhite();
	return output;
}