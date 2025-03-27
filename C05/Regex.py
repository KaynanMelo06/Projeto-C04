import re


txt = "Viver é acalentar sonhos e esperanças, fazendo da fé a nossa inspiração maior. É buscar nas pequenas coisas, um grande motivo para ser feliz"

#Exercicio 1
print("-----Exercicio 1------")
a = re.search(".*sonhos.*", txt)

if a:
    print("Encontrou um match")
else:
    print("Nao  encontrou match")
    
#Exercicio 2
#Este teste retorna uma lista contendo cada ocorrencia de "oi" dentro de um texto.
print("-----Exercicio 2-----")
b = re.findall("[a-zA-Zç]*as", txt)

#matches encontrados
print('Matches: ', b)
#quantidade de matches
print('Quantidade:', len(b))

#Exercicio 3
print("-----Exercicio 3-----")
c = re.sub("grande|maior", "surreal", txt)
print(c)

#Exercicio 4
print("-----Exercicio 4-----")
d = re.search("inspiração", txt)
print(d.span())

#Exercicio 5
print("-----Exercicio 5-----")
e = re.findall("[a-zA-Zç]{9,}", txt)
print('Matches 9+: ', e)

#Exercicio 6
print("-----Exercicio 6-----")
f = re.split("[.,]", txt)
print('Split: ', f)
    
#Exercicio 7
print("-----Exercicio 7-----")
g = re.findall("[a-zA-Zç]*[é]", txt)
print("Matches: ", g)

#Exercicio 8
print("-----Exercicio 8-----")
#\s retira os whitespaces
h = re.findall("[a-zA-Zçé]*\s", txt)
#matches encontrados
print('Matches:', h)
#quantidade de matches
print('Quantidade:', len(h))

