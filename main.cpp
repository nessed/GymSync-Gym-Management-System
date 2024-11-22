#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to generate new Member ID
string generateMemberId() {
    string memberid;
    ifstream file("members.txt");

    if (file.peek() == EOF) {
        memberid = "10001";
    } else {
        string line;
        while (getline(file, line)) {
            memberid = line;
        }
        memberid = to_string(stoi(memberid) + 1);
    }
    file.close();
    return memberid;
}

// Function to register a new member
void newRegistration(sf::RenderWindow &window, sf::Font &font) {
    string name, contactno, membershipstartdate, membershiptype, memberid;
    bool registrationComplete = false;

    sf::Text title("New Member Registration", font, 30);
    title.setFillColor(sf::Color::White);
    title.setPosition(150, 50);

    sf::Text instructions("Fill out the details below:", font, 20);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(150, 120);

    sf::Text namePrompt("Enter your Name: ", font, 20);
    namePrompt.setFillColor(sf::Color::White);
    namePrompt.setPosition(150, 180);

    sf::Text contactPrompt("Enter Contact Number: ", font, 20);
    contactPrompt.setFillColor(sf::Color::White);
    contactPrompt.setPosition(150, 240);

    sf::Text membershipPrompt("Select Membership Type: ", font, 20);
    membershipPrompt.setFillColor(sf::Color::White);
    membershipPrompt.setPosition(150, 300);

    sf::RectangleShape silverButton(sf::Vector2f(200, 50));
    silverButton.setFillColor(sf::Color::Blue);
    silverButton.setPosition(150, 350);

    sf::Text silverText("Silver ($10)", font, 15);
    silverText.setFillColor(sf::Color::White);
    silverText.setPosition(170, 365);

    sf::RectangleShape goldButton(sf::Vector2f(200, 50));
    goldButton.setFillColor(sf::Color::Green);
    goldButton.setPosition(400, 350);

    sf::Text goldText("Gold ($30)", font, 15);
    goldText.setFillColor(sf::Color::White);
    goldText.setPosition(420, 365);

    // User input variables
    string enteredName, enteredContact;
    int membershipChoice = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (silverButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    membershipChoice = 1;
                    membershiptype = "Silver";
                    registrationComplete = true;
                }
                if (goldButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    membershipChoice = 2;
                    membershiptype = "Gold";
                    registrationComplete = true;
                }
            }
        }

        // UI Rendering
        window.clear();
        window.draw(title);
        window.draw(instructions);
        window.draw(namePrompt);
        window.draw(contactPrompt);
        window.draw(membershipPrompt);
        window.draw(silverButton);
        window.draw(silverText);
        window.draw(goldButton);
        window.draw(goldText);
        window.display();

        if (registrationComplete) {
            memberid = generateMemberId();
            ofstream file("members.txt", ios::app);
            file << enteredName + "\n";
            file << enteredContact + "\n";
            file << membershipstartdate + "\n";
            file << membershiptype + "\n";
            file << "Active\n";
            file << memberid + "\n";
            file.close();
            cout << "Registration Successful!" << endl;
            break;
        }
    }
}

// Member Terminal UI
void memberTerminal(sf::RenderWindow &window, sf::Font &font) {
    sf::Text title("Member Terminal", font, 30);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 50);

    sf::RectangleShape registerButton(sf::Vector2f(200, 50));
    registerButton.setFillColor(sf::Color::Blue);
    registerButton.setPosition(200, 200);

    sf::Text registerText("New Registration", font, 20);
    registerText.setFillColor(sf::Color::White);
    registerText.setPosition(220, 215);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (registerButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    newRegistration(window, font);
                }
            }
        }

        // UI Rendering
        window.clear();
        window.draw(title);
        window.draw(registerButton);
        window.draw(registerText);
        window.display();
    }
}

// Main Program UI
void gymManagementSystem() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Gym Management System");
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text welcomeText("Welcome to Gym Management System", font, 30);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setPosition(100, 50);

    sf::RectangleShape memberButton(sf::Vector2f(200, 50));
    memberButton.setFillColor(sf::Color::Blue);
    memberButton.setPosition(150, 200);

    sf::Text memberText("Member Terminal", font, 20);
    memberText.setFillColor(sf::Color::White);
    memberText.setPosition(170, 215);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (memberButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    memberTerminal(window, font);
                }
            }
        }

        // UI Rendering
        window.clear();
        window.draw(welcomeText);
        window.draw(memberButton);
        window.draw(memberText);
        window.display();
    }
}

int main() {
    gymManagementSystem();
    return 0;
}
