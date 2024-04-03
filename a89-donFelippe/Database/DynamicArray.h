#include <iostream>
#include <vector>
#include "Database.h"

class DynamicVector : public std::vector<Components> {
public:
    void print() {
        std::cout << "[ ";
        for (int i = 0; i < size(); i++) {
            std::cout << i << '\n';
            std::cout << "Title: " << at(i).getTitle() << std::endl;
            std::cout << "Presenter: " << at(i).getPresenter() << std::endl;
            std::cout << "Duration: " << at(i).getDuration().hours << "h " << at(i).getDuration().minutes << "m " << at(i).getDuration().seconds << "s" << std::endl;
            std::cout << "Likes: " << at(i).getLikes() << std::endl;
            std::cout << "Link: " << at(i).getLink() << std::endl;
        }
        std::cout << "]\n";
    }

    void readDatabaseFromFile(const std::string& filename, std::vector<Components>& database) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Error: Failed to open database file.");
        }

        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                std::istringstream iss(line);
                std::string token;
                std::vector<std::string> tokens;

                while (std::getline(iss, token, ',')) {
                    tokens.push_back(token);
                }

                if (tokens.size() != 7) {
                    throw std::runtime_error("Error: Invalid component format in file: " + filename);
                }

                Components component;
                component.setTitle(tokens[0]);
                component.setPresenter(tokens[1]);

                // Parse duration
                int hours = std::stoi(tokens[2]);
                int minutes = std::stoi(tokens[3]);
                int seconds = std::stoi(tokens[4]);
                component.setDuration({hours, minutes, seconds});

                // Parse likes
                int likes = std::stoi(tokens[5]);
                component.setLikes(likes);

                component.setLink(tokens[6]);
                database.push_back(component);
            }
        }

        file.close();
    }
    void writeDatabaseToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Error: Failed to open file." << std::endl;
            return;
        }

        for (int i = 0; i < size(); i++) {
            const Components& component = (*this)[i];
            file << component.title << ','
                 << component.presenter << ','
                 << component.duration.hours << ','
                 << component.duration.minutes << ','
                 << component.duration.seconds << ','
                 << component.likes << ','
                 << component.link << '\n';
        }

        file.close();
    }

    void writeDatabaseToCSV(const DynamicVector& database, const std::string& filename) {
        std::ofstream file(filename, std::ios::trunc);

        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        for (int i = 0; i < database.size(); ++i) {
            const Components& component = database[i];
            file << component.getPresenter() << ",";
            file << component.getTitle() << ",";
            file << component.getDuration().toString() << ",";
            file << component.getLink() << "\n";
        }

        file.flush();  // Flush the buffer to ensure data is written
        file.close();
    }

    void writeDatabaseToHTML(const DynamicVector& database, const std::string& filename) {
        std::ofstream file(filename, std::ios::trunc);

        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        file << "<!DOCTYPE html>\n";
        file << "<html>\n";
        file << "<head>\n";
        file << "<title>Playlist</title>\n";
        file << "</head>\n";
        file << "<body>\n";
        file << "<table border=\"1\">\n";
        file << "<tr>\n";
        file << "<td>Artist</td>\n";
        file << "<td>Title</td>\n";
        file << "<td>Duration</td>\n";
        file << "<td>Youtube link</td>\n";
        file << "</tr>\n";

        for (int i = 0; i < database.size(); ++i) {
            const Components& component = database[i];
            file << "<tr>\n";
            file << "<td>" << component.getPresenter() << "</td>\n";
            file << "<td>" << component.getTitle() << "</td>\n";
            file << "<td>" << component.getDuration().toString() << "</td>\n";
            file << "<td><a href=\"" << component.getLink() << "\">Link</a></td>\n";
            file << "</tr>\n";
        }

        file << "</table>\n";
        file << "</body>\n";
        file << "</html>\n";

        file.flush();  // Flush the buffer to ensure data is written
        file.close();
    }

};