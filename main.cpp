#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <string>

// Define a structure for Secret Santa assignments
struct SecretSantaAssignment {
    std::string participant;
    std::string gift;
};

// Function to save Secret Santa assignments to a file
void saveToFile(const std::vector<SecretSantaAssignment>& assignments, int listNumber) {
    std::ofstream outFile("SecretSantaAssignments.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << "\nList " << listNumber << ":\n";
        for (const auto& assignment : assignments) {
            outFile << assignment.participant << " received: " << assignment.gift << std::endl;
        }
        std::cout << "Secret Santa assignments saved to 'SecretSantaAssignments.txt'\n";
        outFile.close();
    }
    else {
        std::cerr << "Error: Unable to open the file for writing.\n";
    }
}

// Function to display Secret Santa assignments
void displayAssignments(const std::vector<SecretSantaAssignment>& assignments) {
    // Add a blank line before displaying assignments
    std::cout << "\n";

    // Assign gifts to participants
    for (const auto& assignment : assignments) {
        std::cout << assignment.participant << " received: " << assignment.gift << std::endl;
    }
}

// Function to read and display contents from the file
void readFromFile() {
    std::ifstream inFile("SecretSantaAssignments.txt");
    if (inFile.is_open()) {
        std::string line;
        std::cout << "\nContents of 'SecretSantaAssignments.txt':\n";
        while (std::getline(inFile, line)) {
            std::cout << line << "\n";
        }
        inFile.close();
    }
    else {
        std::cerr << "Error: Unable to open the file for reading.\n";
    }
}

// Function to perform Secret Santa assignment
void secretSanta(const std::vector<std::string>& participants, std::vector<std::string>& gifts, int& listNumber) {
    // Shuffle the participants vector to randomize the assignments
    std::vector<SecretSantaAssignment> assignments;
    for (size_t i = 0; i < participants.size(); ++i) {
        SecretSantaAssignment assignment;
        assignment.participant = participants[i];
        assignment.gift = gifts[i];
        assignments.push_back(assignment);
    }

    std::random_shuffle(assignments.begin(), assignments.end());

    // Display assignments
    displayAssignments(assignments);

    // Save assignments to a file
    saveToFile(assignments, listNumber++);
}

// Function to randomly swap the order of gifts among participants
void randomlySwapGifts(std::vector<std::string>& participants, std::vector<std::string>& gifts) {
    std::random_shuffle(gifts.begin(), gifts.end());

    // Display the updated list
    for (size_t i = 0; i < participants.size(); ++i) {
        std::cout << participants[i] << " received: " << gifts[i] << std::endl;
    }

    // Clear the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
}

// Function to reset names (participants or gifts) with a nested loop
void resetNames(std::vector<std::string>& names, const std::string& type) {
    names.clear();

    // Use a nested loop to ensure the user enters a valid number
    while (true) {
        std::cout << "Enter the number of " << type << ": ";
        size_t numNames;
        std::cin >> numNames;

        // Check if the input is a valid number
        if (std::cin.fail() || numNames <= 0) {
            std::cout << "Invalid input. Please enter a valid number.\n";

            // Clear the input buffer to prevent an infinite loop
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            // Valid input, proceed with getting names
            for (size_t i = 0; i < numNames; ++i) {
                std::string name;
                std::cout << "Enter " << type << " " << i + 1 << ": ";
                std::cin >> name;
                names.push_back(name);
            }
            break; // Break the loop if valid input
        }
    }
}

// Function to shuffle participants or gifts
void shuffleNames(std::vector<std::string>& names, const std::string& type) {
    std::random_shuffle(names.begin(), names.end());
    std::cout << type << " shuffled.\n";
}

// Function to display the menu
void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add/Reset Participants\n";
    std::cout << "2. Add/Reset Gifts\n";
    std::cout << "3. Assign Secret Santas\n";
    std::cout << "4. Read from File\n";
    std::cout << "5. Clear File\n";
    std::cout << "6. Quit\n";
    std::cout << "7. Randomly Swap Gifts Among Participants\n"; // Updated option for randomly swapping gifts
    std::cout << "Enter your choice: ";
}

// Function to clear the contents of the file
void clearFile() {
    std::ofstream outFile("SecretSantaAssignments.txt", std::ios::trunc); // Open in trunc mode to clear the file
    if (outFile.is_open()) {
        std::cout << "File 'SecretSantaAssignments.txt' has been cleared.\n";
        outFile.close();
    }
    else {
        std::cerr << "Error: Unable to open the file for writing.\n";
    }
}

int main() {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<std::string> participants;
    std::vector<std::string> gifts;

    int listNumber = 1;

    while (true) {
        displayMenu();

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            resetNames(participants, "participants");
            break;
        case 2:
            resetNames(gifts, "gifts");
            break;
        case 3:
            if (participants.size() < 2 || participants.size() != gifts.size()) {
                std::cerr << "Error: Invalid number of participants or gifts. Please check and try again.\n";
                break;
            }
            secretSanta(participants, gifts, listNumber);
            break;
        case 4:
            readFromFile(); // Added option to read from file
            break;
        case 5:
            clearFile();
            break;
        case 6:
            std::cout << "Exiting program.\n";
            return 0;
        case 7:
            randomlySwapGifts(participants, gifts);
            break;
        default:
            std::cerr << "Error: Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
