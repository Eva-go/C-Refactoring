#ifndef LOGSOURCECODE_H
#define LOGSOURCECODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

// 현재 시간을 문자열로 반환
inline std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    struct tm timeInfo;

    // localtime_s 사용 (보안 강화)
    localtime_s(&timeInfo, &now);

    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeInfo);
    return std::string(buf);
}

// 파일 경로에서 파일명만 추출
inline std::string extractFileName(const std::string& filePath) {
    size_t lastSlashIndex = filePath.find_last_of("\\/");
    if (lastSlashIndex != std::string::npos) {
        return filePath.substr(lastSlashIndex + 1); // 경로 없이 파일명만 추출
    }
    return filePath; // 경로가 없는 경우 그대로 반환
}

// 파일 이름에서 확장자 제거
inline std::string removeExtension(const std::string& fileName) {
    size_t lastDotIndex = fileName.find_last_of('.');
    if (lastDotIndex != std::string::npos) {
        return fileName.substr(0, lastDotIndex); // 확장자 제거
    }
    return fileName; // 확장자가 없는 경우 그대로 반환
}

// 디버깅한 소스코드 정보를 메모장에 기록
inline void logSourceCode(const std::string& sourceFilePath) {
    // 소스 파일명 추출 및 확장자 제거
    std::string fileName = extractFileName(sourceFilePath);
    std::string baseName = removeExtension(fileName);

    // 로그 파일 경로 생성 (확장자를 제거한 파일명 + .txt)
    std::string logFilePath = baseName + ".txt";

    // 소스 파일 열기
    std::ifstream sourceFile(sourceFilePath);
    if (!sourceFile.is_open()) {
        std::cerr << "소스 파일을 열 수 없습니다: " << sourceFilePath << std::endl;
        return;
    }

    // 로그 파일 열기
    std::ofstream logFile(logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "로그 파일을 열 수 없습니다: " << logFilePath << std::endl;
        return;
    }

    // 타임스탬프와 파일명 기록
    logFile << "=== Debugged: " << sourceFilePath << " ===" << std::endl;
    logFile << "=== Timestamp: " << getCurrentTime() << " ===" << std::endl;

    // 소스 파일 내용 기록
    std::string line;
    while (std::getline(sourceFile, line)) {
        logFile << line << std::endl;
    }

    logFile << std::endl;
    std::cout << "소스코드가 로그 파일에 기록되었습니다: " << logFilePath << std::endl;
}

#endif // LOGSOURCECODE_H