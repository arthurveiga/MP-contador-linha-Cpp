/**
 * @file contador_linha.cpp
 * @author Arthur da Veiga Feitoza Borges - 13/0050725 (https://github.com/arthurveiga/MP-contador-linha-Cpp)
 * @brief 
 * @version 1.0
 * @date 2018-10-11
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "../include/contador_linha.hpp"

/**
 * @brief abre_arquivo: A função abre_arquivo é simples. Ele abre um arquivo válido no buffer para leitura/escrita. No caso usaremos somente para leitura.
 *      Nele checamos se o arquivo existe e se ele já estava aberto. Se um dos dois casos acontece, é retornado -1, indicando que houve falha. 
 *      Assertivas de entrada: std::filebuf * file, std::string file_name
 *      Assertivas de saída: std::filebuf * file, o valor retornado pela função.
 * @param file o ponteiro do buffer no qual o arquivo será aberto.
 * @param file_name o nome do arquivo que será aberto.
 * @return int retorna se o procedimento teve sucesso ou não.
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
 * @brief A função count_linhas é o coração deste projeto. É nele que contamos quantas linhas um programa em C++ tem.
 *      Esta função consiste em três etapas:
 *          1) Organização de fileString para duas stringstreams cascateadas, levando ao nível de char (arquivo -> linha -> char), onde a primeira tem o arquivo completo e a segunda tem uma linha de cada vez. Essa distribuição é feita da seguinte forma: 
 *              fileString (string - arq) -> data_stream (sstream - arq) -> line (string - linha) -> line_stream (sstream - linha) -> line_char (char);
 *          2) Manipulação de line_char para fazer o tratamento das linhas de código. Esta e a próxima etapa andam juntas: elas formam uma máquina de estados eficiente para fazer as devidas classificações das linhas para ver a linha é contada ou não. E;
 *          3) Contagem, tendo como base o estado resultante. A contagem só acontece nos estados init e barra.
 *      Assertivas de entrada: std::string fileString, a enumeração STATE definida no .hpp,
 *      Assertivas de saída: int count, no par retornado pela função.     
 * @param fileString o arquivo completo em forma de string.
 * @return std::pair <int, int> retorna-se um par onde: 
 *      O primeiro elemento serve para ver se o procedimento teve sucesso e;
 *      o segundo elemento é o número de linhas resultantes da contagem de count_linhas.
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
    /*  case init: é o estado inicial da máquina. observam-se as seguintes situações:
        - line_char é '/' -> estado = barra; ("" -> "/")
        - line_char é ' ' -> deleta-se de line as barras de espaço e checa se o seu tamanho é zero. Se sim, estado = espaço; ("" -> " ").
        - o tamanho da line é zero -> estado = espaco;
    */
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
    /*  case espaço: aqui não se faz nada, só na hora da contagem da linha.
    */
                case espaco:
                    break;
    /*  case barra: aqui já temos o estado no qual temos uma barra ("/"). observam-se as seguintes situações:
        - line_char é '/' -> estado = barra_dupla; ("/" -> "//"), que são comentários de única linha.
        - line_char é '*' -> estado = barra_asterisco; ("/" -> "/*"), que são comentários de múltiplas linhas.
        - se não for nenhum dos casos -> estado = init; ("/" -> "")
    */
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
    /*  case barra_dupla: aqui já temos o estado no qual temos duas barras ("//"), que é comentário de única linha. observa-se a seguinte situação:
        - se o último caractere de line é '\' -> estado = barra_invertida; ("//" -> "// \"), que são comentários de única linha adicionado de uma linha extra.
        - se não acontece a situação acima, o estado é mantido.
    */
                case barra_dupla:
                    if (line.back() == '\\') {
                        estado = barra_invertida;
                    }
                    break;
    /*  case barra_invertida: aqui já temos o estado no qual temos duas barras e uma outra invertida ("// \"), que são comentários de única linha adicionado de uma linha extra. observa-se as seguintes situações:
        - se o último caractere de line não é '\' -> estado = barra_dupla; ("// \" -> "//"), que são comentários de única linha.
        - se não acontece a situação acima, o estado é mantido.
    */
                case barra_invertida:
                    if (line.back() != '\\') {
                        estado = barra_dupla;
                    }
                    break;
    //  case barra_asterisco: aqui já temos o estado
    //      no qual temos uma barra e um asterisco ("/*"),
    //      que é comentário de múltiplas linhas.
    //      observa-se a seguinte situação:
    //  - se ainda há elementos em line_stream
    //      E line_char é '*' -> estado = barra_asterisco_asterisco;
    //      ("/*" -> "/**"), que ainda são comentários de múltiplas linhas.
    //  - se não acontece a situação acima, o estado é mantido.
    //
                case barra_asterisco:
                    if (line_stream) {
                        if (line_char == '*') {
                            estado = barra_asterisco_asterisco;
                            break;
                        }
                    }
                    break;
    //  case barra_asterisco_asterisco:
    //      aqui já temos o estado no qual
    //      temos uma barra e dois asteriscos ("/*"),
    //      que é comentário de múltiplas linhas.
    //      Observa-se a seguinte situação:
    //  - se ainda há elementos em line_stream
    //      E line_char é '/' ->
    //      estado = barra_asterisco_asterisco_barra;
    //      ("/**" -> "/**/"), que é quando o comentário
    //      de múltiplas linhas é fechado.
    //      O caso a seguir é uma situação interessante.
    //  - se não acontece a situação acima,
    //      o estado é mantido.
    //
                case barra_asterisco_asterisco:
                    if (line_stream) {
                        if (line_char == '/') {
                            estado = barra_asterisco_asterisco_barra;
                            break;
                        }
                    }
                    break;
    // case barra_asterisco_asterisco_barra:
    //      aqui fechamos o comentário de
    //      múltiplas linhas ("/**/").
    //      Mas é importante observar que:
    // - se ainda há elementos em line_stream,
    //      estado = init; ("/**/" -> "").
    //      Isso faz com que a máquina de estados resete.
    // - mas, se deleta-se de line as barras de espaço e,
    //      se o seu tamanho é zero é verdadeiro,
    //      estado = espaco; ("/**/" -> " ")
    //
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
            /* casos de init e barra, conta mais uma linha e define estado = init;*/
            case init:
            case barra:
                count++;
                estado = init;
                break;
            /* casos de espaco e barra_dupla, define estado = init somente;*/
            case espaco:
            case barra_dupla:
                estado = init;
                break;
        }
    }
    return std::make_pair(0, count);
}

/**
 * @brief A função fecha_arquivo é simples. Ele fecha o buffer no qual está aberto o arquivo para leitura/escrita.
 *      Assertivas de entrada: std::filebuf * file
 *      Assertivas de saída: std::filebuf * file, o valor retornado pela função.
 * 
 * @param file é o buffer de arquivo que vamos fechar.
 * @return int retorna se o procedimento teve sucesso ou não.
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
 * @brief A função le_arquivo_string_count é a função que o cliente usará. 
 *      Ele faz todo o procedimento de abertura do arquivo, contagem das linhas e fechamento do mesmo.
 *      Assertivas de entrada: std::string file_name, std::filebuf file.
 *      Assertivas de saída: somente o std::make_pair(check, count).
 * 
 * @param file_name é o nome do arquivo que se quer que conte as linhas, desconsiderando comentários e espaços. 
 * @return std::pair <int, int> retorna-se um par onde: 
 *      O primeiro elemento serve para ver se o procedimento teve sucesso e;
 *      o segundo elemento é o número de linhas resultantes da contagem de count_linhas.
 */
std::pair <int, int> le_arquivo_to_string_count(std::string file_name) {
    int count = 0, check = -1;
    if (file_name == "")
        return std::make_pair(-1, count);
    std::filebuf file;
    check = abre_arquivo(&file, file_name);
    if (check == 0) {
        std::stringstream fileInput("");
        fileInput << &file;
        std::string fileString(fileInput.str());
        count = count_linhas(fileString).second;
        check = fecha_arquivo(&file);
        if (check == 0) {
            return std::make_pair(0, count);
        }
        return std::make_pair(-1, count);  // houve erro em fecha_arquivo
    }
    return std::make_pair(-1, count);  // houve erro em abre_arquivo
}
