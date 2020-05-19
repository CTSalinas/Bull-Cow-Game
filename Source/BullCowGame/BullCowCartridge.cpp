// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the Bulls and Cows game!"));
    PrintLine(TEXT("Guess the 7 letter word!")); // Magic Number. Remove!
    PrintLine(TEXT("Press enter to continue!"));

    SetupGame(); //setting up game

    //prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    ClearScreen();

    // checking player guess

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
    }
    else
    {
        PrintLine(TEXT("You have lost!"));
        //Check if Isogram
        //Check if ccorrect characters
        //Reduce Life
    }
    // If life == 0
        // print out of lives
        // prompt to play again
            //if yes, go back to welcome message
            //if no, end session
    
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("isogram"); // Set the HiddenWord
    Lives = 3; // Set Lives
}





/*
 Game Loop:
Print Welcome Message
Set Lives
Set hidden Word
Prompt for Guess
    Check if meets conditions:
        isogram
        check right number of characters
    Guess correct?
        Win
    Guess incorrect?
        Loss
        Life--
    
If life > 0
    guess again
    show lives left

If Life = 0
    Print Fail and hidden word
    Press enter to play again
    check user input
    play again or quit
 */