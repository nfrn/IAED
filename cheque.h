typedef struct {
  long refe, refb, refc;
  int valor;
} cheque;

typedef struct node {
    cheque item;
    struct node *next;
}Node; 

typedef Node *link;

typedef struct {
  link head, tail;
} ChequesPool;

/* funcoes primarias */
link take_cheque(ChequesPool*); /* retira um cheque da fila */
void add_cheque(ChequesPool*, cheque); /* adiciona um cheque a fila */
void delete_pool(ChequesPool*); /* remove a fila da memoria */
link take_cheque_ref(ChequesPool*, long); /* retira o cheque com dado ref da fila e retorna-o */
link get_cheque_ref(ChequesPool*, long); /* retorna o cheque com dado ref da fila */

/* funcoes auxiliares */
void delete_pool_aux(link);