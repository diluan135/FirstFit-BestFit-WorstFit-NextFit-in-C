#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX_STRING_SIZE 20

struct FirstFitNode {
    int process_id;             // Identifica��o do processo (0 para partes vazias)
    int position;               // N�mero de identifica��o do espa�o na mem�ria
    struct FirstFitNode* next;  // Ponteiro para o pr�ximo n� do mesmo tipo
};

struct BestFitNode {
    int process_id;             // Identifica��o do processo (0 para partes vazias)
    int position;               // N�mero de identifica��o do espa�o na mem�ria
    struct BestFitNode* next;   // Ponteiro para o pr�ximo n� do mesmo tipo
};

struct WorstFitNode {
    int process_id;             // Identifica��o do processo (0 para partes vazias)
    int position;               // N�mero de identifica��o do espa�o na mem�ria
    struct WorstFitNode* next;  // Ponteiro para o pr�ximo n� do mesmo tipo
};

struct CircularFitNode {
    int process_id;             // Identifica��o do processo (0 para partes vazias)
    int position;               // N�mero de identifica��o do espa�o na mem�ria
    struct CircularFitNode* next;  // Ponteiro para o pr�ximo n� do mesmo tipo
};

struct FirstFitNode* createFirstFitNode(int process_id, int position);
struct BestFitNode* createBestFitNode(int process_id, int position);
struct WorstFitNode* createWorstFitNode(int process_id, int position);
struct CircularFitNode* createCircularFitNode(int process_id, int position);

struct FirstFitNode* createFirstFitNode(int process_id, int position) {
    struct FirstFitNode* newNode = (struct FirstFitNode*)malloc(sizeof(struct FirstFitNode));
    newNode->process_id = process_id;
    newNode->position = position;
    newNode->next = NULL;
    return newNode;
}

struct BestFitNode* createBestFitNode(int process_id, int position) {
    struct BestFitNode* newNode = (struct BestFitNode*)malloc(sizeof(struct BestFitNode));
    newNode->process_id = process_id;
    newNode->position = position;
    newNode->next = NULL;
    return newNode;
}

struct WorstFitNode* createWorstFitNode(int process_id, int position) {
    struct WorstFitNode* newNode = (struct WorstFitNode*)malloc(sizeof(struct WorstFitNode));
    newNode->process_id = process_id;
    newNode->position = position;
    newNode->next = NULL;
    return newNode;
}

struct CircularFitNode* createCircularFitNode(int process_id, int position) {
    struct CircularFitNode* newNode = (struct CircularFitNode*)malloc(sizeof(struct CircularFitNode));
    newNode->process_id = process_id;
    newNode->position = position;
    newNode->next = NULL;
    return newNode;
}

void createMemory(struct FirstFitNode** firstFitMemory, struct BestFitNode** bestFitMemory,
                  struct WorstFitNode** worstFitMemory, struct CircularFitNode** circularFitMemory, int size) {
    struct FirstFitNode* firstFitHead = NULL;
    struct BestFitNode* bestFitHead = NULL;
    struct WorstFitNode* worstFitHead = NULL;
    struct CircularFitNode* circularFitHead = NULL;

    struct FirstFitNode* firstFitCurrent = NULL;
    struct BestFitNode* bestFitCurrent = NULL;
    struct WorstFitNode* worstFitCurrent = NULL;
    struct CircularFitNode* circularFitCurrent = NULL;

    for (int i = 1; i <= size; i++) {
        // Criar n�s para cada m�todo de aloca��o
        if (i == 1) {
            firstFitHead = createFirstFitNode(0, i);
            bestFitHead = createBestFitNode(0, i);
            worstFitHead = createWorstFitNode(0, i);
            circularFitHead = createCircularFitNode(0, i);

            firstFitCurrent = firstFitHead;
            bestFitCurrent = bestFitHead;
            worstFitCurrent = worstFitHead;
            circularFitCurrent = circularFitHead;
        } else {
            firstFitCurrent->next = createFirstFitNode(0, i);
            bestFitCurrent->next = createBestFitNode(0, i);
            worstFitCurrent->next = createWorstFitNode(0, i);
            circularFitCurrent->next = createCircularFitNode(0, i);

            firstFitCurrent = firstFitCurrent->next;
            bestFitCurrent = bestFitCurrent->next;
            worstFitCurrent = worstFitCurrent->next;
            circularFitCurrent = circularFitCurrent->next;
        }
    }

    *firstFitMemory = firstFitHead;
    *bestFitMemory = bestFitHead;
    *worstFitMemory = worstFitHead;
    *circularFitMemory = circularFitHead;
}



				// inserir em mem�rias

void insertFirstFit(struct FirstFitNode* firstFitMemory, int inserir_processo, int num_processo) {
    struct FirstFitNode* current = firstFitMemory;
    int count = 0;
    struct FirstFitNode* start = NULL;  // Ponto de in�cio para alocar o processo

    while (current != NULL) {
        if (current->process_id == 0) {
            if (count == 0) {
                start = current;  // Guarda o ponto de in�cio para alocar o processo
            }
            count++;
            if (count == inserir_processo) {
                // Alocar o processo nos n�s dispon�veis
                struct FirstFitNode* currentNode = start;
                for (int i = 0; i < inserir_processo; i++) {
                    currentNode->process_id = num_processo;
                    currentNode = currentNode->next;
                }
                printf("Processo %d alocado com sucesso em FirstFit.\n", num_processo);
                return;
            }
        } else {
            count = 0;
        }
        current = current->next;
    }

    printf("Espa�o insuficiente para alocar o processo em FirstFit %d.\n", num_processo);
}

void insertBestFit(struct BestFitNode* bestFitMemory, int inserir_processo, int num_processo) {
    struct BestFitNode* current = bestFitMemory;
    struct BestFitNode* bestFitStart = NULL;  // In�cio do melhor espa�o para inserir o processo
    int bestFitSize = -1;  // Tamanho do melhor espa�o encontrado

    while (current != NULL) {
        if (current->process_id == 0) {
            int holeSize = 0;  // Tamanho do buraco atual
            struct BestFitNode* holeStart = current;  // In�cio do buraco atual
            
            // Encontrar o tamanho do buraco atual
            while (current != NULL && current->process_id == 0) {
                holeSize++;
                current = current->next;
            }
            
            // Verificar se o tamanho do buraco � suficiente para o processo
            if (holeSize >= inserir_processo) {
                // Se o tamanho for exato, inserir o processo aqui e retornar
                if (holeSize == inserir_processo) {
                    struct BestFitNode* currentNode = holeStart;
                    for (int i = 0; i < inserir_processo; i++) {
                        currentNode->process_id = num_processo;
                        currentNode = currentNode->next;
                    }
                    printf("Processo %d alocado com sucesso em BestFit.\n", num_processo);
                    return;
                }
                
                // Se o tamanho for melhor que o atual, atualizar os valores de melhor ajuste
                if (bestFitSize == -1 || holeSize < bestFitSize) {
                    bestFitStart = holeStart;
                    bestFitSize = holeSize;
                }
            }
        } else {
            current = current->next;
        }
    }

    // Inserir o processo no melhor espa�o encontrado (se existir)
    if (bestFitStart != NULL) {
        struct BestFitNode* currentNode = bestFitStart;
        for (int i = 0; i < inserir_processo; i++) {
            currentNode->process_id = num_processo;
            currentNode = currentNode->next;
        }
        printf("Processo %d alocado com sucesso em BestFit.\n", num_processo);
    } else {
        printf("Espa�o insuficiente para alocar o processo %d em BestFit.\n", num_processo);
    }
}

void insertWorstFit(struct WorstFitNode* worstFitMemory, int inserir_processo, int num_processo) {
    struct WorstFitNode* current = worstFitMemory;
    struct WorstFitNode* worstFitStart = NULL;  // In�cio do maior espa�o para inserir o processo
    int worstFitSize = -1;  // Tamanho do maior espa�o encontrado

    while (current != NULL) {
        if (current->process_id == 0) {
            int holeSize = 0;  // Tamanho do buraco atual
            struct WorstFitNode* holeStart = current;  // In�cio do buraco atual
            
            // Encontrar o tamanho do buraco atual
            while (current != NULL && current->process_id == 0) {
                holeSize++;
                current = current->next;
            }
            
            // Verificar se o tamanho do buraco � suficiente para o processo
            if (holeSize >= inserir_processo) {
    // Se o tamanho for maior que o atual maior buraco, atualizar os valores de pior ajuste
    if (holeSize > worstFitSize) {
        worstFitStart = holeStart;
        worstFitSize = holeSize;
    }
}
        } else {
            current = current->next;
        }
    }

    // Inserir o processo no maior espa�o encontrado (se existir)
    if (worstFitStart != NULL) {
        struct WorstFitNode* currentNode = worstFitStart;
        for (int i = 0; i < inserir_processo; i++) {
            currentNode->process_id = num_processo;
            currentNode = currentNode->next;
        }
        printf("Processo %d alocado com sucesso em WorstFit.\n", num_processo);
    } else {
        printf("Espa�o insuficiente para alocar o processo %d em WorstFit.\n", num_processo);
    }
}

int last_position = 1;


void insertCircularFit(struct CircularFitNode* circularFitMemory, int inserir_processo, int num_processo, int tam_memoria) {
    struct CircularFitNode* current = circularFitMemory;
    struct CircularFitNode* start = NULL;  // Ponto de in�cio para alocar o processo
	struct CircularFitNode* primeiro = circularFitMemory;	

    // Encontra o n� onde foi feita a �ltima inser��o
    while (current->position != last_position) {
        current = current->next;
    }

    start = current;  // Define o ponto de in�cio para alocar o processo
	
    int count = 0;  // Contador para acompanhar o espa�o dispon�vel
    int found = 0;  // Indica se foi encontrado um buraco adequado para alocar o processo

    while (1) {
        if (current->process_id == 0) {
            if (count == 0) {
                start = current;  // Atualiza o ponto de in�cio para o novo buraco encontrado
            }
            count++;

            if (count >= inserir_processo) {
                // Alocar o processo nos n�s dispon�veis
                struct CircularFitNode* currentNode = start;
                for (int i = 0; i < inserir_processo; i++) {
                    currentNode->process_id = num_processo;
                    currentNode = currentNode->next;
                }
                last_position = (start->position + inserir_processo) % tam_memoria;  // Atualiza a �ltima posi��o alocada
                found = 1;  // Indica que o processo foi alocado
                printf("Processo %d alocado com sucesso em CircularFit.\n", num_processo);
                break;  // Encerra o loop ao alocar o processo
            }
        } else {
            count = 0;  // Reseta o contador se encontrar um n� ocupado
        }
		
		if(current->position == tam_memoria){
			current->next = primeiro;
		}
        current = current->next;
		
        // Se retornou ao n� de in�cio, n�o h� espa�o dispon�vel
        if (current->position == last_position) {
            printf("Espa�o insuficiente para alocar o processo %d em CircularFit.\n", num_processo);
            break;
        }
    }
}

				// apagar mem�rias
				
void replaceProcessID(struct FirstFitNode* firstFitMemory, int num_processo) {
    struct FirstFitNode* current = firstFitMemory;
    int replaced = 0;

    while (current != NULL) {
        if (current->process_id == num_processo) {
            current->process_id = 0;
            replaced = 1;
        }
        current = current->next;
    }

    if (replaced) {
        printf("Processo %d removido com sucesso em firstFit\n", num_processo);
    } else {
        printf("Nenhum processo com o n�mero %d encontrado em firstFit.\n", num_processo);
    }
}

void replaceProcessIDBestFit(struct BestFitNode* bestFitMemory, int num_processo) {
    struct BestFitNode* current = bestFitMemory;
    int replaced = 0;

    while (current != NULL) {
        if (current->process_id == num_processo) {
            current->process_id = 0;
            replaced = 1;
        }
        current = current->next;
    }

    if (replaced) {
        printf("Processo %d removido com sucesso em bestFit\n", num_processo);
    } else {
        printf("Nenhum processo com o n�mero %d encontrado em bestFit\n", num_processo);
    }
}

void replaceProcessIDWorstFit(struct WorstFitNode* worstFitMemory, int num_processo) {
    struct WorstFitNode* current = worstFitMemory;
    int replaced = 0;

    while (current != NULL) {
        if (current->process_id == num_processo) {
            current->process_id = 0;
            replaced = 1;
        }
        current = current->next;
    }

    if (replaced) {
        printf("Processo %d removido com sucesso em worstFit\n", num_processo);
    } else {
        printf("Nenhum processo com o n�mero %d encontrado em worstFit\n", num_processo);
    }
}

void replaceProcessIDCircularFit(struct CircularFitNode* circularFitMemory, int num_processo, int tam_memoria) {
    struct CircularFitNode* current = circularFitMemory;
    int replaced = 0, i;

     for(i=0; i<tam_memoria; i++){
        if (current->process_id == num_processo) {
            current->process_id = 0;
            replaced = 1;
        }
        current = current->next;
    }

    if (replaced) {
        printf("Processo %d removido com sucesso em circularFit\n", num_processo);
    } else {
        printf("Nenhum processo com o n�mero %d encontrado em circularFit\n", num_processo);
    }
}
	
int main () {
	
	setlocale(LC_ALL, "Portuguese");
	
	printf("\t\tBEM VINDO ARION\n");
	int i, escolhas, escolha_memoria=0, tam_memoria, tipo_memoria=0, num_processo=0, inserir_processo, apagar_processo;
	char bytes[MAX_STRING_SIZE];
	
	struct FirstFitNode* firstFitMemory = NULL;
    struct BestFitNode* bestFitMemory = NULL;
    struct WorstFitNode* worstFitMemory = NULL;
    struct CircularFitNode* circularFitMemory = NULL;
    
    if(escolha_memoria == 0){
					printf("\n\nPrimeiro escolha o tamanho total das suas mem�rias: ");
					scanf("%i", &tam_memoria);
					while(tipo_memoria != 1 && tipo_memoria != 2 && tipo_memoria != 3 && tipo_memoria != 4){
						printf("\nEla vai ser em:\n1-bytes\n2-kilobytes\n3-megabytes\n4-gigabytes?\nDigite o n�mero equivalente ao tipo da mem�ria: ");
						scanf("%i", &tipo_memoria);
						if(tipo_memoria != 1 && tipo_memoria != 2 && tipo_memoria != 3 && tipo_memoria != 4){
							printf("Por favor, digite um valor entre 1 e 4 para prosseguir\n");
						}
					}
					switch (tipo_memoria){
						case 1:{
							strcpy(bytes, "bytes");
							break;
						}
						case 2:{
							strcpy(bytes, "kilobytes");
							break;
						}
						case 3:{
							strcpy(bytes, "megabytes");
							break;
						}
						case 4:{
							strcpy(bytes, "gigabytes");
							break;
						}
					}
					createMemory(&firstFitMemory, &bestFitMemory, &worstFitMemory, &circularFitMemory, tam_memoria);
					printf("Suas mem�rias possuem %d %s", tam_memoria, bytes);
					 struct FirstFitNode* current = firstFitMemory;
					 struct WorstFitNode* currentWorst = worstFitMemory;
					 struct BestFitNode* currentBest = bestFitMemory;
					struct CircularFitNode* currentCircular = circularFitMemory;
					escolha_memoria = 1;
				}
	
	
	
	while(escolhas != 4){
	printf("\n\nEscolha sua op��o:\n");
	printf("1-Inserir Processo em mem�ria\n2-Remover processo em mem�ria\n3-Listar estado das mem�rias\n4-Finalizar aplica��o\n");
	scanf("%i", &escolhas);
		switch (escolhas){
			case 1:{
				num_processo++;
				printf("Qual o tamanho do processo inserido?\n");
				scanf("%i", &inserir_processo);
				insertFirstFit(firstFitMemory, inserir_processo, num_processo);
				insertBestFit(bestFitMemory, inserir_processo, num_processo);
				insertWorstFit(worstFitMemory, inserir_processo, num_processo);
				insertCircularFit(circularFitMemory, inserir_processo, num_processo, tam_memoria);
				
				break;
			}
			
			
			case 2:{
				printf("Digite o n�mero identificador do processo que deseja remover: ");
		        scanf("%d", &apagar_processo);
		         replaceProcessID(firstFitMemory, apagar_processo);
		         replaceProcessIDBestFit(bestFitMemory, apagar_processo);
		         replaceProcessIDWorstFit(worstFitMemory, apagar_processo);
		        replaceProcessIDCircularFit(circularFitMemory, apagar_processo, tam_memoria);
				break;
			}
			
			
			case 3:{
				struct FirstFitNode* current = firstFitMemory;
				struct WorstFitNode* currentWorst = worstFitMemory;
				struct BestFitNode* currentBest = bestFitMemory;
				struct CircularFitNode* currentCircular = circularFitMemory;
				printf("Cada mem�ria possui %d %s.\n", tam_memoria, bytes);
				while (current != NULL) {
		        printf("%d ", current->process_id);
		        current = current->next;
		    	}
		    	printf(" - FirstFit\n");
		    	while (currentBest != NULL) {
		        printf("%d ", currentBest->process_id);
		        currentBest = currentBest->next;
		    	}
		    	printf(" - BestFit\n");		    	
		    	while (currentWorst != NULL) {
		        printf("%d ", currentWorst->process_id);
		        currentWorst = currentWorst->next;
		    	}
		    	printf(" - WorstFit\n");
		    	for(i=0; i<tam_memoria; i++) {
		    	printf("%d ", currentCircular->process_id);
		    	currentCircular = currentCircular->next;
				}
				printf(" - CircularFit\n");
				break;
			}
			
			
			case 4:{
				
				break;
			}
			default :{
				printf("Opcao invalida!");
				break;
			}
			}
		}
	
	

	
	return 0;
}
