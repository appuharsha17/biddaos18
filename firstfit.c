#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main()
{
    int n, m, i, count = 0, j, pn[100];
    int p[100], size[100], internalFragmentation[100];
    bool flag[100];

    // Input: Number of processes and memory partitions
    printf("ENTER THE NO PROCESS AND MEMORY:\n");
    scanf("%d%d", &n, &m);

    // Input: Size of each process
    printf("ENTER THE SIZE OF PROCESS \n");
    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);

    // Input: Size of each memory partition
    printf("ENTER THE SIZE OF MEMORY PARTITION\n\n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &size[i]);
        flag[i] = 0;
        internalFragmentation[i] = 0;
    }

    // Memory allocation using First Fit algorithm
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (p[i] <= size[j] && flag[j] == 0)
            {
                flag[j] = true;
                pn[j] = i;
                internalFragmentation[j] = size[j] - p[i]; // Calculate internal fragmentation
                count++;
                break; // Break out of the inner loop once allocated
            }
        }
    }

    // Output: Display the allocated memory for each partition, the corresponding process, and internal fragmentation
    printf("NO OF PROCESS CAN ACCOMMODATE: %d\n\n", count);
    printf("MEMORY\tPROCESS\tINTERNAL FRAGMENTATION\n");

    int totalInternalFragmentation = 0; // Variable to accumulate total internal fragmentation

    for (i = 0; i < m; i++ )
    {
        if (flag[i] == 1)
        {
            printf("%d <-->%d\t    %d\n", size[i], p[pn[i]], internalFragmentation[i]);
            totalInternalFragmentation += internalFragmentation[i]; // Accumulate total internal fragmentation
        }
        else
            printf("%d\tMEMORY NOT ALLOCATED\n", size[i]);
    }

    printf("\nTotal Internal Fragmentation: %d\n", totalInternalFragmentation);

    return 0;
}