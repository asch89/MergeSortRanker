#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 2000

typedef struct{
	char * name; //dynamic string
}player_t;

//function prototype(s)
player_t* scanRoster(player_t *roster, int* size);
void mergeSortRoster(player_t* roster, int p, int r); //perform mergesort on initial unsorted roster
void merge(player_t* roster, int p, int q, int r); //sort by merging seperated arrays
void makeTeams(player_t* roster, player_t* team1, player_t* team2, int size); //assign first/best half of players to my team, second/worst half to ron's
double averageRank(player_t* team); //calculate the mean for a team

int main(void)
{
    /*
	player_t *roster = (player_t*) malloc(sizeof(player_t) * MAX);
	int index = 0;
	int input = 0;
    printf("-\nWelcome to the MergeSort Ranker! To begin, please input the entries you will be ranking.\n");
	while(index < MAX && input != 2)
	{
	    printf("\nPress 1 to add an entry, Press 2 to continue to ranking\n");
	    scanf("%d", &input);
	    switch(input)
	    {
            case 1:
            {
                roster[index].name = (char *) malloc(sizeof(char) * 50);
                printf("Please type your entry: ");
                scanf(" %[^\n]s", roster[index].name);
                //strcpy(roster[index].name, name);
                ++index;
                break;
            }
            case 2:
            {
                break;
            }
            default:
            {
                printf("\nThat is not a valid input, please try again.\n");
                break;
            }
	    }
	}
	*/
	player_t *roster = (player_t*) malloc(sizeof(player_t) * MAX);
	int index = 0;
	int check = 1;
	char input[50];
    printf("-\nWelcome to the MergeSort Ranker! To begin, please input the entries you will be ranking. Type '0' when you are ready to rank.\n\n");
	while(index < MAX && check != 0)
	{
	    printf("Please type an entry: ");
	    scanf(" %[^\n]s", input);
	    if(!strcmp(input, "0"))
            check = 0;
	    switch(check)
	    {
            case 0:
            {
                break;
            }
            default:
            {
                roster[index].name = (char *) malloc(sizeof(char) * 50);
                strcpy(roster[index].name, input);
                //strcpy(roster[index].name, name);
                ++index;
                break;
            }
	    }

	}

	printf("\nGreat! Now we can begin ranking your entries.\n");
	mergeSortRoster(roster, 0, index-1); //perform sorting greatest to least, merge will be called within this funciton

	int place = 1;
    printf("\nYour Rankings are:\n");
	for(int i = 0; i<index; i++)
    {
        printf("\n%d: %s\n", place, roster[i].name);
        place++;
    }


	return 0;
}




player_t* scanRoster(player_t *roster, int* size)
{

}

void mergeSortRoster(player_t *roster, int p, int r)
{
    if(p < r) //run until we have split array entirely
    {
        int q = (r + p) / 2; //find last element on left side
        mergeSortRoster(roster, p, q); //repeat process on left side
        mergeSortRoster(roster, q + 1, r); //repeat process on right side
        merge(roster, p, q, r); //merge together
    }
}

void merge(player_t* roster, int p, int q, int r)
{
    int n1 = q - p + 1; //find number of elements for leftarr
    int n2 = r - q; //find number of elements for rightarr
    player_t* leftarr = (player_t*) malloc(sizeof(player_t) * n1); //allocate space for leftarr
    player_t* rightarr = (player_t*) malloc(sizeof(player_t) * n2); //allocate space for rightarr
    for(int x = 0; x < n1; ++x)
        leftarr[x] = roster[p + x]; //fill leftarr
    for(int x = 0; x < n2; ++x)
        rightarr[x] = roster[q + x + 1]; //fill rightarr
    int i = 0;
    int j = 0;
    int k = p;
    int choice = 0;
    while (i < n1 && j < n2) //traverse both arrays, take player with higher rank between the two arrays at index i, and place it at index k of our original list
    {
        printf("\nPress 1 for %s, Press 2 for %s\nInput:", leftarr[i].name, rightarr[j].name);
        scanf("%d", &choice);
        switch(choice)
            {
                case 1:
                {
                    roster[k] = leftarr[i];
                    i++;
                    break;
                }
                case 2:
                {
                    roster[k] = rightarr[j];
                    j++;
                    break;
                }
                default:
                {
                    printf("\nThat is not a valid input, please try again.\n");
                    return;
                }
            }
            k++;
    }
    while (i < n1) //if additional values in either array, traverse and add them to original list
    {
        roster[k] = leftarr[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        roster[k] = rightarr[j];
        j++;
        k++;
    }
    free(leftarr);
    free(rightarr);
}

void makeTeams(player_t *roster, player_t *team1, player_t *team2, int size)
{
    int n = (size/2); //get middle of roster value

    for(int i = 0; i<n; i++)
        team2[i] = roster[i]; //traverse my team's array, placing players in the first half of roster on the team
    for(int x = 0; x<n; x++)
        team1[x] = roster[n+x]; //traverse other team's array, placing players in the second half of roster on the team
}
