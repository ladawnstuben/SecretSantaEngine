//ITCS 2530 - Final Project Group 1
//Christian Kalaj, Zackary Sanchez, LaDawn Stuben
//Secret Santa Gift Engine
//Date: 12/15/2023
//This program will allow the user to enter a list of participants and gifts, and then assign Secret Santas to each participant.
//The program will also save the assignments to a file, and allow the user to view the contents of the file.


#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>

const int maxSize = 100; // Maximum number of participants and gifts

// Structure representing a Secret Santa assignment
struct SecretSantaAssignment {
    std::string participant; // Name of the participant
    std::string gift;        // Assigned gift
};

// Function declarations
void displayMenu();
void resetNames(std::string names[], int& size, const std::string& type);
void readFromFile();
void clearFile();
bool is_valid_assignment(const std::string participants[], const std::string shuffledParticipants[], int size);
void secretSanta(const std::string participants[], const std::string gifts[], int size, int& listNumber);
void shuffleNames(std::string names[], int size, const std::string& type); // Prototype for shuffleNames


// Saves Secret Santa assignments to a file (Zackary)
void saveToFile(const SecretSantaAssignment assignments[], int size, int listNumber) {
    std::ofstream outFile("SecretSantaAssignments.txt", std::ios::app); // Opens file in append mode
    if (outFile.is_open()) {
        outFile << "\nList " << listNumber << ":\n";
        for (int i = 0; i < size; ++i) {
            // Writes each assignment to the file
            outFile << assignments[i].participant << " received: " << assignments[i].gift << std::endl;
        }
        std::cout << "Secret Santa assignments saved to 'SecretSantaAssignments.txt'\n";
        outFile.close(); // Closes the file
    }
    else {
        std::cerr << "Error: Unable to open the file for writing.\n";
    }
}

// Displays the Secret Santa assignments to the console
void displayAssignments(const SecretSantaAssignment assignments[], int size) {
    std::cout << "\n";
    for (int i = 0; i < size; ++i) {
        // Prints each assignment to the console
        std::cout << assignments[i].participant << " Received: " << assignments[i].gift << std::endl;
    }
}

// Reads and displays the contents of the assignment file (Zackary)
void readFromFile() {
    std::ifstream inFile("SecretSantaAssignments.txt"); // Opens file for reading
    if (inFile.is_open()) {
        std::string line;
        std::cout << "\nContents of 'SecretSantaAssignments.txt':\n";
        while (std::getline(inFile, line)) {
            // Reads and prints each line from the file
            std::cout << line << "\n";
        }
        inFile.close(); // Closes the file
    }
    else {
        std::cerr << "Error: Unable to open the file for reading.\n";
    }
}
// Function to check if the Secret Santa assignment is valid
bool is_valid_assignment(const std::string participants[], const std::string shuffledParticipants[], int size) {
    for (int i = 0; i < size; ++i) {
        if (participants[i] == shuffledParticipants[i]) {
            return false; // Invalid if a participant is assigned to themselves
        }
    }
    return true; // Valid assignment
}


// Assigns Secret Santas and manages the process (Christian, updated by LaDawn for integration)
void secretSanta(const std::string participants[], const std::string gifts[], int size, int& listNumber) {
    std::string shuffledParticipants[maxSize];
    SecretSantaAssignment assignments[maxSize]; // Local assignments array

    std::random_device rd; // Random device
    std::mt19937 g(rd()); // Random number generator

    // Copy participants to shuffledParticipants and shuffle
    std::copy(participants, participants + size, shuffledParticipants);
    std::shuffle(shuffledParticipants, shuffledParticipants + size, g);

    // Assign gifts to each participant
    for (int i = 0; i < size; ++i) {
        int receiverIndex = (i + 1) % size; // Circular assignment
        assignments[i].participant = shuffledParticipants[i];
        assignments[i].gift = gifts[receiverIndex]; // Assign the gift from the next participant

        std::cout << shuffledParticipants[i] << " will give a gift to " << shuffledParticipants[receiverIndex] << std::endl;
    }

    displayAssignments(assignments, size); // Displays the shuffled assignments
    saveToFile(assignments, size, listNumber++); // Saves the assignments to a file and increments listNumber
}



// Resets the names of participants or gifts (Christian, updated by LaDawn to satisy nested loop requirement)
void resetNames(std::string names[], int& size, const std::string& type) {
    size = 0;

    while (true) {
        std::cout << "Enter the number of " << type << ": ";
        int numNames;
        std::cin >> numNames;

        if (std::cin.fail() || numNames <= 0 || numNames > maxSize) {
            std::cout << "Invalid input. Please enter a valid number (1 to " << maxSize << ").\n";
            std::cin.clear();
            while (std::cin.get() != '\n'); // Clears the input buffer
        }
        else {
            for (int i = 0; i < numNames; ++i) {
                std::string inputName;
                while (true) { // Nested loop starts here
                    std::cout << "Enter " << type << " " << i + 1 << ": ";
                    std::cin >> inputName;

                    if (!inputName.empty() && inputName.length() <= 50) { // Validate name
                        names[i] = inputName; // Assigns name if validation passes
                        break; // Exit the nested loop
                    }
                    else {
                        std::cout << "Invalid name. Please enter a name up to 50 characters.\n";
                    }
                } // Nested loop ends here
            }
            size = numNames;
            break; // Exits the loop on valid input
        }
    }
}

// Shuffles the names of participants or gifts (LaDawn)
void shuffleNames(std::string names[], int size, const std::string& type) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(names, names + size, g); // Using std::shuffle
    std::cout << type << " shuffled.\n";
}

// Displays the main menu (Christian)
void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add Participants\n";
    std::cout << "2. Add Gifts\n";
    std::cout << "3. Assign Secret Santas\n";
    std::cout << "4. Display List From File\n";
    std::cout << "5. Start Over\n";
    std::cout << "6. Quit\n";
    std::cout << "Enter your choice: ";
}

// Clears the contents of the Secret Santa assignment file (Zackary)
void clearFile() {
    std::ofstream outFile("SecretSantaAssignments.txt", std::ios::trunc); // Opens file in truncate mode
    if (outFile.is_open()) {
        std::cout << "File 'SecretSantaAssignments.txt' has been cleared.\n";
        outFile.close(); // Closes the file
    }
    else {
        std::cerr << "Error: Unable to open the file for writing.\n";
    }
}


// Main function (everyone)
int main() {
    // Display welcome message (LaDawn)
    // ASCII art from https://ascii.co.uk/art/santa
    std::cout << "  |_|\n";
    std::cout << "  (>)\n";
    std::cout << " (':')\n";
    std::cout << " ( : )\n";
        std::cout << "========================================\n";
        std::cout << "  Welcome to the Secret Santa Generator!\n";
        std::cout << "========================================\n";
        std::cout << "This program helps you organize a fun and exciting Secret Santa event.\n";
        std::cout << "You can add participants, assign Secret Santas, and manage gifts.\n";
        std::cout << "Let's get started with organizing your Secret Santa!\n";
        std::cout << "To begin, choose an option from the menu below:\n";

    
    std::string participants[maxSize]; // Array for participants
    std::string gifts[maxSize]; // Array for gifts
    SecretSantaAssignment assignments[maxSize]; // Array for assignments

    int participantSize = 0; // Number of participants
    int giftSize = 0; // Number of gifts
    int listNumber = 1; // Counter for assignment lists

    while (true) {
        displayMenu(); // Displays the main menu

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            resetNames(participants, participantSize, "participants"); // Adds participants
            break;
        case 2:
            resetNames(gifts, giftSize, "gifts"); // Adds gifts
            break;
        case 3:
            if (participantSize < 2 || participantSize != giftSize) { // Validates the number of participants and gifts
                std::cerr << "Oops! You must have an equal number of participants and gifts, and at least two participants.\n";
            }
            else {
                secretSanta(participants, gifts, participantSize, listNumber); // Assigns Secret Santas
            }
            break;
        case 4:
            readFromFile(); // Outputs list from file
            break;
        case 5:
            clearFile(); // Clears the file
            break;
        case 6:
            std::cout << "Happy Holidays!\n";
            return 0; // Exits the program
        default:
            std::cerr << "Invalid option. Please enter a valid choice.\n";
        }
    }

    return 0;
}