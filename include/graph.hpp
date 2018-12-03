/**
 * @brief Cabeçalho para a classe de grafo
 * 
 * @file graph.hpp
 * @author Guilherme Brandt
 * @date 2018-11-27
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>

#include <sparse_matrix.hpp>

/**
 * @brief Classe de grafo genérico direcionado
 * 
 * @tparam T 
 * @tparam Weight Tipo de peso das arestas (padrão = int) 
 */
template <
    class T,
    class Weight = int
> class graph {
private:
    size_t _node_id = 0;

    //! Hash map usado para traduzir os nós em números
    std::unordered_map<T, size_t> _nodes;
    static constexpr size_t max_nodes = decltype(_nodes)::max_size();

    //! Tipo usado para representação dos pesos das arestas
    typedef Weight weight_t;

    //! Matriz de arestas
    sparse_matrix<Weight> _edges;

public:
    /**
     * @brief Construtor
     */
    graph() {}

    /**
     * @brief Construtor de cópia
     * 
     * @param other Grafo a ser copiado
     */
    graph(const graph& other) {
        *this = other;
    }

    /**
     * @brief Operador de cópia
	 * 
	 * @param model Objeto modelo
	 * @return graph& Referência da cópia criada
     */
    graph & operator=(const graph& model) {
        if (this == &model)
			return *this;

		_nodes = model._nodes;
        _edges = model._edges;

		return *this;
    }

    /**
     * @brief Adiciona um nó no grafo
     * 
     * @param value Valor do nó
     */
    void add_node(const T& value) {
        if (_nodes.includes(value))
            throw "Nó repetido";

        _nodes[value] = _node_id++;
    }

    /**
     * @brief Remove um nó do grafo
     * 
     * @param value Valor do nó
     */
    void remove_node(const T& value) {
        if (!_nodes.includes(value))
            throw "Nó não existe";

        int node_id = _nodes[value];
        _nodes.remove(value);

        // Remove arestas ligadas ao nó
        _edges.clear_row(node_id);
        _edges.clear_column(node_id);
    }

    /**
     * @brief Cria uma aresta entre dois vértices do grafo
     * 
     * @param src Vértice de saída
     * @param dest Vértice de entrada
     * @param w Peso da aresta
     */
    void add_edge(const T& src, const T& dest, Weight w) {
        if (!_nodes.includes(src) || !_nodes.includes(dest))
            throw "Aresta entre nós inexistentes";

        _edges[_nodes[src]][_nodes[dest]] = w;
    }

    /**
     * @brief Remove uma aresta entre dois vértices do grafo
     * 
     * @param src 
     * @param dest 
     */
    void remove_edge(const T& src, const T& dest) {
        if (!_nodes.includes(src) || !_nodes.includes(dest))
            throw "Aresta entre nós inexistentes";

        _edges[_nodes[src]][_nodes[dest]] = INFINITY;
    }

    /**
     * @brief Salva o grafo num arquivo .gv
     * 
     * @param file Arquivo de destino
     */
    void gv_save(std::ofstream& file) {
        file << "strict digraph {" << std::endl;

        for (auto it = _nodes.begin(); it != _nodes.end(); it++) {
            file << "node" << it->second << " [label=\"" << it->first << "\"]" << std::endl;

            auto edges = _edges[it->second];

            for (auto it2 = edges.begin(); it2 != edges.end(); it2++)
                file << "node" << it->second << " -> node" << it2->first << " [label=" << it2->second << "]" << std::endl;
        }

        file << "}" << std::endl;
    }
};

#endif // GRAPH_HPP