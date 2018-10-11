/**
 * @file testa_contador_linha.cpp
 * @author Arthur da Veiga Feitoza Borges - 13/0050725 (https://github.com/arthurveiga)
 * @brief 
 * @version 0.2.1
 * @date 2018-10-11
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#define CATCH_CONFIG_MAIN  // para não precisar de um main explícito.
#include "catch.hpp"
#include "../include/contador_linha.hpp"

/**
 * @brief 
 * 
 */
TEST_CASE("abre_arquivo", "Testa se o arquivo abre.") {
    SECTION("abre_arquivo: ERRO_stringVazia") {
        printf("abre_arquivo: erro, sem nome de arquivo.\n");
        std::filebuf f;
        CHECK(abre_arquivo(&f, "") == -1);
    }
    SECTION("abre_arquivo: ERRO_arquivoNaoExiste") {
        printf("abre_arquivo: erro, nome de arquivo não existe.\n");
        std::filebuf f;
        CHECK(abre_arquivo(&f, "sample/naoexiste.cpp") == -1);
    }
    SECTION("abre_arquivo: ERRO_arquivoJaAberto") {
        printf("abre_arquivo: erro, arquivo já aberto.\n");
        std::filebuf f;
        abre_arquivo(&f, "sample/hello.cpp");
        CHECK(abre_arquivo(&f, "sample/hello.cpp") == -1);
    }
    SECTION("abre_arquivo: OK") {
        printf("abre_arquivo: OK\n");
        std::filebuf f;
        CHECK(abre_arquivo(&f, "sample/hello.cpp") == 0);
    }
}

/**
 * @brief 
 * 
 */
TEST_CASE("count_linhas", "Testa se as linhas do arquivo estão sendo lidas.")  {
    SECTION("count_linhas: OK_arquivoVazio\n") {
        printf("count_linhas: OK - arquivo vazio\n");
        std::filebuf f;
        abre_arquivo(&f, "sample/vazio.cpp");
        std::stringstream sstr;
        sstr << &f;
        std::string s2(sstr.str());
        CHECK(count_linhas(s2).first == 1);
        CHECK(count_linhas(s2).second == 0);
    }
    SECTION("count_linhas: OK_semComentarios") {
        printf("count_linhas: OK - arquivo sem comentarios\n");
        std::filebuf f;
        abre_arquivo(&f, "sample/hello.cpp");
        std::stringstream sstr;
        sstr << &f;
        std::string s2(sstr.str());
        CHECK(count_linhas(s2).first == 0);
        CHECK(count_linhas(s2).second == 7);
    }
    SECTION("count_linhas: OK_comComentariosBarraDupla") {
        printf("count_linhas: OK - com comentarios de barra dupla\n");
        std::filebuf f;
        abre_arquivo(&f, "sample/hello_barra_dupla.cpp");
        std::stringstream sstr;
        sstr << &f;
        std::string s2(sstr.str());
        CHECK(count_linhas(s2).first == 0);
        CHECK(count_linhas(s2).second == 8);
    }
    SECTION("count_linhas: OK_comComentariosBarraAsterisco") {
        printf("count_linhas: OK - com comentarios de barra asterisco\n");
        std::filebuf f;
        abre_arquivo(&f, "sample/hello_barra_asterisco.cpp");
        std::stringstream sstr;
        sstr << &f;
        std::string s2(sstr.str());
        CHECK(count_linhas(s2).first == 0);
        CHECK(count_linhas(s2).second == 9);
    }
    SECTION("count_linhas: OK_comComentariosTotal") {
        printf("count_linhas: OK - com comentarios de todos os tipos\n");
        std::filebuf f;
        abre_arquivo(&f, "sample/hello_comentarios.cpp");
        std::stringstream sstr;
        sstr << &f;
        std::string s2(sstr.str());
        CHECK(count_linhas(s2).first == 0);
        CHECK(count_linhas(s2).second == 10);
    }
}

/**
 * @brief 
 * 
 */
TEST_CASE("fecha_arquivo", "Testa se o arquivo fechou") {
    SECTION("fecha_arquivo: ERRO_naoHaFilebuf") {
        printf("fecha_arquivo: erro, não há filebuffer\n");
        CHECK(fecha_arquivo(NULL) == -1);
    }
    SECTION("fecha_arquivo: ERRO_arqNaoExiste") {
        printf("fecha_arquivo: erro, arquivo não existe\n");
        std::filebuf f;
        std::string s = "sample/naoexiste.cpp";
        abre_arquivo(&f, s);
        CHECK(fecha_arquivo(&f) == -1);
    }
    SECTION("fecha_arquivo: OK") {
        printf("fecha_arquivo: OK\n");
        std::filebuf f;
        std::string s = "sample/hello.cpp";
        abre_arquivo(&f, s);
        CHECK(fecha_arquivo(&f) == 0);
    }
}

/**
 * @brief 
 * 
 */
TEST_CASE("le_arquivo_to_string_count", "Junção das 3 funções") {
    SECTION("le_arquivo_to_string_count: ERRO_stringVazia") {
        printf("le_arquivo_to_string_count: erro, string vazia\n");
        CHECK(le_arquivo_to_string_count("").first == -1);
        CHECK(le_arquivo_to_string_count("").second == 0);
    }
    SECTION("le_arquivo_to_string_count: ERRO_arqNaoExiste") {
        printf("le_arquivo_to_string_count: erro, arquivo nao existe\n");
        std::string s = "sample/naoexiste.cpp";
        CHECK(le_arquivo_to_string_count(s).first == -1);
        CHECK(le_arquivo_to_string_count(s).second == 0);
    }
    SECTION("le_arquivo_to_string_count: OK") {
        printf("le_arquivo_to_string_count: OK\n");
        std::string s = "sample/hello_comentarios.cpp";
        CHECK(le_arquivo_to_string_count(s).first == 0);
        CHECK(le_arquivo_to_string_count(s).second == 10);
    }
}
