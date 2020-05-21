// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

    SetupGame(); //setting up game

    //prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    
    if (bGameOver){ // If game is over, resetup game.
        ClearScreen();
        SetupGame();
    }
    else{ // Check Player Guess
        ProcessGuess(PlayerInput);

    }
    
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num()-1)]; // Set the HiddenWord
    Lives = HiddenWord.Len() * 2; // Set Lives
    bGameOver = false;


    PrintLine(TEXT("Welcome to the Bulls and Cows game!"));
    PrintLine(TEXT("You have %i lives!"), Lives);
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); 
    PrintLine(TEXT("Type in your guess and press enter to continue!"));
    PrintLine(TEXT("The Hidden word is %s. \nIt is %i characters long."), *HiddenWord, HiddenWord.Len()); // Debug Line
    
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess){
    if (Guess == HiddenWord){
        ClearScreen();
        PrintLine(TEXT("You have won!"));
        EndGame();
        return;
    }
    else{
        // Check if right number of characters
        if (Guess.Len() != HiddenWord.Len()){ 
                PrintLine(TEXT("The Hidden Word has %i letters. \nPlease try again."), HiddenWord.Len());
                return;
        }
        // Check if guess is an isogram
        if (!IsIsogram(Guess)){
            PrintLine(TEXT("No repeating letters, try again."));
            return;
        }

        --Lives; // Reduce Life

        if (Lives <=0){
            ClearScreen();
            PrintLine(TEXT("You have lost all your lives!"));
            PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
            EndGame();
            return;
        }
        else{
            // Show bulls and cows
            FBullCowCount Score = GetBullCows(Guess);
            PrintLine(TEXT("You are incorrect. You have %i remaining lives."), Lives);
            PrintLine(TEXT("You have %i bulls and %i cows."), Score.Bulls, Score.Cows);
            PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
            return;
        }
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const {

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
   return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const{

    TArray<FString> ValidWords;

    for (FString GivenWord : WordList)  
    {   
        if (GivenWord.Len() >=4 && GivenWord.Len()<=8 && IsIsogram(GivenWord))
        {
            ValidWords.Emplace(GivenWord);
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const{
    FBullCowCount Count;

    // for every index of guess is same as index of hidden word, then bull++
    // if not a bull, was it a cow? if yes, cow ++
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++){
        if (Guess[GuessIndex] == HiddenWord[GuessIndex]){
            Count.Bulls++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex]){
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
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