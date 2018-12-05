#include <algorithm>
#include <iostream>

#define _GLIBCXX_USE_C99 1
#include <string>

#include <regex>

#include <graph.hpp>

using namespace std;
using namespace regex_constants;

static const regex VERTEX(R"(^\s*(?:v|vx|vertex)\s*(\w+)\s*$)", icase | optimize);
static const regex REMOVE_VERTEX(R"(^\s*(?:r|remove)\s*(\w+)\s*$)", icase | optimize);
static const regex REMOVE_EDGE(R"(^\s*(?:r|remove)\s*(\w+)\s*->\s*(\w+)\s*$)", icase | optimize);
static const regex EDGE(R"(^\s*(?:e|edge)\s*(\w+)\s*->\s*(\w+)\s+(\d+)\s*$)", icase | optimize);
static const regex SAVEGV(R"(^\s*(?:g|graphviz)\s+([^\\\?%\*]+)\s*$)", icase | optimize);
static const regex QUIT(R"(^\s*(?:q|quit|exit)\s*$)", icase | optimize);

/**
 * @brief Ponto de entrada
 * 
 * @param argc Número de argumentos da linha de comando
 * @param argv Valores dos argumentos da linha de comando
 * @return int Código de retorno
 */
int main(int argc, char** argv) {
    string line;
    smatch m;

    graph<string> g;

    // Cabeçalho
    cout << "Interactive Graph" << endl;
    cout << endl;

    cout << "v|vx|vertex x          : Create vertex X" << endl;
    cout << "r|remove x             : Remove vertex X" << endl;
    cout << "r|remove x->y          : Remove edge from X to Y" << endl;
    cout << "e|edge x->y w          : Create edge from X to Y with weight W" << endl;
    cout << "g|graphviz <filename>  : Save Graphviz model to file" << endl;
    cout << "q|quit|exit            : Quit" << endl;
    cout << endl;

    cout << "Have fun!" << endl;
    cout << endl;

    for (;;) {

        cout << "graph> ";
        getline(cin, line);

        // Encerra o programa
        if (regex_match(line, QUIT)) {
            break;

        // Define o valor de uma posição na matriz
        } else if (regex_search(line, m, VERTEX)) {
            try {
                g.add_node(m[1]);
            } catch (const char* msg) {
                cerr << "Err: " << msg << endl;
            }
            
        // Define o valor de uma posição na matriz
        } else if (regex_search(line, m, REMOVE_VERTEX)) {
            try {
                g.remove_node(m[1]);
            } catch (const char* msg) {
                cerr << "Err: " << msg << endl;
            }

        // Define o valor de uma posição na matriz
        } else if (regex_search(line, m, REMOVE_EDGE)) {
            try {
                g.remove_edge(m[1], m[2]);
            } catch (const char* msg) {
                cerr << "Err: " << msg << endl;
            }

        // Escreve o valor de uma posição da matriz na tela
        } else if (regex_search(line, m, EDGE)) {
            try {
                int w = std::stoi(m[3]);
                g.add_edge(m[1], m[2], w);
            } catch (const char* msg) {
                cerr << "Err: " << msg << endl;
            }

        // Salva a matriz como modelo do graphviz num arquivo
        } else if (regex_search(line, m, SAVEGV)) {
            try {
                ofstream f(m[1]);
                g.gv_save(f);
                f.close();
            } catch (const char* msg) {
                cerr << "Err: " << msg << endl;
            }

        // Comando inválido
        } else {
            cerr << "Err: Invalid command" << endl;
            continue;
        }
    }

    return 0;
}