// FactoryMethod(task1).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SearchFileInfo.h"
#include <codecvt>
#include <windows.h>

namespace fs = std::filesystem;

class IReportFormat {
public:
    virtual void createReport(const std::vector<FileInfo>& files) = 0;
    virtual ~IReportFormat() {}
};


class TxtReportFormat : public IReportFormat {
public:
    void createReport(const std::vector<FileInfo>& files) override {
        // ����� ������ � ���� Txt
        std::ofstream file("report.txt");
        if (file.is_open()) {
            for (const auto& fileInfo : files) {
                file << "�����: " << fileInfo.name << "\n";
                file << "����������: " << fileInfo.type << "\n";
                file << "�����: " << fileInfo.size << "\n";
                file << "�����������: " << fileInfo.modified;
                file << "\n\n";
            }
            file.close();
            std::cout << "���� txt ������ ���������\n";
        }
        else {
            std::cout << "�� ������� �������� ���� txt\n";
        }
    }
};

class CsvReportFormat : public IReportFormat {
public:
    void createReport(const std::vector<FileInfo>& files) override {
        // ����� ������ � ���� csv
        std::ofstream file("report.csv");
        if (file.is_open()) {
            file << "�����,����������,�����,�����������\n";
            for (const auto& fileInfo : files) {
                file << fileInfo.name << ",";
                file << fileInfo.type << ",";
                file << fileInfo.size << ",";
                file << fileInfo.modified;
                file << "\n";
            }
            file.close();
            std::cout << "���� csv ������ ���������\n";
        }
        else {
            std::cout << "��������� �������� ���� ssv\n";
        }
    }
};

class ReportFactory {
public:
    static IReportFormat* createReportFormat(const std::string& format) {
        try {
            if (format == "txt") {
                return new TxtReportFormat();
            }
            else if (format == "csv") {
                return new CsvReportFormat();
            }
            throw std::runtime_error("�� ���� ���������� �����");
        }
        catch (const std::runtime_error& e)
        {
            std::cout << "�������: " << e.what() << std::endl;
            return nullptr;
        }
    }
};


int main()
{
    std::locale::global(std::locale(""));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SearchFileInfo f;

    std::string path;

    std::cout << "������ ���� �� �������� (�:/path/): ";

    std::getline(std::cin, path);

    std::cout << path << std::endl;

    try {
        f.parth_informations(path);

        std::unique_ptr<IReportFormat> reportFormat_txt(ReportFactory::createReportFormat("txt"));
        if (reportFormat_txt)
            reportFormat_txt->createReport(f.all_files_info);
        std::unique_ptr<IReportFormat> reportFormat_csv(ReportFactory::createReportFormat("csv"));
        if (reportFormat_csv)
            reportFormat_csv->createReport(f.all_files_info);
    }
    catch (const std::exception& e) {
        std::cout << "������� � ����� �� ��������:  " << e.what() << std::endl;
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
