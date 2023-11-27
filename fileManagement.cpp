#include <bits/stdc++.h>
using namespace std;

class FileManager {
public:
    void createFile(const std::string& filename) {
        std::ofstream file(filename);
        file.close();
        std::cout << "File created: " << filename << "\n";
    }

    void writeFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename, std::ios::app); // Open for append
        file << content;
        file.close();
        std::cout << "Content written to file: " << filename << "\n";
    }

    std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        std::cout << "Content read from file: " << filename << "\n";
        return content;
    }

    void deleteFile(const std::string& filename) {
        if (remove(filename.c_str()) == 0) {
            std::cout << "File deleted: " << filename << "\n";
        } else {
            std::cerr << "Error deleting file: " << filename << "\n";
        }
    }
};

int main() {
    FileManager fileManager;
    fileManager.createFile("example.txt");
    fileManager.writeFile("example.txt", "Hello, File Management System!\n");
    std::string content = fileManager.readFile("example.txt");
    std::cout << "File Content:\n" << content;
    fileManager.deleteFile("example.txt");

    return 0;
}
