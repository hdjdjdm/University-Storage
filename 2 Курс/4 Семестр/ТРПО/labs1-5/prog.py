file_name = 'gr.txt'
file = open(file_name, 'r')
f = file.readlines()
massAll = []
massPoint = []
massLast = []
i = 0

for string in f:
    massAll.append(string.strip().split(" "))

file.close()

for lvl in massAll:
    for c in lvl:
        massPoint.append(c)

massPoint = [el.strip() for el in massPoint]

print("Последовательность для графа")
for el in massPoint:
    count = 0
    tel = el.split(',')
    for el2 in massPoint:
        tel2 = el2.split(',')
        if tel2[1] == tel[0]:
            print('"{}" -> "{}"'.format(el, el2))
            count += 1
    if count == 0:
        if el not in massLast:
            massLast.append(el)

print("\nВисячие точки")
for el in massLast:
    print(el)

print('Висячих точек', len(massLast))
print('alpha = ', (len(massPoint) - 1) / len(massLast))
