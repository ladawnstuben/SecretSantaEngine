#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>

// Function to save Secret Santa assignments to a file
void saveToFile(const std::vector<std::string>& participants, const std::vector<std::string>& gifts, int listNumber) {
    std::ofstream outFile("SecretSantaAssignments.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << "\nList " << listNumber << ":\n";
        for (size_t i = 0; i < participants.size(); ++i) {
            outFile << participants[i] << " received: " << gifts[i] << std::endl;
        }
        std::cout << "Secret Santa assignments saved to 'SecretSantaAssignments.txt'\n";
        outFile.close();
    }
    else {
        std::cerr << "Error: Unable to open the file for writing.\n";
    }
}

// Function to display Secret Santa assignments
void displayAssignments(const std::vector<std::string>& shuffledParticipants, const std::vector<std::string>& gifts) {
    // Add a blank line before displaying assignments
    std::cout << "\n";

    // Assign gifts to participants
    for (size_t i = 0; i < shuffledParticipants.size(); ++i) {
        std::cout << shuffledParticipants[i] << " received: " << gifts[i] << std::endl;
    }
}

// Function to perform Secret Santa assignment
void secretSanta(const std::vector<std::string>& participants, const std::vector<std::string>& gifts, int& listNumber) {
    // Shuffle the participants vector to randomize the assignments
    std::vector<std::string> shuffledParticipants = participants;
    std::random_shuffle(shuffledParticipants.begin(), shuffledParticipants.end());

    // Display assignments
    displayAssignments(shuffledParticipants, gifts);

    // Save assignments to a file
    saveToFile(shuffledParticipants, gifts, listNumber++);
}

// Function to reset names (participants or gifts)
void resetNames(std::vector<std::string>& names, const std::string& type) {
    names.clear();
    std::cout << "Enter the number of " << type << ": ";
    size_t numNames;
    std::cin >> numNames;

    for (size_t i = 0; i < numNames; ++i) {
        std::cout << "Enter " << type << " " << i + 1 << ": ";
        std::string name;
        std::cin >> name;
        names.push_back(name);
    }
}

// Function to display the menu
void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add/Reset Participants\n";
    std::cout << "2. Add/Reset Gifts\n";
    std::cout << "3. Assign Secret Santas\n";
    std::cout << "4. Quit\n";
    std::cout << "5. Clear File\n";
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
            std::cout << "Exiting program.\n";
            return 0;
        case 5:
            clearFile();
            break;
        default:
            std::cerr << "Error: Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}