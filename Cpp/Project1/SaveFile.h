#ifndef LOGSOURCECODE_H
#define LOGSOURCECODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

// ���� �ð��� ���ڿ��� ��ȯ
inline std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    struct tm timeInfo;

    // localtime_s ��� (���� ��ȭ)
    localtime_s(&timeInfo, &now);

    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeInfo);
    return std::string(buf);
}

// ���� ��ο��� ���ϸ� ����
inline std::string extractFileName(const std::string& filePath) {
    size_t lastSlashIndex = filePath.find_last_of("\\/");
    if (lastSlashIndex != std::string::npos) {
        return filePath.substr(lastSlashIndex + 1); // ��� ���� ���ϸ� ����
    }
    return filePath; // ��ΰ� ���� ��� �״�� ��ȯ
}

// ���� �̸����� Ȯ���� ����
inline std::string removeExtension(const std::string& fileName) {
    size_t lastDotIndex = fileName.find_last_of('.');
    if (lastDotIndex != std::string::npos) {
        return fileName.substr(0, lastDotIndex); // Ȯ���� ����
    }
    return fileName; // Ȯ���ڰ� ���� ��� �״�� ��ȯ
}

// ������� �ҽ��ڵ� ������ �޸��忡 ���
inline void logSourceCode(const std::string& sourceFilePath) {
    // �ҽ� ���ϸ� ���� �� Ȯ���� ����
    std::string fileName = extractFileName(sourceFilePath);
    std::string baseName = removeExtension(fileName);

    // �α� ���� ��� ���� (Ȯ���ڸ� ������ ���ϸ� + .txt)
    std::string logFilePath = baseName + ".txt";

    // �ҽ� ���� ����
    std::ifstream sourceFile(sourceFilePath);
    if (!sourceFile.is_open()) {
        std::cerr << "�ҽ� ������ �� �� �����ϴ�: " << sourceFilePath << std::endl;
        return;
    }

    // �α� ���� ����
    std::ofstream logFile(logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "�α� ������ �� �� �����ϴ�: " << logFilePath << std::endl;
        return;
    }

    // Ÿ�ӽ������� ���ϸ� ���
    logFile << "=== Debugged: " << sourceFilePath << " ===" << std::endl;
    logFile << "=== Timestamp: " << getCurrentTime() << " ===" << std::endl;

    // �ҽ� ���� ���� ���
    std::string line;
    while (std::getline(sourceFile, line)) {
        logFile << line << std::endl;
    }

    logFile << std::endl;
    std::cout << "�ҽ��ڵ尡 �α� ���Ͽ� ��ϵǾ����ϴ�: " << logFilePath << std::endl;
}

#endif // LOGSOURCECODE_H