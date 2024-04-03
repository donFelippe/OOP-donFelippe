#include "Database/DynamicArray.h"
#include <iostream>
#include "Database/Database.h"
#include <vector>
#include <string>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QTableWidgetItem>
#include <QDialogButtonBox>

bool isAdminMode = true;
DynamicVector database;
DynamicVector watchlist;

void openHTMLFileInBrowser(const std::string &filename) {
    std::string command = "start " + filename;
    std::system(command.c_str());
}

std::vector<int> splitIntoIntegers(const std::string &str) {
    std::istringstream iss(str);
    std::vector<int> integers{std::istream_iterator<int>(iss), {}};
    return integers;
}

void writeDatabaseToFile(const std::string &filename, const DynamicVector &database) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < database.size(); ++i) {
            file << database[i];
        }
        file.close();
        std::cout << "Database written to file: " << filename << std::endl;
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

class AdminModeWindow : public QMainWindow {
Q_OBJECT

public:
    AdminModeWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        QWidget *mainWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(mainWidget);

        QPushButton *addButton = new QPushButton("Add Tutorial");
        QPushButton *viewButton = new QPushButton("View Database");
        QPushButton *modifyButton = new QPushButton("Modify Tutorial");
        QPushButton *writeButton = new QPushButton("Write to HTML File");
        QPushButton *exitButton = new QPushButton("Exit");

        layout->addWidget(addButton);
        layout->addWidget(viewButton);
        layout->addWidget(modifyButton);
        layout->addWidget(writeButton);
        layout->addWidget(exitButton);

        mainWidget->setLayout(layout);

        setCentralWidget(mainWidget);

        database.readDatabaseFromFile("database.csv", database);

        connect(addButton, &QPushButton::clicked, this, &AdminModeWindow::onAddButtonClicked);
        connect(viewButton, &QPushButton::clicked, this, &AdminModeWindow::onViewButtonClicked);
        connect(modifyButton, &QPushButton::clicked, this, &AdminModeWindow::onModifyButtonClicked);
        connect(writeButton, &QPushButton::clicked, this, &AdminModeWindow::onWriteButtonClicked);
        connect(exitButton, &QPushButton::clicked, this, &AdminModeWindow::onExitButtonClicked);
    }

private slots:

    void onAddButtonClicked() {
        QDialog dialog(this);
        dialog.setWindowTitle("Add Tutorial");

        QLabel *titleLabel = new QLabel("Title:");
        QLineEdit *titleLineEdit = new QLineEdit();
        QLabel *presenterLabel = new QLabel("Presenter:");
        QLineEdit *presenterLineEdit = new QLineEdit();
        QLabel *durationLabel = new QLabel("Duration:");
        QLineEdit *durationLineEdit = new QLineEdit();
        QLabel *likesLabel = new QLabel("Likes:");
        QLineEdit *likesLineEdit = new QLineEdit();
        QLabel *linkLabel = new QLabel("Link:");
        QLineEdit *linkLineEdit = new QLineEdit();

        QPushButton *addTutorialButton = new QPushButton("Add Tutorial");

        QVBoxLayout *layout = new QVBoxLayout(&dialog);
        layout->addWidget(titleLabel);
        layout->addWidget(titleLineEdit);
        layout->addWidget(presenterLabel);
        layout->addWidget(presenterLineEdit);
        layout->addWidget(durationLabel);
        layout->addWidget(durationLineEdit);
        layout->addWidget(likesLabel);
        layout->addWidget(likesLineEdit);
        layout->addWidget(linkLabel);
        layout->addWidget(linkLineEdit);
        layout->addWidget(addTutorialButton);
        dialog.setLayout(layout);

        connect(addTutorialButton, &QPushButton::clicked, [this, &dialog, titleLineEdit, presenterLineEdit,
                durationLineEdit, likesLineEdit, linkLineEdit]() {
            QString title = titleLineEdit->text();
            QString presenter = presenterLineEdit->text();
            QString duration = durationLineEdit->text();
            Time durationtime;
            std::vector<int> durationnn = splitIntoIntegers(duration.toStdString());
            durationtime.hours = durationnn[0];
            durationtime.minutes = durationnn[1];
            durationtime.seconds = durationnn[2];
            int likes = likesLineEdit->text().toInt();
            QString link = linkLineEdit->text();
            Components c;
            c.setTitle(title.toStdString());
            c.setDuration(durationtime);
            c.setLikes(likes);
            c.setLink(link.toStdString());
            c.setPresenter(presenter.toStdString());
            database.push_back(c);
            QMessageBox::information(this, "Tutorial Added",
                                     QString("Title: %1\nPresenter: %2\nDuration: %3\nLikes: %4\nLink: %5")
                                             .arg(title, presenter, duration, QString::number(likes), link));
            database.writeDatabaseToFile("database.csv");
            dialog.accept();
        });
        
        dialog.exec();
    }

    void onViewButtonClicked() {
        QDialog dialog(this);
        dialog.setWindowTitle("View Database");

        QTableWidget *tableWidget = new QTableWidget(&dialog);
        tableWidget->setRowCount(database.size());
        tableWidget->setColumnCount(5);

        QStringList headers;
        headers << "Title" << "Presenter" << "Duration" << "Likes" << "Link";
        tableWidget->setHorizontalHeaderLabels(headers);

        for (int i = 0; i < database.size(); ++i) {
            const Components &component = database[i];

            QTableWidgetItem *titleItem = new QTableWidgetItem(QString::fromStdString(component.getTitle()));
            tableWidget->setItem(i, 0, titleItem);

            QTableWidgetItem *presenterItem = new QTableWidgetItem(QString::fromStdString(component.getPresenter()));
            tableWidget->setItem(i, 1, presenterItem);

            QString durationStr = QString("%1:%2:%3")
                    .arg(component.getDuration().hours, 2, 10, QLatin1Char('0'))
                    .arg(component.getDuration().minutes, 2, 10, QLatin1Char('0'))
                    .arg(component.getDuration().seconds, 2, 10, QLatin1Char('0'));
            QTableWidgetItem *durationItem = new QTableWidgetItem(durationStr);
            tableWidget->setItem(i, 2, durationItem);

            QTableWidgetItem *likesItem = new QTableWidgetItem(QString::number(component.getLikes()));
            tableWidget->setItem(i, 3, likesItem);

            QTableWidgetItem *linkItem = new QTableWidgetItem(QString::fromStdString(component.getLink()));
            tableWidget->setItem(i, 4, linkItem);
        }

        QVBoxLayout *layout = new QVBoxLayout(&dialog);
        layout->addWidget(tableWidget);
        dialog.setLayout(layout);

        dialog.exec();
    }


    void onModifyButtonClicked() {
        QDialog dialog(this);
        dialog.setWindowTitle("Modify Tutorial");

        QTableWidget *tableWidget = new QTableWidget();
        tableWidget->setColumnCount(5);
        tableWidget->setHorizontalHeaderLabels(
                QStringList() << "Title" << "Presenter" << "Duration" << "Likes" << "Link");
        tableWidget->setRowCount(database.size());

        for (int i = 0; i < database.size(); ++i) {
            const Components &component = database[i];

            QTableWidgetItem *titleItem = new QTableWidgetItem(QString::fromStdString(component.title));
            QTableWidgetItem *presenterItem = new QTableWidgetItem(QString::fromStdString(component.presenter));
            QTableWidgetItem *durationItem = new QTableWidgetItem(
                    QString("%1:%2:%3").arg(component.duration.hours).arg(component.duration.minutes).arg(
                            component.duration.seconds)
            );
            QTableWidgetItem *likesItem = new QTableWidgetItem(QString::number(component.likes));
            QTableWidgetItem *linkItem = new QTableWidgetItem(QString::fromStdString(component.link));

            tableWidget->setItem(i, 0, titleItem);
            tableWidget->setItem(i, 1, presenterItem);
            tableWidget->setItem(i, 2, durationItem);
            tableWidget->setItem(i, 3, likesItem);
            tableWidget->setItem(i, 4, linkItem);
        }

        QVBoxLayout *layout = new QVBoxLayout(&dialog);
        layout->addWidget(tableWidget);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        dialog.setLayout(layout);

        if (dialog.exec() == QDialog::Accepted) {
            for (int i = 0; i < database.size(); ++i) {
                Components &component = database[i];

                QTableWidgetItem *titleItem = tableWidget->item(i, 0);
                QTableWidgetItem *presenterItem = tableWidget->item(i, 1);
                QTableWidgetItem *durationItem = tableWidget->item(i, 2);
                QTableWidgetItem *likesItem = tableWidget->item(i, 3);
                QTableWidgetItem *linkItem = tableWidget->item(i, 4);
                if (titleItem->text().isEmpty()) {
                    database.erase(database.begin() + i);
                    --i;
                    continue;
                }

                if (titleItem)
                    component.title = titleItem->text().toStdString();


                if (presenterItem)
                    component.presenter = presenterItem->text().toStdString();

                if (durationItem) {
                    QStringList durationParts = durationItem->text().split(":");
                    if (durationParts.size() == 3) {
                        component.duration.hours = durationParts[0].toInt();
                        component.duration.minutes = durationParts[1].toInt();
                        component.duration.seconds = durationParts[2].toInt();
                    }
                }

                if (likesItem)
                    component.likes = likesItem->text().toInt();

                if (linkItem)
                    component.link = linkItem->text().toStdString();
            }

            database.writeDatabaseToFile("database.csv");
            QMessageBox::information(this, "Modification", "Database modified successfully!");
        }
    }

    void onWriteButtonClicked() {
        database.writeDatabaseToHTML(database, "htmldatabase.html");
        openHTMLFileInBrowser("D:\\UBB\\a89-donFelippe\\cmake-build-debug\\htmldatabase.html");
        QMessageBox::information(this, "HTML", "Database stored!");
    }

    void onExitButtonClicked() {
        close();
    }
};

int mainuser(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AdminModeWindow adminModeWindow;
    adminModeWindow.show();

    return app.exec();
}


class UserModeWindow : public QMainWindow {
Q_OBJECT

public:
    UserModeWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        createMenu();
    }

private slots:

    void onSeeTutorialsClicked() {
        QString presenter = QInputDialog::getText(this, "Enter Presenter", "Enter the name of the presenter:");

        auto it = database.begin();

        while (it != database.end()) {
            const Components &tutorial = *it;
            if (QString::fromStdString(tutorial.getPresenter()) == presenter) {
                QMessageBox msgBox;
                msgBox.setText(tutorial.toString().c_str());
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::Yes);
                int choice = msgBox.exec();
                it->openYoutubeLink();
                if (choice == QMessageBox::Yes) {
                    watchlist.push_back(tutorial);
                }
                ++it;
                continue;
            }

            ++it;
        }
        QString watchlistText;
        for (auto it = watchlist.begin(); it != watchlist.end(); ++it) {
            Components tutorial = *it;
            watchlistText.append(QString::fromStdString(tutorial.toString()) + "\n\n");
        }

        QMessageBox::information(this, "Watchlist", watchlistText);

    }

    void onShowWatchlistClicked() {
        QString watchlistText;
        for (auto it = watchlist.begin(); it != watchlist.end(); ++it) {
            Components tutorial = *it;
            watchlistText.append(QString::fromStdString(tutorial.toString()) + "\n\n");
        }

        QMessageBox::information(this, "Watchlist", watchlistText);

        for (auto it = watchlist.begin(); it != watchlist.end(); ++it) {
            it->openYoutubeLink();
            QMessageBox likes;
            likes.setText(QString::fromStdString(it->toString()) + "Do you want to like the video?");
            likes.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            int choice = likes.exec();

            if (choice == QMessageBox::Yes) {
                for (auto adm = database.begin(); adm != database.end(); ++adm) {
                    if (adm == it)
                        adm->likes++;
                }
            }
            watchlist.erase(it);
        }
    }

    void onExitClicked() {
        QApplication::quit();

    }

private:
    void createMenu() {
        QMenu *optionsMenu = menuBar()->addMenu("Options");

        QAction *seeTutorialsAction = new QAction("See Tutorials", this);
        connect(seeTutorialsAction, &QAction::triggered, this, &UserModeWindow::onSeeTutorialsClicked);
        optionsMenu->addAction(seeTutorialsAction);

        QAction *showWatchlistAction = new QAction("Show Watchlist", this);
        connect(showWatchlistAction, &QAction::triggered, this, &UserModeWindow::onShowWatchlistClicked);
        optionsMenu->addAction(showWatchlistAction);

        QAction *exitAction = new QAction("Exit", this);
        connect(exitAction, &QAction::triggered, this, &UserModeWindow::onExitClicked);
        optionsMenu->addAction(exitAction);
    }
};

int mainadmin(int argc, char *argv[]) {
    QApplication app(argc, argv);

    UserModeWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    UserModeWindow windowu;
    AdminModeWindow window;
    window.show();
    windowu.show();
    return app.exec();
}