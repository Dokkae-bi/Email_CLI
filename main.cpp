#include <iostream>
#include <string>
#include <iomanip>
#include "email_server.h"
#include "inbox.h"

using namespace std;

// Truncate a string for fixed-width column display
string truncate(const string& s, size_t width) {
    return (s.length() > width) ? s.substr(0, width - 2) + ".." : s;
}

void displayInbox(Inbox& inbox) {
    int count = inbox.num_emails();
    cout << left
         << setw(4)  << "#"
         << setw(26) << "From"
         << setw(34) << "Subject"
         << setw(13) << "Date"
         << "Status\n"
         << string(83, '-') << "\n";
    for (int i = 0; i < count; i++) {
        const Email& e = inbox.getEmail(i);
        cout << setw(4)  << (i + 1)
             << setw(26) << truncate(e.getSender(),  25)
             << setw(34) << truncate(e.getSubject(), 33)
             << setw(13) << e.getDate().toString()
             << (e.isRead() ? "Read" : "Unread") << "\n";
    }
}

void readEmail(Inbox& inbox) {
    cout << "Email number: ";
    int n; cin >> n;
    if (n < 1 || n > inbox.num_emails()) { cout << "Invalid selection.\n"; return; }
    int i = n - 1;
    const Email& e = inbox.getEmail(i);
    cout << "\nFrom:    " << e.getSender()  << "\n"
         << "Subject: " << e.getSubject() << "\n"
         << "Date:    " << e.getDate().toString() << "\n"
         << string(40, '-') << "\n"
         << e.getBody() << "\n";
    inbox.markRead(i);
}

// Delegates to Inbox::remove which handles the left-shift internally
void deleteEmail(Inbox& inbox) {
    cout << "Email number to delete: ";
    int n; cin >> n;

    if (n < 1 || n > inbox.num_emails()) { 
        cout << "Invalid selection.\n"; 
        return; 
    }

    inbox.remove(n - 1);
}

void sortEmails(Inbox& inbox) {
    cout << "How would you like to sort the emails?\n"
         << "1. By Date (newest first)\n"
         << "2. By Read Status (Unread first)\n"
         << "Choice: ";
    int choice; cin >> choice;
    // Sorting logic to be implemented
}

int main() {
    EmailServer server;

    Inbox inbox;

    // populate inbox with a few emails.
    for(int i = 0; i < 5; i++)
        inbox.push(server.getNewEmail());


    int choice;
    do {
        cout << "\n=== Inbox Menu ===\n"
             << "1. View Inbox\n"
             << "2. Read Email\n"
             << "3. Delete Email\n"
             << "4. Get New Email\n"
             << "5. Sort Emails\n"
             << "6. Exit\n"
             << "Choice: ";

        cin >> choice;

        switch (choice) {
            case 1: 
                displayInbox(inbox); 
                break;
            case 2: 
                readEmail(inbox);    
                break;
            case 3: 
                deleteEmail(inbox);  
                break;
            case 4:
                inbox.push(server.getNewEmail());
                break;
            case 5:
                sortEmails(inbox);
                break;
        }

    } while (choice != 6);

    cout << "Goodbye!\n";
    return 0;
}
