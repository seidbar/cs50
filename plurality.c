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
    // Checks if the candidate is present
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    printf("Not found");
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Define 3 Winners max.
    candidate winners[3];
    winners[0].name = "";
    winners[0].votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        // Sort array
        if (candidates[i].votes > winners[0].votes)
        {
            winners[0] = candidates[i];
            winners[1].name = "";
            winners[1].votes = 0;
            winners[2].name = "";
            winners[2].votes = 0;
        }
        // Check if there are more than one winner
        else if (candidates[i].votes == winners[0].votes)
        {
            if (candidates[i].votes == winners[1].votes)
            {
                winners[2] = candidates[i];
            }
            else
            {
                winners[1] = candidates[i];
            }
        }
    }
    printf("%s\n", winners[0].name);
    if (winners[1].votes > 0)
    {
        printf("%s\n", winners[1].name);
        if (winners[2].votes > 0)
        {
            printf("%s\n", winners[2].name);
        }
    }
    return;
}


