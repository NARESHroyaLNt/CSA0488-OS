#include <stdio.h>
#include <stdlib.h>
int findPage(int page, int frames[], int num_frames) 
{
    for (int i = 0; i < num_frames; i++) 
	{
        if (frames[i] == page) 
		{
            return 1;
        }
    }
    return 0;
}
int fifoPageReplacement(int pages[], int num_pages, int num_frames) 
{
    int frames[num_frames];
    for (int i = 0; i < num_frames; i++) 
	{
        frames[i] = -1; 
    }
    int page_faults = 0;
    int insert_pos = 0;
    for (int i = 0; i < num_pages; i++) 
	{
        if (!findPage(pages[i], frames, num_frames)) 
		{
            frames[insert_pos] = pages[i];
            insert_pos = (insert_pos + 1) % num_frames;
            page_faults++;
        }
    }
    return page_faults;
}
int main() 
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int num_pages = sizeof(pages) / sizeof(pages[0]);
    int num_frames = 4;
    int page_faults = fifoPageReplacement(pages, num_pages, num_frames);
    printf("Number of page faults: %d\n", page_faults);
    return 0;
}

