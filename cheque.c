#include "cheque.h"
#include <stdlib.h>
#include <stdio.h>

/* retira o primeiro cheque na pool */
link take_cheque(ChequesPool *pool){
  link ch;
  if (pool->head == NULL){  /*se a pool de cheques tiver vazia, return Null*/
    return NULL;
  }
  ch = pool->head;/*apontador para primeiro cheque*/
  pool->head = (pool->head)->next;/* head da lista=2º elemento da lista*/
  return ch;
}

link take_cheque_ref(ChequesPool *pool, long ref){
  link c, t;
  if (pool->head == NULL){
    return NULL;
  }
  if ((pool->head)->item.refc == ref){/* se a referencia que procuramos for do primeiro*/
    t = pool->head;					
    if (pool->head == pool->tail){     /*retiramos o primeiro da lista,e se a lista contiver apenas um cheque,*/
      pool->tail = NULL;				/*o nodulo aponta para null, pois e o ultimo elemento*/
    }
    pool->head = (pool->head)->next;   /*head=2º elemento*/
    return t;
  }
  for(t = pool->head; t!= NULL; t = t->next){ /*percorre o resto da lista de cheques ate encontrar o desejado*/
    c = t->next;
    if (c!=NULL && (c->item).refc == ref){   /* se for o cheque sesejado*/
      t->next = c->next;
      if (c == pool->tail){					/*retira da lista*/
	pool->tail = t;
      }
      return c;
    }
  }
  return NULL;
}

link get_cheque_ref(ChequesPool *pool, long ref){  /*procura o cheque desejado na lista */
  link current;
  current=pool->head;								/* e retorna uma copia do mesmo */
  while ((current->item).refc != ref && current != NULL){
    current = current->next;
  }
  return current;
}

void add_cheque(ChequesPool *pool, cheque c){
  link nova_node;
  nova_node = malloc(sizeof(Node)); /*criaçao do node com o cheque*/
  nova_node->item = c;
  nova_node->next = NULL;
  
  if (pool->head == NULL) {/*se a pool estiver vazia */
    pool->head = nova_node;
    pool->tail = nova_node;
  } else {		/*insere no fim*/
    (pool->tail)->next = nova_node;/*o proximo do actual ultimo chueque, e o novo node*/
    pool->tail = nova_node;			/* altera a tail, para o novo elemento */
  }
}

void delete_pool(ChequesPool *pool){
  delete_pool_aux(pool->head);
  pool->head = NULL;/*"remove" os apontadores para a head e tail*/
  pool->tail = NULL;
}

void delete_pool_aux(link lk){
  if (lk != NULL) {
    if(lk->next != NULL){/*enqunto o nodulo seguinte existir*/
      delete_pool_aux(lk->next);/*chama a funçao para libertar a memoria desse nodulo*/
    }
    free(lk); /*liberta a memoria dos nodulos*/
  }
}