#include <stdio.h>
#include <stdlib.h>
int findOptimalPageToReplace(int pages[], int np, int frame[], int nf, int index) 
{
    int pos = -1;
    int farthest = index;
    for (int i = 0; i < nf; i++) 
	{
        int j;
        for (j = index; j < np; j++) 
		{
            if (frame[i] == pages[j]) 
			{
                if (j > farthest) 
				{
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == np)
            return i;
    }
    return pos == -1 ? 0 : pos; 
}
void optimalPage(int pages[], int np, int frames[], int nf) 
{
    int pageFaults = 0;
    int counter = 0;
    for (int i = 0; i < np; i++) 
	{
        int found = 0;
        for (int j = 0; j < nf; j++) 
		{
            if (frames[j] == pages[i]) 
			{
                found = 1;
                break;
            }
        }
        if (!found) 
		{
            if (counter < nf) 
			{
                frames[counter++] = pages[i];
            } else {
                int j = findOptimalPageToReplace(pages, np, frames, nf, i + 1);
                frames[j] = pages[i];
            }
            pageFaults++;
        }
    }
    printf("Total Page Faults: %d\n", pageFaults);
}
int main() 
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1};
    int np = sizeof(pages) / sizeof(pages[0]); 
    int nf;
    printf("Enter the number of frames: ");
    scanf("%d", &nf);
    int frames[nf];
    for (int i = 0; i < nf; i++) 
	{
        frames[i] = -1; 
    }
    optimalPage(pages, np, frames, nf);
    return 0;
}
