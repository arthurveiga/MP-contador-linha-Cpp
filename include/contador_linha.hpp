/**
 * @file contador_linha.hpp
 * @author Arthur da Veiga Feitoza Borges - 13/0050725 (https://github.com/arthurveiga)
 * @brief 
 * @version 0.2.1
 * @date 2018-10-11
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef INCLUDE_CONTADOR_LINHA_HPP_
#define INCLUDE_CONTADOR_LINHA_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>

/**
 * @brief 
 * 
 */
enum STATE {
    init,
    espaco,
    barra,
    barra_dupla,
    barra_invertida,
    barra_asterisco,
    barra_asterisco_asterisco,
    barra_asterisco_asterisco_barra
};

/**
 * @brief 
 * 
 * @param file 
 * @param file_name 
 * @return int 
 */
int abre_arquivo(std::filebuf *file, std::string file_name);

/**
 * @brief 
 * 
 * @param fileString 
 * @return std::pair <int, int> 
 */
std::pair <int, int> count_linhas(std::string fileString);

/**
 * @brief 
 * 
 * @param file_name 
 * @return std::pair <int, int> 
 */
std::pair <int, int> le_arquivo_to_string_count(std::string file_name);

/**
 * @brief 
 * 
 * @param file 
 * @return int 
 */
int fecha_arquivo(std::filebuf *file);

#endif  // INCLUDE_CONTADOR_LINHA_HPP_
