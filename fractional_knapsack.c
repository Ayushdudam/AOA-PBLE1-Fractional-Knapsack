#include <stdio.h>
#include <stdlib.h>

#define MAX_PACKAGES 100

typedef struct {
    int id;
    char name[50];
    float value;
    float weight;
    float ratio;
    float fraction;
} Package;

Package packages[MAX_PACKAGES];
int n = 0;
float capacity = 0.0f;
int ratiosCalculated = 0;
int sorted = 0;
int solutionCalculated = 0;

void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

int readInt(const char *prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            clearInputBuffer();
            return value;
        }
        printf("Invalid input. Enter a value from %d to %d.\n", min, max);
        clearInputBuffer();
    }
}

float readPositiveFloat(const char *prompt) {
    float value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &value) == 1 && value > 0.0f) {
            clearInputBuffer();
            return value;
        }
        printf("Invalid input. Enter a value greater than 0.\n");
        clearInputBuffer();
    }
}

void enterPackageDetails(void) {
    int i;

    n = readInt("Enter number of packages (1-100): ", 1, MAX_PACKAGES);
    capacity = readPositiveFloat("Enter delivery capacity: ");

    for (i = 0; i < n; i++) {
        packages[i].id = i + 1;
        printf("\nPackage %d\n", i + 1);
        printf("Enter package name: ");

        if (fgets(packages[i].name, sizeof(packages[i].name), stdin) == NULL) {
            packages[i].name[0] = '\0';
        } else {
            size_t len = 0;
            while (packages[i].name[len] != '\0') {
                if (packages[i].name[len] == '\n') {
                    packages[i].name[len] = '\0';
                    break;
                }
                len++;
            }
        }

        packages[i].value = readPositiveFloat("Enter value: ");
        packages[i].weight = readPositiveFloat("Enter weight: ");
        packages[i].ratio = 0.0f;
        packages[i].fraction = 0.0f;
    }

    ratiosCalculated = 0;
    sorted = 0;
    solutionCalculated = 0;
    printf("\nPackage details entered successfully.\n");
}

void displayPackageDetails(void) {
    int i;

    if (n == 0) {
        printf("\nNo package details available. Please enter packages first.\n");
        return;
    }

    printf("\n================ PACKAGE DETAILS ================\n");
    printf("%-5s %-20s %-10s %-10s %-12s\n",
           "ID", "Name", "Value", "Weight", "Value/Weight");
    printf("--------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-5d %-20s %-10.2f %-10.2f %-12.2f\n",
               packages[i].id, packages[i].name, packages[i].value,
               packages[i].weight, packages[i].ratio);
    }
    printf("Capacity: %.2f\n", capacity);
}

void calculateRatios(void) {
    int i;

    if (n == 0) {
        printf("\nNo package details available. Please enter packages first.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        packages[i].ratio = packages[i].value / packages[i].weight;
    }

    ratiosCalculated = 1;
    sorted = 0;
    solutionCalculated = 0;

    printf("\nValue/Weight ratios calculated successfully.\n");
    printf("%-5s %-20s %-12s\n", "ID", "Name", "Ratio");
    printf("----------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-5d %-20s %-12.2f\n",
               packages[i].id, packages[i].name, packages[i].ratio);
    }
}

void sortPackagesByRatio(void) {
    int i, j;
    Package temp;

    if (n == 0) {
        printf("\nNo package details available. Please enter packages first.\n");
        return;
    }

    if (!ratiosCalculated) {
        calculateRatios();
    }

    /* Bubble sort: O(n^2) time and O(1) auxiliary space. */
    for (i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (packages[j].ratio < packages[j + 1].ratio) {
                temp = packages[j];
                packages[j] = packages[j + 1];
                packages[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }

    sorted = 1;
    solutionCalculated = 0;

    printf("\nPackages sorted by ratio (highest to lowest).\n");
    printf("%-5s %-20s %-12s\n", "ID", "Name", "Ratio");
    printf("----------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-5d %-20s %-12.2f\n",
               packages[i].id, packages[i].name, packages[i].ratio);
    }
}

float findMaximumValue(void) {
    int i;
    float remainingCapacity;
    float totalValue = 0.0f;

    if (n == 0) {
        printf("\nNo package details available. Please enter packages first.\n");
        return 0.0f;
    }

    if (!ratiosCalculated) calculateRatios();
    if (!sorted) sortPackagesByRatio();

    for (i = 0; i < n; i++) packages[i].fraction = 0.0f;
    remainingCapacity = capacity;

    /* Greedy selection after sorting: O(n). Overall: O(n^2) due to sorting. */
    for (i = 0; i < n && remainingCapacity > 0.000001f; i++) {
        if (packages[i].weight <= remainingCapacity) {
            packages[i].fraction = 1.0f;
            remainingCapacity -= packages[i].weight;
            totalValue += packages[i].value;
        } else {
            packages[i].fraction = remainingCapacity / packages[i].weight;
            totalValue += packages[i].value * packages[i].fraction;
            remainingCapacity = 0.0f;
        }
    }

    solutionCalculated = 1;
    printf("\nMaximum value that can be carried: %.2f\n", totalValue);
    return totalValue;
}

void displaySelectedPackages(void) {
    int i;
    float totalWeight = 0.0f;
    float totalValue = 0.0f;

    if (n == 0) {
        printf("\nNo package details available. Please enter packages first.\n");
        return;
    }
    if (!solutionCalculated) {
        printf("\nPlease select option 5 (Find Maximum Value) first.\n");
        return;
    }

    printf("\n================ SELECTED PACKAGES ================\n");
    for (i = 0; i < n; i++) {
        if (packages[i].fraction > 0.000001f) {
            float selectedWeight = packages[i].weight * packages[i].fraction;
            float selectedValue = packages[i].value * packages[i].fraction;
            printf("Package %d (%s): %.2f fraction, Weight = %.2f, Value = %.2f\n",
                   packages[i].id, packages[i].name, packages[i].fraction,
                   selectedWeight, selectedValue);
            totalWeight += selectedWeight;
            totalValue += selectedValue;
        }
    }

    printf("\nTotal selected weight: %.2f\n", totalWeight);
    printf("Maximum value: %.2f\n", totalValue);
}

void displayMenu(void) {
    printf("\n================ SMART DELIVERY PLANNING ================\n");
    printf("1. Enter Package Details\n");
    printf("2. Display Package Details\n");
    printf("3. Calculate Value/Weight Ratio\n");
    printf("4. Sort Packages by Ratio\n");
    printf("5. Find Maximum Value\n");
    printf("6. Display Selected Packages\n");
    printf("7. Exit\n");
    printf("==========================================================\n");
}

int main(void) {
    int choice;

    printf("PBLE 1: Smart Delivery Planning - Fractional Knapsack\n");
    while (1) {
        displayMenu();
        choice = readInt("Enter your choice (1-7): ", 1, 7);
        switch (choice) {
            case 1: enterPackageDetails(); break;
            case 2: displayPackageDetails(); break;
            case 3: calculateRatios(); break;
            case 4: sortPackagesByRatio(); break;
            case 5: findMaximumValue(); break;
            case 6: displaySelectedPackages(); break;
            case 7:
                printf("\nProgram exited successfully.\n");
                return 0;
        }
    }
}
