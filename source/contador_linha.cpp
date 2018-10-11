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
    if (fileString == "") {
        return std::make_pair(1, 0);    
    }
    int count = 0, line_number = 0;
    STATE estado = init;
    std::stringstream data_stream(fileString);
    std::string line;
    while (std::getline(data_stream, line)) {  
        //std::cout << "\t LINE: " << line << "\n"; // ---------------      
        std::stringstream line_stream(line);
        char line_char;
        // análise da linha do código para contagem
        while (line_stream) {
            line_char = line_stream.get();
            switch(estado){
                case init:
                    if (line.size() == 0) 
                        estado = espaco;
                    if (line_char != ' ') {
                        if (line_char != '/') {
                            while (line_stream){
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
                        // if (line_char == '*') {
                        //     estado = barra_asterisco; //TODO
                        // } else {
                        //     estado = init;
                        // }
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
            }
        }
        line_number++;
        //std::cout << "\t ----> line: " << line_number << ", state: " << estado << "\n"; // ---------------
        // máquina de estado: contará linha ou não?

        switch(estado){
            case init: 
            case barra:
                count++;
                estado = init;
                break;
            case espaco:
            case barra_dupla:
            case barra_asterisco_asterisco_barra:
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
