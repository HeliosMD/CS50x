#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Loops through all candidates
    for (int j = 0; j < candidate_count; j++)
    {
        // Validates the candidate name
        if (strcmp(name, candidates[j].name) == 0)
        {
            // Increases a vote if it is a valid name
            candidates[j].votes++;
            //printf("%i\n", candidates[j].votes);
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Declare variables needed
    string winner[9];
    int higher_vote = 0;
    int winner_index = 0;
    int winners = 0;

    // Check whose candidate had most votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > higher_vote)
        {
            winner[0] = candidates[i].name;
            higher_vote = candidates[i].votes;
            winner_index = i;
        }
    }

    // Check if there is tie and with whom
    for (int i = 0; i < candidate_count; i++)
    {
        if (i != winner_index)
        {
            if (candidates[i].votes == higher_vote)
            {
                winners++;
                winner[winners] = candidates[i].name;
            }
        }
    }

    // Display winners
    for (int i = 0; i <= winners; i++)
    {
        printf("%s\n", winner[i]);
    }
    return;
}


