/**
 * @brief 
 * 
 * @file testa_contador_linha.cpp
 * @author Arthur da Veiga Feitoza Borges - 13/0050725
 * @date 2018-09-19
 */

#define CATCH_CONFIG_MAIN  // para não precisar de um main explícito.
#include "catch.hpp"
#include "../include/contador_linha.hpp"

TEST_CASE("abre_arquivo", "Testa se o arquivo abre.") {
    SECTION("abre_arquivo: ERRO_stringVazia") {
        printf("abre_arquivo: erro, sem nome de arquivo.\n");
        std::filebuf f;
        CHECK(abre_arquivo(&f, "") == -1);
    }
    SECTION("abre_arquivo: ERRO_arquivoNaoExiste") {
        printf("abre_arquivo: erro, string com nome de arquivo que não existe.\n");
        std::filebuf f;
        CHECK(abre_arquivo(&f, "sample/naoexiste.cpp") == -1);
    }
    SECTION("abre_arquivo: OK") {
        printf("abre_arquivo: OK\n");
        std::filebuf f;
        CHECK(abre_arquivo(&f, "sample/hello.cpp") == 0);
    }
}

TEST_CASE("count_linhas", "Testa se as linhas do arquivo estão sendo lidas.")  {
    SECTION("count_linhas: OK_stringVazia\n") {
        printf("count_linhas: OK_stringVazia");
        CHECK(count_linhas("").first == 1);
    }
    SECTION("count_linhas: OK_arquivoVazio\n") {
        printf("count_linhas: OK - arquivo vazio\n");
        std::filebuf f;
        abre_arquivo(&f, "sample/vazio.cpp");
        std::stringstream sstr;
        sstr << &f;
        std::string s2(sstr.str());
        CHECK(count_linhas(s2).first == 0);    
        CHECK(count_linhas(s2).second == 1);    
    }
    SECTION("count_linhas: OK_semComentarios\n") {
        printf("count_linhas: OK - arquivo sem comentarios\n");
        std::filebuf f;
        abre_arquivo(&f, "sample/hello.cpp");
        std::stringstream sstr;
        sstr << &f;
        std::string s2(sstr.str());
        CHECK(count_linhas(s2).first == 0);    
        CHECK(count_linhas(s2).second == 7);    
    }
    SECTION("count_linhas: OK_comComentarios\n") {
        printf("count_linhas: OK - arquivo com comentarios\n");
        std::filebuf f;
        abre_arquivo(&f, "sample/hello_comentarios.cpp");
        std::stringstream sstr;
        sstr << &f;
        std::string s2(sstr.str());
        CHECK(count_linhas(s2).first == 0);    
        CHECK(count_linhas(s2).second == 6);    
    }
}

TEST_CASE("le_arquivo_to_string_count", "Testa se o arquivo é transferido para um buffer de string.") {
    SECTION("le_arquivo_to_string_count: ERRO_bufferArqNaoExiste") {
        printf("le_arquivo_to_string_count: erro, buffer de arquivo não existe\n");
        CHECK(le_arquivo_to_string_count(NULL).first == -1);
    }
    SECTION("le_arquivo_to_string_count: ERRO_arquivoFechado") {
        printf("le_arquivo_to_string_count: erro, buffer de arquivo não está aberto\n");
        std::filebuf f;
        abre_arquivo(&f, "");
        CHECK(le_arquivo_to_string_count(&f).first == -1);
    }
    SECTION("le_arquivo_to_string_count: OK") {
        printf("le_arquivo_to_string_count: OK\n");
        std::filebuf f;
        std::string s = "sample/hello.cpp";
        abre_arquivo(&f, s);
        CHECK(le_arquivo_to_string_count(&f).first == 0);
        //TODO CHECK(le_arquivo_to_string_count(&f).first == numero que deu de count);
    }
}

