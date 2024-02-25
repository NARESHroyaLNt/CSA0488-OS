#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 
#define MAX_PAGES 100
int findLRU(int timeStamp[], int num_frames) 
{
    int i, minimum = timeStamp[0], pos = 0;
    for (i = 1; i < num_frames; ++i) 
	{
        if (timeStamp[i] < minimum) 
		{
            minimum = timeStamp[i];
            pos = i;
        }
    }
    return pos;
}
int lruPageReplacement(int pages[], int num_pages, int num_frames) 
{
    int frames[num_frames], timeStamp[num_frames];
    int page_faults = 0, counter = 0, flag1, flag2, i, j, pos;
    for (i = 0; i < num_frames; ++i) 
	{
        frames[i] = -1;
    }
    for (i = 0; i < num_pages; ++i) 
	{
        flag1 = flag2 = 0;
        for (j = 0; j < num_frames; ++j) 
		{
            if (frames[j] == pages[i]) 
			{
                counter++;
                timeStamp[j] = counter; 
                flag1 = flag2 = 1;
                break;
            }
        }
        if (flag1 == 0) 
		{
            for (j = 0; j < num_frames; ++j) 
			{
                if (frames[j] == -1) 
				{
                    counter++;
                    page_faults++;
                    frames[j] = pages[i];
                    timeStamp[j] = counter; 
                    flag2 = 1;
                    break;
                }
            }
        }
        if (flag2 == 0) 
		{
            pos = findLRU(timeStamp, num_frames);
            counter++;
            page_faults++;
            frames[pos] = pages[i];
            timeStamp[pos] = counter;
        }
    }
    return page_faults;
}
int main() 
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int num_pages = sizeof(pages) / sizeof(pages[0]);
    int num_frames = 4;
    int page_faults = lruPageReplacement(pages, num_pages, num_frames);
    printf("Number of page faults: %d\n", page_faults);
    return 0;
}

