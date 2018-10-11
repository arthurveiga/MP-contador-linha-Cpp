/**
 * @file contador_linha.cpp
* @author Arthur da Veiga Feitoza Borges - 13/0050725 (https://github.com/arthurveiga)
 * @brief 
 * @version 0.2.1
 * @date 2018-10-11
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "../include/contador_linha.hpp"

/**
 * @brief abre_arquivo: 
 * 
 * @param file 
 * @param file_name 
 * @return int 
 */
int abre_arquivo(std::filebuf * file, std::string file_name) {
    if (file_name == "") {
        return -1;
    } else {
        if (!file->is_open()) {
            file->std::filebuf::open(file_name, std::fstream::in);
            if (file->is_open()) {
                return 0;
            }
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
std::pair <int, int> count_linhas(std::string fileString) {
    if (fileString == "") {
        return std::make_pair(1, 0);
    }
    int count = 0, line_number = 0;
    STATE estado = init;
    std::stringstream data_stream(fileString);
    std::string line;
    while (std::getline(data_stream, line)) {
        std::stringstream line_stream(line);
        char line_char;
        // análise da linha do código para contagem
        while (line_stream) {
            line_char = line_stream.get();
            switch (estado) {
                case init:
                    if (line.size() == 0)
                        estado = espaco;
                    if (line_char != ' ') {
                        if (line_char != '/') {
                            while (line_stream) {
                                line_char = line_stream.get();
                            }
                        } else {
                            estado = barra;
                        }
                    } else {
                        line.erase(line.find_last_not_of(" \n\r\t")+1);
                        if (line.size() == 0)
                            estado = espaco;
                    }
                    break;
                case espaco:
                    break;
                case barra:
                    if (line_char == '/') {
                        estado = barra_dupla;
                    } else {
                        if (line_char == '*') {
                            estado = barra_asterisco;
                        } else {
                            estado = init;
                        }
                    }
                    break;
                case barra_dupla:
                    if (line.back() == '\\') {
                        estado = barra_invertida;
                    }
                    break;
                case barra_invertida:
                    if (line.back() != '\\') {
                        estado = barra_dupla;
                    }
                    break;
                case barra_asterisco:
                    if (line_stream) {
                        if (line_char == '*') {
                            estado = barra_asterisco_asterisco;
                            break;
                        }
                    }
                    break;
                case barra_asterisco_asterisco:
                    if (line_stream) {
                        if (line_char == '/') {
                            estado = barra_asterisco_asterisco_barra;
                            break;
                        }
                    }
                    break;
                case barra_asterisco_asterisco_barra:
                    if (line_stream)
                        estado = init;
                    line.erase(line.find_last_not_of(" \n\r\t")+1);
                    if (line.size() == 0)
                        estado = espaco;
                    break;
            }
        }
        line_number++;
        // máquina de estado: contará linha ou não?

        switch (estado) {
            case init:
            case barra:
                count++;
                estado = init;
                break;
            case espaco:
            case barra_dupla:
                estado = init;
                break;
        }
    }
    return std::make_pair(0, count);
}

/**
 * @brief 
 * 
 * @param file 
 * @return int 
 */
int fecha_arquivo(std::filebuf *file) {
    if (file == NULL)
        return -1;
    if (file->is_open()) {
        file->close();
        return 0;
    }
    return -1;
}

/**
 * @brief 
 * 
 * @param file 
 * @return std::pair <int, int> 
 */
std::pair <int, int> le_arquivo_to_string_count(std::string file_name) {
    int count = 0;
    std::filebuf file;
    abre_arquivo(&file, file_name);
    if (file.is_open()) {
        std::stringstream fileInput("");
        fileInput << &file;
        std::string fileString(fileInput.str());
        count = count_linhas(fileString).second;
        fecha_arquivo(&file);
        return std::make_pair(0, count);
    }
    return std::make_pair(-1, count);
}
