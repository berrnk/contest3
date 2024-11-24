import math
import matplotlib.pyplot as plt
import pandas as pd

exact_value = 0.25 * math.pi + 1.25 * math.asin(0.8) - 1
data_part1 = pd.read_csv('a1_part1.txt', sep=" ", header=None, names=["points", "approximation"])
data_part2 = pd.read_csv('a1_part2.txt', sep=" ", header=None, names=["points", "approximation"])
data = pd.concat([data_part1, data_part2])

data['relative_deviation'] = abs(data['approximation'] - exact_value) / exact_value

plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.plot(data['points'], data['approximation'], label='Приближенная площадь', color='b')
plt.axhline(exact_value, color='r', linestyle='--', label='Точное значение')
plt.xlabel('Число точек')
plt.ylabel('Приближенная площадь')
plt.title('Зависимость приближенной площади от числа точек')
plt.legend()
plt.subplot(1, 2, 2)
plt.plot(data['points'], data['relative_deviation'], label='Относительное отклонение', color='g')
plt.xlabel('Число точек')
plt.ylabel('Относительное отклонение')
plt.title('Зависимость относительного отклонения от числа точек')
plt.legend()
plt.tight_layout()
plt.show()
