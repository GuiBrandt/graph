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
> graph {
private:
    //! Hash map usado para traduzir os nós em números
    unordered_map<T, size_t> _nodes;
    static constexpr size_t max_nodes = decltype(_nodes)::max_size();

    size_t _node_id = 0;

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
    graph & operator=(const graph& other) {
        if (this == &model)
			return *this;

		_nodes = other._nodes;
        _edges = other._edges;

		return *this;
    }

    /**
     * @brief Adiciona um nó no grafo
     * 
     * @param value Valor do nó
     */
    void node(const T& value) {
        if (_nodes.includes(value))
            throw "Nó repetido";

        _nodes[value] = _node_id++;
    }

    /**
     * @brief Cria uma aresta entre dois vértices do grafo
     * 
     * @param src Vértice de saída
     * @param dest Vértice de entrada
     * @param w Peso da aresta
     */
    void edge(const T& src, const T& dest, Weight w) {
        if (!_nodes.includes(src) || !_nodes.includes(dest))
            throw "Aresta entre nós inexistentes";

        _edges[_nodes[src]][_nodes[dest]] = w;
    }
};

#endif // GRAPH_HPP