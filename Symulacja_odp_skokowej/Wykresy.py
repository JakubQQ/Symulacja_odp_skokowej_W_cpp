import pandas as pd
import matplotlib.pyplot as plt
dane = pd.read_csv("E:\\Users\\kkuku\\Desktop\\gamba tree\\Symulacja_odp_skokowej\\Symulacja_odp_skokowej\\wyniki.csv", header=None, names=['n','y'])
plt.plot(dane['n'],dane['y'],marker='o',linestyle='-',color='b')
plt.title('Odpowiedz skokowa ukladu dyskretnego')
plt.xlabel('Numer probki (n)')
plt.ylabel('Amplituda y[n]')
plt.show()