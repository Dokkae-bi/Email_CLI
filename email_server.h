#pragma once
#include <string>
#include <vector>

struct Date {
    int year  = 0;
    int month = 0;
    int day   = 0;

    Date() = default;
    Date(const std::string& s);   // expects "YYYY-MM-DD"

    std::string toString() const; // returns "YYYY-MM-DD"
    int         toInt()    const; // returns YYYYMMDD as a single comparable integer
};

class Email {
public:
    Email() {
        sender  = "";
        subject = "";
        body    = "";
        date    = Date();
        read    = false;
    }
    
    Email(const std::string& sender, const std::string& subject,
          const std::string& body,   const std::string& date, bool read = false);

    std::string getSender()  const;
    std::string getSubject() const;
    std::string getBody()    const;
    Date        getDate()    const;
    bool        isRead()     const;
    void        markRead();

private:
    std::string sender;
    std::string subject;
    std::string body;
    Date        date;
    bool        read;
};

class EmailServer {
public:
    EmailServer(const std::string& dataFile = "emails.json");

    Email getNewEmail();
    int   totalEmails() const;

private:
    std::vector<Email> emails;
};
