/**
 * @brief 
 * 
 * @file checklist.hpp
 * @author Arthur da Veiga Feitoza Borges - 13/0050725
 * @date 2018-09-19
 */

#ifndef _HOME_ARTHORIUS_DOCUMENTS_UNB_MP_TRABALHOS_TRAB1_INCLUDE_CONTADOR_LINHA_HPP_
#define _HOME_ARTHORIUS_DOCUMENTS_UNB_MP_TRABALHOS_TRAB1_INCLUDE_CONTADOR_LINHA_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
std::pair <int, int> count_linhas (std::string fileString);

/**
 * @brief 
 * 
 * @param file 
 * @return std::pair <int, int> 
 */
std::pair <int, int> le_arquivo_to_string_count (std::filebuf * file);

#endif