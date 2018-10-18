#include <iostream>
#include <string>
#include "fBullCowGame.h"

using FText = std::string;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();
FText GetValidGuess();

FBullCowGame BCGame;

// the entry point of our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while(bPlayAgain);

	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// TODO change from FOR to WHILE loop once we are validating tries
	do {
		FText Guess = GetValidGuess(); 

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows;
	}
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries);

	PrintGameSummary();

	return;
}

void PrintGameSummary()
{
	std::cout << std::endl << std::endl;
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You have won!";
	}
	else
	{
		std::cout << "You died";
	}

	std::cout << std::endl << std::endl;

	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word? (y/n) ";
	FText Response = "";
	getline(std::cin, Response);
	std::cout << std::endl << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

// introduce the game
void PrintIntro() {
	std::cout << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl << std::endl;
	std::cout << "           ,_,         ___ " << std::endl;
	std::cout << "          (o o)       (o o) " << std::endl;
	std::cout << "   /------- \\_/       \\_/ -------\\ " << std::endl;
	std::cout << "  / | BULL |             |  COW | \\ " << std::endl;
	std::cout << " *  |-,--- |             | ---#-|  * " << std::endl;
	std::cout << "    ^      ^             ^      ^ " << std::endl << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;

	return;
}

// loop until user gets valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do
	{
		// get guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << std::endl << std::endl;
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use all lowercase letters";
			break;
		default:
			break;
		}
	}
	while (Status != EGuessStatus::OK); // keep looping until no erorrs

	return Guess;
}