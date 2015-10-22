#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cheque.h"
#include "cliente.h"
ChequesPool ch;
linkCl cls;

void get_string(char str[], int maxlength){
  int i = 0;
  int c = getchar();
  while(c != 32 && c != '\n' && c!=EOF && i<maxlength){ /* ate encontrar espaco, ou a linha mudar */
    str[i] = c;
    i++;
    c = getchar();
  }
  str[i] = '\0'; /* carater final */
}

void kill(){
  /* apaga dados da memoria*/
  delete_pool(&ch);
  delete_arvore(&cls);
}

void sair(){
  stats *s;
  s = malloc(sizeof(stats));
  s->ncl = 0;
  s->nch = 0;
  s->vch = 0;
  get_final_stats(cls, s);
 
  printf("%ld %ld %ld\n", s->ncl, s->nch, s->vch);
  free(s);
}

void info(){ /*informaçao de todos os clientes, se existirem*/
  if (cls == NULL){
    printf("No active clients\n");
    return;
  }
  printInfo_clientes(cls);
}

void add_cheque_stats(cheque c){
  linkCl emi, ben;
  emi = search_ref(cls, c.refe);
  
  if (emi == NULL){
    /* emissor nao existe na estatistica */
    emi = novo_cliente(&cls, c.refe);
  }
  
  ben = search_ref(cls, c.refb);
  
  if (ben == NULL){
    ben = novo_cliente(&cls, c.refb);
  }
    
  ben->item->nchb += 1;
  ben->item->vchb += c.valor;
  emi->item->nche += 1;
  emi->item->vche += c.valor;
}

void rem_cheque_stats(cheque c){
  linkCl emi, ben;
  
  ben = search_ref(cls, c.refb);
  ben->item->nchb--;
  ben->item->vchb -= c.valor;
  if (ben->item->nchb == 0 && ben->item->nche == 0){
    cls = delete_cliente(cls, ben->item->ref);
  }
  
  emi = search_ref(cls, c.refe);
  emi->item->nche--;
  emi->item->vche -= c.valor;
  if (emi->item->nchb == 0 && emi->item->nche == 0){
    cls = delete_cliente(cls, emi->item->ref);
  }
}

void processa_cheque_ref(){
  long ref;
  link node_cheque;
  scanf("%ld", &ref);
  node_cheque = take_cheque_ref(&ch, ref);
  if (node_cheque != NULL){
    rem_cheque_stats(node_cheque->item);
    free(node_cheque);
  } else {
    printf("Cheque %ld does not exist\n", ref);
  }
}

void processa_cheque(){
  link node_cheque;
  node_cheque = take_cheque(&ch);
  if (node_cheque != NULL){
    rem_cheque_stats(node_cheque->item);
    free(node_cheque);
  } else {
    printf("Nothing to process\n");
  }
}

void informacao_cliente(){/*procura cliente por referencia, e devolve no output as suas informaçoes */
  linkCl cn;
  long ref;
  scanf("%ld", &ref);
  cn = search_ref(cls, ref);
  printf("Cliente-info: %ld %d %d %d %d\n", cn->item->ref, cn->item->nche, cn->item->vche, cn->item->nchb, cn->item->vchb);
}

void informacao_cheque(){/*output das caracteristicas do cheque que queremos(referencia no input)*/
  long ref;
  link node_cheque;
  cheque c;
  scanf("%ld", &ref);
  node_cheque = get_cheque_ref(&ch, ref);
  c = node_cheque->item;
  printf("Cheque-info: %ld %d %ld --> %ld\n", c.refc, c.valor, c.refe, c.refb);
}

void adicionar_cheque(){/*cria cheque com as caracteristicas do input*/
  cheque novo_ch;
  scanf("%d %ld %ld %ld", &(novo_ch).valor, &(novo_ch).refe, &(novo_ch).refb, &(novo_ch).refc);
  add_cheque(&ch, novo_ch);/*e adiciona a lista de cheques*/
  add_cheque_stats(novo_ch);
}

int main () {
  char cmd[20];
  ch.head = NULL;
  ch.tail = NULL;
  cls = NULL;
  while(1){ /* le o comando introduzido */
    scanf("%s", cmd);
    if (strcmp(cmd, "cheque") == 0){
      adicionar_cheque();
    }else if (strcmp(cmd, "infocheque") == 0){
      informacao_cheque();
    }else if (strcmp(cmd, "infocliente") == 0){
      informacao_cliente();
    } else if (strcmp(cmd, "processaR") == 0){
      processa_cheque_ref();
    } else if (strcmp(cmd, "processa") == 0){
      processa_cheque();
    } else if (strcmp(cmd, "info") == 0){
      info();
    } else if (strcmp(cmd, "sair") == 0){
      sair();
      kill();
      return EXIT_SUCCESS;
    } 
  }
  return EXIT_FAILURE;
}