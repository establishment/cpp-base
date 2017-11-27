#ifndef CPP_BASE_OS_HPP
#define CPP_BASE_OS_HPP

#include <sys/stat.h>

#include <string>

#include "utils.hpp"


namespace Base {
int DirExists(const std::string& path);

int PathBeginsWith(const std::string& path, const std::string& with);

void MakeDir(const std::string& s_path, int mode = 0777);

void Touch(std::string path);

void RMTree(const char* path);

void ChownTree(const char* path, uid_t uid, gid_t gid);

void RChmod(const std::string& command);

void Chmod(const std::string& command);

void Setfacl(const std::string& command);

}  // namespace Base

#endif // CPP_BASE_OS_HPP
