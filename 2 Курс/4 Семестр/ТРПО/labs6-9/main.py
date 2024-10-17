import numpy as np
import matplotlib.pyplot as plt

x = np.array([1, 2, 3, 4, 5, 6, 7])
y = np.array([4, 4, 3, 3, 2, 1, 0])
massDiscrepancy = []
A = np.vstack([x, np.ones(len(x))]).T
m, c = np.linalg.lstsq(A, y, rcond=None)[0]
for i in range(7):
    massDiscrepancy.append(y[i] - (m * x[i] + c))
md = np.array(massDiscrepancy)
# print('A=',A)
plt.plot(x, y, 'o', label='Данные', markersize=10)
plt.plot(x, m * x + c, 'r', label='Аппроксимация')
plt.plot(x,md,'b',label='Невязки')
plt.plot(x,np.square(massDiscrepancy),'o',label='Квадраты невязок')
plt.legend()
plt.show()

sum = 0
X = np.array([1, 2, 3, 4, 5, 6, 7])
Y = np.array([4, 4, 3, 3, 2, 1, 0])
coefficients = np.polyfit(X, Y, 1)
a, b = coefficients
new_X = np.array([1, 2, 3, 4, 5, 6, 7])
predicted_Y = a * new_X + b
print('a=', a, ' b=', b, '\n')
print('Апрокс У=')
for each in predicted_Y:
    print(each)
print('Невязки=')
for each in massDiscrepancy:
    sum += each
    print(each)
print('Невязки(квадрат)=')
for each in massDiscrepancy:
    print(each * each)

print('Сумма невязок=', sum)

