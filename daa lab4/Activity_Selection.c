#include <stdio.h>
#include <stdlib.h> 

#define MAX_ACTIVITIES 100  // Define a maximum number of activities

// Function to compare two activities based on their finish times
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Function to perform the activity selection
void activity_selection(int start[], int finish[], int n) {
    // Create an array of activities where each activity has a start and finish time
    int activities[MAX_ACTIVITIES][2];
    
    // Copy the start and finish times into the activities array
    for (int i = 0; i < n; i++) {
        activities[i][0] = start[i];
        activities[i][1] = finish[i];
    }

    // Sort activities based on their finish times
    qsort(activities, n, sizeof(activities[0]), compare);

    // The first activity always gets selected
    int last_selected = 0;
    printf("Selected activities:\n");
    printf("Activity %d (Start: %d, Finish: %d)\n", last_selected + 1, activities[last_selected][0], activities[last_selected][1]);

    // Check the rest of the activities
    for (int i = 1; i < n; i++) {
        if (activities[i][0] >= activities[last_selected][1]) {
            printf("Activity %d (Start: %d, Finish: %d)\n", i + 1, activities[i][0], activities[i][1]);
            last_selected = i;
        }
    }
}

int main() {
    int n;

    // Input the number of activities
    printf("Enter the number of activities (max %d): ", MAX_ACTIVITIES);
    scanf("%d", &n);

    // Check if the number of activities is within bounds
    if (n <= 0 || n > MAX_ACTIVITIES) {
        printf("Invalid number of activities. Please enter a number between 1 and %d.\n", MAX_ACTIVITIES);
        return 1;
    }

    int start[MAX_ACTIVITIES], finish[MAX_ACTIVITIES];

    // Input the start and finish times for the activities
    printf("Enter the start times:\n");
    for (int i = 0; i < n; i++) {
        printf("Start time for Activity %d: ", i + 1);
        scanf("%d", &start[i]);
    }

    printf("Enter the finish times:\n");
    for (int i = 0; i < n; i++) {
        printf("Finish time for Activity %d: ", i + 1);
        scanf("%d", &finish[i]);
        // Ensure finish time is greater than start time
        if (finish[i] <= start[i]) {
            printf("Finish time must be greater than start time for Activity %d!\n", i + 1);
            return 1; // Exit if invalid
        }
    }

    // Perform the activity selection
    activity_selection(start, finish, n);

    return 0;
}
