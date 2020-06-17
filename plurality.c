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
void sort_candidates(int position);

// Start Program
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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highest_vote = 0;
    string winner;
    bool tied = false;

    // Sort list of candidates
    sort_candidates(0);

    // Search for the highest vote
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= highest_vote)
        {
            highest_vote = candidates[i].votes;
            winner = candidates[i].name;
        }
    }

    // Print Winner or Winners
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == highest_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    // In order to have multiple winners we need to sort the list according to the votes
    // Then we need to print all candidates that meet the criteria of highest vote

    return;
}

void sort_candidates(int position)
{
    string temp_name;
    int temp_votes = 0;

    // Break if end of list
    if (position == (candidate_count - 1))
    {
        return;
    }

    if (candidates[position].votes > candidates[position + 1].votes)
    {
        temp_name = candidates[position + 1].name;
        temp_votes = candidates[position + 1].votes;

        // Swap position in list
        candidates[position + 1].name = candidates[position].name;
        candidates[position + 1].votes = candidates[position].votes;
        candidates[position].name = temp_name;
        candidates[position].votes = temp_votes;
    }
    else
    {
        sort_candidates(position + 1);
    }

    return;
}
