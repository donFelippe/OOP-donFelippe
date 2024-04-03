#ifndef A45_DONFELIPPE_DATABASE_H
#define A45_DONFELIPPE_DATABASE_H

#include <string>
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <QString>

struct Time {
    int hours;
    int minutes;
    int seconds;

    std::string toString() const {
        return std::to_string(hours)+"h, "+std::to_string(minutes)+"m, "+std::to_string(seconds)+"s ";
    }
};

struct Components {
    std::string title;
    std::string presenter;
    Time duration;
    int likes;
    std::string link;

    Components() : likes(0) {
    }

    std::string toString() const {
        std::string result;
        result += "Title: " + title + "\n";
        result += "Presenter: " + presenter + "\n";
        result += "Duration: " + std::to_string(duration.hours) + "h "
                  + std::to_string(duration.minutes) + "m "
                  + std::to_string(duration.seconds) + "s" + "\n";
        result += "Likes: " + std::to_string(likes) + "\n";
        result += "Link: " + link + "\n";

        return result;
    }
    friend std::ostream &operator<<(std::ostream &os, const Components &component) {
        os << component.title << '\n'
           << component.presenter << '\n'
           << component.duration.hours << ' ' << component.duration.minutes << ' ' << component.duration.seconds << '\n'
           << component.likes << '\n'
           << component.link << '\n';
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Components &component) {
        std::getline(is, component.title);
        std::cin.clear();
        std::getline(is, component.presenter);
        is >> component.duration.hours >> component.duration.minutes >> component.duration.seconds;
        is >> component.likes;
        std::getline(is >> std::ws, component.link);
        return is;
    }

    void setTitle(const std::string &newTitle) {
        title = newTitle;
    }

    void setPresenter(const std::string &newPresenter) {
        presenter = newPresenter;
    }

    void setDuration(const Time &newDuration) {
        duration = newDuration;
    }

    void setLikes(int newLikes) {
        likes = newLikes;
    }

    void setLink(const std::string &newLink) {
        link = newLink;
    }

    const std::string &getTitle() const {
        return title;
    }

    const std::string &getPresenter() const {
        return presenter;
    }

    const Time &getDuration() const {
        return duration;
    }

    int getLikes() const {
        return likes;
    }

    const std::string &getLink() const {
        return link;
    }

    void openYoutubeLink() {
        QString qLink = QString::fromStdString(link);
        std::wstring wLink = qLink.toStdWString();
        ShellExecute(NULL, L"open", wLink.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
    void print() {
        std::cout << "[ " << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Presenter: " << presenter << std::endl;
        std::cout << "Duration: " << duration.hours << "h " << duration.minutes << "m " << duration.seconds << "s"
                  << std::endl;
        std::cout << "Likes: " << likes << std::endl;
        std::cout << "Link: " << link << std::endl;
        std::cout << "]\n";
    }

    void read(std::ifstream& file) {
        std::string line;
        int lineCount = 0;

        while (std::getline(file, line)) {
            switch (lineCount % 5) {
                case 0:
                    title = line;
                    break;
                case 1:
                    presenter = line;
                    break;
                case 2: {
                    std::istringstream iss(line);
                    int hours, minutes, seconds;
                    iss >> hours >> minutes >> seconds;
                    duration = { hours, minutes, seconds };
                    break;
                }
                case 3: {
                    std::istringstream iss(line);
                    iss >> likes;
                    break;
                }
                case 4:
                    link = line;
                    break;
            }

            lineCount++;
        }
    }
};

#endif // A45_DONFELIPPE_DATABASE_H
