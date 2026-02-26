#include "email_server.h"
#include "json.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using json = nlohmann::json;
using namespace std;

// Date method implementations

Date::Date(const string& s) {
    // expects "YYYY-MM-DD"
    sscanf(s.c_str(), "%d-%d-%d", &year, &month, &day);
}

string Date::toString() const {
    ostringstream oss;
    oss << year << '-'
        << setfill('0') << setw(2) << month << '-'
        << setfill('0') << setw(2) << day;
    return oss.str();
}

int Date::toInt() const {
    return year * 10000 + month * 100 + day;
}

// Email method implementations

Email::Email(const string& sender, const string& subject,
             const string& body,   const string& date, bool read)
    : sender(sender), subject(subject), body(body), date(date), read(read) {}

string Email::getSender()  const { return sender; }
string Email::getSubject() const { return subject; }
string Email::getBody()    const { return body; }
Date   Email::getDate()    const { return date; }
bool   Email::isRead()     const { return read; }
void   Email::markRead()         { read = true; }

// EmailServer method implementations

EmailServer::EmailServer(const string& dataFile) {
    srand(static_cast<unsigned int>(time(nullptr)));

    ifstream file(dataFile);
    if (!file.is_open()) {
        cout << "[EmailServer] Warning: Cannot open \"" << dataFile << "\". No emails loaded.\n";
        return;
    }

    json data = json::parse(file);
    file.close();

    for (const auto& obj : data)
        emails.push_back(Email(obj["sender"], obj["subject"], obj["body"], obj["date"], obj["read"]));
}

Email EmailServer::getNewEmail() {
    if (emails.empty())
        return Email("server@no-reply.com", "(no emails)", "", "", false);
    int index = rand() % static_cast<int>(emails.size());
    return emails[index];
}

int EmailServer::totalEmails() const {
    return static_cast<int>(emails.size());
}
