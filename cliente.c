#include "cliente.h"
#include <stdlib.h>
#include <stdio.h>

/*cria e defina um nodulo da arvore*/
linkCl NEW(cliente *item, linkCl l, linkCl r){
  linkCl li;
  li = (linkCl)malloc(sizeof(struct nodeCl));    
  li->item = item;
  li->l = l;
  li->r = r;
  li->height = 1;
  return li;
}
/*retorna a altura do nodulo na arvore */
int height(linkCl h){ 
  if (h == NULL) return 0; 
  return h->height;
}

linkCl AVLbalance(linkCl h){
  int balanceFactor;
  if (h==NULL) return h;
  
  balanceFactor = Balance(h);
  if(balanceFactor>1){/*se desiquilibrada para o lado esquerdo */
    if (Balance(h->l) > 0) h=rotR(h);/*se o filho da esquerda do h, tiver apenas um filho da esquerda, apenas e necessario rotate right*/
    else h = rotLR(h);		/* se nao, fazemos uma rotaçao dupla, totate left -> rotate right */
  } 
  else if (balanceFactor<-1){/*se desiquilibrada para o lado direto */
    if (Balance(h->r) < 0) h=rotL(h);
    else h =rotRL(h);
  } 
  else {  /*a arvore esta equilibrada, actualiza a height do topo*/
    int height_left = height(h->l);
    int height_right = height(h->r);/*height da cabeça=height maior dos filhos +1*/
    h->height = height_left > height_right ? height_left +1 : height_right +1;
  }
  return h;
}

int Balance(linkCl h){/*return balancefactor do nodulo da arvore*/
  if ( h == NULL ) return 0;
  return height(h->l) - height(h->r);
}

linkCl rotLR(linkCl h){/*rotate left, then rotate right do nodulo da arvore*/
  if (h==NULL) return h;
  h->l = rotL(h->l);
  return rotR(h);
}

linkCl rotRL(linkCl h){/*rotate right, then rotate left do nodulo da arvore*/
  if (h==NULL) return h;
  h->r = rotR(h->r);
  return rotL(h);
}

linkCl rotL(linkCl h){
  int height_left, height_right;
  linkCl x = h->r;
  h->r = x-> l;
  x->l = h;
  /*atualiza a altura nos nodulos envolvidos*/
  height_left = height(h->l);
  height_right = height(h->r);
  h->height = height_left > height_right ? height_left +1 : height_right +1;
  
  height_left = height(x->l);
  height_right = height(x->r);
  x->height = height_left > height_right ? height_left + 1 : height_right +1;
  return x;
}

linkCl rotR(linkCl h){
  int height_left, height_right;
  linkCl x = h->l;
  h->l = x->r;
  x->r = h;
  /*atualiza a altura nos nodulos envolvidos*/
  height_left = height(h->l);
  height_right = height(h->r);
  h->height = height_left > height_right ? height_left+1 : height_right +1;
  
  height_left = height(x->l);
  height_right = height(x->r);
  x->height = height_left > height_right ? height_left+1 : height_right +1;
  
  return x;
}

linkCl insert_cliente(linkCl h, cliente *item){
  if (h == NULL){
    return NEW(item, NULL, NULL);
  }	
  if (item->ref < h->item->ref){/*se a ref do cliente no nodulo for maior, insere na esquerda*/
    h->l = insert_cliente(h->l, item);/*chamada recursiva ao nodulo da esquerda*/
  } else { 						/*se menor, insere o novlo cliente na direita da arvore*/
    h->r = insert_cliente(h->r, item);/*chamada recursiva ao nodulo da direita*/
  }
  h = AVLbalance(h);/*equilibra a arvore*/
  return h;
}

linkCl novo_cliente(linkCl *h, long ref){
  linkCl cref;
  cliente *c; /*cria novo cliente */
  c = malloc(sizeof(cliente));
  c->ref = ref; /*define caracteristicas do cliente*/
  c->vche = 0;
  c->nche = 0;
  c->vchb = 0;
  c->nchb = 0;
  *h = insert_cliente(*h, c);/*adiciona o cliente a arvore,e equilibra a arvore*/
  cref = search_ref(*h, ref);
  return cref;
}

linkCl max(linkCl h){ /*retorna o nodulo do cliente com maior referencia*/
  while(h!=NULL && h->r!=NULL){
    h = h->r;
  }
  return h;
}

linkCl min(linkCl h){/*retorna o nodulo do cliente com menor referencia*/
  while(h!=NULL && h->l!=NULL){
    h = h->l;
  }
  return h;
}

linkCl search_ref(linkCl h, long ref){/*procura na arvore, o nodulo do cliente com determinada referencia*/
  if (h == NULL){
    return NULL;
  }
  if (h->item->ref == ref){/*se for o primeiro elemento*/
    return h;
  }
  if (ref < h->item->ref){/*se a referencia for menor que a do nodulo actual,*/
    return search_ref(h->l, ref);/*continua a procurar nos nodulos seguintes para a esquerda*/
  }
  else {
    return search_ref(h->r, ref);/*se for maior, procura para o lado direito da arvore*/
  }
}

linkCl delete_cliente(linkCl h, long ref){/*apaga o cliente da arvore*/
  linkCl aux;
  cliente *x;
  if (h==NULL) return h;
  else if (ref < h->item->ref) h->l=delete_cliente(h->l, ref);/*procura a posiçao do cliente, se a referencia e menor que o cliente actual, procura na esquerda*/
  else if (ref > h->item->ref) h->r=delete_cliente(h->r, ref);/*senao procura na direita, ate o cliente obtido ser o desejado*/
  else{
    if ( h-> l != NULL && h->r != NULL ) {
      aux = max(h->l);
      {x = h->item; h->item = aux->item; aux->item = x;}
      h->l = delete_cliente(h->l, aux->item->ref);
    } else {
      aux = h;
      if ( h->l == NULL && h->r == NULL ) h=NULL;
      else if (h->l == NULL) h = h->r;
      else h=h->l;
      free(aux->item);
      free(aux);
    }
  }
  h = AVLbalance(h);/*equilibra arvore*/
  return h;
}

void printInfo_clientes(linkCl h){
  if (h == NULL) return;
  printInfo_clientes(h->l);/*continua a fazer output dos clientes da arvora, para o lado esquerdo da arvore*/
  printInfo_cliente(*(h->item));/*output do cliente nesta posicao*/
  printInfo_clientes(h->r);/*e para a direita*/
}

void printInfo_cliente(cliente c){/*output das caracteristicas do cliente*/
  printf("*%ld %d %d %d %d\n", c.ref, c.nche, c.vche, c.nchb, c.vchb);
}

void get_final_stats(linkCl h, stats *c){
  if (h == NULL) return;
  get_final_stats(h->l, c);
  c->nch += h->item->nche;
  c->vch += h->item->vche;
  c->ncl++;
  get_final_stats(h->r, c);
}

void delete_arvore(linkCl *Ac){/*apaga a arvore da memoria*/
  if (*Ac == NULL){
    return;
  } else {
    delete_arvore_aux(*Ac);
    *Ac = NULL;
  }
  
}

void delete_arvore_aux(linkCl link){
  if (link !=NULL){
    delete_arvore_aux(link->l);/*liberta memoria do resto dos nodulos para a esquerda e direita*/
    delete_arvore_aux(link->r);
    free(link->item);
    free(link);
  } 
}

