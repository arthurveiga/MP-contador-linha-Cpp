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

int abre_arquivo(std::filebuf *file, std::string file_name);
int le_linhas_sstream(std::stringstream * fileInputStream);
std::pair <int, int> bufferiza_arquivo_to_sstream(std::filebuf * file); 

#endif