/**
 * nxpinhum5326/pmmoBuilder alpha
 */

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

class pmmpBuilder {

public:

    void createProject(const std::string& destinationPath, const std::string& projectName, const std::string& namespaceName) {
        fs::create_directory(destinationPath + "/" + projectName);
        fs::create_directory(destinationPath + "/" + projectName + "/src");
        std::string srcPath = destinationPath + "/" + projectName + "/src";
        createNamespace(srcPath, namespaceName);

        //main.php içeriği/content
        std::string mainFileContent = R"(<?php

namespace )" + namespaceName + R"(;

use pocketmine\plugin\PluginBase;

class Main extends PluginBase {

}
)";
        createFile(srcPath + "/" + namespaceName, "Main.php", mainFileContent);

        //plugin.yml içeriği/content
        std::string yamlFileContent = R"(name: )" + projectName + R"(
version: 1.0.0
api: 5.0.0
author: )" + namespaceName + R"(
main: )" + namespaceName + R"(\Main
)";
        createFile(destinationPath + "/" + projectName, "plugin.yml", yamlFileContent);
    }

private:

    void createNamespace(const std::string& path, const std::string& namespaceName) {
        fs::create_directory(path + "/" + namespaceName);
    }
    void createFile(const std::string& path, const std::string& filename, const std::string& content) {
        std::ofstream file(path + "/" + filename);
        file << content;
        file.close();
    }
};

int main() {

    pmmpBuilder builder;

    //şimdilik bu kadar basit bir kullanım :c
    std::string prefix = "pmmpBuilder ALPHA > ";

    std::string destination;
    std::string projectName;
    std::string namespaceName;

    std::cout << prefix << "Where the project will be created(destination path): ";
    std::getline(std::cin, destination);

    std::cout << prefix << "Project/Plugin name: ";
    std::getline(std::cin, projectName);

    std::cout << prefix << "Namespace/Author(for now) name: ";
    std::getline(std::cin, namespaceName);

    builder.createProject(destination, projectName, namespaceName);

    std::cout << "pmmpBuilder > Plugin basement created." << std::endl;

    return 0;
}
