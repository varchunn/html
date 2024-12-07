#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
using namespace std;

bool validateHTML(const char* filePath) 
{
    ifstream file(filePath);
    if (!file) {
        cout << "Помилка: файл не знайдено." << endl;
        return false;
    }
    char line[256];
    char tags[100][50];
    int tagIndex = 0;
    while (file.getline(line, 256))
    {
        char* pos = strstr(line, "<");
        while (pos != NULL) {
            char* end = strstr(pos, ">");
            if (!end) {
                cout << "Помилка: Незакритий '<' знайдено." << endl;
                return false;
            }
            char tag[50];
            strncpy(tag, pos + 1, end - pos - 1);
            tag[end - pos - 1] = '\0';

            if (tag[0] != '/') 
            {
                strcpy(tags[tagIndex++], tag);
            }
            else
            {
                if (tagIndex == 0 || strcmp(tags[tagIndex - 1], tag + 1) != 0)
                {
                    cout << "Помилка: Невідповідний закритий тег </" << tag + 1 << ">." << endl;
                    return false;
                }
                tagIndex--;
            }

            pos = strstr(end + 1, "<");
        }
    }

    if (tagIndex != 0)
    {
        cout << "Помилка: Незакритий тег <" << tags[tagIndex - 1] << ">." << endl;
        return false;
    }

    file.close();
    return true;
}

int main() 
{
    char filePath[100];
    cout << "Введіть шлях до HTML-файлу: ";
    cin.getline(filePath, 100);

    if (validateHTML(filePath)) 
    {
        cout << "HTML файл є валідним." << endl;
    }
    else
    {
        cout << "HTML файл не є валідним." << endl;
    }
    cout << "Натисніть будь-яку клавішу для виходу...";
    return 0;
}
