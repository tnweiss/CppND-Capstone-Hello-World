#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <memory>

std::string trimEdges(std::string);

std::vector<std::shared_ptr<std::string>> splitSharedPtr(std::string, char);

std::vector<std::string> splitRValue(std::string, char);

std::vector<std::string> parseWhere(std::string, char delim);

std::vector<std::string> listFilesInDirectory(std::string);
#endif