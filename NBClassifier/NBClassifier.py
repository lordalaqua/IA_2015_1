#                   Classificador Naive Bayes 
#                   Lorenzo Pezzi Dal'Aqua
#                   Inteligência Artificial
#                       Turma U - 2015/1
import csv
from numpy import *

NUM_CLASSES = 10

# Função para calcular o valor da distribuição gaussiana
def gaussian(x,average,std_deviation,variance):
    exponent = -power(x-average,2)/(2*power(std_deviation,2))   
    return (1/((2*pi)*std_deviation))*exp(exponent)

# Execução do classificador:

# Ler arquivo com todos dados
with open('data/usps.csv', 'r') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    lines = []
    for i,line in enumerate(reader):
        lines.append([])
        for elem in line:
            lines[i].append(float(elem))

# Ler arquivo de indices designado  (Nº 18)
with open('indices/18.csv', 'r') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    indices = []
    for line in reader:
        for elem in line:
            indices.append(int(elem))

# Selecionar apenas indices desejados dos dados originais
complete_set = array(lines)[indices]

# Tamanho dos dados de validação
validation_len = int(len(complete_set)/NUM_CLASSES);

avg_confusion_matrix = zeros((NUM_CLASSES,NUM_CLASSES))
avg_matches = 0
avg_precision = zeros((NUM_CLASSES,1))
avg_recall = zeros((NUM_CLASSES,1))
avg_f_measure = zeros((NUM_CLASSES,1))
# Realizar o 10-fold cross-validation
for k in range(NUM_CLASSES):
    # =========================== Divisão dos dados ============================
    validation_start = k*validation_len
    validation_end = validation_start+validation_len
    validation_set = complete_set[validation_start:validation_end]
    dataset = concatenate((complete_set[:validation_start], \
        complete_set[validation_end:]))

    # ============================ Treinamento =================================
    # Calcular média
    average = zeros((NUM_CLASSES,len(dataset[0])-1))
    num_elems = zeros(NUM_CLASSES)

    # Calcular somatórios
    for row in dataset:
        average[row[-1]] += row[:-1]
        num_elems[row[-1]] += 1

    # Dividir por total de elementos
    for i,row in enumerate(average):
        row /= num_elems[i]

    # Calcular variância de cada classe
    variance = zeros((NUM_CLASSES,len(dataset[0])-1))

    # Calcular a soma das diferenças da média ao quadrado
    for row in dataset:
        diff = row[:-1] - average[row[-1]]
        variance[row[-1]] += diff * diff

    # Dividir por total de elementos
    for i,row in enumerate(variance):
        row /= num_elems[i]

    # Calcular o desvio padrão
    std_deviation = sqrt(variance)


    # ===================== Classificação por MAP ==============================
    # 
    confusion_matrix = zeros((NUM_CLASSES,NUM_CLASSES),dtype=int8)
    matches = 0

    # Testa com todos os dados de validação
    for input_index in range(validation_len):
        max_sum = 0
        index = -1
        # Procura o maior valor entre todas classes
        for i in range(NUM_CLASSES):
            likelihood = gaussian(validation_set[input_index][:-1], \
                average[i],std_deviation[i],variance[i])
            # Calcula o somatório dos logaritmos do likelihood 
            # (exclui valores muito próximos de zero do logaritmo)
            s = sum(log(likelihood.clip(min=1e-10)))
            if s > max_sum:
                max_sum = s;
                index = i
        # Popula a matriz de confusão da iteração atual
        confusion_matrix[validation_set[input_index][-1]][index] += 1
        if validation_set[input_index][-1] == index :
            matches += 1

    print(">>>>>>>> Iteration",k,"<<<<<<<<<")
    print(matches,"matches out of ",validation_len, matches/validation_len, "accuracy")
    print(confusion_matrix)
    # Calcula as métricas de precisão e recall para cada classe    
    for i in range(NUM_CLASSES):
        precision_sum = 0
        recall_sum = 0
        for j in range(NUM_CLASSES):
            precision_sum += confusion_matrix[j,i]
            recall_sum += confusion_matrix[i,j]
        precision = confusion_matrix[i,i]/precision_sum
        recall = confusion_matrix[i,i]/recall_sum
        f_measure = 2*recall*precision/(recall+precision)
        # Acumula as métricas para calcular as médias
        avg_precision[i] += precision
        avg_recall[i] += recall
        avg_f_measure += f_measure
        # Exibe as métricas calculadas para cada classe
        print("Class",i,"Precision",precision,"Recall",recall,"F_measure",f_measure)
    # Soma todas matrizes de confusão para calcular a média
    avg_confusion_matrix += confusion_matrix
    avg_matches += matches
# Divide a soma das matrizes pelo número de classes
avg_confusion_matrix /= NUM_CLASSES
avg_matches /= NUM_CLASSES

# Exibe a matriz resultante
print(">>>>>>>> FINAL RESULTS <<<<<<<<<")
print(avg_matches,"matches out of ",validation_len,"in average", matches/validation_len, "accuracy")
print("Average Confusion Matrix")
print(avg_confusion_matrix)
avg_precision = avg_precision / NUM_CLASSES
avg_recall = avg_recall / NUM_CLASSES
avg_f_measure = avg_f_measure / NUM_CLASSES
for i in range(NUM_CLASSES):    
    # Exibe as métricas médias calculadas
    print("Class",i,"Precision",avg_precision[i],"Recall",avg_recall[i],"F_measure",avg_f_measure[i])

