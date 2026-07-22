//First Library...
#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class clsString
{
private:
	string _Value;

	

public:

	clsString()
	{

	}

	clsString(string Value)
	{
		_Value = Value;
	}

	void SetValue(string Value)
	{
		_Value = Value;
	}
	string GetValue()
	{
		return _Value;
	}
	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static short Length(string S1)
	{
		return S1.length();
	};
	short Length()
	{
		return _Value.length();
	};

	static short CountWords(string Text)
	{
		string delim = " ";// delimiter
		short Counter = 0;
		short Pos = 0;
		string sWord;// define a string variable 

		// use find() function to get the position of the delimiters
		while ((Pos = Text.find(delim)) != string::npos) /*Text.npos == std::string::npos == string::npos*/
		{
			sWord = Text.substr(0, Pos);// store the word

			if (sWord != "")
			{
				Counter++;
			}

			Text.erase(0, Pos + delim.length());/* erase() until positon and move to next word. */

		}

		if (Text != "")
		{
			Counter++; // it Count last word of the string...
		}

		return Counter;
	}
	short CountWords()
	{
		return CountWords(_Value);
	}

	static string UpperFirstLetterOfEachWord(string Text)
	{
		bool isFirstLetter = true;

		for (short i = 0; i < Text.length(); i++)
		{
			if (Text[i] != ' ' && isFirstLetter)
			{
				Text[i] = toupper(Text[i]);
			}

			isFirstLetter = (Text[i] == ' ' ? true : false);
			//isFirstLetter = ((Text[i] == ' ') || (ispunct(Text[i])) ? true : false); //Mohammad Abu-Hadhoud
		}

		return Text;

	}
	void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string Text)
	{
		bool isFirstLetter = true;

		for (short i = 0; i < Text.length(); i++)
		{
			if (Text[i] != ' ' && isFirstLetter)
			{
				Text[i] = tolower(Text[i]);
			}

			isFirstLetter = (Text[i] == ' ' ? true : false);
			//isFirstLetter = ((Text[i] == ' ') || (ispunct(Text[i])) ? true : false); //Mohammad Abu-Hadhoud
		}

		return Text;

	}
	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllString(string Text)
	{
		for (short i = 0; i < Text.length(); i++)
		{
			Text[i] = toupper(Text[i]);
		}

		return Text;
	}
	void UpperAllString()
	{
		_Value = UpperAllString(_Value);
	}

	static string LowerAllString(string Text)
	{
		for (short i = 0; i < Text.length(); i++)
		{
			Text[i] = tolower(Text[i]);
		}

		return Text;
	}
	void LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	static char InvertLetterCase(char Character)
	{
		return (isupper(Character) ? tolower(Character) : toupper(Character));
	}

	static string InvertAllLettersCase(string Text)
	{
		for (short i = 0; i < Text.length(); i++)
		{
			Text[i] = InvertLetterCase(Text[i]);
		}

		return Text;

	}
	void InvertAllLettersCase()
	{
		_Value = InvertAllLettersCase(_Value);
	}

	enum enWhatToCount { CapitalLetters, SmallLetters, Digit, Punctuation, AllLetters };
	static short CountLetters(string Text, enWhatToCount WhatToCount = enWhatToCount::AllLetters) //Default Parameters
	{
		short Count = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (WhatToCount == enWhatToCount::CapitalLetters && (isupper(Text[i])))
				Count++;

			if (WhatToCount == enWhatToCount::SmallLetters && (islower(Text[i])))
				Count++;

			if (WhatToCount == enWhatToCount::Digit && (isdigit(Text[i])))
				Count++;

			if (WhatToCount == enWhatToCount::Punctuation && (ispunct(Text[i])))
				Count++;

			if (WhatToCount == enWhatToCount::AllLetters && (Text[i] != ' '))
				Count++;
		}

		return Count;

	}
	short CountLetters(enWhatToCount WhatToCount = enWhatToCount::AllLetters)
	{
		return CountLetters(_Value, WhatToCount);
	}

	static short CountCapitalLetters(string Text)
	{
		short Count = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (isupper(Text[i]))
			{
				Count++;
			}
		}

		return Count;

	}
	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static short CountSmallLetters(string Text)
	{
		short Count = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (islower(Text[i]))
			{
				Count++;
			}
		}

		return Count;

	}
	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	static short  CountSpecificLetter(string S1, char Letter, bool MatchCase = true)
	{

		short Counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{

			if (MatchCase)
			{
				if (S1[i] == Letter)
					Counter++;
			}
			else
			{
				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}

		}

		return Counter;
	}
	short  CountSpecificLetter(char Letter, bool MatchCase = true)
	{
		return CountSpecificLetter(_Value, Letter, MatchCase);
	}

	static bool IsVowel(char Letter)
	{
		Letter = tolower(Letter);

		return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));
	}

	static short CountVowels(string Text)
	{
		short Counter = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (IsVowel(Text[i]))
				Counter++;
		}

		return Counter;
	}
	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static vector<string> Split(string Text, string Delim)
	{
		vector <string> vString;

		short Pos = 0;

		// define a string variable 
		string sWord;//....|| string Token;

		// use find() function to get the position of the delimiter
		while ((Pos = Text.find(Delim)) != std::string::npos)
		{
			sWord = Text.substr(0, Pos);// store the word

			//if (sWord != "")
			//{
				vString.push_back(sWord);
			//}

			Text.erase(0, Pos + Delim.length());/* erase() until positon and move to next word. */

		}

		if (Text != "")
		{
			vString.push_back(Text);// It adds last word of the string...
		}

		return vString;

	}
	vector<string> Split(string Delim)
	{
		return Split(_Value, Delim);
	}

	static string TrimLeft(string Text)
	{
		for (short i = 0; i < Text.length(); i++)
		{
			if (Text[i] != ' ')
			{
				return Text.substr(i, Text.length() - i);
			}
		}

		return "";
	}
	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string Text)
	{
		for (int i = Text.length() - 1; i >= 0; i--)
		{
			if (Text[i] != ' ')
			{
				return Text.substr(0, i + 1);
			}
		}

		return "";
	}
	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static string Trim(string Text)
	{
		return TrimLeft(TrimRight(Text));
	}
	void Trim()
	{
		_Value = Trim(_Value);
	}

	static string JoinString(vector<string> vString, string Delim)
	{
		string Text;

		for (string& S : vString)
		{
			Text = Text + S + Delim;
		}

		return Text.substr(0, Text.length() - Delim.length());
	}

	static string JoinString(string ArrString[], short arrLength, string Delim)
	{
		string Text = "";

		for (short i = 0; i < arrLength; i++)
		{
			Text = Text + ArrString[i] + Delim;
		}

		return Text.substr(0, Text.length() - Delim.length());
	}

	static string ReverseWordsInString(string Text)
	{
		string Delim = " ";

		vector <string> vString = Split(Text, Delim);

		string sWord = "";

		vector <string>::iterator iter;

		iter = vString.end();

		while (iter != vString.begin())
		{
			iter--;
			sWord += *iter + Delim;
		}

		return sWord.substr(0, sWord.length() - Delim.length());

		/*Mohammad Mahmoud Rajab Agha I'm From Deir Al_Zoor   -->   Al_Zoor Deir From I'm Agha Rajab Mahmoud Mohammad */
	}
	void ReverseWordsInString()
	{
		_Value = ReverseWordsInString(_Value);
	}

	static string ReplaceWordInStringUsingBuiltInFunction(string Text, string StringToReplace,string sRepalceTo)
	{
		short pos = Text.find(StringToReplace);
		while (pos != std::string::npos)
		{
			Text = Text.replace(pos, StringToReplace.length(),
				sRepalceTo);
			pos = Text.find(StringToReplace);//find next
		}
		return Text;
	}
	void ReplaceWordInStringUsingBuiltInFunction(string StringToReplace, string sReplaceTo)
	{
		_Value = ReplaceWordInStringUsingBuiltInFunction(_Value, StringToReplace, sReplaceTo);
	}

	static string ReplaceWord(string Text, string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		vector<string> vString = Split(Text, " ");

		for (string& S : vString)
		{
			if (MatchCase)
			{
				if (S == StringToReplace)
				{
					S = sReplaceTo;
				}
			}

			else
			{
				if (LowerAllString(S) == LowerAllString(StringToReplace))
				{
					S = sReplaceTo;
				}
			}
		}

		return JoinString(vString, " ");

		// Mohammed = Mohammed -> MatchCase...
		// mOhAmmAD = mohammed -> Don't MatchCase...

	}
	void ReplaceWord(string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		_Value = ReplaceWord(_Value, StringToReplace, sReplaceTo, MatchCase);
	}

	static string RemovePunctuations(string Text)
	{
		string S = "";

		for (short i = 0; i < Text.length(); i++)
		{
			if (!ispunct(Text[i]))
			{
				S += Text[i];
			}
		}

		return S;
	}
	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}




	//Append 

	static short CountNumberOfUpperCase(const string& Password)
	{
		short Count = 0;

		for (int i = 0; i < Password.size(); i++)
		{
			if (isupper(Password[i]))
				Count++;
		}
		return Count;
	}
	short CountNumberOfUpperCase()
	{
		return CountNumberOfUpperCase(_Value);
	}

	static short CountNumberOfLowerCase(const string& Password)
	{
		short Count = 0;

		for (int i = 0; i < Password.size(); i++)
		{
			if (islower(Password[i]))
				Count++;
		}
		return Count;
	}
	short CountNumberOfLowerCase()
	{
		return CountNumberOfLowerCase(_Value);
	}

	static short CountNumberPunctuation(const string& Password)
	{
		short Count = 0;

		for (int i = 0; i < Password.size(); i++)
		{
			if (ispunct(Password[i]))
				Count++;
		}
		return Count;
	}
	short CountNumberPunctuation()
	{
		return CountNumberPunctuation(_Value);
	}


};