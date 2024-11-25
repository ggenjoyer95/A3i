import pandas as pd
import matplotlib.pyplot as plt
file_path = 'rnd.csv'  # можно указать два других файла чтобы получить соответствующие файлы
df = pd.read_csv(file_path)
df.columns = df.columns.str.strip()
print(df.columns)
plt.figure(figsize=(10, 6))
plt.plot(df['Test No.1'], df[''], label='', color='blue', marker='o')
plt.plot(df['Test No.2'], df[''], label='', color='red', marker='x')
plt.title('Время работы алгоритмов сортировки')
plt.xlabel('Размер массива')
plt.ylabel('Время работы (мс)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
