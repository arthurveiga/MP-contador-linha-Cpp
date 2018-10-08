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
    SECTION("abre_arquivo: ERRO_stringNula") {
        printf("abre_arquivo: erro, sem nome de arquivo.\n");
        std::filebuf f;
        CHECK(abre_arquivo(&f, "") == -1);
    }
    SECTION("abre_arquivo: ERRO_nomeErradoArquivo") {
        printf("abre_arquivo: erro, string com nome errado de arquivo.\n");
        std::filebuf f;
        std::string s = "sample/helo.cpp";
        CHECK(abre_arquivo(&f, s) == -1);
    }
    SECTION("abre_arquivo: OK") {
        printf("abre_arquivo: OK");
        std::filebuf f;
        std::string s = "sample/hello.cpp";
        CHECK(abre_arquivo(&f, s) == 0);
    }
}

TEST_CASE("le_arquivo", "Testa se o arquivo é lido.") {
    SECTION("le_arquivo: ERRO_bufferArqNaoExiste") {
        printf("le_arquivo: erro, buffer de arquivo não existe");
        CHECK(le_arquivo(NULL).first == -1);
    }
    SECTION("le_arquivo: ERRO_arquivoFechado") {
        printf("le_arquivo: erro, buffer de arquivo não está aberto");
        std::filebuf f;
        abre_arquivo(&f, "");
        CHECK(le_arquivo(&f).first == -1);
    }
    SECTION("le_arquivo: OK") {
        printf("le_arquivo: OK");
        std::filebuf f;
        CHECK(le_arquivo(&f).first == 0);
    }
}
