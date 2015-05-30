#                   Classificador Naive Bayes 
#                   Lorenzo Pezzi Dal'Aqua
#                   
# 
# 
# 
# 
#
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
    confusion_matrix = zeros((NUM_CLASSES,NUM_CLASSES))
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
        # Computa os matches corretos
        confusion_matrix[validation_set[input_index][-1]][index] += 1
    #print(confusion_matrix)
    avg_confusion_matrix += confusion_matrix

avg_confusion_matrix /= NUM_CLASSES
print(avg_confusion_matrix)    
for i in range(NUM_CLASSES):
    precision_sum = 0
    recall_sum = 0
    for j in range(NUM_CLASSES):
        precision_sum += avg_confusion_matrix[j,i]
        recall_sum +=avg_confusion_matrix[i,j]
    precision = avg_confusion_matrix[i,i]/precision_sum
    recall = avg_confusion_matrix[i,i]/recall_sum
    f_measure = 2*recall*precision/(recall+precision)
    print("Class",i,"Precision",precision,"Recall",recall,"F_measure",f_measure)