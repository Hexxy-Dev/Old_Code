#include <iostream>
#include <string>
#include <unordered_map>

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

//https://www.khanacademy.org/computing/computer-science/cryptography/cryptochallenge/a/cryptochallenge-introduction

std::string DoubleLetters(const std::string& s)
{
	std::string o;
	for (size_t i = 0; i < s.size(); i++) {
		o += s[i];
		o += s[i];
	}
	return o;
}

std::string Lowercase(const std::string& s)
{
	std::string o;
	for (size_t i = 0; i < s.size(); i++)
		if (s[i] >= 'A' && s[i] <= 'Z')
			o += s[i] + ('a' - 'A');
		else
			o += s[i];
	return o;
}

void CesarDecrypt(const std::string& s)
{
	std::unordered_map<char, uint16_t> freq;

	for (size_t i = 0; i < s.size(); i++)
		freq[s[i]]++;

	std::pair<char, uint16_t> max;

	for (auto& v : freq) {
		printf("%c %d\n", v.first, v.second);
		if (max.second < v.second)
			max = v;
	}

	printf("\nSelected: %c\n\n", max.first);

	int8_t off = max.first - 'e';

	std::unordered_map<char, char> Alphabet;

	char c = 'A';
	for (char i = 'a' + off; i <= 'z'; i++)
		Alphabet[i] = c++;
	for (char i = 'a'; i < 'a' + off; i++)
		Alphabet[i] = c++;

	for (size_t i = 0; i < s.size(); i++)
		printf("%c", Alphabet[s[i]]);
	puts("\n\n");
}

void VigenereDecrypt(const std::string& s, const std::string& cipher)
{
	size_t j = 0;
	for (size_t i = 0; i < s.size(); i++) {
		int8_t r = (s[i] - 'a') - (cipher[j] - 'a');
		if (r < 0)
			printf("%c", 'Z' + r + 1);
		else
			printf("%c", 'A' + r);
		j++;
		if (j == cipher.size())
			j = 0;
	}
	puts("\n\n");
}

void VisualTelegraphDecrypt(const std::string& s, const char** map)
{
	for (size_t i = 0; i < s.size(); i++) {
		uint8_t j = s[i++] - '0';
		uint8_t k = s[i] - '0';
		printf("%c", map[j - 1][k - 1]);
	}
	puts("\n\n");
}

void FinalDecrypt(const std::string& s1, const std::string& s2, const char** map)
{
	//convert all digits to binary
	std::string bin;
	for (size_t i = 0; i < s1.size(); i++)
		switch (s1[i]) {
		case '0': bin += '\0'; bin += '\0'; break;
		case '1': bin += '\0'; bin += '\1'; break;
		case '2': bin += '\1'; bin += '\0'; break;
		case '3': bin += '\1'; bin += '\1'; break;
		}

	//vowels = 1 consonant = 0 space is ignored y is vowel
	std::string text;
	for (size_t i = 0; i < s2.size(); i++)
		if (s2[i] != ' ')
			text += (std::string("aeiouy").find(s2[i]) != std::string::npos);

	//XOR the two
	std::string out;
	for (size_t i = 0; i < bin.size(); i++)
		out += (bin[i] != text[i]);


	//split in 6 bits 2 3-bit numbers to use in the 6x6 polibus
	size_t l = (out.size() / 6) * 6;
	for (size_t i = 0; i < l; i++) {
		uint8_t x = out[i] * 4 + out[i + 1] * 2 + out[i + 2];
		i += 3;
		uint8_t y = out[i] * 4 + out[i + 1] * 2 + out[i + 2];
		i += 2;

		printf("%c", map[x][y]);
	}
}

int main()
{
	std::string s12 = "vwduwljudeehghyhubwklqjlfrxogilqgsohdvhuhwxuqdqbeoxhsulqwviruydxowd qgdodupghvljqedvhgrqzklfkedqnbrxghflghrqldpvhwwlqjxsvdihkrxvhfr";
	CesarDecrypt(s12);
	//START I GRABBED EVERYTHING I COULD FIND PLEASE RETURN ANY BLUEPRINTS FOR VAULT
	//AND ALARM DESIGN BASED ON WHICH BANK YOU DECIDE ON I AM SETTING UP SAFE HOUSE CO
	std::string s1 = "gluhtlishjrvbadvyyplkaohavbyjpwolypzavvdlhrvuuleatlzzhnlzdpajoavcpnlulyljpwolyrlfdvykpzaolopkkluzftivsvmklhaoputfmhcvypalovsilpuluk";
	CesarDecrypt(s1);
	//ZE NAME BLACKOUT WORRIED THAT OUR CIPHER IS TOO WEAK ON NEXT MESSAGE SWITCH TO
	//VIGENERE CIPHER KEY WORD IS THE HIDDEN SYMBOL OF DEATH IN MY FAVORITE HOLBEIN END


	std::string s21 = "Klkbnqlcytfysryucocphgbdizzfcmjwkuchzyeswfogmmetwwossdchrzyldsbwnydednzwnefydthtddbojicemlucdygicczhoadrzcylwadsxpilpiecskomoltejtkmqqymehpmmjxyolwpeewjckznpccpsvsxauyodhalmriocwpelwbcniyfxmwjcemcyrazdqlsomdbfljwnbijxpddsyoehxpceswtoxwbleecsaxcnuetzywfn";
	std::string s22 = "skull";
	//chipher is s32 with every letter doubled
	VigenereDecrypt(Lowercase(s21), DoubleLetters(s22));
	//START WARNING I HEARD REPORT OF OUR BREAK IN ON THE NEWS STILL WAITING ON ALARM
	//TEST SCHEDULES I WILL REPORT BACK TOMORROW WITH FINAL PLAN FOR EXTRA SECURITY
	//I SUGGEST WE BURN OUR LETTERS AFTER READING AND SWITCH OUR LETTERS TO NUMBERS
	//USING POLYBIUS SQUARE DROP MESSAGE UNDER THE BENCH AT TRAIN STATION END

	std::string s3 = "445411345411233353445412424342443251412123113113531554425442444243443251415343543242344111255135533413424322534311445434534322513431421432513412533412155415345133514444112251444254424444153451235515432134511113112123514254315333214243514453153414345125425315443351543253414443513544";
																																																																									//44343513544
	const char* map3[5] = {
		"AFKPU",
		"BGLQV",
		"CHMRW",
		"DINSX",
		"EJOTY"
	};
	VisualTelegraphDecrypt(s3, map3);
	//START ALMOST FINISHED BLACKOUT IT IS IN SHEDON THIRD AVE WORKING ON A STRONGER
	//CIPHER FOR FUTURE MESSAGES IT IS SURELY UNBREAKABLE IT COMBINES OUR PREVIOUS
	//METHODS NEWS

	std::string s41 = "2033222100333001022022023220113303300332030022013323231003221313200111032220202022332013231333223033012021101211003223132202001031023320310312011133322302010032101030011023311002003023311003030102330223213012031222000313310010112103230220130232303123332002123330003012301303010303232202302003222332230202312023133002";
	std::string s42 = "the whole grain goodness of blue chip dividend stocks has its limits utility stocks consumer staples pipelines telecoms and real estate investment trusts have all lost ground over the past month even while the broader market has been flat with the bond market signalling an expectation of rising interest rates the five year rally for steady blue chip dividend payers has stalled should you be scared if you own a lot of these stocks either directly or through mutual funds or exchange traded funds david baskin president of baskin financial services has a two pronged answer keep your top quality dividend stocks but be prepared to follow his firms example in trimming holdings in stocks such as transcanada corp keyera corp and pembina pipeline corp lets have mr baskin run us through his thinking on dividend stocks which are the big part of the portfolios his firm puts together for clients a mini manifesto for the managers";
	// 2 0 3
	// 3 * 1
	// 1 2 0
	const char* map4[6] = {
		"FGHIJK",
		"EXYZ0L",
		"DW781M",
		"CV692N",
		"BU543O",
		"ATSRQP"
	};
	FinalDecrypt(s41, s42, map4);
	//START CIBC BANK SEE SCHEMATICS FOR ALARM AND VAULT HIT TOMORROW AT 10 AM AFTER
	//ALARM TEST VAULT CODE IS 5567 MEET AT BLACKOUT EN 7

	puts("\n\n");

	//Crypto checkpoint 2
	
	//hi
	//02 03
	//000010000011
	//101001010110
	//101011010101
	//in
	//03 35
	//000011011101
	//101001010110
	//101010001011
	//me
	//25 10
	//010101001000
	//101001010110
	//111100011110

	// 2 0 3
	// 3 * 1
	// 1 2 0
	//03 33 13 11 11 22
	//010111010010000101010010 1
	//001111110111010101011010
	//011000100101010000001000 1
	//011 000 100 101 010 000 001 000
	//30 45 20 10
	//code
	//L
	//15
	//001101
	//P
	//55
	//101101
	//W
	//21
	//010001



	//Crypto checkpoint 3

	//START 4142113642
	//SEE 411515
	//BANK 12113225
	//ALARM 1126113631
	//VAULT 4411432642
	//10AM 53661131
	//5567 61616263
	//BLACKOUT 1226111325334342

	std::string Word = "START SEE BANK ALARM VAULT 10AM 5567 BLACKOUT";
	std::string hmm = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

	for (size_t i = 0; i < Word.size(); i++) {
		size_t j = 0;
		if (Word[i] == ' ') {
			printf(" ");
			i++;
		}
		for (; j < hmm.size(); j++)
			if (hmm[j] == Word[i])
				break;
		printf("%d%d", j / 6 + 1, j % 6 + 1);
	}
}