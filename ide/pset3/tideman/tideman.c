#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// Debuging function prototypes
void print_preferences(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    /* print_preferences(); */

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Check if the candidate ranked is between the array
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(name, candidates[k]) == 0)
        {
            // Rank the candidate
            ranks[rank] = k;
            /* printf("%s: %i\n", candidates[k], ranks[rank]); */
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Translate ranks to preferences
    for (int j = 0; j < candidate_count; j++)
    {
        for (int k = j + 1; k < candidate_count; k++)
        {
            preferences[ranks[j]][ranks[k]]++;
            /* printf("%s over %s : %i\n", candidates[ranks[j]], candidates[ranks[k]], preferences[ranks[j]][ranks[k]]); */
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Cycles through all preferences and stores them into pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > 0) /* && (i != j) */
            {
                for (int k = 0; k < preferences[i][j]; k++)
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Does nothing to result, just calculates matrix
    int max_prefs = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > max_prefs)
            {
                max_prefs = preferences[i][j];
            }
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] == max_prefs)
            {
                locked[i][j] = true;
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Calculates winner without sorting pairs or locking pairs
    int votes[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        votes[i] = 0;
        for (int j = 0; j < pair_count; j++)
        {
            if (pairs[j].winner == i)
            {
                votes[i]++;
            }
        }
    }
    int max_votes = 0;
    int max_cand = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if ((votes[i] > votes[j]) && (votes[i] > max_votes))
            {
                max_votes = votes[i];
                max_cand = i;
            }
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if ((votes[i] == votes[j]) && (votes[i] == max_votes))
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    max_cand = i;
                }
                else if (preferences[j][i] > preferences[i][j])
                {
                    max_cand = j;
                }
            }
        }
    }

    printf("%s\n", candidates[max_cand]);
    return;
}

// Prints the overall preferences (for debbuging purposes)
void print_preferences(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                printf("%s over %s : %i\n", candidates[i], candidates[j], preferences[i][j]);
            }
        }
    }
    printf("\n");
}