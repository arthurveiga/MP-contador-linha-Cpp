/**
 * @brief 
 * 
 * @file contador_linha.cpp
 * @author Arthur da Veiga Feitoza Borges - 13/0050725
 * @date 2018-09-19
 */
#include "../include/contador_linha.hpp"

/**
 * @brief abre_arquivo: 
 * 
 * @param file 
 * @param file_name 
 * @return int 
 */
int abre_arquivo (std::filebuf * file, std::string file_name) {
    if (file_name == "") {
        return -1;
    } else {
        file->std::filebuf::open(file_name, std::fstream::in);
        if (file->is_open()) {
            return 0;
        }
        return -1;
    }
}

/**
 * @brief 
 * 
 * @param fileString 
 * @return std::pair <int, int> 
 */
std::pair <int, int> count_linhas (std::string fileString) {
    // int count = 0;
    // return std::make_pair(0, count);
}

/**
 * @brief 
 * 
 * @param file 
 * @return std::pair <int, int> 
 */
std::pair <int, int> le_arquivo_to_string_count (std::filebuf * file) {
    int count = 0;
    std::stringstream fileInput ("");
    if (file == NULL) {
        return std::make_pair(-1, count);
    }
    if (file->is_open()) {
        fileInput << file;
        std::string fileString;
        fileString.assign(fileInput.str());
        count = count_linhas(fileString).second;
        return std::make_pair(0, count);
    }
    return std::make_pair(-1, count); 
}
