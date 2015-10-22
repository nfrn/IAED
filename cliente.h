typedef struct {
  long ref;
  int nche, vche, nchb, vchb;
} cliente;

typedef struct nodeCl* linkCl;

struct nodeCl {
  cliente *item; 
  int height;
  linkCl l, r;
};

typedef struct {
  long ncl, nch, vch;
} stats;

/* funcoes principais */
void get_final_stats(linkCl, stats*); /* coleta a informacao de todos os clientes (para o print final) */
void printInfo_clientes(linkCl); /* imprime a informacao dos clientes por ordem de ref crescente (info)*/
linkCl delete_cliente(linkCl, long); /* retira o cliente com o dado ref da arvore, e apaga-o da memoria */
linkCl novo_cliente(linkCl*, long); /* adiciona o cliente com o dado ref a arvore e retorna o node adicionado */
linkCl take_cliente(linkCl, long); /* retira o cliente com o dado ref da arvore e retorna o seu node */
linkCl search_ref(linkCl, long); /* retorna o node do cliente com dado ref, se nao existir retorna NULL */
void delete_arvore(linkCl*); /* remove a arvore da memoria */

/* funcoes auxiliares */
void printInfo_cliente(cliente);
int height(linkCl);
linkCl AVLbalance(linkCl);
int Balance(linkCl);
linkCl rotLR(linkCl);
linkCl rotRL(linkCl);
linkCl rotL(linkCl);
linkCl rotR(linkCl);
void delete_arvore_aux(linkCl);
linkCl NEW(cliente*, linkCl, linkCl);
linkCl insert_cliente(linkCl, cliente*);
linkCl max(linkCl h);
linkCl min(linkCl h);