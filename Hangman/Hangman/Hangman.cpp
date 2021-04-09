//Calls useful libraries
#include <ctime>
#include <cstring>
#include <iostream>
#include <cstdlib>

//Initialises custom functions 
void play(void);
void draw(int numGuesses);
void instructions(void);

//Main function that acts like a main menu
int main()
{
	srand(time(0));
	char choice = '0';
	bool exitFlag = false;
	while (exitFlag == false)
	{
		std::cout << "+--------------+   " << std::endl;
		std::cout << "|              |   " << std::endl;
		std::cout << "|              0   " << std::endl;
		std::cout << "|             /|\\ " << std::endl;
		std::cout << "|              |   " << std::endl;
		std::cout << "|             / \\ " << std::endl;
		std::cout << "|                  " << std::endl;
		std::cout << "================== " << std::endl;

		std::cout << "Please select an option \n " << std::endl;
		std::cout << "1. Start Game \n";
		std::cout << "2. Tutorial \n";
		std::cout << "3. Quit Game " << std::endl;

		std::cin >> choice;

		do
		{
			if (choice == '1')
			{
				std::cout << "Game started " << std::endl;
				system("CLS"); //Clears screen
				play();
			}

			else if (choice == '2')
			{
				instructions();
			}

			else if (choice == '3')
			{
				std::cout << "Game ended " << std::endl;
				system("pause");
				system("CLS"); //Clears screen
				exitFlag = true;
				exit(0);
			}

			else
			{
				std::cout << "Invalid choice" << std::endl;
				std::cin.clear();
				std::cin >> choice;
			}

			if (exitFlag == true)
			{
				exit(0);
			}

		} while (choice != '1' || choice != '2' || choice != '3');
	}
	system("pause");
	return 0;
}

void play(void) //Defines function that runs main game code
{
	//Variables and Arrays needed to run game code
	char words[30][12] = { "paris", "london", "rome", "berlin", "madrid", "lisbon", "dublin", "glasgow", "brussels", "sydney",
						   "boston", "dallas", "washington", "liverpool", "manchester", "southampton", "bournemouth", "beijing", "tokyo", "shanghai",
						   "moscow", "vienna", "copenhagen", "stockholm", "athens", "budapest", "warsaw", "Luxembourg", "prague", "barcelona" };

	char previousLetters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char usedLetters[26] = { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' };

	char hiddenWord[80] = { 0 };
	char completedWord[80] = { 0 };
	char guess;
	int randomNum = 0;
	int numGuesses = 6;
	int score = 0;
	int guesses = 0;
	bool correctGuess = false;
	bool newGuess = false;
	bool isLetter = false;

	randomNum = rand() % 30;
	strcpy(&hiddenWord[0], &words[randomNum][0]); //Selects random word from the array of words

	int len = strlen(hiddenWord); //Saves the length of the word for easier use later
	int missingLetters = 0; //Variable that acts as win conditions

	memset(completedWord, '*', len);
	/*for (int i = 0; i < strlen(hiddenWord); i++)
	{
		completedWord[i] = '*';
	}*/

	std::cout << completedWord << std::endl;

	while (numGuesses > 0)
	{
		draw(numGuesses); //Calls draw function
		std::cout << "Lives: " << numGuesses << "\n" << std::endl;
		std::cout << "Score: " << score << "\n" << std::endl;
		std::cout << "Please guess a letter > ", std::cin >> guess; //Player makes their guess
		
		isLetter = false;
		guess = tolower(guess);

		while (isLetter == false)
		{
			if (isalpha(guess)) //Checks if guess is a letter
			{
				isLetter = true;
			}
			else //Stops code from falsely taking guesses if input is not a word
			{
				std::cout << "Please guess a letter \n" << std::endl;
				std::cin >> guess; //Player makes their guess
				guess = tolower(guess);
			}
		}

		correctGuess = false;

		system("CLS");

		for (int i = 0; i < strlen(completedWord); i++)
		{
			if (hiddenWord[i] == guess && completedWord[i] == '*') //If guess is correct, places the letter in the correct position
			{
				completedWord[i] = guess;
				std::cout << completedWord << std::endl;
				missingLetters++;
				score++;
				correctGuess = true;
			}
		}

		for (int i = 0; i < strlen(previousLetters); i++)
		{
			if (previousLetters[i] == guess) //Removes guess from the list of words that haven't been used
			{
				previousLetters[i] = '*';
				usedLetters[i] = guess;
			}

			else if (usedLetters[i] == guess) //If the guess is found in used letters, this stops it taking guesses or adding points unfairly
			{
				std::cout << completedWord << std::endl;
				std::cout << "This letter has already been used" << std::endl;
				correctGuess = true;
				break;
			}
		}

		//Removes a guess if the letter is not in the word
		if (correctGuess == false)
		{
			std::cout << completedWord << std::endl;
			numGuesses--;
		}

		//Win condition if all letters are filled in
		if (missingLetters == len)
		{
			draw(numGuesses);
			std::cout << "Word complete!\n" << "You win!" << std::endl;
			score = score + numGuesses;
			std::cout << "Final score: " << score << std::endl;
			system("pause");
			system("CLS");
			main();
		}

	}

	//lose condition
	draw(numGuesses);
	std::cout << "Word incomplete" << std::endl;
	std::cout << "The word was: " << hiddenWord << std::endl;
	std::cout << "Final score: " << score << std::endl;
	system("pause");
	system("CLS");
	main();
}

void draw(int numGuesses) //Draws out hangman body 
{

	/*
	+--------------+
	|              |
	|              0
	|             /|\\
	|              |
	|             / \\
	|
	=================
	*/
	if (numGuesses == 6)
	{
		std::cout << "+--------------+  " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "==================" << std::endl;
	}

	else if (numGuesses == 5)
	{
		std::cout << "+--------------+  " << std::endl;
		std::cout << "|              |  " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "==================" << std::endl;
	}

	else if (numGuesses == 4)
	{
		std::cout << "+--------------+  " << std::endl;
		std::cout << "|              |  " << std::endl;
		std::cout << "|              0  " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "==================" << std::endl;
	}

	else if (numGuesses == 3)
	{
		std::cout << "+--------------+  " << std::endl;
		std::cout << "|              |  " << std::endl;
		std::cout << "|              0  " << std::endl;
		std::cout << "|              |  " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "==================" << std::endl;
	}

	else if (numGuesses == 2)
	{
		std::cout << "+--------------+  " << std::endl;
		std::cout << "|              |  " << std::endl;
		std::cout << "|              0  " << std::endl;
		std::cout << "|             /|\\" << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "==================" << std::endl;
	}

	else if (numGuesses == 1)
	{
		std::cout << "+--------------+  " << std::endl;
		std::cout << "|              |  " << std::endl;
		std::cout << "|              0  " << std::endl;
		std::cout << "|             /|\\" << std::endl;
		std::cout << "|              |  " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "==================" << std::endl;
	}

	else if (numGuesses == 0)
	{
		std::cout << "+--------------+  " << std::endl;
		std::cout << "|              |  " << std::endl;
		std::cout << "|              0  " << std::endl;
		std::cout << "|             /|\\" << std::endl;
		std::cout << "|              |  " << std::endl;
		std::cout << "|             / \\" << std::endl;
		std::cout << "|                 " << std::endl;
		std::cout << "==================" << std::endl;
	}

}

void instructions(void)
{
	system("CLS");
	std::cout << "A word will be randomly selected" << std::endl;
	std::cout << "The word will not be revealed at the start" << std::endl;
	std::cout << "To win, you will have to guess the letters in the word" << std::endl;
	std::cout << "Correct letters will be revealed in their positions" << std::endl;
	std::cout << "You will lose if you get 6 guesses wrong\n" << std::endl;
	system("pause");
	system("CLS");
	main();
}