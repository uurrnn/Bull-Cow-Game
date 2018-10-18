#include "fBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() // constructor
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,6},{5,8},{6,12},{7,15} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if the guess isnt an isogram, return error
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	// if the guess isnt all lowercase, return error
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	// if the guess length is wrong, return error
	else if (Guess.length() != MyHiddenWord.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	// otherwise, return OK
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a vaild guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	for (int32 i = 0; i < MyHiddenWord.length(); i++)
	{
		for (int32 j = 0; j < Guess.length(); j++)
		{
			// if they match then
			if (Guess[i] == MyHiddenWord[j])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}

	}
	if (BullCowCount.Bulls == MyHiddenWord.length())
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess)
	{
		Letter = tolower(Letter); // lowercase letter
		if (!LetterSeen[Letter])  // check if letter has already been used
		{
			LetterSeen[Letter] = true; // check off letter
		}
		else // if letter is in map then return false
		{
			return false;
		}
	}		
		
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
