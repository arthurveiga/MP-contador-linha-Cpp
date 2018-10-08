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

std::pair<int, int> le_arquivo (std::filebuf * file) {

}
